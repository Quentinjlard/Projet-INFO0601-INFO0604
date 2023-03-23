#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "level.h"
#include "tableAdressage.h"

level_t loadLevel(int numNiv, TableAdressage_s * tableAdressage) {
    level_t level;
    off_t adr = tableAdressage->adresse[numNiv];
    int fd = open("file.bin", O_RDONLY);
    lseek(fd, adr, SEEK_SET);
    if (fd == -1) {
        perror("Erreur d'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    if (read(fd, &level, sizeof(level_t)) != sizeof(level_t)) {
        perror("Erreur de lecture du fichier ");
        exit(EXIT_FAILURE);
    }
    

    close(fd);
    return  level;
}

void level_display(level_t *level) {
    int i, j;
    
    for(i = 0; i < WIDTH + 2; i++)
        printf("*");
    printf("\n");
    
    for(i = 0; i < HEIGHT; i++) {
        printf("*");
        for(j = 0; j < WIDTH; j++) {
            printf("\x1b[%dm%C\x1b[0m", level->colors[i][j], level->cells[i][j]);
        }
        printf("*\n");
    }
    
    for(i = 0; i < WIDTH + 2; i++)
        printf("*");
    printf("\n");
}

// Fonction pour trouver un emplacement libre dans le fichier
off_t rechercheEspaceVide(int fd, TableVide_s *tableVide) {
    for (int i = 0; i < N; i++) {
        if (tableVide->taille[i] >= sizeof(level_t)){
            off_t val = tableVide->debut[i];
            supprimer_table_vide(tableVide, i);
            return val;
        }
    }
    return lseek(fd, 0, SEEK_END);
    
}

int ajouterLevel(level_t * level, TableAdressage_s * tableAdresse, TableVide_s * tableVide) {
    int err;

    int fd = open("file.bin", O_RDWR);
    // Lecture de la table d'adresses
    lseek(fd, 0, SEEK_SET);
    if((err=read(fd, tableAdresse, sizeof(TableAdressage_s)))==-1)
    {
        perror("File read error");
        exit(EXIT_FAILURE);
    };
    
    // Lecture de la table de vide
    lseek(fd, sizeof(TableAdressage_s), SEEK_SET);
    if((err=read(fd, tableVide, sizeof(TableVide_s)))==-1)
    {
        perror("File read error");
        exit(EXIT_FAILURE);
    };
    


    // Trouver un emplacement libre dans le fichier

    off_t adresse = rechercheEspaceVide(fd, tableVide);

    // Écrire la chaîne de caractères à l'emplacement trouvé
    lseek(fd, adresse, SEEK_SET);
    level_display(level);
    if((err=write(fd, level, sizeof(level_t)))==-1)
    {
        perror("File read error");
        exit(EXIT_FAILURE);
    };

    // Ajouter l'adresse du niveau à la table d'adresses
    int i=0;
    while(tableAdresse->adresse[i] != 0){
        i++;
    }
    tableAdresse->adresse[i] = adresse;
   

    // Mettre à jour la table d'adresses et la table de vide dans le fichier
    lseek(fd, 0, SEEK_SET);
    if((err=write(fd, tableAdresse, sizeof(TableAdressage_s)))==-1)
    {
        perror("File read error");
        exit(EXIT_FAILURE);
    };
    lseek(fd, sizeof(TableAdressage_s), SEEK_SET);

    if((err=write(fd, tableVide, sizeof(TableVide_s)))==-1)
    {
        perror("File read error");
        exit(EXIT_FAILURE);
    };

    if((err=close(fd))==-1)
    {
        perror("File read error");
        exit(EXIT_FAILURE);
    };

    return 0;
}

int supprimerLevel(TableAdressage_s * tableAdresse, TableVide_s * tableVide, int niv) {

    int fd = open("file.bin", O_RDWR);
    int err;

    // Lecture de la table d'adresses
    lseek(fd, 0, SEEK_SET);
    if((err=read(fd, tableAdresse, sizeof(TableAdressage_s)))==-1)
    {
        perror("File read error");
        exit(EXIT_FAILURE);
    };

    // Lecture de la table de vide
    lseek(fd, sizeof(TableAdressage_s), SEEK_SET);
    if((err=read(fd, tableVide, sizeof(TableVide_s)))==-1)
    {
        perror("File read error");
        exit(EXIT_FAILURE);
    };

    // Vérifier que l'index est valide
    int index =niv;
    if (index < 0 || index >= N || tableAdresse->adresse[index] == 0) {
        printf("Entrée non valide\n");
        return 1;
    }

    // Supprimer l'entrée de la table d'adresses
    off_t adresse = tableAdresse->adresse[index];
    tableAdresse->adresse[index] = 0;

    // Ajouter un trou à la table de vide
    for (int i = 0; i < N; i++) {
        if (tableVide->taille[i] == 0) {
            level_t* buffer = (level_t*) malloc(sizeof(level_t));
            lseek(fd, adresse, SEEK_SET);
            if((err=read(fd, buffer, sizeof(level_t)))==-1)
            {
                perror("File read error");
                exit(EXIT_FAILURE);
            };
            tableVide->debut[i] = adresse;
            tableVide->taille[i] = sizeof(level_t);
            break;
        }
    }

    // Mettre à jour la table d'adresses et la table de vide dans le fichier
    lseek(fd, 0, SEEK_SET);
    if((err=write(fd, tableAdresse, sizeof(TableAdressage_s)))==-1)
    {
        perror("File write error");
        exit(EXIT_FAILURE);
    };
    lseek(fd, sizeof(TableAdressage_s), SEEK_SET);
    if((err=write(fd, tableVide, sizeof(TableVide_s)))==-1)
    {
        perror("File write error");
        exit(EXIT_FAILURE);
    };

    if((err=close(fd))==-1)
    {
        perror("Close error");
        exit(EXIT_FAILURE);
    };
    
    return 0;
}

   