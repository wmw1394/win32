#include <windows.h>  

using namespace std;

#define IDC_OK_BUTTON 101
#define IDC_CANCEL_BUTTON 102
#define RADIO_BUTTON1 103
#define OPTION_SIZE 10
#define LOGIN_ERR 1001
#define REG_ERR 1002
#define APN_CHK 1003
#define LINK_DOWN 1004
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

class Answer
{
public:
	BOOL answered;
	BOOL isNumber;
	INT int_result;
	LPCTSTR string_result;
	Answer() : answered(false), isNumber(true), int_result(0), string_result(TEXT("")) {}
	void setText(TCHAR* result) {
		answered = true;
		isNumber = false;
		string_result = result;
		//strcpy(string_result, result);
	}
	void setInt(INT result) {
		answered = true;
		isNumber = true;
		int_result = result;
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
	int numQns = 20;
	Question* Qns;
	Answer* Anws;
	HWND* handlers;

	//place to set questions
	void setQns() {
		Qns = new Question[numQns];
		Anws = new Answer[numQns];
		handlers = new HWND[numQns];

		Option opt01 = Option(TEXT("FBB"), 1);
		Option opt02 = Option(TEXT("MVSAT"), 8);
		Question qn0 = Question(TEXT("What terminal are you using?"), 0, 2, -1);
		qn0.addOption(opt01, 0);
		qn0.addOption(opt02, 1);
		Qns[0] = qn0;


		Option opt11 = Option(TEXT(""), 2);
		Question qn1 = Question(TEXT("Signal level?"), 0, 0, -1);
		qn1.addOption(opt11, 0);
		Qns[1] = qn1;

		Option opt21 = Option(TEXT(""), 3);
		Question qn2 = Question(TEXT("What is the model?"), 0, 0, -1);
		qn2.addOption(opt21, 0);
		Qns[2] = qn2;

		Option opt31 = Option(TEXT(""), 4);
		Question qn3 = Question(TEXT("What is the heading?"), 0, 0, -1);
		qn3.addOption(opt31, 0);
		Qns[3] = qn3;

		Option opt41 = Option(TEXT(""), 5);
		Question qn4 = Question(TEXT("What is the lattitude/longitude?"), 0, 0, -1);
		qn4.addOption(opt41, 0);
		Qns[4] = qn4;

		Option opt51 = Option(TEXT(""), 6);
		Question qn5 = Question(TEXT("What is the installation location on ship?"), 0, 0, -1);
		qn5.addOption(opt51, 0);
		Qns[5] = qn5;

		Option opt61 = Option(TEXT(""), 7);
		Question qn6 = Question(TEXT("What is the blokage by ship?"), 0, 0, -1);
		qn6.addOption(opt61, 0);
		Qns[6] = qn6;

		Option opt71 = Option(TEXT("CME148 Login Error"), -1001);
		Option opt72 = Option(TEXT("CME149 Double Registration"), -1002);
		Option opt73 = Option(TEXT("CME133 APN Check"), -1003);
		Question qn7 = Question(TEXT("What is the error in the launchpad?"), 0, 3, -1);
		qn7.addOption(opt71, 0);
		qn7.addOption(opt72, 1);
		qn7.addOption(opt73, 2);
		Qns[7] = qn7;

		Option opt81 = Option(TEXT(""), 9);
		Question qn8 = Question(TEXT("What is the satellite pointing position?"), 0, 0, -1);
		qn8.addOption(opt81, 0);
		Qns[8] = qn8;

		Option opt91 = Option(TEXT(""), 10);
		Question qn9 = Question(TEXT("What is the lattitude/longitude?"), 0, 0, -1);
		qn9.addOption(opt91, 0);
		Qns[9] = qn9;

		Option opt101 = Option(TEXT(""), 11);
		Question qn10 = Question(TEXT("What is the AZ/EL/Heading?"), 0, 0, -1);
		qn10.addOption(opt101, 0);
		Qns[10] = qn10;

		Option opt111 = Option(TEXT("Green"), 12);
		Option opt112 = Option(TEXT("Orange"), 12);
		Question qn11 = Question(TEXT("Modem LED: What is the color of RX LED?"), 0, 2, -1);
		qn11.addOption(opt111, 0);
		qn11.addOption(opt112, 1);
		Qns[11] = qn11;

		Option opt121 = Option(TEXT("Green"), 13);
		Option opt122 = Option(TEXT("Orange"), 13);
		Question qn12 = Question(TEXT("Modem LED: What is the color of TX LED?"), 0, 2, -1);
		qn12.addOption(opt121, 0);
		qn12.addOption(opt122, 1);
		Qns[12] = qn12;

		Option opt131 = Option(TEXT("Green"), 14);
		Option opt132 = Option(TEXT("Orange"), 14);
		Question qn13 = Question(TEXT("Modem LED: What is the color of Status LED?"), 0, 2, -1);
		qn13.addOption(opt131, 0);
		qn13.addOption(opt132, 1);
		Qns[13] = qn13;

		Option opt141 = Option(TEXT("Green"), 15);
		Option opt142 = Option(TEXT("Red"), 15);
		Question qn14 = Question(TEXT("Modem LED: What is the color of Network LED?"), 0, 2, -1);
		qn14.addOption(opt141, 0);
		qn14.addOption(opt142, 1);
		Qns[14] = qn14;

		Option opt151 = Option(TEXT("Green"), -1004);
		Option opt152 = Option(TEXT("Orange"), -1004);
		Question qn15 = Question(TEXT("Modem LED: What is the color of Power LED?"), 0, 2, -1);
		qn15.addOption(opt151, 0);
		qn15.addOption(opt152, 1);
		Qns[15] = qn15;
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
			100, 100, 450,
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
			numOpt * 24 + 80,         // y position 
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
			numOpt * 24 + 80,         // y position 
			60,        // Button width
			30,        // Button height
			window_handle,     // Parent window
			(HMENU)IDC_CANCEL_BUTTON,       // No menu.
			instance_handle,
			NULL);      // Pointer not needed.
		//backbutton_handle
		ShowWindow(backbutton_handle, SW_HIDE);

		SendMessage(handlers[0], BM_SETCHECK, BST_CHECKED, 0);
		//SendMessage(radiobutton_handle_5, BM_SETCHECK, BST_CHECKED, 0);
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		SetWindowLongPtr(window_handle, GWL_USERDATA, (LONG)this);
		ShowWindow(window_handle, SW_SHOW);
		UpdateWindow(window_handle);
	}
	~frame_window() {
		delete[] Qns;
		delete[] Anws;
		delete[] handlers;
		UnregisterClass(window_class_name, instance_handle);
	}

	void cleanWnds() {
		INT numOpt = Qns[currQn].NumOfOptions;
		
		for (INT i = 0; i < numOpt; i++) {
			DestroyWindow(handlers[i]);
			handlers[i] = HWND();
		}
		ShowWindow(backbutton_handle, SW_HIDE);
		ShowWindow(okbutton_handle, SW_HIDE);

	}

	void redrawWindow(bool next) {

		int index = -1;

		for (int i = 0; i < getNumBtns(); i++) {
			int id = 103 + i;
			if (IsDlgButtonChecked(text_handle_1, id)) {
				index = i;
			}
		}


		if (!next) {
			//if it is going back, only go back if there is a page before it
			if (Qns[currQn].PrevQn >= 0) {
				currQn = Qns[currQn].PrevQn;
			}
			else
			{
				return;
			}
		} else {

			//note down the selection of user

			if (index < 0) {
				//user enter text
				INT len = GetWindowTextLength(handlers[1]);
				TCHAR* buff;
				buff = new TCHAR[1024]();
				GetWindowText(handlers[1], buff, len);
				Anws[currQn].setText(buff);
				int x = _wtoi(buff);
				bool bol = isdigit(x);

				//reset index in order to navigate to next question
				index = 0;
			}
			else {
				//user chose an option
				Anws[currQn].setInt(index);

			}
			int temp = currQn;
			if (Qns[currQn].options[index].NextQn < 0) {
				finalResultCall(-Qns[currQn].options[index].NextQn);
				return;
				//call some final function
			}
			currQn = Qns[currQn].options[index].NextQn;
			Qns[currQn].PrevQn = temp;
		}


		INT numOpt = Qns[currQn].NumOfOptions;

		if (numOpt == 0) {
			numOpt = 3;
		}

		drawDialog(numOpt);

		if (Qns[currQn].NumOfOptions == 0) {
			drawTextBox();
		}
		else {
			drawOptions(numOpt);
		}


		//reset the button positions
		SetWindowPos(okbutton_handle, HWND_BOTTOM, 290, numOpt * 24 + 80, 60, 30, SWP_SHOWWINDOW);
		SetWindowPos(backbutton_handle, HWND_BOTTOM, 360, numOpt * 24 + 80, 60, 30, SWP_SHOWWINDOW);
		ShowWindow(backbutton_handle, SW_SHOW);
		ShowWindow(okbutton_handle, SW_SHOW);

		RECT aRect;
		GetWindowRect(window_handle, &aRect);
		if (aRect.bottom <= numOpt * 24 + 120) {
			SetWindowPos(window_handle, HWND_BOTTOM, 100, 100, numOpt * 24 + 120, 300, SWP_SHOWWINDOW);
		}
	}

	void drawDialog(INT numOpt) {

		cleanWnds();
		RedrawWindow(window_handle, NULL, NULL, RDW_INVALIDATE);
		DestroyWindow(text_handle_1);
		RedrawWindow(window_handle, NULL, NULL, RDW_INVALIDATE);


		text_handle_1 = CreateWindowEx(WS_EX_TRANSPARENT, L"Button",
			Qns[currQn].qnDesc,
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			20, 30, 400,
			numOpt * 24 + 30, window_handle, (HMENU)11,
			instance_handle, NULL);

	}

	void drawOptions(INT numOpt) {

		//recreate buttons
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

	void drawTextBox() {
		TCHAR lpszLatin[] = L"Lorem ipsum dolor sit amet, consectetur "
			L"adipisicing elit, sed do eiusmod tempor ";
		handlers[1] = CreateWindowEx(
			0, L"EDIT",   // predefined class 
			NULL,         // no window title 
			WS_CHILD | WS_VISIBLE | WS_VSCROLL |
			ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL,
			4, 20, 390, 60,   // set size in WM_SIZE message 
			text_handle_1,         // parent window 
			(HMENU)103,   // edit control ID 
			instance_handle,
			NULL);        // pointer not needed 

						  // Add text to the window. 
		SendMessage(handlers[1], WM_SETTEXT, 0, (LPARAM)lpszLatin);
	}

	void finalResultCall(INT caseNum) {
		switch (caseNum)
		{
		case LOGIN_ERR:
			//placeholders, can change to call for library functions
			cleanWnds();
			RedrawWindow(window_handle, NULL, NULL, RDW_INVALIDATE);
			DestroyWindow(text_handle_1);
			RedrawWindow(window_handle, NULL, NULL, RDW_INVALIDATE);


			text_handle_1 = CreateWindowEx(WS_EX_TRANSPARENT, L"Edit",
				TEXT("Please check your credentials and try again."),
				WS_CHILD | WS_VISIBLE | WS_VSCROLL |
				ES_LEFT | ES_MULTILINE | ES_READONLY,
				20, 60, 400,
				110, window_handle, (HMENU)11,
				instance_handle, NULL);
			break;
		case REG_ERR:
			//placeholders, can change to call for library functions
			cleanWnds();
			RedrawWindow(window_handle, NULL, NULL, RDW_INVALIDATE);
			DestroyWindow(text_handle_1);
			RedrawWindow(window_handle, NULL, NULL, RDW_INVALIDATE);


			text_handle_1 = CreateWindowEx(WS_EX_TRANSPARENT, L"Edit",
				TEXT("Please power off your launchpad for 20 minutes and reattempte a connection."),
				WS_CHILD | WS_VISIBLE | WS_VSCROLL |
				ES_LEFT | ES_MULTILINE | ES_READONLY,
				20, 60, 400,
				110, window_handle, (HMENU)11,
				instance_handle, NULL);
			break;		
		case APN_CHK:
				//placeholders, can change to call for library functions
				cleanWnds();
				RedrawWindow(window_handle, NULL, NULL, RDW_INVALIDATE);
				DestroyWindow(text_handle_1);
				RedrawWindow(window_handle, NULL, NULL, RDW_INVALIDATE);


				text_handle_1 = CreateWindowEx(WS_EX_TRANSPARENT, L"Edit",
					TEXT("Please check if the APN you entered is correct."),
					WS_CHILD | WS_VISIBLE | WS_VSCROLL |
					ES_LEFT | ES_MULTILINE | ES_READONLY,
					20, 60, 400,
					110, window_handle, (HMENU)11,
					instance_handle, NULL);
				break;
		case LINK_DOWN:
			cleanWnds();
			RedrawWindow(window_handle, NULL, NULL, RDW_INVALIDATE);
			DestroyWindow(text_handle_1);
			RedrawWindow(window_handle, NULL, NULL, RDW_INVALIDATE);

			if (Anws[14].int_result == 1 && Anws[11].int_result == 1 && Anws[15].int_result == 0) {
				text_handle_1 = CreateWindowEx(WS_EX_TRANSPARENT, L"Edit",
					TEXT("Please check link connection."),
					WS_CHILD | WS_VISIBLE | WS_VSCROLL |
					ES_LEFT | ES_MULTILINE | ES_READONLY,
					20, 60, 400,
					110, window_handle, (HMENU)11,
					instance_handle, NULL);
			}

			break;
		default:
			break;
		}
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
