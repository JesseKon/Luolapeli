/**
 * *** This file is part of Luolapeli ***
 * 
 * 
 */

#ifndef _LUOLAPELI_H_
#define _LUOLAPELI_H_

#include <iostream>
#include <string>
#include <stdexcept>

#include <SDL.h>
#include <SDL_mixer.h>

#include "Constants.h"
#include "Menu.h"


class Luolapeli
{
public:

    /**
     * 
     */
    Luolapeli(
        const std::uint32_t screenWidth,
        const std::uint32_t screenHeight,
        const std::string& screenTitle
    );


    /**
     * 
     */
    ~Luolapeli(
    );


    /**
     * Destroys menu and quits SDL.
     */
    auto Destroy(
    ) noexcept -> void;


private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;
    Menu* m_Menu;

};

#endif