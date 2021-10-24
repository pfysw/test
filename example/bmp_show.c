/*
 * main.c
 *
 *  Created on: Oct 27, 2020
 *      Author: Administrator
 */

#include <stdio.h>
#include <stdlib.h>
#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
int main()
{
	HINSTANCE hInstance = GetModuleHandle (NULL);
	int nCmdShow = 1;
    // Register the window class.
    const char * CLASS_NAME  = L"Sample Window Class";

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

void PaintDemo(HWND hwnd)
{
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
    EndPaint(hwnd, &ps);
}

BOOL PaintBmp(HWND hWnd)
{
    PAINTSTRUCT ps;
   // HDC hDC = BeginPaint(hWnd, &ps);
    // 获取窗口的客户区域的显示设备上下文环境的句柄
    HDC hDC = GetDC(hWnd);
    // 创建一个与hDC兼容的内存设备上下文环境
    HDC hBuf = CreateCompatibleDC(hDC);
    // 加载位图, 获取位图句柄
    HBITMAP hBmp = (HBITMAP)LoadImage(NULL, L"D:\\devc++\\lookcode\\smzy\\bg2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    // 选择位图句柄到hBuf中, 并获取返回的原来位图句柄
    HBITMAP hOldBmp = (HBITMAP)SelectObject(hBuf, hBmp);
    // 绘图
    BitBlt(hDC, 0, 0, 764, 397, hBuf, 0, 0, SRCCOPY);
    // 还原位图对象
    SelectObject(hBuf, hOldBmp);
    // 释放位图
    DeleteObject(hBmp);
    // 释放兼容的内存设备上下文环境
    DeleteDC(hBuf);
    // 释放设备上下文环境
    ReleaseDC(hWnd, hDC);
   // EndPaint(hWnd, &ps);
    return TRUE;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            //PaintDemo(hwnd);
            PaintBmp(hwnd);
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
