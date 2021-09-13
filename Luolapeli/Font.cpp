/**
 * *** This file is part of Luolapeli ***
 *
 *
 */

#include "font.h"


/* ********************************************************************************************* */
Font::Font(
    const std::string& fontMap, 
    SDL_Window* window, 
    SDL_Renderer* renderer
)
{
    if (!window || !renderer) {
        // TODO: throw
    }

    m_Window = window;
    m_Renderer = renderer;
    m_FontSurface = nullptr;
    m_Font = nullptr;

    Load(fontMap);
}


/* ********************************************************************************************* */
Font::~Font(
)
{
    Free();
}


/* ********************************************************************************************* */
auto Font::Load(
    const std::string& fontMap
) noexcept -> void
{
    // Font texture
    m_FontSurface = SDL_LoadBMP(fontMap.c_str());
    if (!m_FontSurface) {
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    if (SDL_SetColorKey(m_FontSurface, SDL_TRUE, 0x000000) != 0) {
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    m_Font = SDL_CreateTextureFromSurface(m_Renderer, m_FontSurface);
    if (!m_Font) {
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }
}


/* ********************************************************************************************* */
auto Font::Free(
) noexcept -> void
{
    if (m_Font) {
        SDL_DestroyTexture(m_Font);
        m_Font = nullptr;
    }

    if (m_FontSurface) {
        SDL_FreeSurface(m_FontSurface);
        m_FontSurface = nullptr;
    }
}


/* ********************************************************************************************* */
auto Font::Write(
    const std::string& str,
    const std::int32_t posX,
    const std::int32_t posY,
    const std::uint8_t r,
    const std::uint8_t g,
    const std::uint8_t b
) noexcept -> void
{
    // Set text color
    SDL_SetTextureColorMod(m_Font, r, g, b);

    for (std::size_t i = 0; i < str.length(); ++i) {
        char c = std::tolower(str[i]);

        /*
          Numbers are on the first line of the font map
          number 0 ASCII is 48
        */
        if (c >= '0' && c <= '9') {
            SDL_Rect source = { s_FontWidth * (int(c) - 48), s_FontHeight * 0, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }

        /*
          Letters are on the third line of the font map
          letter 'a' ASCII is 97
        */
        if (c >= 'a' && c <= '}') {
            SDL_Rect source = { s_FontWidth * (int(c) - 97), s_FontHeight * 2, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }

        /*
          Special characters
          TODO: clean up
        */
        if (c == '.') {
            SDL_Rect source = { s_FontWidth * 0, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == ',') {
            SDL_Rect source = { s_FontWidth * 1, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == '!') {
            SDL_Rect source = { s_FontWidth * 2, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == '?') {
            SDL_Rect source = { s_FontWidth * 3, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == '\'') {
            SDL_Rect source = { s_FontWidth * 4, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == '\"') {
            SDL_Rect source = { s_FontWidth * 5, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == '€') {
            SDL_Rect source = { s_FontWidth * 6, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == '$') {
            SDL_Rect source = { s_FontWidth * 7, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == '%') {
            SDL_Rect source = { s_FontWidth * 8, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == '&') {
            SDL_Rect source = { s_FontWidth * 9, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == '+') {
            SDL_Rect source = { s_FontWidth * 10, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == '-') {
            SDL_Rect source = { s_FontWidth * 11, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == '*') {
            SDL_Rect source = { s_FontWidth * 12, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == '/') {
            SDL_Rect source = { s_FontWidth * 13, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == '(') {
            SDL_Rect source = { s_FontWidth * 14, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == ')') {
            SDL_Rect source = { s_FontWidth * 15, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == ':') {
            SDL_Rect source = { s_FontWidth * 16, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
        else if (c == ';') {
            SDL_Rect source = { s_FontWidth * 17, s_FontHeight * 1, s_FontWidth, s_FontHeight };
            SDL_Rect dest = { posX + i * s_FontWidth, posY, s_FontWidth, s_FontHeight };
            SDL_RenderCopy(m_Renderer, m_Font, &source, &dest);
        }
    }
}