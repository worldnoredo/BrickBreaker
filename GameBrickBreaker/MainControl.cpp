#include "MainControl.h"
#include <cstdlib>

int MainControl::WIDTH;
int MainControl::HEIGHT;

Ball* ball=nullptr;
Player* player = nullptr;
Bot* bot = nullptr;

Brick* brick[number_brick_y][number_brick_x];
Brick* brick_const;

TextObject game_mark;
TextObject game_level;

Menu menu;
int number_mark = 0;
int number_level = menu.GetLevel();

AlertScreen alert;

MainControl::MainControl()
{
    this->window   = nullptr;
    this->renderer = nullptr;

    this->font_mark = nullptr;
    this->font_level = nullptr;
    this->font_menu = nullptr;

    this->end_loop = false;
    this->move_ball = false;
    this->is_win = false;
    this->start = 0;
    this->replay = false;

    this->chunk_brick = nullptr;
    this->chunk_player = nullptr;
    this->chunk_wall = nullptr;
    this->chunk_win = nullptr;
    this->chunk_lost = nullptr;
    this->music = nullptr;


}

MainControl::~MainControl()
{
    //dtor
    this->window   = nullptr;
    this->renderer = nullptr;

    this->font_mark = nullptr;
    this->font_level = nullptr;
    this->font_menu = nullptr;
    this->font_alert = nullptr;

    this->chunk_brick = nullptr;
    this->chunk_player = nullptr;
    this->chunk_wall = nullptr;
    this->music = nullptr;
}

void MainControl::Init()
{
    WIDTH= 640;
    HEIGHT=640;
    if(SDL_Init(SDL_INIT_EVERYTHING)<0) {
        std::cout<<"Can't Initialize the SDL Libraries"<<SDL_GetError();
        end_loop=true;
        return;
    }

    int imgFlags = IMG_INIT_PNG;
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        std::cout << "SDL_image could not initialize! SDL_image Error: %s\n" << IMG_GetError();
        end_loop = true;
        return;
    }

    window = SDL_CreateWindow("bricker",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN);
    if(window==nullptr) {
        std::cout<<"Can't create Window "<<SDL_GetError();
        end_loop =true;
        return;
    }

    renderer = SDL_CreateRenderer(this->window,-1,0);
    if(renderer==nullptr) {
        std::cout<<"Can't create Renderer"<<SDL_GetError();
        end_loop=true;
        return;
    }
}

void MainControl::LoadObject(int number)
{
    player = new Player();
    ball = new Ball();
    bot = new Bot();

    TileMap tile_map;
    tile_map.LoadTile(number);
    for(int i = 0; i < number_brick_y; i++)
    {
        for(int j = 0; j < number_brick_x; j++)
        {
             brick[i][j] = new Brick() ;
             int y = (i+ 2) * 50;
             int x = (j + 2) * 50;
             int number = tile_map.tile[i][j];
             brick[i][j]->SetLevel(number);
             brick[i][j]->setHitBox(x, y);
        }
    }
    brick_const = new Brick();
    brick_const->setHitBox(0, 40);
    brick_const->SetLevel(4);
}

void MainControl::LoadMusic()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
	{
		std::cout << "Can't open audio" << Mix_GetError();
		end_loop = true;
		return;
	}

	chunk_brick = Mix_LoadWAV("music//va_cham_voi_brick.mp3");
	if (chunk_brick == NULL)
	{
		std::cout << "Can't loadWAV " << Mix_GetError();
		end_loop = true;
		return;
	}

    chunk_player = Mix_LoadWAV("music//va_cham_voi_player.mp3");
    if (chunk_player == NULL)
	{
		std::cout << "Can't loadWAV " << Mix_GetError();
		end_loop = true;
		return;
	}

	chunk_wall = Mix_LoadWAV("music//va_cham_voi_tuong.mp3");
	if (chunk_wall == NULL)
	{
		std::cout << "Can't loadWAV " << Mix_GetError();
		end_loop = true;
		return;
	}

	chunk_win = Mix_LoadWAV("music//nhacthang.mp3");
	if (chunk_win == NULL)
	{
		std::cout << "Can't loadWAV " << Mix_GetError();
		end_loop = true;
		return;
	}

	chunk_lost = Mix_LoadWAV("music//nhacthua.mp3");
	if (chunk_wall == NULL)
	{
		std::cout << "Can't loadWAV " << Mix_GetError();
		end_loop = true;
		return;
	}

	music = Mix_LoadMUS("music/nhacnen.mp3");
	if (music == NULL)
	{
		std::cout << "Can't loadMUS " << Mix_GetError();
		end_loop = true;
		return;
	}
}

void MainControl::LoadText()
{
    if(TTF_Init() < 0)
    {
        std::cout << "Cant't open TTF_Init: " << TTF_GetError();
        end_loop = true;
        return;
    }

    font_mark = TTF_OpenFont("text//emmasophia.ttf", 15);
    if(font_mark == nullptr)
    {
        std::cout << "Can't create Font: " << TTF_GetError();
        end_loop = true;
        return;
    }

    game_mark.SetColor(TextObject::BLUE_COLOR);
    game_mark.SetRect(10, 5);

    font_level = TTF_OpenFont("text//emmasophia.ttf", 15);
    game_level.SetColor(TextObject::BLUE_COLOR);
    game_level.SetRect(650- 110, 5);

    font_menu = TTF_OpenFont("text//Bubblegum.ttf", 70);
    if(font_menu == nullptr)
    {
        std::cout << "Can't create Font: " << TTF_GetError();
        end_loop = true;
        return;
    }
    menu.LoadTextMenu();

    font_alert = TTF_OpenFont("text//type.ttf", 15);
    if(font_alert == nullptr)
    {
        std::cout << "Can't create Font: " << TTF_GetError();
        end_loop = true;
        return;
    }
    alert.LoadTextMenu();
}


bool MainControl::clearmap()
{
    for(int i = 0; i < number_brick_y; i++)
        for(int j = 0; j < number_brick_x; j++)
            if (brick[i][j]->GetLevel() != 0) return false;
    return true;
}

bool MainControl::isCollided(SDL_Rect rect1 , SDL_Rect rect2 )
{
    bool isCollided = 0;
    if((rect1.x <= rect2.x   && rect2.x <= rect1.x + rect1.w ) || (rect2.x <= rect1.x  && rect1.x <= rect2.x + rect2.w ))
    {
        if((rect1.y <= rect2.y  && rect2.y <= rect1.y + rect1.h ) || (rect2.y <= rect1.y   && rect1.y <= rect2.y + rect2.h) )
        {
            isCollided = 1;
        }
    }
    return isCollided;
}

void MainControl::collisionOfBallAndPlayer()
{
    if(ball->getY() == HEIGHT - player->PLAYER_HITBOX_HEIGHT - ball->BALL_HITBOX_HEIGHT - 1||
       ball->getY() == HEIGHT - player->PLAYER_HITBOX_HEIGHT - ball->BALL_HITBOX_HEIGHT - 2)
    {
        if(ball->getY_Velocity() > 0)
        {
            ball->setX_Y_Velocity(1,1);
        }
    }
    if(ball->getY() == HEIGHT - player->PLAYER_HITBOX_HEIGHT - ball->BALL_HITBOX_HEIGHT )
    {
        if (!Mix_Playing(-1))
            Mix_PlayChannel(-1, chunk_player, 0);
        if(ball->getX() >= player->getX() - ball->BALL_HITBOX_WIDTH
        && ball->getX() < player->getX() + player->PLAYER_HITBOX_WIDTH / 4)
        {
            if(ball->getX_Velocity() > 0)
            {
                ball->setX_Y_Velocity(-2,2 * ball->getY_Velocity() );
            }
            if(ball->getX_Velocity() < 0)
            {
                ball->reverseY_Velocity();
            }
        }
        if(ball->getX() >= player->getX() + player->PLAYER_HITBOX_WIDTH / 4
        && ball->getX() < player->getX() + player->PLAYER_HITBOX_WIDTH / 2)
        {
            ball->setX_Y_Velocity(-1,-2);
        }
        if(ball->getX() >= player->getX() + player->PLAYER_HITBOX_WIDTH / 2
        && ball->getX() < player->getX() + 3 * player->PLAYER_HITBOX_WIDTH / 4)
        {
            ball->setX_Y_Velocity(1,-2);
        }
        if(ball->getX() >= player->getX() + 3* player->PLAYER_HITBOX_WIDTH / 4
        && ball->getX() <= player->getX() +  player->PLAYER_HITBOX_WIDTH )
        {
            ball->setX_Y_Velocity(2, -2);
        }
    }

}

void MainControl::collisionOfBallAndBrick()
{
    for(int i = 0; i < number_brick_y; i++)
    {
        for(int j = 0; j < number_brick_x; j++)
        {
            if(isCollided(ball->getHitBox(), brick[i][j]->getHitBox()) == 1 )
            {
                if (!Mix_Playing(-1))
                    Mix_PlayChannel(-1, chunk_brick, 0);

                SDL_Rect tempBallHitBox = ball->getHitBox();
                tempBallHitBox.x -= ball->getX_Velocity();

                if(isCollided(tempBallHitBox, brick[i][j]->getHitBox()) == 0)
                {
                    ball->reverseX_Velocity();
                }
                else
                {
                    ball->reverseY_Velocity();
                }
                int number = brick[i][j]->GetLevel() - 1;
                brick[i][j]->SetLevel(number);
                number_mark++;
            }
        }
    }

}

void MainControl::botAction()
{
    bot->catchMotionOfBall(ball->getX(), ball->getY());
    if (ball->getY_Velocity()<0)
    if(isCollided(ball->getHitBox(), bot->getHitBox()) == true)
    {
        SDL_Rect tempBallHitBox = ball->getHitBox();
        tempBallHitBox.x -= ball->getX_Velocity();
        if(isCollided(tempBallHitBox, bot->getHitBox()) == 0)
        {
            ball->reverseX_Velocity();
        }
        else
        {
            ball->reverseY_Velocity();
        }
        if (!Mix_Playing(-1))
            Mix_PlayChannel(-1, chunk_player, 0);
    }
    bot->backToCenter(ball->getY());
}

void MainControl::endGame()
{
    if(number_level%2)
    {
        if(clearmap() == true)
        {
            is_win = true;
            start = 2;
            move_ball = false;

        }
        else if(ball->getY() > HEIGHT- player->PLAYER_HITBOX_HEIGHT)
        {
            is_win = false;
            start = 2;
            move_ball = false;
        }
        else if(ball->getY() < 50)
        {
            if (!Mix_Playing(-1))
            Mix_PlayChannel(-1, chunk_wall, 0);
            ball->reverseY_Velocity();
        }

        bot->setHitBox(-100, -100);
    }
    if((number_level+1)%2)
    {
        if(ball->getY() > HEIGHT- player->PLAYER_HITBOX_HEIGHT)
        {
            is_win = false;
            start = 2;
            move_ball = false;
        }
        else if(ball->getY() < 50)
        {
            is_win = true;
            start = 2;
            move_ball = false;
        }
    }
    if(number_level == 7) end_loop = true;
}

void MainControl::handleEvent()
{
    SDL_PollEvent(&event);
    player->handleEvent(event);


    if(alert.handleEvent(event) == 2) end_loop = true;
    if(alert.handleEvent(event) == 3 )
    {
        start = 1;
        number_level++;
        LoadObject(number_level);
        std::cout << number_level;
        event.key.keysym.sym = SDLK_0;
    }

    if(alert.handleEvent(event) == 4)
    {
        start = 1;
        number_mark=0;
        LoadObject(number_level);

    }
    if(end_loop == false)
    {
        while(SDL_PollEvent(&event));
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    end_loop = true;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_UP)
                        move_ball = true;
                    if(event.key.keysym.sym == SDLK_DOWN)
                        move_ball = false;
                    break;
                default :
                    break;
            }
        }
    }
        if(menu.handleEvent(event) == 1)
        {
            start = 1;
            number_level = menu.GetLevel();
            LoadObject(number_level);
        }
}

void MainControl::update()
{
    endGame();
    collisionOfBallAndPlayer();
    collisionOfBallAndBrick();
    {
    int chance=rand()%100+1;
    if (chance<=bot->bot_chance) botAction();
    }
    std::string str_mark = ("Mark: ");
    str_mark += std::to_string(number_mark);
    game_mark.SetText(str_mark);

    std::string str_level = ("Level: ");
    str_level += std::to_string(number_level);
    game_level.SetText(str_level);

    if(move_ball == true)
    {
        ball->update();
        player->update();
    }
    if((number_level+1)%2)bot->update();
}

void MainControl::render()
{
    SDL_RenderClear(renderer);
    if(start == 0)
    {
        menu.ShowMenu(renderer, font_menu);
        //ball->render(renderer);
    }
    else if(end_loop == false)
    {
        if(start >= 2) alert.ShowMenu(renderer, font_alert, is_win);
        if (!Mix_PlayingMusic()) Mix_PlayMusic(music, -1);
        int y = ball->getY();
        ball->render(renderer);
        player->render(renderer);

        if(number_level%2)
        {
            for(int i = 0; i < number_brick_y; i++)
            {
                for(int j = 0; j < number_brick_x; j++)
                {
                    if(brick[i][j]->GetLevel() > 0) brick[i][j]->render(renderer);
                    else brick[i][j]->setHitBox(-100,-100);
                }
            }
        }

        if((number_level+1)% 2)
        {
            bot->render(renderer);

            for(int i = 0; i < number_brick_y; i++)
            {
                for(int j = 0; j < number_brick_x; j++)
                {
                    brick[i][j]->SetLevel(0);
                    brick[i][j]->setHitBox(-100,-100);
                }
            }
        }
        brick_const->render(renderer);

        game_mark.CreateGameText(font_mark, renderer);
        game_level.CreateGameText(font_level, renderer);

        SDL_SetRenderDrawColor(renderer,8,16,36,1);

    }

    SDL_RenderPresent(renderer);
}
void MainControl::delay()
{
    SDL_Delay(6-number_level/2);
}

void MainControl::close()
{
    SDL_DestroyWindow(this->window);
    SDL_DestroyRenderer(this->renderer);
    Mix_CloseAudio();

    SDL_Quit();
}
