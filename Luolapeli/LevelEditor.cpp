/**
 * *** This file is part of Luolapeli ***
 * 
 * 
 */

#include "LevelEditor.h"


/* ********************************************************************************************* */
LevelEditor::LevelEditor(
    SDL_Window* const window,
    SDL_Renderer* const renderer
) : Resources(window, renderer)
{
    m_Window = window;
    m_Renderer = renderer;

    m_Cursor = { 0, 0, 0, 1 };      // default cursor state
    m_LevelName = "untitled.lvl";   // default level name

    InitEmptyLevel();
    StartEditor();
}


/* ********************************************************************************************* */
LevelEditor::~LevelEditor(
)
{

}


/* ********************************************************************************************* */
auto LevelEditor::InitEmptyLevel(
) -> void
{
    m_LevelGraphicalData.resize(LevelData::s_LevelHeight);
    for (std::size_t i = 0; i < LevelData::s_LevelHeight; ++i)
        m_LevelGraphicalData.at(i).resize(LevelData::s_LevelWidth);

    m_LevelInformationData.resize(LevelData::s_LevelHeight);
    for (std::size_t i = 0; i < LevelData::s_LevelHeight; ++i)
        m_LevelInformationData.at(i).resize(LevelData::s_LevelWidth);

    m_LevelGraphicalData = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };

    m_LevelInformationData = {
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
    };
}


/* ********************************************************************************************* */
auto LevelEditor::StartEditor(
) -> void
{
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

    std::int32_t tileChoosed = 1;   // Which graphical tile is currently being hold
    std::int32_t infoChoosed = 1;   // Which information tile is currently being hold

    enum class TileType { GRAPHICS, INFORMATION } tileType = TileType::GRAPHICS;

    // Main loop
    bool quit = false;
    SDL_Event e;
    while (!quit) {

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;

            if (e.type == SDL_KEYDOWN) { 
                switch (e.key.keysym.sym) {

                case SDLK_ESCAPE:   // ESC = exit
                    {   // Confirm exiting editor
                        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                        SDL_RenderClear(m_Renderer);
                        m_Font->Write("exit editor? (y/n)", 32, 100, 255, 20, 0);
                        m_Font->Write("unsaved data will be lost", 32, 110, 255, 20, 0);

                        bool quit_sub = false;
                        SDL_Event e;
                        while (!quit_sub) {

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

                case SDLK_F1:       // F1 = use graphical tiles
                    tileType = TileType::GRAPHICS;
                    break;

                case SDLK_F2:       // F2 = use information tiles
                    tileType = TileType::INFORMATION;
                    break;

                case SDLK_q:        // Q = previous tile
                    if (tileType == TileType::GRAPHICS) 
                        tileChoosed <= 0 ? tileChoosed = NUM_OF_TILES - 1 : tileChoosed--;
                    if (tileType == TileType::INFORMATION)
                        infoChoosed <= 0 ? infoChoosed = NUM_OF_INFO_TILES : infoChoosed--;
                    break;

                case SDLK_e:        // E = next tile
                    if (tileType == TileType::GRAPHICS)
                        tileChoosed >= NUM_OF_TILES - 1 ? tileChoosed = 0 : tileChoosed++;
                    if (tileType == TileType::INFORMATION)
                        infoChoosed >= NUM_OF_INFO_TILES ? infoChoosed = 0 : infoChoosed++;
                    break;

                case SDLK_RETURN:   // ENTER or SPACE = put tile at cursor
                case SDLK_SPACE:
                    if (tileType == TileType::GRAPHICS)
                        m_LevelGraphicalData[m_Cursor.y][m_Cursor.x] = tileChoosed;
                    if (tileType == TileType::INFORMATION)
                        m_LevelInformationData[m_Cursor.y][m_Cursor.x] = infoChoosed;
                    break;

                case SDLK_F5:       // F5 = save level
                    SaveLevel();
                    break;

                case SDLK_F9:       // F9 = load level
                    LoadLevel();
                    break;

                case SDLK_UP:
                case SDLK_w:
                    m_Cursor.y <= 0 ? m_Cursor.y = LevelData::s_LevelHeight - 1 : m_Cursor.y--;
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    m_Cursor.y >= LevelData::s_LevelHeight - 1 ? m_Cursor.y = 0 : m_Cursor.y++;
                    break;

                case SDLK_LEFT:
                case SDLK_a:
                    m_Cursor.x <= 0 ? m_Cursor.x = LevelData::s_LevelWidth - 1 : m_Cursor.x--;
                    break;

                case SDLK_RIGHT:
                case SDLK_d:
                    m_Cursor.x >= LevelData::s_LevelWidth - 1 ? m_Cursor.x = 0 : m_Cursor.x++;
                    break;

                default:
                    break;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_Renderer);

        // Draw tiles
        for (std::size_t y = 0; y < LevelData::s_LevelHeight; ++y) {
            for (std::size_t x = 0; x < LevelData::s_LevelWidth; ++x) {
                std::uint8_t tileToDraw = m_LevelGraphicalData.at(y).at(x);
                std::uint8_t data = m_LevelInformationData.at(y).at(x);

                SDL_Rect dest = { x * TILE_WIDTH, y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };

                // Background
                SDL_RenderCopy(m_Renderer, m_Tileset, &tile_rect[0], &dest);

                // Foreground
                SDL_RenderCopy(m_Renderer, m_Tileset, &tile_rect[tileToDraw], &dest);

                // No data
                if (data == 0) continue;

                // Player
                else if (data == 1) {
                    SDL_Rect source = { 0, 0, m_PlayerSurface->w, m_PlayerSurface->h };
                    SDL_RenderCopy(m_Renderer, m_Player, &source, &dest);
                }

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

                // Exit tile
                else if (data == 4) {
                    SDL_Rect source = { TILE_WIDTH * 1, TILE_HEIGHT * 1, TILE_WIDTH, TILE_HEIGHT };
                    SDL_RenderCopy(m_Renderer, m_Tileset, &source, &dest);
                }
            }
        }

        // Draw cursor
        {
            // Change color
            m_Cursor.color += 15 * m_Cursor.dir;
            if (m_Cursor.color > 255)
                m_Cursor.color = 255, m_Cursor.dir = -1;
            if (m_Cursor.color < 0)
                m_Cursor.color = 0, m_Cursor.dir = 1;

            // Draw preview of graphical tiles
            if (tileType == TileType::GRAPHICS) {
                SDL_SetTextureAlphaMod(m_Tileset, int(128 + m_Cursor.color / 2));
                SDL_Rect dest = { m_Cursor.x * TILE_WIDTH, m_Cursor.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
                SDL_RenderCopy(m_Renderer, m_Tileset, &tile_rect[tileChoosed], &dest);
                SDL_SetTextureAlphaMod(m_Tileset, SDL_ALPHA_OPAQUE);
            }

            // Draw preview of information tiles
            if (tileType == TileType::INFORMATION) {

                // Player spawn
                if (infoChoosed == 1) {
                    SDL_SetTextureAlphaMod(m_Player, int(128 + m_Cursor.color / 2));
                    SDL_Rect source = { 0, 0, m_PlayerSurface->w, m_PlayerSurface->h };
                    SDL_Rect dest = { m_Cursor.x * TILE_WIDTH, m_Cursor.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
                    SDL_RenderCopy(m_Renderer, m_Player, &source, &dest);
                    SDL_SetTextureAlphaMod(m_Player, SDL_ALPHA_OPAQUE);
                }

                // Key
                if (infoChoosed == 2) {
                    SDL_SetTextureAlphaMod(m_Key, int(128 + m_Cursor.color / 2));
                    SDL_Rect source = { 0, 0, m_KeySurface->w, m_KeySurface->h };
                    SDL_Rect dest = { m_Cursor.x * TILE_WIDTH, m_Cursor.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
                    SDL_RenderCopy(m_Renderer, m_Key, &source, &dest);
                    SDL_SetTextureAlphaMod(m_Key, SDL_ALPHA_OPAQUE);
                }

                // Stone
                if (infoChoosed == 3) {
                    SDL_SetTextureAlphaMod(m_Stone, int(128 + m_Cursor.color / 2));
                    SDL_Rect source = { 0, 0, m_StoneSurface->w, m_StoneSurface->h };
                    SDL_Rect dest = { m_Cursor.x * TILE_WIDTH, m_Cursor.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
                    SDL_RenderCopy(m_Renderer, m_Stone, &source, &dest);
                    SDL_SetTextureAlphaMod(m_Stone, SDL_ALPHA_OPAQUE);
                }

                // Exit tile
                if (infoChoosed == 4) {
                    SDL_Rect source = { TILE_WIDTH * 1, TILE_HEIGHT * 1, TILE_WIDTH, TILE_HEIGHT };
                    SDL_Rect dest = { m_Cursor.x * TILE_WIDTH, m_Cursor.y * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT };
                    SDL_RenderCopy(m_Renderer, m_Tileset, &source, &dest);
                }
            }

            // Draw square around the previewed tile or information element
            SDL_SetRenderDrawColor(m_Renderer, 255, m_Cursor.color, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderDrawLine(m_Renderer,                   // Top
                m_Cursor.x * TILE_WIDTH,
                m_Cursor.y * TILE_HEIGHT,
                m_Cursor.x * TILE_WIDTH + TILE_HEIGHT,
                m_Cursor.y * TILE_HEIGHT);

            SDL_RenderDrawLine(m_Renderer,                   // Right
                m_Cursor.x * TILE_WIDTH + TILE_WIDTH,
                m_Cursor.y * TILE_HEIGHT,
                m_Cursor.x * TILE_WIDTH + TILE_WIDTH,
                m_Cursor.y * TILE_HEIGHT + TILE_HEIGHT);

            SDL_RenderDrawLine(m_Renderer,                   // Bottom
                m_Cursor.x * TILE_WIDTH + TILE_WIDTH,
                m_Cursor.y * TILE_HEIGHT + TILE_HEIGHT,
                m_Cursor.x * TILE_WIDTH,
                m_Cursor.y * TILE_HEIGHT + TILE_HEIGHT);

            SDL_RenderDrawLine(m_Renderer,                   // Left
                m_Cursor.x * TILE_WIDTH,
                m_Cursor.y * TILE_HEIGHT + TILE_HEIGHT,
                m_Cursor.x * TILE_WIDTH,
                m_Cursor.y * TILE_HEIGHT);
        }

        // Draw information text
        {
            std::string str = "level editor * \"";
            str += m_LevelName;
            str += "\"";
            m_Font->Write(str, 16, 260, 255, 150, 0);

            m_Font->Write("wasd - move cursor, space - place tile", 16, 270, 200, 150, 0);
            m_Font->Write("f1 - graphical tiles", 16, 278, 180, 150, 0);
            m_Font->Write("f2 - information tiles", 16, 286, 180, 150, 0);
            m_Font->Write("q and e - scroll tiles", 16, 294, 180, 150, 0);
            m_Font->Write("f5 - save, f9 - load, esc - exit", 16, 310, 180, 150, 0);
        }

        // Draw screen
        SDL_RenderPresent(m_Renderer);
        SDL_Delay(60);
    }
};


/* ********************************************************************************************* */
auto LevelEditor::SaveLevel(
) -> void
{
    std::string filename = m_LevelName;
    SDL_StartTextInput();

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

                case SDLK_RETURN:
                    quit = true;
                    break;

                case SDLK_BACKSPACE:
                    if (filename.length() > 0) 
                        filename.pop_back();
                    break;

                default:
                    break;
                }
            }

            if (e.type == SDL_TEXTINPUT) {
                filename += e.text.text;
            }

        }

        // Clear screen
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_Renderer);

        // Write filename
        {
            m_Font->Write("give filename: ", 32, 64, 255, 150, 0);
            m_Font->Write(filename, 32, 74, 255, 150, 0);

            // Draw a little cursor to help
            m_Font->Write("-", 32 + (filename.length() * 8), 78, 255, 110, 0);
        }

        // Draw screen
        SDL_RenderPresent(m_Renderer);
    }

    SDL_StopTextInput();

    // Check if the file already exists
    std::fstream f_check;
    //f_check.open("Customlevels/" + filename, std::ios::in);
    f_check.open("Customlevels/" + filename, std::ios::in | std::ios::binary);

    if (f_check.is_open()) {
        m_Font->Write("file already exists!", 32, 100, 255, 20, 0);
        m_Font->Write("do you want to override? (y/n)", 32, 110, 255, 20, 0);

        bool quit = false;
        SDL_Event e;
        while (!quit) {
            
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                    case SDLK_y:        // Override savefile
                    case SDLK_RETURN:
                        quit = true;
                        break;

                    case SDLK_n:        // Don't override savefile
                    case SDLK_ESCAPE:
                        return;
                        break;

                    default:
                        break;
                    }
                }
            }

            SDL_RenderPresent(m_Renderer);
        }
    }
    f_check.close();

    // Open file for writing
    std::fstream f;
    f.open("Customlevels/" + filename, std::ios::out | std::ios::binary);

    for (std::size_t y = 0; y < LevelData::s_LevelHeight; ++y)
        f.write(reinterpret_cast<const char*>(m_LevelGraphicalData.at(y).data()), LevelData::s_LevelWidth * sizeof(std::uint8_t));

    for (std::size_t y = 0; y < LevelData::s_LevelHeight; ++y)
        f.write(reinterpret_cast<const char*>(m_LevelInformationData.at(y).data()), LevelData::s_LevelWidth * sizeof(std::uint8_t));

    f.close();

    // Update level name
    m_LevelName = filename;

    // Information text for user
    {
        m_Font->Write("saved!", 32, 126, 20, 255, 20);
        SDL_RenderPresent(m_Renderer);
        SDL_Delay(1000);
    }
}


/* ********************************************************************************************* */
auto LevelEditor::LoadLevel(
) -> void
{
    // Search for files
    // push_back filenames without directory name 'Customlevels/'
    std::vector<std::string> filenames;
    for (const auto& e : std::filesystem::directory_iterator("Customlevels/"))
        filenames.push_back(e.path().string().substr(13, e.path().string().length() - 13));

    std::string openFilename;

    short item_choosen = 0;                 // Which filename is currently selected
    short items_total = filenames.size();   // Total number of files

    short color_g = 0;  // Color value (0 - 255)
    short dir = 1;      // Color direction (1 or -1)

    bool quit = false;
    SDL_Event e;
    while (!quit) {

        while (SDL_PollEvent(&e)) {

            if (e.type == SDL_QUIT)
                quit = true;

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:   // Exit from load menu
                    quit = true;
                    break;

                case SDLK_RETURN:   // Select current item
                    openFilename = filenames[item_choosen];
                    quit = true;
                    break;

                case SDLK_UP:
                case SDLK_w:
                    item_choosen <= 0 ? item_choosen = items_total - 1 : item_choosen--;
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    item_choosen >= items_total - 1 ? item_choosen = 0 : item_choosen++;
                    break;

                default:
                    break;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_Renderer);

        // Write text
        {
            // Selection color
            color_g += 15 * dir;
            if (color_g > 255)
                color_g = 255, dir = -1;
            if (color_g < 0)
                color_g = 0, dir = 1;

            m_Font->Write("open file", 32, 64, 255, 150, 0);

            // List filenames
            for (int i = 0; i < filenames.size(); ++i) {
                m_Font->Write(filenames[i].c_str(), 32, 80 + (i * 10), 255, item_choosen == i ? color_g : 110, 0);
            }
        }

        // Draw screen
        SDL_RenderPresent(m_Renderer);
    }

    std::string filename = "Customlevels/" + openFilename;
    std::fstream f;
    f.open(filename, std::ios::in | std::ios::binary);

    for (std::size_t y = 0; y < LevelData::s_LevelHeight; ++y)
        f.read(reinterpret_cast<char*>(m_LevelGraphicalData.at(y).data()), LevelData::s_LevelWidth * sizeof(std::uint8_t));

    for (std::size_t y = 0; y < LevelData::s_LevelHeight; ++y)
        f.read(reinterpret_cast<char*>(m_LevelInformationData.at(y).data()), LevelData::s_LevelWidth * sizeof(std::uint8_t));

    f.close();

    // Update level name
    m_LevelName = openFilename;
}
