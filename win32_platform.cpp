//
// Created by @Candl3 on 2022-08-20.
//

#include <windows.h>

bool running = true;
void* buffer_memory;
int buffer_width;
int buffer_height;

LRESULT CALLBACK window_callback(
    _In_ HWND hwnd,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
){
    LRESULT result = 0;

    switch(uMsg) {
        case WM_CLOSE:
        case WM_DESTROY: {
            running = false;
        }
            break;

        case WM_SIZE: {
            RECT rect;
            GetClientRect(hwnd, &rect);
            buffer_width = rect.right - rect.left;
            buffer_height = rect.bottom - rect.top;

            int buffer_size = buffer_width * buffer_height * sizeof(unsigned int);

            if(buffer_memory) VirtualFree(buffer_memory, 0, MEM_RELEASE);
            buffer_memory = VirtualAlloc(NULL, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        }
            break;



        default: {
            result = DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    return result;
};

int winMain(
        HINSTANCE hInstance,
        HINSTANCE hPrevInstance,
        LPSTR lpCmdLine,
        int nCmdShow) {

    // Create Windows Class

    WNDCLASS windows_class = {};
    windows_class.style = CS_HREDRAW | CS_VREDRAW;
    windows_class.lpszClassName = "Mania Game";
    windows_class.lpfnWndProc = window_callback;

    // Register Class
    RegisterClass(&windows_class);

    // Create Window
    HWND window = CreateWindowA(
            windows_class.lpszClassName, "Mania Game",
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            1280,
            720,
            NULL,
            NULL,
            hInstance,
            NULL);


    // Message Loop
    while (running){

        //input
        MSG message;
        while (PeekMessage(&message,
                           window,
                           0,
                           0,
                           PM_REMOVE)
                           ){
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        //Simulate

        //Render
    }
}
