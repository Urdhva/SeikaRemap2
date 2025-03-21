#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <new>

#include "main.h"

HMENU hMenu;

//this is the program entry point 
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    //this is a pointer to a function, thats why no parenthesis
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;      //the class name we defined

    RegisterClass(&wc);

    // StateInfo* pState = new (std::nothrow) StateInfo;
    // if(!RegisterClassW(&wc))    return -1;      //if window fails to load, return -1

    //so this is a data structure apparently.
    //keep this structure same for every window
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

    //the get message loop keeps running to take input/messages from the user. 
    //the function removes the first message at the head of the queue
    MSG msg = {};       //this is actually a structure - handles all kinds of messages (keyboard and mouse)
    while(GetMessage(&msg, NULL, 0,0) > 0){
        //takes messages from the keyboard and translates it. 
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    } 

    return 0;
}

//this stands for window procedure
//basically - wParam and lParam are defined based on uMsg.
//uMsg tells us what message is being passed. wParam and lParam gives properties of that message
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    //this whole function is used as a switch case for *messages* from windows
    switch(uMsg){
        case WM_COMMAND:
            switch(wParam)
            {
            case 1:
                MessageBox(hwnd, L"I love Old-Kimchi", L"Okay", 1);
            }
            return 0;
        case WM_CREATE:
        {
            DefWindowProc(hwnd, uMsg, wParam, lParam);
            AddMenus(hwnd);
        }
        return 0 ;       
        case WM_DESTROY:
            //this is self explanatory
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
        default: 
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

void AddMenus(HWND hwnd){
    hMenu = CreateMenu();

    //always check data type and fill in a random value when you want to test. 
    AppendMenuW(hMenu, MF_STRING, 1, L"File");
    AppendMenuW(hMenu, MF_STRING, 2, L"Edit");
    AppendMenuW(hMenu, MF_STRING, 3, L"Selection");
    AppendMenuW(hMenu, MF_STRING, 4, L"View");

    SetMenu(hwnd, hMenu);
}


//windowProc defines the behavior of the window. How the window interacts
//with the user and all

