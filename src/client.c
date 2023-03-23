#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "include.h"
#include "includeAll.h"

/**
 *  Se connecter au serveur, par défaut :
 *  Port : 1234
 *  Adresse : 127.0.0.1
 */

void client()
{

    // Variables jeu
    int choix, nbJoueur = 1;

    // Variables serveur UDP
    int sockfd, port;
    char msg[MAX];
    struct sockaddr_in address;
    char adresseServeur[MAX];
    request_t request = {"Jouer"};
    response_t response;

    // Variables serveur TCP
    int portTCP, fd;
    struct sockaddr_in addressTCP;

    // Création socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nVeuillez saisir l'adresse du serveur.\n ");
    // Récupération adresse serveur
    if (scanf("%s", adresseServeur) == -1)
    {
        perror("Erreur saisie");
        exit(EXIT_FAILURE);
    };

    printf("Veuillez saisir le port du serveur.\n ");
    // Récupération port UDP
    if (scanf("%d", &port) == -1)
    {
        perror("Erreur saisie");
        exit(EXIT_FAILURE);
    };

    // Remplissage serveur adresse
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (inet_pton(AF_INET, adresseServeur, &address.sin_addr) != 1)
    {
        perror("Erreur conversion de l'adresse");
        exit(EXIT_FAILURE);
    }

    // Envoie requête
    if (sendto(sockfd, &request, sizeof(request), 0, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) == -1)
    {
        perror("Erreur lors de l'envoi du message");
        exit(EXIT_FAILURE);
    }

    // Attente réponse
    if (recvfrom(sockfd, &response, sizeof(response), 0, NULL, 0) == -1)
    {
        perror("Erreur récupération ");
        exit(EXIT_FAILURE);
    }
    printf("\n\n\n\n\n%s", response.msg);

    // Attente entrée pour choix (créer partie ou rejoindre) (1 ou 2 en boucle)
    do
    {
        if (scanf("%s", msg) == -1)
        {
            perror("Erreur saisie");
            exit(EXIT_FAILURE);
        }
        if (strcmp(msg, "1") == 0 && strcmp(msg, "2") == 0)
        {
            printf("Vous avez entré %s, veuillez entrer 1 ou 2.\n", msg);
        }
    } while (strcmp(msg, "1") == 0 && strcmp(msg, "2") == 0);
    strcpy(request.msg, msg);
    choix = atoi(msg);

    // Envoie réponse
    if (sendto(sockfd, &request, sizeof(request), 0, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) == -1)
    {
        perror("Erreur lors de l'envoi du message");
        exit(EXIT_FAILURE);
    }

    // Attente réponse
    if (recvfrom(sockfd, &response, sizeof(response), 0, NULL, 0) == -1)
    {
        perror("Erreur récupération");
        exit(EXIT_FAILURE);
    }
    printf("\n\n\n\n\n%s", response.msg);

    switch (choix)
    {
    // Créer partie
    case 1:

        // Attente entrée pour nbJoueurs
        do
        {
            if (scanf("%s", msg) == -1)
            {
                perror("Erreur saisie");
                exit(EXIT_FAILURE);
            }
            if (atoi(msg) > 4 || atoi(msg) <= 0)
            {
                printf("Vous avez entré %s, veuillez entrer un nombre entre 1 et 4.\n", msg);
            }
        } while (atoi(msg) > 4 || atoi(msg) <= 0);
        nbJoueur = atoi(msg);
        strcpy(request.msg, msg);

        // Envoie réponse
        if (sendto(sockfd, &request, sizeof(request), 0, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) == -1)
        {
            perror("Erreur lors de l'envoi du message");
            exit(EXIT_FAILURE);
        }

        // Attente réponse (liste levels)
        if (recvfrom(sockfd, &response, sizeof(response), 0, NULL, 0) == -1)
        {
            perror("Erreur récupération");
            exit(EXIT_FAILURE);
        }
        printf("\n\n\n\n\n\n%s", response.msg);
        int verif = 0;
        while (verif != 1)
        {
            // Attente entrée pour niveau
            printf("\nVeuillez entrer un nom de niveau valide parmi ceux disponibles :\n ");
            if (scanf("%s", msg) == -1)
            {
                perror("Erreur saisie");
                exit(EXIT_FAILURE);
            }

            strcpy(request.msg, msg);

            // Envoie réponse
            if (sendto(sockfd, &request, sizeof(request), 0, (struct sockaddr *)&address, sizeof(struct sockaddr_in)) == -1)
            {
                perror("Erreur lors de l'envoi du message");
                exit(EXIT_FAILURE);
            }

            // Attente réponse (liste levels)
            if (recvfrom(sockfd, &response, sizeof(response), 0, NULL, 0) == -1)
            {
                perror("Erreur récupération");
                exit(EXIT_FAILURE);
            }

            if (strcmp(response.msg, "true") == 0)
            {
                verif = 1;
            }
        }

        break;
    // Rejoindre partie
    case 2:
        break;
    }

    // Récupération numéro de port UDP
    if (recvfrom(sockfd, &response, sizeof(response), 0, NULL, 0) == -1)
    {
        perror("Erreur récupération");
        exit(EXIT_FAILURE);
    }
    portTCP = atoi(response.msg);

    /**
     * Initialisation Connexion TCP
     */
    // Create socket
    if ((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
    {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Fill the address structure
    memset(&addressTCP, 0, sizeof(struct sockaddr_in));
    addressTCP.sin_family = AF_INET;
    addressTCP.sin_port = htons(portTCP);
    if (inet_pton(AF_INET, adresseServeur, &addressTCP.sin_addr.s_addr) != 1)
    {
        perror("Error converting address");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(fd, (struct sockaddr *)&addressTCP, sizeof(addressTCP)) == -1)
    {
        perror("Error connecting to the server");
        exit(EXIT_FAILURE);
    }

    // Lancement du jeu
    if (nbJoueur == 1)
    {
        playingField(request.msg);
    }

    // Fermeture socket
    if (close(sockfd) == -1)
    {
        perror("Erreur lors de la fermeture de la socket");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
