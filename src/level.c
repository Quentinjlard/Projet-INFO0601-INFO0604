/**
 * @file level.c
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @author COGNE Romain (romain.cogne@etudiant.univ-reims.fr)
 * @brief
 * @version 0.1
 * @date 2023-02-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "level.h"
#include "tableAdressage.h"

// Chargement d'un niveau
level_t loadLevel(int numNiv, tableAdressage_t *tableAdressage, char *nomNiv)
{
    level_t level;
    off_t adr = tableAdressage->adresse[numNiv];
    int fd = open(nomNiv, O_RDONLY);
    int verif = 1;
    if (tableAdressage->adresse[numNiv] == 0)
    {
        init_matLevel(&level);
        verif = 0;
    }
    lseek(fd, adr, SEEK_SET);
    if (fd == -1)
    {
        perror("Erreur d'ouverture du fichier (level)");
        exit(EXIT_FAILURE);
    }
    if (verif == 1)
    {
        if (read(fd, &level, sizeof(level_t)) != sizeof(level_t))
        {
            perror("Erreur de lecture du fichier (level)");
            exit(EXIT_FAILURE);
        }
    }

    close(fd);
    return level;
}

// Nettoie la fenêtre de niveau
void clear_windowLevel(WINDOW *windowLevel)
{
    for (int i = 0; i < nbCols; i++)
    {
        for (int j = 0; j < nblignes; j++)
        {
            wattron(windowLevel, COLOR_PAIR(1));
            mvwprintw(windowLevel, j + 1, i + 1, " ");
        }
    }
    wrefresh(windowLevel);
}

// Affichage d'un niveau
void level_display(WINDOW *windowLevel, level_t level)
{
    clear_windowLevel(windowLevel);
    int i, j;
    for (i = 0; i < nbCols; i++)
    {
        for (j = 0; j < nblignes; j++)
        {   
            wattron(windowLevel, COLOR_PAIR(level.colors[i * nblignes + j]));

            if (level.cells[i * nblignes + j]== 'B')
                mvwaddch(windowLevel, j + 1, i + 1, ' ');

            if (level.cells[i * nblignes + j]== '#')
                mvwaddch(windowLevel, j + 1, i + 1, '#');

            if (level.cells[i * nblignes + j]== 'V')
                mvwaddch(windowLevel, j + 1, i + 1, 'V');

            if (level.cells[i * nblignes + j]== ACS_LTEE)
                mvwaddch(windowLevel, j + 1, i + 1, ACS_LTEE);

            if (level.cells[i * nblignes + j]== ACS_HLINE)
                mvwaddch(windowLevel, j + 1, i + 1, ACS_HLINE);

            if (level.cells[i * nblignes + j]== ACS_RTEE)
                mvwaddch(windowLevel, j + 1, i + 1, ACS_RTEE);

            if (level.cells[i * nblignes + j]== 'S')
                mvwaddch(windowLevel, j + 1, i + 1, ' ');

            if (level.cells[i * nblignes + j]== 'E')
                mvwaddch(windowLevel, j + 1, i + 1, ' ');

            if (level.cells[i * nblignes + j]== '^')
                mvwaddch(windowLevel, j + 1, i + 1, ' ');

            if (level.cells[i * nblignes + j]== ACS_PLUS)
                mvwaddch(windowLevel, j + 1, i + 1, ACS_PLUS);

            if (level.cells[i * nblignes + j]==  'K')
                mvwaddch(windowLevel, j + 1, i + 1, ' ');

            if (level.cells[i * nblignes + j]==  'o')
                mvwaddch(windowLevel, j + 1, i + 1, 'o');    

            if (level.cells[i * nblignes + j]==  'D')
                mvwaddch(windowLevel, j + 1, i + 1, ' ');    

            if (level.cells[i * nblignes + j]==  ACS_LLCORNER)
                mvwaddch(windowLevel, j + 1, i + 1, ACS_LLCORNER);

            if (level.cells[i * nblignes + j]==  ACS_LRCORNER)
                mvwaddch(windowLevel, j + 1, i + 1, ACS_LRCORNER);

            if (level.cells[i * nblignes + j]==  ACS_ULCORNER)
                mvwaddch(windowLevel, j + 1, i + 1, ACS_ULCORNER);

            if (level.cells[i * nblignes + j]==  ACS_URCORNER)
                mvwaddch(windowLevel, j + 1, i + 1, ACS_URCORNER);

            if (level.cells[i * nblignes + j]==  ACS_BTEE)
                mvwaddch(windowLevel, j + 1, i + 1, ACS_BTEE);

            if (level.cells[i * nblignes + j]==  ACS_TTEE)
                mvwaddch(windowLevel, j + 1, i + 1, ACS_TTEE);

            if (level.cells[i * nblignes + j]==  '0')
                mvwaddch(windowLevel, j + 1, i + 1, '0'); 

            if (level.cells[i * nblignes + j]==  '1')
                mvwaddch(windowLevel, j + 1, i + 1, '1');

            if (level.cells[i * nblignes + j]==  '2')
                mvwaddch(windowLevel, j + 1, i + 1, '2'); 

            if (level.cells[i * nblignes + j]==  '3')
                mvwaddch(windowLevel, j + 1, i + 1, '3');   

            if (level.cells[i * nblignes + j]==  '4')
                mvwaddch(windowLevel, j + 1, i + 1, '4'); 

            if (level.cells[i * nblignes + j]==  '5')
                mvwaddch(windowLevel, j + 1, i + 1, '5');     
        }
    }
    wrefresh(windowLevel);
}

// Trouver emplacement vide dans le niveau
off_t rechercheEspaceVide(int fd, tableAdressage_t *tableAdresse)
{
    int i = 0;
    if (tableAdresse->adresse[0] == 0)
    {
        return lseek(fd, 9600, SEEK_SET);
    }
    while (i < N - 1 && tableAdresse->adresse[i] != 0)
    {
        i++;
    }

    if (i >= N - 1 && tableAdresse->adresse[i] != 0)
    {
        perror("Table adressage pleine");
        exit(EXIT_FAILURE);
    }

    return lseek(fd, tableAdresse->adresse[i - 1] + 9600, SEEK_SET);
}

// Ajouter un niveau dans le fichier
int ajouterLevel(level_t *level, tableAdressage_t *tableAdresse, char *nomNiv)
{
    int err;

    int fd = open(nomNiv, O_RDWR);
    // Lecture de la table d'adresses
    lseek(fd, 0, SEEK_SET);
    if ((err = read(fd, tableAdresse, sizeof(tableAdressage_t))) == -1)
    {
        perror("Erreur lecture table d'adressage (level)");
        exit(EXIT_FAILURE);
    };
    lseek(fd, sizeof(tableAdressage_t), SEEK_SET);

    // Trouver un emplacement libre dans le fichier

    off_t adresse = rechercheEspaceVide(fd, tableAdresse);

    // Écrire la chaîne de caractères à l'emplacement trouvé
    lseek(fd, adresse, SEEK_SET);
    printf("%ld", adresse);

    if ((err = write(fd, level, sizeof(level_t))) == -1)
    {
        perror("Erreur écriture level (level)");
        exit(EXIT_FAILURE);
    };

    // Ajouter l'adresse du niveau à la table d'adresses
    int i = 0;
    while (tableAdresse->adresse[i] != 0)
    {
        i++;
    }
    tableAdresse->adresse[i] = adresse;

    // Mettre à jour la table d'adresses dans le fichier
    lseek(fd, 0, SEEK_SET);
    if ((err = write(fd, tableAdresse, sizeof(tableAdressage_t))) == -1)
    {
        perror("Erreur écriture table d'adressage (level)");
        exit(EXIT_FAILURE);
    };
    lseek(fd, sizeof(tableAdressage_t), SEEK_SET);

    // Fermer descripteur de fichier
    if ((err = close(fd)) == -1)
    {
        perror("Erreur fermeture descripteur de fichier (level)");
        exit(EXIT_FAILURE);
    };

    return 0;
}

// Initialiser niveau
void init_matLevel(level_t *level)
{
    for (int i = 0; i < nblignes * nbCols; i++)
    {
        level->cells[i] = ' ';
        level->colors[i] = 1;
    }
}

// Supprimer niveau
int supprimerLevel(tableAdressage_t *tableAdresse, int niv, char *nomNiv)
{
    int err, fd = 0;
    if ((fd = open(nomNiv, O_RDWR)) == -1)
    {
        perror("Erreur ouverture fichier (level)");
        exit(EXIT_FAILURE);
    }

    // Lecture de la table d'adresses
    lseek(fd, 0, SEEK_SET);
    if ((err = read(fd, tableAdresse, sizeof(tableAdressage_t))) == -1)
    {
        perror("Erreur lecture table d'adressage(level)");
        exit(EXIT_FAILURE);
    };

    // Vérifier que l'index est valide
    int index = niv;
    if (index < 0 || index >= N || tableAdresse->adresse[index] == 0)
    {
        // printf("Entrée non valide\n");
        return 1;
    }

    // Supprimer l'entrée de la table d'adresses
    tableAdresse->adresse[index] = 0;

    // Mettre à jour la table d'adresses dans le fichier
    lseek(fd, 0, SEEK_SET);
    if ((err = write(fd, tableAdresse, sizeof(tableAdressage_t))) == -1)
    {
        perror("Erreur ecriture table adressage (level)");
        exit(EXIT_FAILURE);
    };
    lseek(fd, sizeof(tableAdressage_t), SEEK_SET);

    return 0;
}

// Afficher fenêtre de debug
void afficherDEBUG(level_t level, WINDOW *wDEBUG)
{
    for (int i = 0; i < nbCols; i++)
    {
        for (int j = 0; j < nblignes; j++)
        {
            mvwaddch(wDEBUG, j + 1, i + 1, level.cells[i * nblignes + j]);
        }
    }
    wrefresh(wDEBUG);
}