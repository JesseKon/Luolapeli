/**
 * *** This file is part of Luolapeli ***
 * 
 * 
 */

#include "Resources.h"


/* ********************************************************************************************* */
Resources::Resources(
    SDL_Window* const window,
    SDL_Renderer* const renderer
)
{
    if (!window || !renderer) {
        // TODO: throw
    }

    m_Window = window;
    m_Renderer = renderer;

    m_TilesetSurface = nullptr;
    m_Tileset = nullptr;
    m_PlayerSurface = nullptr;
    m_Player = nullptr;
    m_KeySurface = nullptr;
    m_Key = nullptr;
    m_StoneSurface = nullptr;
    m_Stone = nullptr;

    m_Font = nullptr;

    m_Music = nullptr;
    m_AudioFanfare = nullptr;
    m_AudioPickKey = nullptr;
    m_AudioFootstep = nullptr;

    Load();
}


/* ********************************************************************************************* */
Resources::~Resources(
)
{
    Free();
}


/* ********************************************************************************************* */
auto Resources::Load(
) -> void
{
    // Load font
    m_Font = new Font("Data/font.bmp", m_Window, m_Renderer);

    // Tilemap texture
    m_TilesetSurface = SDL_LoadBMP("Data/tilemap_bmp.bmp");
    if (!m_TilesetSurface) {
        Free();
        std::string errorMsg("Error while loading resources: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    if (SDL_SetColorKey(m_TilesetSurface, SDL_TRUE, 0xFFFFFF) != 0) {
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    m_Tileset = SDL_CreateTextureFromSurface(m_Renderer, m_TilesetSurface);
    if (!m_Tileset) {
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    // Player texture
    m_PlayerSurface = SDL_LoadBMP("Data/player_bmp.bmp");
    if (!m_PlayerSurface) {
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    if (SDL_SetColorKey(m_PlayerSurface, SDL_TRUE, 0xFFFFFF) != 0) {
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    m_Player = SDL_CreateTextureFromSurface(m_Renderer, m_PlayerSurface);
    if (!m_Player) {
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    // Key texture
    m_KeySurface = SDL_LoadBMP("Data/key_bmp.bmp");
    if (!m_KeySurface) {
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    if (SDL_SetColorKey(m_KeySurface, SDL_TRUE, 0xFFFFFF) != 0) {
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    m_Key = SDL_CreateTextureFromSurface(m_Renderer, m_KeySurface);
    if (!m_Key) {
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    // Stone texture
    m_StoneSurface = SDL_LoadBMP("Data/stone_bmp.bmp");
    if (!m_StoneSurface) {
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    if (SDL_SetColorKey(m_StoneSurface, SDL_TRUE, 0xFFFFFF) != 0) {
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    m_Stone = SDL_CreateTextureFromSurface(m_Renderer, m_StoneSurface);
    if (!m_Stone) {
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
    }

    // Foot step sound effect
    m_AudioFootstep = Mix_LoadWAV("Data/foot_step.ogg");
    if (!m_AudioFootstep) {
#ifndef NDEBUG
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
#else
        std::cout << "Warning: " << SDL_GetError() << std::endl;
#endif
    }

    // Key picking sound effect
    m_AudioPickKey = Mix_LoadWAV("Data/pick_key.ogg");
    if (!m_AudioPickKey) {
#ifndef NDEBUG
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
#else
        std::cout << "Warning: " << SDL_GetError() << std::endl;
#endif
    }

    // Fanfare sound effect
    m_AudioFanfare = Mix_LoadWAV("Data/fanfare.ogg");
    if (!m_AudioFanfare) {
#ifndef NDEBUG
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
#else
        std::cout << "Warning: " << SDL_GetError() << std::endl;
#endif
    }

    // Background music
    m_Music = Mix_LoadMUS("Data/music.ogg");
    if (!m_Music) {
#ifndef NDEBUG
        Free();
        std::string errorMsg("Error: " + std::string(SDL_GetError()) + '\n');
        throw std::runtime_error(errorMsg);
#else
        std::cout << "Warning: " << SDL_GetError() << std::endl;
#endif
    }

    std::cout << "Resources loaded successfully!" << std::endl;
}



/* ********************************************************************************************* */
auto Resources::Free(
) noexcept -> void
{
    if (m_Font) {
        delete m_Font;
        m_Font = nullptr;
    }

    if (m_Tileset) {
        SDL_DestroyTexture(m_Tileset);
        m_Tileset = nullptr;
    }

    if (m_TilesetSurface) {
        SDL_FreeSurface(m_TilesetSurface);
        m_TilesetSurface = nullptr;
    }

    if (m_Player) {
        SDL_DestroyTexture(m_Player);
        m_Player = nullptr;
    }

    if (m_PlayerSurface) {
        SDL_FreeSurface(m_PlayerSurface);
        m_PlayerSurface = nullptr;
    }

    if (m_Key) {
        SDL_DestroyTexture(m_Key);
        m_Key = nullptr;
    }

    if (m_KeySurface) {
        SDL_FreeSurface(m_KeySurface);
        m_KeySurface = nullptr;
    }

    if (m_Stone) {
        SDL_DestroyTexture(m_Stone);
        m_Stone = nullptr;
    }

    if (m_StoneSurface) {
        SDL_FreeSurface(m_StoneSurface);
        m_StoneSurface = nullptr;
    }

    if (m_AudioFanfare) {
        Mix_FreeChunk(m_AudioFanfare);
        m_AudioFanfare = nullptr;
    }

    if (m_AudioPickKey) {
        Mix_FreeChunk(m_AudioPickKey);
        m_AudioPickKey = nullptr;
    }

    if (m_AudioFootstep) {
        Mix_FreeChunk(m_AudioFootstep);
        m_AudioFootstep = nullptr;
    }

    if (m_Music) {
        Mix_FreeMusic(m_Music);
        m_Music = nullptr;
    }

    std::cout << "Resources freed from memory" << std::endl;
}