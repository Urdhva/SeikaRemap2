#pragma once

#include <windows.h>

#include <string>
#include <functional>

namespace ichiji
{
    class Seika
    {
    private:
        HINSTANCE hInstance;
        HWND windowHandle;
        bool running = false;

        std::wstring windowTitle;
        int windowHeight;
        int windowWidth;

        //user defined game update function
        std::function<void(float delta)> update;

        void startWindow();

    public:
        //all of this is to create a singleton instance - aka not more than once instance of the app is running
        Seika(){};      //default constructor
        Seika(const Seika&) = delete;
        Seika& operator=(const Seika&) = delete;

        ~Seika() {}

        inline static Seika& getInstance(){
            static Seika seika;
            return seika;
        }

        inline static void start(){
            getInstance().startWindow();
        }

        inline static void setGameUpdate(const std::function<void(float delta)>& update){
            //update is a variable
            getInstance().update = update;
        }

        inline std::wstring getWindowTitle(){return getInstance().windowTitle;}
        inline int getWindowHeight(){return getInstance().windowHeight;}
        inline int getWindowWidth(){return getInstance().windowWidth;}



    };
}

ichiji::Seika startWindow(){
    //don't use wchar - try with basic char first
    const char* className = "ichijiWindow";
    WNDCLASS windowClass = {};
    
}