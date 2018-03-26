#pragma once

#include <GLFW/glfw3.h>

class EventHandler
{
    public:
        void onKeyboardInput();
        void onMouseInput();
        void onResume();
        void onPause();
        void onTick();
    protected:
        //
    private:
        
};
