/**
 * *** This file is part of Luolapeli ***
 * 
 * 
 */


#ifndef _RESOURCES_H_
#define _RESOURCES_H_

#include <SDL.h>
#include <SDL_mixer.h>

#include "Font.h"


class Resources 
{
protected:

    /**
     * Constructor.
     */
    Resources(
        SDL_Window* const window, 
        SDL_Renderer* const renderer
    );


    /**
     * Destructor that calls Free.
     */
    ~Resources(
    );


    /**
     * Loads game assets.
     */
    auto Load(
    ) -> void;


    /**
     * Frees game assets.
     */
    auto Free(
    ) noexcept -> void;


protected:
    SDL_Surface* m_TilesetSurface;
    SDL_Texture* m_Tileset;

    SDL_Surface* m_PlayerSurface;
    SDL_Texture* m_Player;

    SDL_Surface* m_KeySurface;
    SDL_Texture* m_Key;

    SDL_Surface* m_StoneSurface;
    SDL_Texture* m_Stone;

    Font* m_Font;

    Mix_Chunk* m_AudioFootstep; // Played every time player takes a step
    Mix_Chunk* m_AudioPickKey;  // Played when player picks a key
    Mix_Chunk* m_AudioFanfare;  // Played when player finds exit tile
    Mix_Music* m_Music;         // Background music


private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

};

#endif  // _RESOURCES_H_