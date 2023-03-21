#ifndef _INCLUDE_
#define _INCLUDE_

// Maximum message size
#define MAX 256

// Port
#define PORT 1234

// Request
typedef struct
{
    char msg[MAX];
} request_t;

// Response
typedef struct
{
    char msg[MAX];
} response_t;

void client();

#endif
