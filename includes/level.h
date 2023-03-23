#ifndef _LEVEL_
#define _LEVEL_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <wchar.h>

#include "level.h"
#include "tableVide.h"
#include "tableAdressage.h"


typedef enum {
    // Foreground colors
    FG_BLACK = 30,
    FG_RED =31,
    FG_GREEN = 32,
    FG_YELLOW = 33,
    FG_BLUE = 34,
    FG_MAGENTA = 35,
    FG_CYAN = 36,
    FG_WHITE = 37,

    // Background Colors
    BK_BLACK = 40,
    BK_RED = 41,
    BK_GREEN = 42,
    BK_YELLOW = 43,
    BK_BLUE = 44,
    BK_MAGENTA = 45,
    BK_CYAN = 46,
    BK_WHITE = 47
} color_t;

// Grid size
#define HEIGHT     20
#define WIDTH      60

// Structure of a level
typedef struct {
    wint_t cells[HEIGHT][WIDTH];
    color_t colors[HEIGHT][WIDTH];
} level_t;

level_t loadLevel(int, TableAdressage_s *);
void level_display(level_t *);
int supprimerLevel(TableAdressage_s * tableAdresse, TableVide_s * tableVide, int niv);
int ajouterLevel(level_t * level, TableAdressage_s * tableAdresse, TableVide_s * tableVide);
off_t rechercheEspaceVide(int fd, TableVide_s *tableVide);
#endif