#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "include.h"

void fils(int nbJ)
{
    printf("Lancement du serveur...");
    switch (nbJ)
    {
    case 1:
        printf("Le nombre de joueur requis est bon");
        break;
    case 2:
    case 3:
    case 4:
        printf("En attente de joueurs");
        break;
    }
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{

    // Variables Jeu
    int occupe = 0, nbJoueur;
    // Vauriables Serveur
    int sockfd;
    struct sockaddr_in server_address, client_address;
    request_t request;
    response_t response;
    socklen_t size = sizeof(struct sockaddr_in);
    // Création socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("Erreur lors de la création de la socket.");
        exit(EXIT_FAILURE);
    }

    // Remplissage adresse du serveur
    memset(&server_address, 0, sizeof(struct sockaddr_in));
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Nommage de la socket
    if (bind(sockfd, (struct sockaddr *)&server_address, sizeof(struct sockaddr_in)) == -1)
    {
        perror("Erreur nommage socket");
        exit(EXIT_FAILURE);
    }

    while (occupe == 0)
    {
        // En attente d'une requête d'un client
        printf("Serveur: en attente d'une requête.\n");
        if (recvfrom(sockfd, &request, sizeof(request), 0, (struct sockaddr *)&client_address, &size) == -1)
        {
            perror("Erreur lors de la réception de la requête");
            exit(EXIT_FAILURE);
        }

        // Vérification requête
        printf("Serveur: message reçu : '%s'.\n", request.msg);
        if (strcmp(request.msg, "Jouer") == 0)
        {
            occupe = 1;
        }

        // Affichage menu et démarrage de partie
        if (occupe == 1)
        {

            // Réponse (menu)
            strcpy(response.msg, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n----------------------------------------------------\n\t\t\tJEU\n----------------------------------------------------\n\n\t[1] Créer une partie.\n\t[2] Rejoindre une partie existante.\n----------------------------------------------------\n\n\n\n\n\n\n\n");

            // Envoi menu :
            if (sendto(sockfd, &response, sizeof(response), 0, (struct sockaddr *)&client_address, sizeof(struct sockaddr_in)) == -1)
            {
                perror("Erreur lors de l'envoi d'une requête");
                exit(EXIT_FAILURE);
            }
            printf("Serveur: menu envoyé.\n");

            // Attente réponse (tant que mauvais réponse)
            printf("Serveur: en attente de la réponse du client\n");
            do
            {
                if (recvfrom(sockfd, &request, sizeof(request), 0, (struct sockaddr *)&client_address, &size) == -1)
                {
                    perror("Erreur lors de la réception de la requête");
                    exit(EXIT_FAILURE);
                }
                printf("Serveur: message reçu : '%s'.\n", request.msg);
            } while (strcmp(request.msg, "1") != 0 && strcmp(request.msg, "2") != 0);

            // Switch pour choix du joueur (créer ou rejoindre)
            switch (atoi(request.msg))
            {
            // Créer partie
            case 1:
                strcpy(response.msg, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n----------------------------------------------------\n\t\t\tJEU\n----------------------------------------------------\n\n\tVeuillez entre le nombre de joueur (MAX 4).\n----------------------------------------------------\n\n\n\n\n\n\n\n\n\n\n");

                // Envoi demande nbre de joueurs :
                if (sendto(sockfd, &response, sizeof(response), 0, (struct sockaddr *)&client_address, sizeof(struct sockaddr_in)) == -1)
                {
                    perror("Erreur lors de l'envoi d'une requête");
                    exit(EXIT_FAILURE);
                }
                printf("Serveur: demande de nombre de joueur envoyé.\n");

                // Récupération nombre de joueurs :
                if (recvfrom(sockfd, &request, sizeof(request), 0, (struct sockaddr *)&client_address, &size) == -1)
                {
                    perror("Erreur lors de la réception de la requête");
                    exit(EXIT_FAILURE);
                }
                printf("Serveur: nombre de joueur pour la partie ( message reçu ) : '%s'.\n", request.msg);
                nbJoueur = atoi(request.msg);

                // Dans le fils
                if (fork() == 0)
                {
                    fils(nbJoueur);
                }
                break;

            // Rejoindre partie
            case 2:
                strcpy(response.msg, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n----------------------------------------------------\n\t\t\tJEU\n----------------------------------------------------\n\n\t\tListe des parties en cours :\n----------------------------------------------------\n\n\n\n\n\n\n\n\n\n\n");
                // Envoi liste de parties en cours :
                if (sendto(sockfd, &response, sizeof(response), 0, (struct sockaddr *)&client_address, sizeof(struct sockaddr_in)) == -1)
                {
                    perror("Erreur lors de l'envoi d'une requête");
                    exit(EXIT_FAILURE);
                }
                printf("Serveur: liste de parties en cours envoyée.\n");
                break;
            }
        }
    }

    // Fermeture socket
    if (close(sockfd) == -1)
    {
        perror("Erreur fermeture de la socket");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
