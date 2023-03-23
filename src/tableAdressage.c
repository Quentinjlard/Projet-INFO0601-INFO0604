

#include "tableAdressage.h"

#define N 20

TableAdressage_s *creation_table()
{
    TableAdressage_s *table = (TableAdressage_s *)malloc(sizeof(TableAdressage_s));
    memset(table->adresse, 0, sizeof(table->adresse));
    return table;
}

void ajout_table_adressage(TableAdressage_s *table, off_t addresse, int index)
{
    table->adresse[index] = addresse;
}

void supprimer_table_adressage(TableAdressage_s *table, int index)
{
    table->adresse[index] = 0;
}

off_t lire_table_adressage(TableAdressage_s *table, int index)
{
    return table->adresse[index];
}

void affichage_table_adressage(TableAdressage_s *table)
{
    for (int i = 0; i < N; i++)
    {
        printf("Adresse %d: %ld\n", i, table->adresse[i]);
    }
}
