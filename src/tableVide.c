

#include "tableVide.h"

TableVide_s *creation_table_vide()
{
    TableVide_s *table = (TableVide_s *)malloc(sizeof(TableVide_s));
    memset(table->debut, 0, sizeof(table->debut));
    memset(table->taille, 0, sizeof(table->taille));
    return table;
}

void ajout_table_vide(TableVide_s *table, off_t debut, off_t taille, int index)
{
    table->debut[index] = debut;
    table->taille[index] = taille;
}

void supprimer_table_vide(TableVide_s *table, int index)
{
    table->debut[index] = 0;
    table->taille[index] = 0;
}

off_t lire_table_vide(TableVide_s *table, int index)
{
    return table->debut[index];
}

void affichage_table_vide(TableVide_s *table)
{
    for (int i = 0; i < N; i++)
    {
        printf("Trou %d: début=%ld, taille=%d\n", i, table->debut[i], table->taille[i]);
    }
}
