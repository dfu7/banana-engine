#include "Zyla.h"

#include <iostream>
#include "Global.h"
#include "Physics.h"

void Zyla::InitializeScene()
{
    // coin counter ui [this is so bad rn omg]

    TTF_Init();

    Sans = TTF_OpenFont("OpenSans-Bold.ttf", 24);

    numStr = std::to_string(0);
    strcpy_s(tab2, numStr.c_str());

    CoinTextSurface = TTF_RenderText_Solid(Sans, tab2, White);
    CoinText = SDL_CreateTextureFromSurface(Global::renderer, CoinTextSurface);
    CoinTextRect.x = Global::SCREEN_WIDTH - 30;
    CoinTextRect.y = 0;
    CoinTextRect.w = 30;
    CoinTextRect.h = 30;

    // inventory ui

    ui_hotbar = Global::Spawn<Entity>("hotbar.bmp", 50, 50, false);
    ui_hotbar->bounds.w = Global::SCREEN_WIDTH * 0.4f;
    ui_hotbar->bounds.h = Global::SCREEN_HEIGHT * 0.1f;
    // gameplay setup

    rupee = Global::Spawn<Entity>(
        "rupee.bmp", 
        Global::RandomFloatInRange(0.f, static_cast<float>(Global::SCREEN_WIDTH)),
        Global::RandomFloatInRange(0.f, static_cast<float>(Global::SCREEN_HEIGHT)), 
        true
    );

    player = Global::Spawn<Player>("link.bmp", Global::SCREEN_CENTER_X, Global::SCREEN_CENTER_Y, true);

    // shop setup
    
    layerManager = new LayerManager(7);
    shop = new Shop(4, layerManager);

    r1 = Global::Spawn<Entity>("rupee.bmp", Global::RandomFloatInRange(0.f, static_cast<float>(Global::SCREEN_WIDTH)), Global::RandomFloatInRange(0.f, static_cast<float>(Global::SCREEN_HEIGHT)), false);
    r2 = Global::Spawn<Entity>("rupee.bmp", Global::RandomFloatInRange(0.f, static_cast<float>(Global::SCREEN_WIDTH)), Global::RandomFloatInRange(0.f, static_cast<float>(Global::SCREEN_HEIGHT)), false);
    r3 = Global::Spawn<Entity>("rupee.bmp", Global::RandomFloatInRange(0.f, static_cast<float>(Global::SCREEN_WIDTH)), Global::RandomFloatInRange(0.f, static_cast<float>(Global::SCREEN_HEIGHT)), false);
    r4 = Global::Spawn<Entity>("rupee.bmp", Global::RandomFloatInRange(0.f, static_cast<float>(Global::SCREEN_WIDTH)), Global::RandomFloatInRange(0.f, static_cast<float>(Global::SCREEN_HEIGHT)), false);

    shop->AddItem(r1, 100);
    shop->AddItem(r2, 100);
    shop->AddItem(r3, 100);
    shop->AddItem(r4, 100);

    // store entities

    allEntities.push_back(r1);
    allEntities.push_back(r2);
    allEntities.push_back(r3);
    allEntities.push_back(r4);
    allEntities.push_back(player);
    allEntities.push_back(rupee);
    allEntities.push_back(ui_hotbar);

    layerManager->AddEntityToRender(ui_hotbar, 4);
    layerManager->AddEntityToRender(rupee, 3);
    layerManager->AddEntityToRender(player, 3);
    layerManager->AddEntityToRender(r1, 5);
    layerManager->AddEntityToRender(r2, 5);
    layerManager->AddEntityToRender(r3, 2);
    layerManager->AddEntityToRender(r4, 5);
}

void Zyla::RunScene()
{ 
    while (isActive)
    {
        Global::UpdateVariables(); // move to another thread and put somewhere else?
        layerManager->UpdateEntities();

        // handle input & player movement
        SDL_Event e;
        SDL_PumpEvents();
        
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                isActive = false;
                break;
            case SDL_KEYDOWN:
                if (e.key.keysym.sym == SDLK_e && e.key.repeat == 0)
                {
                    if (!shop->isOpen)
                    {
                        shop->OpenShop();
                    }
                    else
                    {
                        shop->CloseShop();
                    }
                }
                if (shop->isOpen && e.key.keysym.sym == SDLK_a && e.key.repeat == 0)
                {
                    shop->MoveIndicatorLeft();
                }
                if (shop->isOpen && e.key.keysym.sym == SDLK_d && e.key.repeat == 0)
                {
                    shop->MoveIndicatorRight();
                }
                break;
            }
        }

        float moveX = 0.f;
        float moveY = 0.f;

        if (!shop->isOpen)
        {
            // this needs to be optimized
            if (currentKeyStates[SDL_SCANCODE_W])
            {
                moveY -= 1;
            }
            if (currentKeyStates[SDL_SCANCODE_A])
            {
                moveX -= 1;
            }
            if (currentKeyStates[SDL_SCANCODE_S])
            {
                moveY += 1;
            }
            if (currentKeyStates[SDL_SCANCODE_D])
            {
                moveX += 1;
            }

            player->Move(moveX, moveY);
        }


        // check collision if moved
        if (moveX != 0 || moveY != 0)
        {
            if (Physics::CheckCollision(player, rupee))
            {
                player->addCoins(1);

                // randomly relocate coin
                rupee->SetLocation(
                    Global::RandomFloatInRange(0.f, static_cast<float>(Global::SCREEN_WIDTH)),
                    Global::RandomFloatInRange(0.f, static_cast<float>(Global::SCREEN_HEIGHT))
                );
            }
        }

        // update coin ui
        numStr = std::to_string(player->getCoins());
        strcpy_s(tab2, numStr.c_str());

        CoinTextSurface = TTF_RenderText_Solid(Sans, tab2, White);
        CoinText = SDL_CreateTextureFromSurface(Global::renderer, CoinTextSurface);
        SDL_RenderCopy(Global::renderer, CoinText, NULL, &CoinTextRect);

        // forces 60 fps?
        SDL_Delay(1000 / 60);
    }

    SDL_FreeSurface(CoinTextSurface);
    SDL_DestroyTexture(CoinText);
}
