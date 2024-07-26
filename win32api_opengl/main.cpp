#include <windows.h>
#include "render.h"
#include <gl/GLU.h>
#include <gl/GL.h>
#include <thread>

#pragma comment(lib, "opengl32.lib")

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_SIZE:
        glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "OpenGLWindowClass";
    if (!RegisterClass(&wc)) {
        MessageBox(NULL, "窗口类注册失败!", "错误", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    HWND hwnd = CreateWindow("OpenGLWindowClass", "OpenGL示例", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
    if (!hwnd) {
        MessageBox(NULL, "窗口创建失败!", "错误", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }


    // 创建输入框
    HWND hEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        50, 150, 200, 250, hwnd, NULL, hInstance, NULL);
    if (!hEdit) {
        MessageBox(NULL, "输入框创建失败!", "错误", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    // 创建输入框
    HWND hEdit1 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        350, 50, 200, 250, hwnd, NULL, hInstance, NULL);
    if (!hEdit) {
        MessageBox(NULL, "输入框创建失败!", "错误", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    reander(hEdit);
    reander(hEdit1);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}