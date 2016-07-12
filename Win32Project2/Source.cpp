#include <windows.h>  
 
using namespace std;

#define IDC_OK_BUTTON 101
#define IDC_CANCEL_BUTTON 102
#define RADIO_BUTTON1 103
#pragma comment(lib, "comctl32.lib")

class frame_window {
private:
	LPWSTR window_class_name;
	HINSTANCE instance_handle;
	HCURSOR cursor_arrow;
	HWND window_handle;
	HWND text_handle_1;
	HWND text_handle_2;
	HWND radiobutton_handle_1;
	HWND radiobutton_handle_2;
	HWND radiobutton_handle_3;
	HWND radiobutton_handle_4;
	HWND radiobutton_handle_5;
	HWND radiobutton_handle_6;
	HWND radiobutton_handle_7;
	HWND okbutton_handle;
	HWND backbutton_handle;
	RECT client_rectangle;
	int pressed;
	int count = 0;
public:
	frame_window(LPWSTR window_class_identity) : window_class_name(window_class_identity), pressed(-1) {
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
			100, 100, screen_width - 200,
			screen_height - 200, NULL, NULL,
			instance_handle, NULL);
		RECT client_rectangle;
		GetClientRect(window_handle, &client_rectangle);
		int width = client_rectangle.right - client_rectangle.left;
		int height = client_rectangle.bottom - client_rectangle.top;
		text_handle_1 = CreateWindowEx(WS_EX_TRANSPARENT, L"Button",
			L"How did you find your experience at Dream-In-Code?",
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			20, 30, 400,
			130, window_handle, (HMENU)11,
			instance_handle, NULL);
		text_handle_2 = CreateWindowEx(WS_EX_TRANSPARENT, L"Button",
			L"Did you find the help you needed?",
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			20, 170, 400,
			130, window_handle, (HMENU)11,
			instance_handle, NULL);
		radiobutton_handle_1 = CreateWindowEx(0, L"Button", L"Good",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
			4, 20, 280,
			20, text_handle_1, (HMENU)RADIO_BUTTON1,
			instance_handle, NULL);
		radiobutton_handle_2 = CreateWindowEx(0, L"Button", L"OK",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			4, 44, 280,
			20, text_handle_1, (HMENU)12,
			instance_handle, NULL);
		radiobutton_handle_3 = CreateWindowEx(0, L"Button", L"Bad",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			4, 68, 280,
			20, text_handle_1, (HMENU)11,
			instance_handle, NULL);
		radiobutton_handle_4 = CreateWindowEx(0, L"Button", L"Terrible",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			4, 92, 280,
			20, text_handle_1, (HMENU)12,
			instance_handle, NULL);
		radiobutton_handle_5 = CreateWindowEx(0, L"Button", L"Yes",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP,
			4, 20, 280,
			20, text_handle_2, (HMENU)11,
			instance_handle, NULL);
		radiobutton_handle_6 = CreateWindowEx(0, L"Button", L"Almost",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			4, 44, 280,
			20, text_handle_2, (HMENU)12,
			instance_handle, NULL);
		radiobutton_handle_7 = CreateWindowEx(0, L"Button", L"No",
			WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			4, 68, 280,
			20, text_handle_2, (HMENU)11,
			instance_handle, NULL);
		okbutton_handle = CreateWindowEx(0,
			L"BUTTON",  // Predefined class; Unicode assumed 
			L"OK",      // Button text 
			WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
			290,         // x position 
			310,         // y position 
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
			310,         // y position 
			60,        // Button width
			30,        // Button height
			window_handle,     // Parent window
			(HMENU)IDC_CANCEL_BUTTON,       // No menu.
			instance_handle,
			NULL);      // Pointer not needed.
		//backbutton_handle
		SendMessage(radiobutton_handle_1, BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(radiobutton_handle_5, BM_SETCHECK, BST_CHECKED, 0);
		SetCursor(LoadCursor(NULL, IDC_ARROW));
		SetWindowLongPtr(window_handle, GWL_USERDATA, (LONG)this);
		ShowWindow(window_handle, SW_SHOW);
		UpdateWindow(window_handle);
	}
	~frame_window() {
		UnregisterClass(window_class_name, instance_handle);
	}
	void redrawWindow() {
		count++;
		TCHAR szBuffer[10];
		wsprintf(szBuffer, TEXT("Player %d"), count);
		int msgboxID = MessageBox(
			NULL,
			L"Radio button",
			szBuffer,
			MB_ICONEXCLAMATION | MB_YESNO
			);

		text_handle_1 = CreateWindowEx(WS_EX_TRANSPARENT, L"Button",
			L"Change this code?",
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			20, 30, 400,
			130, window_handle, (HMENU)11,
			instance_handle, NULL);
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
				//RADIO_BUTTON1
			case RADIO_BUTTON1: {

			}
			break;
			case IDC_OK_BUTTON: {
				LONG x = GetWindowLong(GetWindow(window_handle, GW_CHILD), GWL_ID);
				if (IsDlgButtonChecked(GetWindow(window_handle, GW_CHILD), RADIO_BUTTON1)) {
					This->redrawWindow();
				}
				
			}
			break;
			case IDC_CANCEL_BUTTON: {
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
