/**
 * *** This file is part of Luolapeli ***
 * 
 * 
 */

#ifndef _FONT_H_
#define _FONT_H_

#include <string>
#include <stdexcept>
#include <algorithm>

#include <SDL.h>
#include <iostream>

class Font
{
public:

    /**
     * 
     */
    Font(
        const std::string& fontMap, 
        SDL_Window* window, 
        SDL_Renderer* renderer
    );


    /**
     * 
     */
    ~Font(
    );


    /**
     * Create new font.
     */
    auto Load(
        const std::string& fontMap
    ) noexcept -> void;


    /**
     * Write text to given coordinates.
     * -> str = string to write
     * -> posX = text position x
     * -> posY = text position y
     * -> r = text red color
     * -> g = text green color
     * -> b = text blue color
     */
    auto Write(
        const std::string& str,
        const std::int32_t posX,
        const std::int32_t posY,
        const std::uint8_t r,
        const std::uint8_t g,
        const std::uint8_t b
    ) noexcept -> void;


    /**
     * Frees font resources.
     */
    auto Free(
    ) noexcept -> void;


private:
    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

    SDL_Surface* m_FontSurface;
    SDL_Texture* m_Font;

    static constexpr std::int32_t s_FontWidth = 8;
    static constexpr std::int32_t s_FontHeight = 8;
};

#endif  // _FONT_H_