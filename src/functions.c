#include "functions.h"


/**
 * ncurses initialisation.
 */
void ncurses_init() {
  initscr();	        // Start ncurses mode
  cbreak();	            // Disable the buffer cache
  noecho();             // Disable the display of typed characters
  keypad(stdscr, TRUE);	// Activate specific keys (arrows)
  refresh();            // Update display
  curs_set(FALSE);      // Hide the cursor
}

/**
 * Stop ncurses.
 */
void ncurses_stop() {
  endwin();
}

/**
 * Colors initialisation.
 */
void ncurses_colors() {
  // Check color support
  if(has_colors() == FALSE) {
    ncurses_stop();
    fprintf(stderr, "The terminal doesn't support colors.\n");
    exit(EXIT_FAILURE);
  }

  // Activate colors
  start_color();
}

/**
 * Mouse initialisation.
 */
void ncurses_init_mouse() {
  if(!mousemask(BUTTON1_PRESSED, NULL)) {
    ncurses_stop();
    fprintf(stderr, "Mouse isn't supported.\n");
    exit(EXIT_FAILURE);
  }
}

/**
 * Get the mouse position.
 */
int mouse_getpos(int *x, int *y) {
  MEVENT event;
  int result = getmouse(&event);
  if(result == OK) {
    *x = event.x;
    *y = event.y;
  }
  return result;
}

/**
 * @brief Function to declare the different colours in the palette.
 * 
 */
void palette() {   
    

        // +----+--------------------------------+
        // | ID |      Lettre     |      Fond    |
        // +----+--------------------------------+
        // | 1  |      Noir       |      Noir    |
        // | 2  |      Rouge      |      Noir    |
        // | 3  |      Vert       |      Noir    |
        // | 4  |      Jaune      |      Noir    |
        // | 5  |      Blue       |      Noir    |
        // | 6  |     Magenta     |      Noir    |
        // | 7  |      Cyan       |      Noir    |
        // | 8  |      Blanc      |      Noir    |
        // | 9  |      Noir       |      Cyan    |

    init_pair(1, COLOR_BLACK,COLOR_BLACK);
    init_pair(2, COLOR_RED,COLOR_BLACK);
    init_pair(3, COLOR_GREEN,COLOR_BLACK);
    init_pair(4, COLOR_YELLOW,COLOR_BLACK);
    init_pair(5, COLOR_BLUE,COLOR_BLACK);
    init_pair(6, COLOR_MAGENTA,COLOR_BLACK);
    init_pair(7, COLOR_CYAN,COLOR_BLACK);
    init_pair(8, COLOR_WHITE,COLOR_BLACK);

    init_pair(9, COLOR_BLACK,COLOR_CYAN);
    init_pair(10, COLOR_BLACK,COLOR_MAGENTA);
    init_pair(11, COLOR_BLACK,COLOR_GREEN);
    init_pair(12, COLOR_BLACK,COLOR_YELLOW);
    init_pair(13, COLOR_BLACK,COLOR_BLUE);
}