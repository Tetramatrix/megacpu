// Megacpu.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Megacpu.h"
#include "process.h"    /* _beginthread, _endthread */
//#include "IOAccess.h"

#define MAX_LOADSTRING 100
#define	WM_USER_SHELLICON WM_USER + 1

// Global Variables:
HINSTANCE hInst;	// current instance
HWND hWnd;
NOTIFYICONDATA nidApp;
HMENU hPopMenu;
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
TCHAR szApplicationToolTip[MAX_LOADSTRING];	    // the main window class name
//BOOL bDisable = FALSE;							// keep application state
int oldmenu;

void RunTest(TCHAR *AppName, TCHAR *CmdLine)
{
    ShellExecute(NULL, "runas", AppName, CmdLine, NULL, SW_HIDE);
}

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void MyThread       ( void *dummy );

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MEGACPU, szWindowClass, MAX_LOADSTRING);
	
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	_beginthread( MyThread, 0, (void *) (0) );
	
	RunTest(_T("C:\\Program Files (x86)\\Megacpu\\tpc.exe"),_T("-cfgfile \"C:\\Program Files (x86)\\Megacpu\\fast.cfg\""));
	oldmenu = IDM_FAST;

	RunTest(_T("C:\\Program Files (x86)\\Megacpu\\tpc.exe"), _T("-rampuptime 15"));
	RunTest(_T("C:\\Program Files (x86)\\Megacpu\\tpc.exe"), _T("-rampuptime 0"));
	RunTest(_T("C:\\Program Files (x86)\\Megacpu\\tpc.exe"), _T("-c1enable 1"));
	RunTest(_T("C:\\Program Files (x86)\\Megacpu\\tpc.exe"), _T("-c1enable 0"));
	RunTest(_T("C:\\Program Files (x86)\\Megacpu\\tpc.exe"), _T("-htcenable"));
	RunTest(_T("C:\\Program Files (x86)\\Megacpu\\tpc.exe"), _T("-htctemplimit 115"));

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MEGACPU));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int) msg.wParam;
}


void MyThread( void *param )
{
    //int i = *(int *)param;    
    while (1) 
	{   
		/* Wait one second between loops. */
		Sleep( 1000*60*60*2L );
		DialogBox(hInst, MAKEINTRESOURCE(IDD_DONATION), hWnd, About); 
	}	
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MEGACPU));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MEGACPU);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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
   //HWND hWnd;
   HICON hMainIcon;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   hMainIcon = LoadIcon(hInstance,(LPCTSTR)MAKEINTRESOURCE(IDI_MEGACPU)); 

   nidApp.cbSize = sizeof(NOTIFYICONDATA); // sizeof the struct in bytes 
   nidApp.hWnd = (HWND) hWnd;              //handle of the window which will process this app. messages 
   nidApp.uID = IDI_MEGACPU;           //ID of the icon that will appear in the system tray 
   nidApp.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP; //ORing of all the flags 
   nidApp.hIcon = hMainIcon; // handle of the Icon to be displayed, obtained from LoadIcon 
   nidApp.uCallbackMessage = WM_USER_SHELLICON; 
   LoadString(hInstance, IDS_APPTOOLTIP,nidApp.szTip,MAX_LOADSTRING);
   Shell_NotifyIcon(NIM_ADD, &nidApp); 

   return TRUE;
}

void Init()
{
	// user defined message that will be sent as the notification message to the Window Procedure 
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
    POINT lpClickPoint;
	MENUITEMINFO mii = {sizeof(MENUITEMINFO) };
	BOOL status;

	switch (message)
	{
		case WM_USER_SHELLICON: 
			
			// systray msg callback 
			switch(LOWORD(lParam)) 
			{   
				case WM_RBUTTONDOWN: 
					
					UINT uFlag = MF_BYPOSITION|MF_UNCHECKED|MF_STRING;
					GetCursorPos(&lpClickPoint);
					hPopMenu = CreatePopupMenu();

					InsertMenu(hPopMenu,0xFFFFFFFF,MF_BYPOSITION|MF_STRING,IDM_ABOUT,_T("About"));
					InsertMenu(hPopMenu,0xFFFFFFFF,MF_SEPARATOR,IDM_SEP,_T("SEP"));
		
					InsertMenu(hPopMenu,0xFFFFFFFF,uFlag,IDM_MEGA,_T("Mega")); 
					InsertMenu(hPopMenu,0xFFFFFFFF,uFlag,IDM_FAST,_T("Fast"));
					InsertMenu(hPopMenu,0xFFFFFFFF,uFlag,IDM_MEDIUM,_T("Cruise")); 
					InsertMenu(hPopMenu,0xFFFFFFFF,uFlag,IDM_LOW,_T("Low"));
					InsertMenu(hPopMenu,0xFFFFFFFF,MF_SEPARATOR,IDM_SEP,_T("SEP"));													
					InsertMenu(hPopMenu,0xFFFFFFFF,MF_BYPOSITION|MF_STRING,IDM_EXIT,_T("Exit"));

					//hMenu = GetMenu(hWnd);
					mii.fMask = MIIM_STATE;
					status = GetMenuItemInfo(hPopMenu, oldmenu, FALSE, &mii);
					mii.fState ^= MFS_CHECKED;
					status = SetMenuItemInfo(hPopMenu, oldmenu, FALSE, &mii);	

					SetForegroundWindow(hWnd);
					TrackPopupMenu(hPopMenu,TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_BOTTOMALIGN,lpClickPoint.x, lpClickPoint.y,0,hWnd,NULL);
					return TRUE; 
			}
			break;

	case WM_COMMAND:

		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if (wmId != IDM_ABOUT) 
		{
			oldmenu = wmId;
		}

		// Parse the menu selections:
		switch (wmId)
		{
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;

			case IDM_MEGA:
				RunTest(_T("C:\\Program Files (x86)\\Megacpu\\tpc.exe"),_T("-cfgfile \"C:\\Program Files (x86)\\Megacpu\\mega.cfg\""));
				break;

			case IDM_FAST:
				RunTest(_T("C:\\Program Files (x86)\\Megacpu\\tpc.exe"),_T("-cfgfile \"C:\\Program Files (x86)\\Megacpu\\fast.cfg\""));
				break;

			case IDM_MEDIUM:
				RunTest(_T("C:\\Program Files (x86)\\Megacpu\\tpc.exe"),_T("-cfgfile \"C:\\Program Files (x86)\\Megacpu\\cruise.cfg\""));
				break;

			case IDM_LOW:
				RunTest(_T("C:\\Program Files (x86)\\Megacpu\\tpc.exe"),_T("-cfgfile \"C:\\Program Files (x86)\\Megacpu\\low.cfg\""));
				break;
			
			case IDM_EXIT:
				Shell_NotifyIcon(NIM_DELETE,&nidApp);
				DestroyWindow(hWnd);
				break;
			
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
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