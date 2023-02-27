#ifndef __IncludeH_H__
#define __IncludeH_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include <dirent.h>

#include "functions.h"

#include "publisher.h"

#include "item.h"

#include "fileMap.h"

#include "playingField.h"

#define HEIGHT 22
#define WIDTH  62

#define NEAN    0
#define BLOCK   1
#define TRAP    2
#define LIFE    3
#define BOMBE   4
#define LADDER  5
#define START   6
#define EXIT    7
#define GATEP   8
#define GATEG   9
#define GATEY   10
#define GATEB   11
#define KEYP    12
#define KEYG    13
#define KEYY    14
#define KEYB    15
#define DOOR1   16
#define DOOR2   17
#define DOOR3   18
#define DOOR4   19
#define DOOR5   20
#define PROBE   21
#define ROBOT   22

// Mode = 0 => Editeur
// Mode = 1 => Game 

// int MODE = 0;

#endif