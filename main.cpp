#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lparam);

//this is the program entry point 
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;      //the class name we defined

    RegisterClass(&wc);

    //create the window


    //so this is a data structure apparently.
    HWND hwnd = CreateWindowEx(
        0,      //window styles like transparency
        CLASS_NAME,         //window class namme i guess
        L"Beginnings",          //window text
        WS_OVERLAPPEDWINDOW,        

        //size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,
        NULL,
        hInstance,
        NULL
    );          //ends with a semicolon, hence a data structure defintion

    if(hwnd == NULL){return 0;}

    ShowWindow(hwnd, nCmdShow);

    //run message loop

    MSG msg = {};
    while(GetMessage(&msg, NULL, 0,0) > 0){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    } 
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg){
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hwnd, &ps);

                //painting occurs here
                FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
                EndPaint(hwnd, &ps);
            }
            return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//windowProc defines the behavior of the window. How the window interacts
//with the user and all

