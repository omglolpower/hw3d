
#include <Windows.h>
#include "WindowsMessageMap.h"
// define custom windows procedure:
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static WindowsMessageMap mm;
	OutputDebugString( mm(msg, lParam, wParam).c_str() );

	switch (msg)
	{
	case WM_CLOSE:
			PostQuitMessage(69);
			break;
	case WM_KEYDOWN:
		if (wParam == 'F')
		{
			SetWindowText(hWnd, "F down");
		}
		break;
	case WM_KEYUP:
		if (wParam == 'F')
		{
			SetWindowText(hWnd, "F up");
		}
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR	  lpCmdLine,
	int		  nCmdShow
)
{
	const auto pClassName = "VasyaVoron";
	//register class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);
	HWND hwnd = CreateWindowEx(
		0,
		pClassName,
		"Hello World!",
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200,
		640, 640,
		nullptr,
		nullptr,
		hInstance,
		nullptr
	);
		ShowWindow(hwnd, SW_SHOW);
		MSG msg;
		BOOL gResult;

		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	}

		if (gResult == -1)
		{
			return -1;
		}
		else return msg.wParam;
	
}