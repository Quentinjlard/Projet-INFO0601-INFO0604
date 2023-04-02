/**
 * @file include.h
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @author COGNE Romain (romain.cogne@etudiant.univ-reims.fr)
 * @brief
 * @version 0.1
 * @date 2023-02-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _INCLUDE_
#define _INCLUDE_

// Maximum message size
#define MAX 256

// Port
#define PORT 1234
#define PORT2 0

// Request
typedef struct
{
    char msg[MAX * 2];
} request_t;

// Response
typedef struct
{
    char msg[MAX * 2];
} response_t;

void client();

#endif
