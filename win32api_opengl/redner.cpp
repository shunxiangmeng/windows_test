#include <windows.h>
#include <gl/GL.h>
#include <thread>
#include <chrono>
#include <gl/GLU.h>

void InitOpenGL(HWND hwnd) {
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,
        8,
        0,
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };

    HDC hdc = GetDC(hwnd);
    int pixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pixelFormat, &pfd);
    HGLRC hglrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hglrc);
}

void DrawScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(-1.0f, -1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glEnd();
}

void reander(HWND hwnd) {

    std::thread([hwnd]() {
        
        InitOpenGL(hwnd);

        while (true) {

            DrawScene();
            HDC hdc = GetDC(hwnd);
            SwapBuffers(hdc);
            ReleaseDC(hwnd, hdc);

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        
    }).detach();

}

