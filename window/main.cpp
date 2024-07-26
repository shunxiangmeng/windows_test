#include <windows.h>

// ���ڹ��̺���
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
    // ע�ᴰ����
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "Tftpd32WindowClass";
    RegisterClass(&wc);

    // ��������
    HWND hwnd = CreateWindow("Tftpd32WindowClass", "window_test", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);
    if (!hwnd) {
        MessageBox(NULL, "���ڴ���ʧ��!", "����", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    // ���������
    HWND hEdit = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
        50, 50, 200, 25, hwnd, NULL, hInstance, NULL);
    if (!hEdit) {
        MessageBox(NULL, "����򴴽�ʧ��!", "����", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    // ��ʾ����
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // ��Ϣѭ��
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}