/**
 * *** This file is part of Luolapeli ***
 * 
 * 
 */

#include "Luolapeli.h"


/* ********************************************************************************************* */
Luolapeli::Luolapeli(
    const std::uint32_t screenWidth,
    const std::uint32_t screenHeight,
    const std::string& screenTitle
)
{
    m_Window = nullptr;
    m_Renderer = nullptr;
    m_Menu = nullptr;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Destroy();
        std::string errorMsg("SDL could not be initialized: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    // Create window
    SDL_Window* m_Window = SDL_CreateWindow(
        screenTitle.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        screenWidth, screenHeight, SDL_WINDOW_SHOWN
    );

    if (!m_Window) {
        Destroy();
        std::string errorMsg("Window could not be created: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    // Create renderer
    SDL_Renderer* m_Renderer = SDL_CreateRenderer(m_Window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!m_Renderer) {
        Destroy();
        std::string errorMsg("Renderer could not be created: " + std::string(SDL_GetError()) + 'n');
        throw std::runtime_error(errorMsg);
    }

    // Init mixer and open audio
    if (!Mix_Init(MIX_INIT_OGG)) {
        Destroy();
        std::string errorMsg("Could not init audio: " + std::string(Mix_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        Destroy();
        std::string errorMsg("Could not init audio: " + std::string(Mix_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    Mix_AllocateChannels(8);

    // Set scale to 2.0 for more pixelated graphical style
    SDL_RenderSetScale(m_Renderer, 2.0f, 2.0f);

    if (SDL_SetRenderDrawBlendMode(m_Renderer, SDL_BLENDMODE_BLEND) != 0) {
        Destroy();
        std::string errorMsg("Could not set draw blend mode: " + std::string(Mix_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    // Start game menu
    m_Menu = new Menu(m_Window, m_Renderer);

    // Quit game after exiting menu
    Destroy();

}


/* ********************************************************************************************* */
Luolapeli::~Luolapeli(
)
{
    Destroy();
}


/* ********************************************************************************************* */
auto Luolapeli::Destroy(
) noexcept -> void
{
    if (m_Menu) {
        delete m_Menu;
        m_Menu = nullptr;
    }

    if (m_Renderer) {
        SDL_DestroyRenderer(m_Renderer);
        m_Renderer = nullptr;
    }

    if (m_Window) {
        SDL_DestroyWindow(m_Window);
        m_Window = nullptr;
    
    }

    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
}