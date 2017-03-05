#include <Windows.h>
#include "generic.h"
#if defined (win32)
	#define IS_WIN32 TRUE
#else
	#define IS_WIN32 FALSE
#endif

HINSTANCE hInst; //instanta curenta
LPCTSTR lpszAppName = "Generic";
LPCTSTR lpszTitle = "Generic application";
BOOL RegisterWin95(CONST WNDCLASS* lpwc);


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	MSG msg;
	HWND hWnd;
	WNDCLASS wx;

	wx.style = CS_HREDRAW | CS_VREDRAW ;
	wx.lpfnWndProc = (WNDPROC)WndProc;
	wx.cbClsExtra = 0;
	wx.cbWndExtra = 0;
	wx.hInstance = 0;
	wx.hIcon = LoadIcon(hInstance, lpszAppName);
	wx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wx.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wx.lpszMenuName = lpszAppName;
	wx.lpszClassName = lpszAppName;

	if(!RegisterWin95(&wx))
		return false;
	hInst = hInstance;
	hWnd = CreateWindow(lpszAppName,
						lpszTitle,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, 0,
						CW_USEDEFAULT, 0,
						NULL,
						NULL,
						hInstance,
						NULL);
	if(!hWnd)
		return false;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while(GetMessage(&msg, NULL, 0,0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return(msg.wParam);
}

BOOL RegisterWin95(CONST WNDCLASS* lpwc){
	WNDCLASSEX wcex;
	wcex.style = lpwc -> style;
	wcex.lpfnWndProc = lpwc->lpfnWndProc;
	wcex.cbClsExtra = lpwc -> cbClsExtra;
	wcex.cbWndExtra = lpwc ->cbWndExtra;
	wcex.hInstance = lpwc -> hInstance;
	wcex.hIcon = lpwc -> hIcon;
	wcex.hCursor = lpwc -> hCursor;
	wcex.hbrBackground = lpwc->hbrBackground;
	wcex.lpszMenuName = lpwc->lpszMenuName;
	wcex.lpszClassName = lpwc->lpszClassName;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.hIconSm = LoadIcon(wcex.hInstance, "SMALL");
	return RegisterClassEx(&wcex);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	switch (uMsg){
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			case IDM_TEST:
				ShowWindow(hWnd, SW_SHOWMAXIMIZED);//1259
				break;
			case IDH_CANCEL:
				MessageBeep(0);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return (DefWindowProc(hWnd, uMsg, wParam, lParam));
	}
	return(0L);
}


