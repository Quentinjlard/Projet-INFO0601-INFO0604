#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "include.h"

/**
 *  Se connecter au serveur, par défaut :
 *  Port : 1234
 *  Adresse : 127.0.0.1
 */


int main(int argc, char *argv[]) {

    //Variables jeu
    int choix;
    int nbJoueur;

    //Variables serveur
    int sockfd,port;
    char msg[MAX];
    struct sockaddr_in address;
    char adresseServeur[MAX];
    request_t request = { "Jouer" };
    response_t response;

    
    // Création socket
    if((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    //Vérification nombre paramètres (Adresse + Port)
    if (argc != 3) {
        perror("Utilisation : ./client ADRESSE PORT");
        exit(EXIT_FAILURE);
    }

    //Récupération adresse serveur
    strcpy(adresseServeur,argv[1]);

    //Récupération port UDP
    port = atoi(argv[2]);

    // Remplissage serveur adresse
    memset(&address, 0, sizeof(struct sockaddr_in));
    address.sin_family = AF_INET;
    address.sin_port = htons(atoi(argv[2]));
    if(inet_pton(AF_INET, argv[1], &address.sin_addr) != 1) {
        perror("Erreur conversion de l'adresse");
        exit(EXIT_FAILURE);
    }

    // Envoie requête
    if(sendto(sockfd, &request, sizeof(request), 0, (struct sockaddr*)&address, sizeof(struct sockaddr_in)) == -1) {
        perror("Erreur lors de l'envoi du message");
        exit(EXIT_FAILURE);
    }

    // Attente réponse
    if(recvfrom(sockfd, &response, sizeof(response), 0, NULL, 0) == -1) {
        perror("Erreur récupération ");
        exit(EXIT_FAILURE);
    }
    printf("%s", response.msg);

    //Attente entrée pour choix (créer partie ou rejoindre) (1 ou 2 en boucle)
    do {
        scanf("%s",msg);
        if (strcmp(msg,"1") == 0 && strcmp(msg,"2") == 0) {
            printf("Vous avez entré %s, veuillez entrer 1 ou 2.\n",msg);
        }
    } while( strcmp(msg,"1") == 0 && strcmp(msg,"2") == 0);
    strcpy(request.msg,msg);
    choix = atoi(msg);

    // Envoie réponse
    if(sendto(sockfd, &request, sizeof(request), 0, (struct sockaddr*)&address, sizeof(struct sockaddr_in)) == -1) {
        perror("Erreur lors de l'envoi du message");
        exit(EXIT_FAILURE);
    }

    // Attente réponse
    if(recvfrom(sockfd, &response, sizeof(response), 0, NULL, 0) == -1) {
        perror("Erreur récupération");
        exit(EXIT_FAILURE);
    }
    printf("%s", response.msg);

    switch(choix) {

        //Créer partie
        case 1:

            //Attente entrée pour nbJoueurs
            do {
                scanf("%s",msg);
                if (atoi(msg) > 4 || atoi(msg) <= 0) {
                    printf("Vous avez entré %s, veuillez entrer un nombre entre 1 et 4.\n",msg);
                }
            } while( atoi(msg) > 4 || atoi(msg) <= 0);
            nbJoueur = atoi(msg);
            strcpy(request.msg,msg);

            // Envoie réponse
            if(sendto(sockfd, &request, sizeof(request), 0, (struct sockaddr*)&address, sizeof(struct sockaddr_in)) == -1) {
                perror("Erreur lors de l'envoi du message");
                exit(EXIT_FAILURE);
            }
        break;
        //Rejoindre partie
        case 2: 
        break;
    }

        




    // Fermeture socket
    if(close(sockfd) == -1) {
        perror("Erreur lors de la fermeture de la socket");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

