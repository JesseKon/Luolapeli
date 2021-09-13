/**
 * *** This file is part of Luolapeli ***
 * 
 * 
 */

#include "Menu.h"


/* ********************************************************************************************* */
Menu::Menu(
    SDL_Window* const window, 
    SDL_Renderer* const renderer
)
{
    m_Window = window;
    m_Renderer = renderer;

    // Load font
    m_Font = new Font("Data/font.bmp", m_Window, m_Renderer);

    // Create levelData and level descriptions for menu
    levelData = std::make_unique<LevelData>();
    levelData->CreateLevelDescriptions();

    // Start menu
    StartMenu();
}


/* ********************************************************************************************* */
Menu::~Menu(
)
{

}


/* ********************************************************************************************* */
auto Menu::StartMenu(
) -> void
{
    std::int32_t choice = 1;  // Menu item choice
    std::int32_t menuItems = 6; // Num of menu items

    std::int8_t color_g = 0;	// Changing green color value to indicate active menu item
    std::int32_t dir = 1;		// Color direction (1 or -1)

    bool quit = false;
    SDL_Event e;
    while (!quit) {

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;

            // Navigate through menu items
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = true;
                    break;

                case SDLK_UP:
                case SDLK_w:
                    choice <= 1 ? choice = menuItems : choice--;
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    choice >= menuItems ? choice = 1 : choice++;
                    break;

                case SDLK_RETURN:
                case SDLK_SPACE:
                    ActivateMenuItem(choice, quit);
                    break;

                case SDLK_1:
                    ActivateMenuItem(1, quit);
                    break;
                    
                case SDLK_2:
                    ActivateMenuItem(2, quit);
                    break;

                case SDLK_3:
                    ActivateMenuItem(3, quit);
                    break;

                case SDLK_4:
                    ActivateMenuItem(4, quit);
                    break;

                case SDLK_5:
                    ActivateMenuItem(5, quit);
                    break;

                case SDLK_6:
                    ActivateMenuItem(6, quit);
                    break;

                default:
                    break;
                }
            }
        }

        // Draw background
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_Renderer);

        // Write information
        {
            // Movement to the colors
            color_g += 8 * dir;
            if (color_g > 255)
                color_g = 255, dir = -1;
            if (color_g < 0)
                color_g = 0, dir = 1;

            // Header
            m_Font->Write("main menu", 8, 8, 255, 125, 0);

            // Write menu items and highlight active
            m_Font->Write("play", 32, 110, 255, choice == 1 ? color_g : 125, 0);
            m_Font->Write("custom levels", 32, 130, 255, choice == 2 ? color_g : 125, 0);
            m_Font->Write("level editor", 32, 150, 255, choice == 3 ? color_g : 125, 0);
            m_Font->Write("credits", 32, 170, 255, choice == 4 ? color_g : 125, 0);
            m_Font->Write("options", 32, 190, 255, choice == 5 ? color_g : 125, 0);
            m_Font->Write("exit", 32, 210, 255, choice == 6 ? color_g : 125, 0);

            // Write arrow next to menu text
            m_Font->Write("*", 20, 110 + 20 * (choice - 1), 255, color_g, 0);
        }

        SDL_RenderPresent(m_Renderer);
    }
}


/* ********************************************************************************************* */
auto Menu::ActivateMenuItem(
    const std::int32_t choice,
    bool& quit
) -> void
{
    // Build-in levels
    if (choice == 1)
        Menu_Play();

    // Custom level
    else if (choice == 2)
        Menu_PlayCustom();

    // Level editor
    else if (choice == 3)
        Menu_LevelEditor();

    // Credits
    else if (choice == 4)
        Menu_Credits();

    // Options
    else if (choice == 5)
        Menu_Options();

    // Exit
    else if (choice == 6)
        quit = true;
}


/* ********************************************************************************************* */
auto Menu::Menu_Play(
) -> void
{
    std::uint32_t choice = 1;                                      // Activated menu item
    const std::int32_t menuItems = levelData->s_NumOfLevels - 1;     // Number of menu items
    std::int32_t levelsBeaten = levelData->GetLevelsBeaten();      // How many levels are beaten

    std::int32_t color_g = 0;  // Changing green color value to indicate active menu item
    std::int32_t dir = 1;      // Color direction (1 or -1)

    bool quit = false;
    SDL_Event e;
    while (!quit) {

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;

            // Navigate through menu items
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {

                // Return
                case SDLK_ESCAPE:
                    quit = true;
                    break;

                case SDLK_UP:
                case SDLK_w:
                    choice <= 1 ? choice = 1 : choice--;
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    choice >= levelsBeaten ? choice = levelsBeaten : choice++;
                    break;

                case SDLK_RETURN:
                case SDLK_SPACE:
                    StartLevel(choice, "");
                    levelsBeaten = levelData->GetLevelsBeaten(); // Update levels beaten data
                    break;

                default:
                    break;
                }
            }
        }

        // Draw background
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_Renderer);

        {
            m_Font->Write("main menu * levels", 8, 8, 255, 125, 0);  // Header

            // Movement to the colors
            color_g += 8 * dir;
            if (color_g > 255)
                color_g = 255, dir = -1;
            if (color_g < 0)
                color_g = 0, dir = 1;

            // Write menu items
            for (int i = 1; i < levelData->s_NumOfLevels; ++i) {
                std::string str = "level ";
                str += std::to_string(i);
                str += ": ";
                str += levelData->GetLevelDescription(i);
                m_Font->Write(str, 32, 42 + (i * 10), 255,
                    choice == i ? color_g : 125,        // Activate item
                    i <= levelsBeaten ? 0 : 255);      // "Greyed out"
            }

            // Write arrow next to menu text
            m_Font->Write("*", 20, 42 + (choice * 10), 255, color_g, 0);
        }

        // Draw screen
        SDL_RenderPresent(m_Renderer);
        SDL_Delay(60);
    }
}


/* ********************************************************************************************* */
auto Menu::Menu_PlayCustom(
) -> void
{
    // Search for files
    // push_back filenames without directory name 'Customlevels/'
    std::vector<std::string> filenames;
    for (const auto& e : std::filesystem::directory_iterator("Customlevels/"))
        filenames.push_back(e.path().string().substr(13, e.path().string().length() - 13));

    std::string choosenLevelName;

    std::int32_t itemChoosen = 0;                 // Which filename is currently selected
    std::int32_t itemsTotal = filenames.size();   // Total number of files

    std::int32_t color_g = 0;  // Color value (0 - 255)
    std::int32_t dir = 1;      // Color direction (1 or -1)

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
                    choosenLevelName = filenames[itemChoosen];
                    StartLevel(0, choosenLevelName);
                    break;

                case SDLK_UP:
                case SDLK_w:
                    itemChoosen <= 0 ? itemChoosen = itemsTotal - 1 : itemChoosen--;
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    itemChoosen >= itemsTotal - 1 ? itemChoosen = 0 : itemChoosen++;
                    break;

                default:
                    break;
                }
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_Renderer);

        {
            m_Font->Write("main menu * custom levels", 8, 8, 255, 125, 0);  // Header

            // Selection color
            color_g += 15 * dir;
            if (color_g > 255)
                color_g = 255, dir = -1;
            if (color_g < 0)
                color_g = 0, dir = 1;

            m_Font->Write("open file", 32, 64, 255, 150, 0);

            // List filenames
            for (std::size_t i = 0; i < filenames.size(); ++i) {
                m_Font->Write(filenames[i].c_str(), 32, 80 + (i * 10), 255, itemChoosen == i ? color_g : 110, 0);
            }
        }

        // Draw screen
        SDL_RenderPresent(m_Renderer);
    }
}


/* ********************************************************************************************* */
auto Menu::StartLevel(
    std::int32_t levelNum, 
    const std::string& filename
) -> void 
{
    Game* game = new Game(m_Window, m_Renderer, levelNum, filename);
    bool restartLevel = game->RestartLevel();
    levelNum = game->LevelNum();

    delete game;

    // Restart the level if requested
    if (restartLevel)
        StartLevel(levelNum, filename);
}


/* ********************************************************************************************* */
auto Menu::Menu_LevelEditor(
) -> void
{
    LevelEditor* levelEditor = new LevelEditor(m_Window, m_Renderer);
    delete levelEditor;
}


/* ********************************************************************************************* */
auto Menu::Menu_Credits(
) noexcept -> void
{
    bool quit = false;
    SDL_Event e;
    while (!quit) {

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;

            // Press any key to quit credits menu
            if (e.type == SDL_KEYDOWN)
                quit = true;
        }

        SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(m_Renderer);

        {
            m_Font->Write("main menu * credits", 8, 8, 255, 125, 0);  // Header

            m_Font->Write("made by jesse k}n}nen", 32, 64, 255, 125, 0);
            m_Font->Write("inspired by dos-game called paganitzu", 32, 74, 255, 125, 0);

            m_Font->Write("uses", 32, 100, 255, 125, 0);
            m_Font->Write("* sdl2", 32, 110, 255, 125, 0);
            m_Font->Write("* sdl2_image", 32, 120, 255, 125, 0);
            m_Font->Write("* sdl2_mixer", 32, 130, 255, 125, 0);

            m_Font->Write("press any key to enter main menu", 32, 260, 255, 125, 0);
        }

        // Draw screen
        SDL_RenderPresent(m_Renderer);
        SDL_Delay(30);
    }
}


/**
 * Menu -> options
 */
auto Menu::Menu_Options(
) noexcept -> void
{

    /**
     * TODO: music volume control in fixed steps
     * TODO: effects volume control in fixed steps
     */

}