// Freehand.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Freehand.h"
#include "App.h"
#include <cassert>
#include <string>
#define MAX_LOADSTRING 100


	
// Global Variables:

HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


AppObjectType cuurentAppObjType = AppObjectType::Line;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_FREEHAND, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	App app;
	app.init();
	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FREEHAND));
	
	
	
	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FREEHAND));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FREEHAND);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}
	
	App::Instance()->setHwnd(hWnd);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE: {
		//init Menu
		//DestroyMenu(GetMenu(hWnd));
		//auto v = SetMenu(hWnd, nullptr);
		HMENU mainMenu = CreateMenu();

		/*const wchar_t* caption = L"File";

		MENUITEMINFO info;
		info.cbSize = sizeof(info);
		info.fMask = MIIM_FTYPE | MIIM_STRING | MIIM_ID;
		info.fType = MFT_STRING;
		info.wID = 199;
		

		info.dwTypeData = const_cast<wchar_t*>(caption);
		info.cch = static_cast<UINT>(wcslen(caption));

		InsertMenuItem(mainMenu, 0, true, &info);*/
		
		MENUITEMINFO s;
		const wchar_t* caption = L"File";
		s.cbSize = sizeof(s);
		s.fMask = MIIM_TYPE;
		s.fType = MFT_STRING;
		s.dwTypeData = const_cast<wchar_t*>(caption);
		s.cch = wcslen(caption);


		InsertMenuItem(mainMenu, 0, true, &s);
		SetMenu(hWnd, mainMenu);
		//DrawMenuBar(hWnd);

	}break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_FILE_SAVE:
			printf("onSave!\n");
			//App::Instance()->save();
			break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	} break;

	case WM_KEYDOWN: {
		switch (wParam)
		{
		case VK_F1: { cuurentAppObjType = AppObjectType::Line; } break;
		case VK_F2: { cuurentAppObjType = AppObjectType::Point; } break;
		case VK_F3: { App::Instance()->save();} break;
		case VK_F4: { App::Instance()->load();} break;

		default: { } break;
		}
	} break;

	case WM_LBUTTONDOWN: 
	case WM_MBUTTONDOWN: 
	case WM_RBUTTONDOWN: 
	case WM_LBUTTONUP: 
	case WM_MBUTTONUP: 
	case WM_RBUTTONUP: 
	case WM_MOUSEMOVE: { App::Instance()->_onWin32MouseEvent(message, wParam, lParam); } break;

	
	case WM_PAINT:
	{
		PAINTSTRUCT ps;


		HDC hdc = BeginPaint(hWnd, &ps);
		

		App::Instance()->draw(hdc);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

int main() {
	wWinMain(GetInstanceModule(nullptr), nullptr, 0, SW_SHOW);
	return 0;
}