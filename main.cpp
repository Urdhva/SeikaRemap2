#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <new>

#include "main.h"

#define CHANGE_TITLE 4

HMENU hMenu;
HWND hEdit, hLogo ;
HICON hImg, hGenerateImg;

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
    switch(uMsg)
    {
    case WM_COMMAND:
    {    
        switch(wParam)
        {
        case 1:
            MessageBox(hwnd, L"I love Old-Kimchi", L"Okay", 1);
            break;
        }
        case CHANGE_TITLE:
            wchar_t text[100];
            GetWindowTextW(hEdit, text, 100);
            SetWindowTextW(hwnd, text);
            break;
    }
    return 0;
    case WM_CREATE:
    {
        DefWindowProc(hwnd, uMsg, wParam, lParam);
        DisplayImage(hwnd);
        AddControls(hwnd);
        AddMenus(hwnd);
    }
    return 0 ;       
    case WM_DESTROY:
    {
        //this is self explanatory
        PostQuitMessage(0);
    }
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

    return 0;
}

void AddMenus(HWND hwnd){
    hMenu = CreateMenu();

    //always check data type and fill in a random value when you want to test. 
    AppendMenuW(hMenu, MF_STRING, 1, L"File");
    AppendMenuW(hMenu, MF_STRING, 2, L"Edit");
    AppendMenuW(hMenu, MF_STRING, 3, L"Selection");
    AppendMenuW(hMenu, MF_STRING, 5, L"View");

    SetMenu(hwnd, hMenu);
}

//windowProc defines the behavior of the window. How the window interacts
//with the user and all
void AddControls(HWND hwnd)
{
    // CreateWindowW(L"Static", L"FirstWindow", WS_VISIBLE | WS_BORDER | SS_CENTER | WS_CHILD, 200, 100, 100, 50, hwnd, NULL, NULL, NULL);
    hEdit = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL
        , 200, 152, 100, 152, hwnd, NULL, NULL, NULL);

    CreateWindowW(L"Button", L"Change Title", WS_VISIBLE | WS_CHILD,  200, 204, 100, 50, hwnd, (HMENU)CHANGE_TITLE, NULL, NULL);

    hLogo = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_ICON, 350, 60, 100, 100, hwnd, NULL, NULL, NULL);
    SendMessageW(hLogo, STM_SETIMAGE, IMAGE_ICON, (LPARAM)hImg);
}

void DisplayImage(HWND hwnd)
{
    //we need to take a handle
    //loading the image into the handler
    hImg = (HICON)LoadImageW(NULL, L"Ruriko-in4.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

}
