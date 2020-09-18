#ifndef MAINCONTROL_H_INCLUDED
#define MAINCONTROL_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Player.h"
#include "Ball.h"
#include "Bot.h"
#include "TileMap.h"
#include "Brick.h"
#include "TextObject.h"
#include "Menu.h"
#include "AlertScreen.h"



class MainControl
{
    public:
        virtual ~MainControl();
        MainControl();
        void Init();
        void LoadObject(int number);
        void LoadMusic();
        void LoadText();

        bool clearmap();
        void resetmap();

        bool isCollided(SDL_Rect rect1, SDL_Rect rect2);
        void collisionOfBallAndPlayer();
        void collisionOfBallAndBrick();
        void botAction();

        bool isEndLoop() const {return end_loop;};
        void endGame();

        void handleEvent();
        void update();
        void render();
        void close();
        void delay();
        static int WIDTH ;
        static int HEIGHT;

    private:
        SDL_Window *window;
        SDL_Renderer *renderer;

        TTF_Font* font_mark;
        TTF_Font* font_level;
        TTF_Font* font_menu;
        TTF_Font* font_alert;


        SDL_Event event;
        bool end_loop;
        bool move_ball;
        int is_win;
        int start;
        bool replay;

        Mix_Chunk* chunk_brick;
        Mix_Chunk* chunk_player;
        Mix_Chunk* chunk_wall;
        Mix_Chunk* chunk_win;
        Mix_Chunk* chunk_lost;
        Mix_Music* music;
};

#endif // MAINCONTROL_H_INCLUDED
