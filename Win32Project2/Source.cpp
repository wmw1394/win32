#include <windows.h>  
 
using namespace std;

#define IDC_OK_BUTTON 101
#define IDC_CANCEL_BUTTON 102
#define RADIO_BUTTON1 103
#define OPTION_SIZE 10
#pragma comment(lib, "comctl32.lib")

class Option {

public:
	LPCTSTR OptDesc;
	INT NextQn;
	Option(LPCTSTR desc, INT qn): OptDesc(desc), NextQn(qn) {}
	Option(): OptDesc(TEXT("")), NextQn(0) {}
};

class Question {

public:
	LPCTSTR qnDesc;
	INT Index;
	INT NumOfOptions;
	INT PrevQn;
	Option options[OPTION_SIZE];

	Question() : qnDesc(TEXT("")), Index(0), NumOfOptions(0), PrevQn(0) {}
	Question(LPCTSTR desc, INT idx, INT numOpt, INT prev) : qnDesc(desc), Index(idx), NumOfOptions(numOpt), PrevQn(prev) {}
	void addOption(Option opt, INT idx) {
		if (idx < OPTION_SIZE)
			options[idx] = opt;
	}
};

class frame_window {
private:
	LPWSTR window_class_name;
	HINSTANCE instance_handle;
	HCURSOR cursor_arrow;
	HWND window_handle;
	HWND text_handle_1;
	HWND okbutton_handle;
	HWND backbutton_handle;
	RECT client_rectangle;
	int pressed;
	int count = 0;
	int currQn = 0;
	//number of questions
	int numQns = 3;
	Question* Qns;
	HWND handlers[10];

	//place to set questions
	void setQns() {
		Qns = new Question[numQns];

		Option opt01 = Option(TEXT("Good"), 1);
		Option opt02 = Option(TEXT("So so"), 2);
		Option opt03 = Option(TEXT("Bad"), 2);
		Question qn0 = Question(TEXT("How are you"), 0, 3, -1);
		qn0.addOption(opt01, 0);
		qn0.addOption(opt02, 1);
		qn0.addOption(opt03, 2);
		Qns[0] = qn0;


		Option opt11 = Option(TEXT("Yes"), 1);
		Option opt12 = Option(TEXT("No"), 2);
		Question qn1 = Question(TEXT("Are you happy?"), 0, 2, 1);
		qn1.addOption(opt11, 0);
		qn1.addOption(opt12, 1);
		Qns[1] = qn1;

		Option opt21 = Option(TEXT("Yes"), 1);
		Option opt22 = Option(TEXT("No"), 2);
		Question qn2 = Question(TEXT("Do you like?"), 0, 2, 1);
		qn2.addOption(opt21, 0);
		qn2.addOption(opt22, 1);
		Qns[2] = qn2;
	}

	
public:
	frame_window(LPWSTR window_class_identity) : window_class_name(window_class_identity), pressed(-1) {
		setQns();
		int screen_width = GetSystemMetrics(SM_CXFULLSCREEN);
		int screen_height = GetSystemMetrics(SM_CYFULLSCREEN);
		instance_handle = GetModuleHandle(NULL);

		WNDCLASS window_class = { CS_OWNDC, main_window_proc, 0, 0,
			instance_handle, NULL,
			NULL, NULL, NULL,
			window_class_name };

		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   
		// Create a standard frame window   
		//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   

		RegisterClass(&window_class);
		window_handle = CreateWindowEx(WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE,
			window_class_name,
			L"Radio button Example",
			WS_OVERLAPPEDWINDOW |
			WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
			100, 100, 600,
			300, NULL, NULL,
			instance_handle, NULL);
		RECT client_rectangle;
		GetClientRect(window_handle, &client_rectangle);
		int width = client_rectangle.right - client_rectangle.left;
		int height = client_rectangle.bottom - client_rectangle.top;

		//initialize question UI
		int numOpt = Qns[currQn].NumOfOptions;
		text_handle_1 = CreateWindowEx(WS_EX_TRANSPARENT, L"Button",
			Qns[currQn].qnDesc,
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			20, 30, 400,
			numOpt * 24 + 30, window_handle, (HMENU)11,
			instance_handle, NULL);

		for (int i = 0; i < numOpt; i++) {
			int y = 20 + i * 24;
			int menu = 103 + i;

			if(i > 0) {
				handlers[i] = CreateWindowEx(0, L"Button", Qns[currQn].options[i].OptDesc,
					WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
					4, y, 280,
					20, text_handle_1, (HMENU)menu,
					instance_handle, NULL);
			}
			else {
				handlers[i] = CreateWindowEx(0, L"Button", Qns[currQn].options[i].OptDesc,
					WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
					4, y, 280,
					20, text_handle_1, (HMENU)menu,
					instance_handle, NULL);
			}
		}

		okbutton_handle = CreateWindowEx(0,
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"OK",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			290,         // x position 
			numOpt * 24 + 70,         // y position 
			60,        // Button width
			30,        // Button height
			window_handle,     // Parent window
			(HMENU)IDC_OK_BUTTON,       // No menu.
			instance_handle,
			NULL);      // Pointer not needed.

		backbutton_handle = CreateWindowEx(0,
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"Cancel",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD,  // Styles 
			360,         // x position 
			numOpt * 24 + 70,         // y position 
			60,        // Button width
			30,        // Button height
			window_handle,     // Parent window
			(HMENU)IDC_CANCEL_BUTTON,       // No menu.
			instance_handle,
			NULL);      // Pointer not needed.
		//backbutton_handle
		
		SendMessage(handlers[0], BM_SETCHECK, BST_CHECKED, 0);
		//SendMessage(radiobutton_handle_5, BM_SETCHECK, BST_CHECKED, 0);
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		SetWindowLongPtr(window_handle, GWL_USERDATA, (LONG)this);
		ShowWindow(window_handle, SW_SHOW);
		UpdateWindow(window_handle);
	}
	~frame_window() {
		delete[] Qns;
		UnregisterClass(window_class_name, instance_handle);
	}

	void cleanWnds() {
		INT numOpt = Qns[currQn].NumOfOptions;
		
		for (INT i = 0; i < numOpt; i++) {
			DestroyWindow(handlers[i]);
			handlers[i] = HWND();

		}
	}

	void redrawWindow(bool next) {
		int y = IsDlgButtonChecked(text_handle_1, 103);
		int z = IsDlgButtonChecked(text_handle_1, 104);
		int s = IsDlgButtonChecked(text_handle_1, 105);
		int index = -1;
		for (int i = 0; i < getNumBtns(); i++) {
			int id = 103 + i;
			if (IsDlgButtonChecked(text_handle_1, id)) {
				index = i;
			}
		}

		cleanWnds();
		RedrawWindow(window_handle, NULL, NULL, RDW_INVALIDATE);

		if (!next) {
			currQn = Qns[currQn].PrevQn;
		} else if (index >= 0) {
			currQn = Qns[currQn].options[index].NextQn;
		}
		else {
			return;
		}

		INT numOpt = Qns[currQn].NumOfOptions;

		DestroyWindow(text_handle_1);
		RedrawWindow(window_handle, NULL, NULL, RDW_INVALIDATE);


		text_handle_1 = CreateWindowEx(WS_EX_TRANSPARENT, L"Button",
			Qns[currQn].qnDesc,
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			20, 30, 400,
			numOpt * 24 + 30, window_handle, (HMENU)11,
			instance_handle, NULL);

		//SetWindowText(text_handle_1, Qns[currQn].qnDesc);
		//SetWindowPos(text_handle_1, HWND_BOTTOM, 20, 30, 400, numOpt * 24 + 30, SWP_SHOWWINDOW);
		//MoveWindow(text_handle_1, 20, 30, 400, numOpt * 24 + 30, true);
		//AdjustWindowRectEx()

		for (INT i = 0; i < numOpt; i++) {
			INT y = 20 + i * 24;
			INT menu = 103 + i;

			if (i > 0) {
				handlers[i] = CreateWindowEx(0, L"Button", Qns[currQn].options[i].OptDesc,
					WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
					4, y, 280,
					20, text_handle_1, (HMENU)menu,
					instance_handle, NULL);
			}
			else {
				handlers[i] = CreateWindowEx(0, L"Button", Qns[currQn].options[i].OptDesc,
					WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
					4, y, 280,
					20, text_handle_1, (HMENU)menu,
					instance_handle, NULL);
			}
		}

		SendMessage(handlers[0], BM_SETCHECK, BST_CHECKED, 0);

	}

	int getNumBtns() {
		return Qns[currQn].NumOfOptions;
	}

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   
	// Windows message processing function   
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   
	static LRESULT WINAPI main_window_proc(HWND window_handle, UINT message,
		WPARAM wparam, LPARAM lparam) {
		frame_window *This = (frame_window *)GetWindowLongPtr(window_handle,
			GWL_USERDATA);
		switch (message) {
		case WM_PAINT:
		{
			PAINTSTRUCT paint_structure;
			RECT client_rect;
			HDC paint_device_context, paint_dc;
			HBITMAP bitmap;

			paint_device_context = BeginPaint(window_handle, &paint_structure);
			paint_dc = CreateCompatibleDC(paint_device_context);
			GetClientRect(window_handle, &client_rect);
			int window_width = client_rect.right - client_rect.left;
			int window_height = client_rect.bottom - client_rect.top;
			bitmap = CreateBitmap(window_width, window_height, 1, 32, NULL);
			HGDIOBJ old_bitmap = SelectObject(paint_dc, bitmap);

			// Fill the client aread with the user selected face colour  
			HBRUSH light_brush = CreateSolidBrush(GetSysColor(COLOR_BTNFACE));
			FillRect(paint_dc, &paint_structure.rcPaint, light_brush);
			DeleteObject(light_brush);

			BitBlt(paint_device_context, 0, 0,
				client_rect.right - client_rect.left,
				client_rect.bottom - client_rect.top,
				paint_dc, 0, 0, SRCCOPY);
			SelectObject(paint_dc, old_bitmap);
			DeleteObject(bitmap);
			DeleteDC(paint_dc);
			EndPaint(window_handle, &paint_structure);
			return 0;
		}
		break;
		case WM_ERASEBKGND:
		{
			return TRUE;
		}
		break;
		case WM_SIZE:
		{
			RECT client_rectangle;
			GetClientRect(window_handle, &client_rectangle);
			int width = client_rectangle.right - client_rectangle.left;
			int height = client_rectangle.bottom - client_rectangle.top;
			InvalidateRect(window_handle, NULL, TRUE);
			return 0;
		}
		break;
		//TODO
		case WM_COMMAND:
		{
			switch (LOWORD(wparam))
			{

			case IDC_OK_BUTTON: {
				LONG x = GetWindowLong(GetWindow(window_handle, GW_CHILD), GWL_ID);
				int y = IsDlgButtonChecked(GetWindow(window_handle, GW_CHILD), 103);
				This->redrawWindow(true);
				
			}
			break;
			case IDC_CANCEL_BUTTON: {
				LONG x = GetWindowLong(GetWindow(window_handle, GW_CHILD), GWL_ID);
						//RedrawWindow(window_handle, NULL, NULL, RDW_INVALIDATE);
						InvalidateRect(window_handle, NULL, TRUE);
						This->redrawWindow(false);
			}
			break;
			default:
				break;
			}
		}
		break;
		case WM_CLOSE:
		{
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
			// The user wants to close the window   
			//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

			PostQuitMessage(0);
			return 0;
		}
		break;
		}
		return DefWindowProc(window_handle, message, wparam, lparam);
	}

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   
	// Windows message loop   
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	void run() {
		MSG window_message;
		while (GetMessage(&window_message, NULL, 0, 0)) {
			TranslateMessage(&window_message);
			DispatchMessage(&window_message);
		}
	}
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   
// Windows main entry point   
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++   

int WINAPI wWinMain(HINSTANCE instance_handle, HINSTANCE, LPWSTR, INT) {
	frame_window main_window(L"my base window");
	main_window.run();
	return 0;
}
