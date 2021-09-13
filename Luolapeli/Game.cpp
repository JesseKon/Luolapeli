/**
 * *** This file is part of Luolapeli ***
 * 
 * 
 */

#include "Game.h"


/* ********************************************************************************************* */
Game::Game(
    SDL_Window* const window, 
    SDL_Renderer* const renderer, 
    const int levelNum, const 
    std::string& levelName
) : Resources(window, renderer)
{
    m_Window = window;
    m_Renderer = renderer;

    m_PlayerPos = { 0, 0 };

    m_RestartLevel = false;
    m_NumOfKeys = 0;

    // Create "build in" levels
    m_LevelData = std::make_unique<LevelData>();
    m_LevelData->CreateLevelData();

    PlayLevel(levelNum, levelName);
}


/* ********************************************************************************************* */
Game::~Game(
)
{

}


/* ********************************************************************************************* */
auto Game::RestartLevel(
) const noexcept -> bool
{
    return m_RestartLevel;
}


/* ********************************************************************************************* */
auto Game::LevelNum(
) const noexcept -> std::int32_t
{
    return m_LevelNum;
}


/* ********************************************************************************************* */
auto Game::PlayLevel(
    const int levelNum, 
    const std::string& levelName
) -> void
{
    m_LevelNum = levelNum;

    // Custom level? 
    if (m_LevelNum == 0) {

        std::ifstream f;
        f.open("Customlevels/" + levelName, std::ios::in | std::ios::binary);

        // TODO: clean up these!
        std::vector<std::vector<std::uint8_t>> levelGraphicalData;
        std::vector<std::vector<std::uint8_t>> levelInformationData;

        // Resize containers
        levelGraphicalData.resize(m_LevelData->s_LevelHeight);
        for (std::size_t i = 0; i < m_LevelData->s_LevelHeight; ++i)
            levelGraphicalData.at(i).resize(m_LevelData->s_LevelWidth);

        levelInformationData.resize(m_LevelData->s_LevelHeight);
        for (std::size_t i = 0; i < m_LevelData->s_LevelHeight; ++i)
            levelInformationData.at(i).resize(m_LevelData->s_LevelWidth);


        // Read from file
        for (std::size_t y = 0; y < m_LevelData->s_LevelHeight; ++y)
            f.read(reinterpret_cast<char*>(levelGraphicalData.at(y).data()), LevelData::s_LevelWidth * sizeof(std::uint8_t));

        for (std::size_t y = 0; y < m_LevelData->s_LevelHeight; ++y)
            f.read(reinterpret_cast<char*>(levelInformationData.at(y).data()), LevelData::s_LevelWidth * sizeof(std::uint8_t));

        if (f.is_open()) f.close();


        // Copy data to a playable level
        for (std::size_t y = 0; y < m_LevelData->s_LevelHeight; ++y) {
            for (std::size_t x = 0; x < m_LevelData->s_LevelWidth; ++x) {
                m_LevelData->SetLevelGraphicalData(0, y, x) = levelGraphicalData.at(y).at(x);
                m_LevelData->SetLevelInformationData(0, y, x) = levelInformationData.at(y).at(x);
            }
        }

    }

    // Tile coordinates
    SDL_Rect tile_rect[NUM_OF_TILES];
    tile_rect[0] = { TILE_WIDTH * 0, TILE_HEIGHT * 0, TILE_WIDTH, TILE_HEIGHT }; // Floor
    tile_rect[1] = { TILE_WIDTH * 1, TILE_HEIGHT * 0, TILE_WIDTH, TILE_HEIGHT }; // Wall
    tile_rect[2] = { TILE_WIDTH * 2, TILE_HEIGHT * 0, TILE_WIDTH, TILE_HEIGHT }; // Door upwards
    tile_rect[3] = { TILE_WIDTH * 3, TILE_HEIGHT * 0, TILE_WIDTH, TILE_HEIGHT }; // Door rightwards
    tile_rect[4] = { TILE_WIDTH * 4, TILE_HEIGHT * 0, TILE_WIDTH, TILE_HEIGHT }; // Locked door upwards
    tile_rect[5] = { TILE_WIDTH * 5, TILE_HEIGHT * 0, TILE_WIDTH, TILE_HEIGHT }; // Locked door rightwards
    tile_rect[6] = { TILE_WIDTH * 2, TILE_HEIGHT * 1, TILE_WIDTH, TILE_HEIGHT }; // Door leftwards
    tile_rect[7] = { TILE_WIDTH * 3, TILE_HEIGHT * 1, TILE_WIDTH, TILE_HEIGHT }; // Door downwards
    tile_rect[8] = { TILE_WIDTH * 4, TILE_HEIGHT * 1, TILE_WIDTH, TILE_HEIGHT }; // Locked door leftwards
    tile_rect[9] = { TILE_WIDTH * 5, TILE_HEIGHT * 1, TILE_WIDTH, TILE_HEIGHT }; // Locked door downwards

    // Find player spawn location
    for (std::int32_t y = 0; y < m_LevelData->s_LevelHeight; ++y) {
        for (std::int32_t x = 0; x < m_LevelData->s_LevelWidth; ++x) {
            std::uint8_t data = m_LevelData->GetLevelInformationData(m_LevelNum, y, x);

            if (data != 1)
                continue;

            // 1 = player
            else if (data == 1) {
                m_PlayerPos = { x, y };
                break;
            }
        }
    }


    // FPS controller
    struct Frame {
        std::uint32_t lastTime = 0;
        std::uint32_t timeElapsed = 0;
    } frame;

    m_StepsTaken = 0;

    {   // Show splash screen before starting level
        SDL_SetRenderDrawColor(m_Renderer, 0x99, 0x79, 0x50, 127);
        SDL_RenderClear(m_Renderer);

        SDL_Rect rect = {
            SCREEN_WIDTH / 8 * 1, SCREEN_HEIGHT / 8 * 1,
            SCREEN_WIDTH / 8 * 2, SCREEN_HEIGHT / 8 * 2
        };

        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 127);
        SDL_RenderFillRect(m_Renderer, &rect);

        std::string str = "starting level ";

        // Write level number if playing build-in levels
        if (m_LevelNum)
            str.append(std::to_string(m_LevelNum));

        // Write level name if playing custom levels
        else
            m_Font->Write(levelName, SCREEN_WIDTH / 8 * 1 + 32, SCREEN_HEIGHT / 8 * 1 + 44, 255, 150, 0);

        m_Font->Write(str, SCREEN_WIDTH / 8 * 1 + 32, SCREEN_HEIGHT / 8 * 1 + 32, 255, 150, 0);

        SDL_RenderPresent(m_Renderer);
        SDL_Delay(1000);
    }

    // Start game loop
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        frame.lastTime = SDL_GetTicks();

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;

            // Player controls
            else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:   // Exit game

                    {
                        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                        SDL_RenderClear(m_Renderer);
                        m_Font->Write("exit level? (y/n)", 32, 100, 255, 20, 0);

                        bool quit_sub = false;
                        SDL_Event e;
                        while (!quit_sub) {

                            // Confirm quit
                            while (SDL_PollEvent(&e)) {
                                if (e.type == SDL_KEYDOWN) {
                                    switch (e.key.keysym.sym) {
                                    case SDLK_y:
                                    case SDLK_RETURN:
                                        quit_sub = true;
                                        quit = true;
                                        break;

                                    case SDLK_n:
                                    case SDLK_ESCAPE:
                                        quit_sub = true;
                                        break;

                                    default:
                                        break;
                                    }
                                }
                            }

                            SDL_RenderPresent(m_Renderer);
                        }
                    }
                    break;

                case SDLK_r: // Restart level
                    {
                        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                        SDL_RenderClear(m_Renderer);
                        m_Font->Write("restart level? (y/n)", 32, 100, 255, 20, 0);

                        bool quit_sub = false;
                        SDL_Event e;
                        while (!quit_sub) {

                            // Confirm restart level
                            while (SDL_PollEvent(&e)) {
                                if (e.type == SDL_KEYDOWN) {
                                    switch (e.key.keysym.sym) {
                                    case SDLK_y:
                                    case SDLK_RETURN:
                                        m_RestartLevel = true;
                                        quit_sub = true;
                                        quit = true;
                                        break;

                                    case SDLK_n:
                                    case SDLK_ESCAPE:
                                        quit_sub = true;
                                        break;

                                    default:
                                        break;
                                    }
                                }
                            }

                            SDL_RenderPresent(m_Renderer);
                        }
                    }
                    break;

                case SDLK_UP:
                case SDLK_w:
                    MovePlayer(MoveDirection::UP);
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    MovePlayer(MoveDirection::DOWN);
                    break;

                case SDLK_LEFT:
                case SDLK_a:
                    MovePlayer(MoveDirection::LEFT);
                    break;

                case SDLK_RIGHT:
                case SDLK_d:
                    MovePlayer(MoveDirection::RIGHT);
                    break;

                default:
                    break;
                }
            }
        }

        // Play music if available
        if (!Mix_PlayingMusic() && m_Music) {
            Mix_VolumeMusic(MIX_MAX_VOLUME / 4);
            Mix_PlayMusic(m_Music, -1);
        }

        // Clear screen
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_Renderer);

        // Limit steps so the number fits on the screen
        if (m_StepsTaken > 999)
            m_StepsTaken = 999;

        // Draw tilemap and data elements
        for (std::size_t y = 0; y < m_LevelData->s_LevelHeight; ++y) {
            for (std::size_t x = 0; x < m_LevelData->s_LevelWidth; ++x) {
                std::uint8_t tile_to_draw = m_LevelData->GetLevelGraphicalData(m_LevelNum, y, x);
                std::uint8_t data = m_LevelData->GetLevelInformationData(m_LevelNum, y, x);

                SDL_Rect dest = { x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

                // Background
                SDL_RenderCopy(m_Renderer, m_Tileset, &tile_rect[0], &dest);

                // Foreground
                SDL_RenderCopy(m_Renderer, m_Tileset, &tile_rect[tile_to_draw], &dest);

                if (data == 0) continue;

                // A key
                else if (data == 2) {
                    SDL_Rect source = { 0, 0, m_KeySurface->w, m_KeySurface->h };
                    SDL_RenderCopy(m_Renderer, m_Key, &source, &dest);
                }

                // A stone
                else if (data == 3) {
                    SDL_Rect source = { 0, 0, m_StoneSurface->w, m_StoneSurface->h };
                    SDL_RenderCopy(m_Renderer, m_Stone, &source, &dest);
                }
            }
        }

        {   // Draw player
            SDL_Rect source = { 0, 0, m_PlayerSurface->w, m_PlayerSurface->h };
            SDL_Rect dest = { m_PlayerPos.x * TILE_WIDTH, m_PlayerPos.y * TILE_HEIGHT, m_PlayerSurface->w, m_PlayerSurface->h };
            SDL_RenderCopy(m_Renderer, m_Player, &source, &dest);
        }


        // Exit tile reached
        if (m_LevelData->GetLevelInformationData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x) == 4) {
            ReachedExit();
            break;
        }

        {   // Info box under the game area
            std::string str = "keys found: ";
            str += std::to_string(m_NumOfKeys);
            m_Font->Write(str, 276, 262, 255, 125, 0);

            std::string steps = "steps taken: ";
            steps += std::to_string(m_StepsTaken);
            m_Font->Write(steps, 268, 272, 255, 125, 0);

            std::string level = "level: ";
            if (m_LevelNum > 0)
                level += std::to_string(m_LevelNum);
            else
                level += levelName;

            m_Font->Write(level, 16, 262, 255, 125, 0);

            m_Font->Write("press r to restart level", 16, 290, 255, 125, 0);
            m_Font->Write("press esc to return main menu", 16, 300, 255, 125, 0);
        }

        // Draw screen
        SDL_RenderPresent(m_Renderer);

        // Limit FPS
        frame.timeElapsed = SDL_GetTicks() - frame.lastTime;
        std::uint32_t delayTime = 1000 / SCREEN_FPS - frame.timeElapsed;
        if (delayTime > 1000 / SCREEN_FPS)
            delayTime = 1000 / SCREEN_FPS;
        
        SDL_Delay(delayTime);
    }
}


/* ********************************************************************************************* */
auto Game::MovePlayer(
    const MoveDirection moveDirection
) -> void
{
    if (moveDirection == MoveDirection::UP) {
        
        // Make sure that the player is within the game area limits
        if (m_PlayerPos.y <= 0)
            return;

        // Is there a wall, a locked door from backside or a door sideways?
        if (m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y - 1, m_PlayerPos.x) == 1 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y - 1, m_PlayerPos.x) == 3 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y - 1, m_PlayerPos.x) == 5 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y - 1, m_PlayerPos.x) == 6 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y - 1, m_PlayerPos.x) == 8 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y - 1, m_PlayerPos.x) == 9)
            return;

        // Are we in a opened door? If so, we can move parallel to that door
        if (m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x) == 3 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x) == 6)
            return;

        // Is there a key?
        if (m_LevelData->GetLevelInformationData(m_LevelNum, m_PlayerPos.y - 1, m_PlayerPos.x) == 2) {
            m_NumOfKeys++;

            // Play key picking sound effect
            if (m_AudioPickKey) Mix_PlayChannel(1, m_AudioPickKey, 0);
            
            // Erase key from data
            m_LevelData->SetLevelInformationData(m_LevelNum, m_PlayerPos.y - 1, m_PlayerPos.x) = 0;
        }

        // Is there a stone?
        if (m_LevelData->GetLevelInformationData(m_LevelNum, m_PlayerPos.y - 1, m_PlayerPos.x) == 3) {

            // Game area limits?
            if (m_PlayerPos.y - 1 <= 0)
                return;

            // If in the pushing direction there is:
            // -> another stone
            // -> a wall
            // -> a closed exit
            // -> game area limits
            // ==> then we can not push the stone in that direction
            if (m_LevelData->GetLevelInformationData(m_LevelNum, m_PlayerPos.y - 2, m_PlayerPos.x) == 3 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y - 2, m_PlayerPos.x) == 1 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y - 2, m_PlayerPos.x) == 4 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y - 2, m_PlayerPos.x) == 5 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y - 2, m_PlayerPos.x) == 8 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y - 2, m_PlayerPos.x) == 9)
                return;

            // If there is:
            // -> a key
            // -> an opened exit
            // ==> then we can push the stone in that direction
            m_LevelData->SetLevelInformationData(m_LevelNum, m_PlayerPos.y - 1, m_PlayerPos.x) = 0;
            m_LevelData->SetLevelInformationData(m_LevelNum, m_PlayerPos.y - 2, m_PlayerPos.x) = 3;
        }

        // Is there a locked door? Locked doors can be opened only from the keyside
        if (m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y - 1, m_PlayerPos.x) == 4) {

            // We need a key to unlock the door
            if (m_NumOfKeys > 0) {
                m_NumOfKeys--;
                m_LevelData->SetLevelGraphicalData(m_LevelNum, m_PlayerPos.y - 1, m_PlayerPos.x) = 2;

                // Return, don't go to through the door yet
                return;
            }

            // No keys, the door can't be unlocked
            else {
                return;
            }
        }

        // All fine, move the player and play footstep
        m_StepsTaken++;
        m_PlayerPos.y--;
        if (m_AudioFootstep) Mix_PlayChannel(-1, m_AudioFootstep, 0);
        return;
    }

    else if (moveDirection == MoveDirection::DOWN) {

        // Within area limits?
        if (m_PlayerPos.y >= m_LevelData->s_LevelHeight - 1)
            return;

        // Wall, a locked door from backside or a door sideways?
        if (m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y + 1, m_PlayerPos.x) == 1 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y + 1, m_PlayerPos.x) == 3 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y + 1, m_PlayerPos.x) == 5 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y + 1, m_PlayerPos.x) == 6 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y + 1, m_PlayerPos.x) == 8 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y + 1, m_PlayerPos.x) == 4)
            return;

        // Are we in a opened door? If so, we can move parallel to that door
        if (m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x) == 3 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x) == 6)
            return;

        // A key?
        if (m_LevelData->GetLevelInformationData(m_LevelNum, m_PlayerPos.y + 1, m_PlayerPos.x) == 2) {
            m_NumOfKeys++;
            if (m_AudioPickKey) Mix_PlayChannel(1, m_AudioPickKey, 0);
            m_LevelData->SetLevelInformationData(m_LevelNum, m_PlayerPos.y + 1, m_PlayerPos.x) = 0;
        }

        // A stone?
        if (m_LevelData->GetLevelInformationData(m_LevelNum, m_PlayerPos.y + 1, m_PlayerPos.x) == 3) {

            if (m_PlayerPos.y + 2 >= m_LevelData->s_LevelHeight)
                return;

            if (m_LevelData->GetLevelInformationData(m_LevelNum, m_PlayerPos.y + 2, m_PlayerPos.x) == 3 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y + 2, m_PlayerPos.x) == 1 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y + 2, m_PlayerPos.x) == 4 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y + 2, m_PlayerPos.x) == 5 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y + 2, m_PlayerPos.x) == 8 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y + 2, m_PlayerPos.x) == 9)
                return;

            m_LevelData->SetLevelInformationData(m_LevelNum, m_PlayerPos.y + 1, m_PlayerPos.x) = 0;
            m_LevelData->SetLevelInformationData(m_LevelNum, m_PlayerPos.y + 2, m_PlayerPos.x) = 3;
        }

        // A locked door?
        if (m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y + 1, m_PlayerPos.x) == 9) {
            if (m_NumOfKeys > 0) {
                m_NumOfKeys--;
                m_LevelData->SetLevelGraphicalData(m_LevelNum, m_PlayerPos.y + 1, m_PlayerPos.x) = 7;
                return;
            }
            else {
                return;
            }
        }

        // Move player 
        m_StepsTaken++;
        m_PlayerPos.y++;
        if (m_AudioFootstep) Mix_PlayChannel(-1, m_AudioFootstep, 0);
        return;
    }

    else if (moveDirection == MoveDirection::LEFT) {

        // Within area limits?
        if (m_PlayerPos.x <= 0)
            return;

        // Wall, locked door from backside or door sideways?
        if (m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 1) == 1 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 1) == 2 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 1) == 4 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 1) == 7 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 1) == 9 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 1) == 5)
            return;

        // Are we in a opened door? If so, we can move parallel to that door
        if (m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x) == 2 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x) == 7)
            return;

        // A key?
        if (m_LevelData->GetLevelInformationData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 1) == 2) {
            m_NumOfKeys++;
            if (m_AudioPickKey) Mix_PlayChannel(1, m_AudioPickKey, 0);
            m_LevelData->SetLevelInformationData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 1) = 0;
        }

        // A stone?
        if (m_LevelData->GetLevelInformationData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 1) == 3) {

            if (m_PlayerPos.x - 1 <= 0)
                return;

            if (m_LevelData->GetLevelInformationData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 2) == 3 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 2) == 1 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 2) == 4 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 2) == 5 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 2) == 8 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 2) == 9)
                return;

            m_LevelData->SetLevelInformationData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 1) = 0;
            m_LevelData->SetLevelInformationData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 2) = 3;
        }

        // A locked door?
        if (m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 1) == 8) {
            if (m_NumOfKeys > 0) {
                m_NumOfKeys--;
                m_LevelData->SetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x - 1) = 6;
                return;
            }
            else {
                return;
            }
        }

        // Move player
        m_StepsTaken++;
        m_PlayerPos.x--;
        if (m_AudioFootstep) Mix_PlayChannel(-1, m_AudioFootstep, 0);
        return;
    }

    else if (moveDirection == MoveDirection::RIGHT) {

        // Within area limits?
        if (m_PlayerPos.x >= m_LevelData->s_LevelWidth - 1)
            return;

        // Wall, locked door from backside or door sideways?
        if (m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 1) == 1 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 1) == 2 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 1) == 4 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 1) == 7 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 1) == 9 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 1) == 8)
            return;

        // Are we in a opened door? If so, we can move parallel to that door
        if (m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x) == 2 ||
            m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x) == 7)
            return;

        // A key?
        if (m_LevelData->GetLevelInformationData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 1) == 2) {
            m_NumOfKeys++;
            if (m_AudioPickKey) Mix_PlayChannel(1, m_AudioPickKey, 0);
            m_LevelData->SetLevelInformationData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 1) = 0;
        }

        // A stone?
        if (m_LevelData->GetLevelInformationData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 1) == 3) {

            if (m_PlayerPos.x + 2 >= m_LevelData->s_LevelWidth)
                return;

            if (m_LevelData->GetLevelInformationData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 2) == 3 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 2) == 1 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 2) == 4 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 2) == 5 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 2) == 8 ||
                m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 2) == 9)
                return;

            m_LevelData->SetLevelInformationData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 1) = 0;
            m_LevelData->SetLevelInformationData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 2) = 3;
        }

        // A locked door?
        if (m_LevelData->GetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 1) == 5) {
            if (m_NumOfKeys > 0) {
                m_NumOfKeys--;
                m_LevelData->SetLevelGraphicalData(m_LevelNum, m_PlayerPos.y, m_PlayerPos.x + 1) = 3;
                return;
            }
            else {
                return;
            }
        }

        // Move player and play footstep audio
        m_StepsTaken++;
        m_PlayerPos.x++;
        if (m_AudioFootstep) Mix_PlayChannel(-1, m_AudioFootstep, 0);
        return;
    }
}


/* ********************************************************************************************* */
auto Game::ReachedExit(
) noexcept -> void
{
    // Update datafile to open next level
    if (m_LevelNum)
        m_LevelData->SetLevelsBeaten(m_LevelNum + 1);

    Mix_HaltMusic();

    // Show splash screen and play fanfare
    {
        SDL_Rect rect = {
            SCREEN_WIDTH / 8 * 1, SCREEN_HEIGHT / 8 * 1,
            SCREEN_WIDTH / 8 * 2, SCREEN_HEIGHT / 8 * 2
        };

        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 127);
        SDL_RenderFillRect(m_Renderer, &rect);

        m_Font->Write("level cleared!",
            SCREEN_WIDTH / 8 * 1 + 40, SCREEN_HEIGHT / 8 * 1 + 32,
            255, 150, 0);

        if (m_AudioFanfare) {
            Mix_VolumeChunk(m_AudioFanfare, MIX_MAX_VOLUME / 4);
            Mix_PlayChannel(-1, m_AudioFanfare, 0);
        }

        SDL_RenderPresent(m_Renderer);
        SDL_Delay(1000);
    }

    int g = 0;
    int dir = 1;

    bool quit = false;
    SDL_Event e;
    while (!quit) {

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = true;
                    break;

                case SDLK_SPACE:
                case SDLK_RETURN:
                    quit = true;

                    // Restart with upgraded level number only if it's
                    // a build-in level
                    if (m_LevelNum) {
                        (++m_LevelNum) < m_LevelData->s_NumOfLevels ? m_LevelNum :
                            m_LevelNum = m_LevelData->s_NumOfLevels;
                        m_RestartLevel = true;
                    }

                    break;

                case SDLK_r:
                    quit = true;
                    m_RestartLevel = true;
                    break;

                default:
                    break;
                }
            }
        }

        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_Renderer);

        // Change colors
        g += 8 * dir;
        if (g > 255)
            dir = -1, g = 255;
        if (g < 0)
            dir = 1, g = 0;

        std::string steps = "it took ";
        steps += std::to_string(m_StepsTaken);
        steps += " steps!";
        m_Font->Write("you won!", 32, 128, 255, 0, 0);
        m_Font->Write(steps, 32, 138, 255, 30, 0);

        // An option to play next level if it was not the last build-in
        // level or it's not a custom level
        if (m_LevelNum < m_LevelData->s_NumOfLevels && m_LevelNum != 0)
            m_Font->Write("press enter to next level", 32, 150, 255, 150, 0);

        m_Font->Write("press r to restart current level", 32, 160, 255, 150, 0);
        m_Font->Write("press esc to main menu", 32, 170, 255, 150, 0);

        SDL_RenderPresent(m_Renderer);
        SDL_Delay(60);
    }
}


/* ********************************************************************************************* */
auto Game::SetLevelDescriptions(
) noexcept -> void
{

}