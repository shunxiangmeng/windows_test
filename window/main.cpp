#include <windows.h>

// 窗口过程函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_SIZE:
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 注册窗口类
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Tftpd32WindowClass";
    RegisterClass(&wc);

    // 创建窗口
    HWND hwnd = CreateWindow("Tftpd32WindowClass", "window_test", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);
    if (!hwnd) {
        MessageBox(NULL, "窗口创建失败!", "错误", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    // 创建输入框
    HWND hEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        50, 50, 200, 25, hwnd, NULL, hInstance, NULL);
    if (!hEdit) {
        MessageBox(NULL, "输入框创建失败!", "错误", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    // 显示窗口
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}