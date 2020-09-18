#include <iostream>
#include <SDL.h>
#include "MainControl.h"


using namespace std;

int main(int agrc, char* argv[])
{
    const int FPS =180;
    const int frame_delay =1000/FPS;
    Uint32 time=0;

    MainControl main_control = MainControl();
    main_control.Init();
    main_control.LoadObject(1);
    main_control.LoadMusic();
    main_control.LoadText();
    while(!main_control.isEndLoop())
    {
//        main_control.resetmap();
        main_control.handleEvent();                 //get the user event
        main_control.update();
        main_control.render();
        main_control.delay();//-time/20000);
    }
    main_control.close();
    return 0;
}
