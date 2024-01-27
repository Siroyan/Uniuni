#define STRICT
#include <windows.h>

#include "resource.h"

LRESULT	CALLBACK	WindowProc			(HWND, UINT, WPARAM, LPARAM);
BOOL	CALLBACK	DialogWindowProc	(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevious, LPSTR lpszCmdLine, int nCmdShow)
{
	WNDCLASS wc;
	HWND hWnd;
	MSG msg;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_UNIUNI));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wc.lpszClassName = "WindowClassName";

	RegisterClass(&wc);
	hWnd = CreateWindow
	(
		"WindowClassName",
		"Uniuni",
		WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX,
		100, 100,
		1500, 900,
		(HWND)NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT	CALLBACK WindowProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	switch (nMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_HELP_VERSION:

			DialogBox(
				(HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE),
				MAKEINTRESOURCE(IDD_DIALOG_VERSION),
				hWnd,
				(DLGPROC)DialogWindowProc);
			break;
		case ID_FILE_QUIT:
			DestroyWindow(hWnd);
			return 0;
		default:
			break;
		}
	}
	return DefWindowProc(hWnd, nMsg, wParam, lParam);
}

BOOL CALLBACK DialogWindowProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static	RECT	rt, rtParent;
	LONG	w, h, x, y;
	switch (iMsg)
	{
	case WM_INITDIALOG:
		//モーダルダイアログボックスを作成
		GetWindowRect(hWnd, &rt);
		GetWindowRect(GetParent(hWnd), &rtParent);
		w = rt.right - rt.left;
		h = rt.bottom - rt.top;
		x = rtParent.right / 2 - w / 2;
		y = rtParent.bottom / 2 - h / 2;
		SetWindowPos(hWnd, 0, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		return TRUE;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		return FALSE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_DIALOG_VERSION_CLOSE:
			EndDialog(hWnd, 0);
			break;
		}
		return TRUE;
	default:
		return FALSE;
	}
}
