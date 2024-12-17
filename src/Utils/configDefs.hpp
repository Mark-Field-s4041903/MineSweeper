/* Configs for numfield */
#define NONE 0
#define MINE -1

/* Game character settings */
#define EMPTY_CHAR '~'
#define UNKNOWN_CHAR '?'
#define HIT_MINE_CHAR 'X'
#define GAMEOVER_DISPLAY_CHAR '@'
#define WIN_MINE_CHAR '!'

/* GUI: For the main window */
#define WINDOW_NAME "MineSweeper"
#define CELL_SIZE 32
#define OUTLINE_THICKNESS 1
#define CELL_BASE_COLOUR sf::Color(132, 132, 132, 255) // Grey
#define CELL_UNKNOWN_COLOUR sf::Color(255, 120, 0, 255) // Orange
#define CELL_REVEALED_MIN_COLOUR sf::Color::Green
#define CELL_GAMEOVER_COLOUR sf::Color::Red
#define CELL_BACKGROUND sf::Color::White
#define CELL_OUTLINE sf::Color::Black

/* GUI: For the text on the window */
#define FONT_PATH "src/Interface/Fonts/times.ttf"
#define TEXT_SIZE 24
#define TEXT_COLOUR sf::Color::Black