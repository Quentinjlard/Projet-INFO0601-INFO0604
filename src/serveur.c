#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>

#include "include.h"

void fils(int nbJ)
{

    printf("Lancement du serveur...\n");
    switch (nbJ)
    {
    case 1:
        printf("Le nombre de joueur requis est bon\n");
        break;
    case 2:
    case 3:
    case 4:
        printf("En attente de joueurs\n");
        break;
    }
    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    DIR *dossier;
    struct dirent *entree;
    char *extension;

    // Variables Jeu
    int occupe = 0, nbJoueur;
    char nomLevel[MAX];

    // Variables Serveur UDP
    int sockfd;
    struct sockaddr_in server_address, client_address;
    request_t request;
    response_t response;
    socklen_t size = sizeof(struct sockaddr_in);

    // Variables Serveur TCP
    int fd, sockclient;
    char portTCP[2560];
    struct sockaddr_in address;

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
            strcpy(response.msg, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n-------------------------------\n\tJEU\n-------------------------------\n\n [1] Créer une partie.\n [2] Rejoindre une partie existante.\n-------------------------------\n");

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
                strcpy(response.msg, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n-------------------------------\n\tJEU\n-------------------------------\n\n Veuillez entre le nombre de joueur (MAX 4).\n-------------------------------\n");

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
                strcpy(response.msg, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n-------------------------------\n\tJEU\n-------------------------------\n\n Liste des niveaux.\n-------------------------------\n");

                // Ouverture dossier, liste niveaux
                dossier = opendir(".");
                if (dossier != NULL)
                {

                    while ((entree = readdir(dossier)) != NULL)
                    {
                        extension = strrchr(entree->d_name, '.');
                        if (extension && !strcmp(extension, ".bin"))
                        {
                            strcat(response.msg, " - ");
                            strcat(response.msg, entree->d_name);
                            strcat(response.msg, "\n");
                        }
                    }
                }
                // Envoi liste des niveaux :
                if (sendto(sockfd, &response, sizeof(response), 0, (struct sockaddr *)&client_address, sizeof(struct sockaddr_in)) == -1)
                {
                    perror("Erreur lors de l'envoi d'une requête");
                    exit(EXIT_FAILURE);
                }
                printf("Serveur: liste des niveaux.\n");

                // Boucle pour choisir niveau par client
                int verif = 0;

                while (verif != 1)
                {
                    // Récupération nom de niveau :
                    if (recvfrom(sockfd, &request, sizeof(request), 0, (struct sockaddr *)&client_address, &size) == -1)
                    {
                        perror("Erreur lors de la réception de la requête");
                        exit(EXIT_FAILURE);
                    }
                    dossier = opendir(".");
                    if (dossier != NULL)
                    {
                        while ((entree = readdir(dossier)) != NULL)
                        {
                            extension = strrchr(entree->d_name, '.');
                            if (extension && !strcmp(extension, ".bin"))
                            {
                                printf("Nom de niveau reçu : %s \n", request.msg);
                                if (strcmp(request.msg, entree->d_name) == 0)
                                {
                                    verif = 1;
                                    strcpy(nomLevel, request.msg);
                                }
                            }
                        }
                    }

                    if (verif == 0)
                    {
                        strcpy(response.msg, "false");
                        if (sendto(sockfd, &response, sizeof(response), 0, (struct sockaddr *)&client_address, sizeof(struct sockaddr_in)) == -1)
                        {
                            perror("Erreur lors de l'envoi d'une requête");
                            exit(EXIT_FAILURE);
                        }
                        printf("Serveur: envoie réponse (mauvais nom de niveau).\n");
                    }
                }
                // Nom de niveau valide
                strcpy(response.msg, "true");
                if (sendto(sockfd, &response, sizeof(response), 0, (struct sockaddr *)&client_address, sizeof(struct sockaddr_in)) == -1)
                {
                    perror("Erreur lors de l'envoi d'une requête");
                    exit(EXIT_FAILURE);
                }
                printf("Serveur: demande d'envoi de niveau bien reçu.\n");

                closedir(dossier);

                /**
                 * Initialisation connexion TCP
                 */
                // Create socket
                if ((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
                {
                    perror("Error creating socket");
                    exit(EXIT_FAILURE);
                }

                // Fill server address
                memset(&address, 0, sizeof(struct sockaddr_in));
                address.sin_family = AF_INET;
                address.sin_addr.s_addr = htonl(INADDR_ANY);
                address.sin_port = htons(PORT2);

                // Name socket
                if (bind(fd, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) == -1)
                {
                    perror("Error naming socket");
                    exit(EXIT_FAILURE);
                }

                // Switch the socket in passive mode
                if (listen(fd, 1) == -1)
                {
                    perror("Error switching socket in passive mode");
                    exit(EXIT_FAILURE);
                }

                // Envoi du numéro de port TCP

                sprintf(portTCP, "%d", PORT2);

                strcpy(response.msg, portTCP);
                if (sendto(sockfd, &response, sizeof(response), 0, (struct sockaddr *)&client_address, sizeof(struct sockaddr_in)) == -1)
                {
                    perror("Erreur lors de l'envoi d'une requête");
                    exit(EXIT_FAILURE);
                }
                printf("Serveur: envoi numéro de port TCP.\n");

                // Wait for a connexion
                printf("Server: Attente d'une connexion client\n");
                if ((sockclient = accept(fd, NULL, NULL)) == -1)
                {
                    if (errno != EINTR)
                    {
                        perror("Error waiting connexion");
                        exit(EXIT_FAILURE);
                    }
                }

                // Dans le fils
                if (fork() == 0)
                {
                    fils(nbJoueur);
                }
                break;

            // Rejoindre partie
            case 2:
                strcpy(response.msg, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n----------------------------------------------------\n\t\t\tJEU\n----------------------------------------------------\n\n\t\tListe des parties en cours :\n----------------------------------------------------\n\n\n\n\n\n\n\n\n\n\n");
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
