#ifndef HTTPS_C
#define HTTPS_C

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>


#include <dirent.h>
#include <sys/stat.h>
#include <signal.h>


#define PORT 443
#define BIND_ADDR "0.0.0.0"

#define CERT_FILE "/home/itamar/Documents/Workspace/Backend/certs/cert.pem"
#define KEY_FILE  "/home/itamar/Documents/Workspace/Backend/certs/key.pem"
//#define CERT_FILE "/etc/letsencrypt/live/opaq.co.il/fullchain.pem"
//#define  KEY_FILE "/etc/letsencrypt/live/opaq.co.il/privkey.pem"
#define HOME      "/home/itamar/Documents/Workspace/www"
#define ITL_C     "/home/itamar/Documents/Workspace/itl/code.itl"
#define BACKLOG 10


#include "ITL/itl.h"

#include "SSL.h"
#include "io.h"  // depends -> helpers, file


// 

    

void https_start(){

    load_program();

    files = getAllFilePaths(HOME);

    
    DUMP_PATHS for (int i = 0; i < files.count; i++)
      fprintf(stdout,"\e[94m%s\e[0m\n", files.paths[i]);
    
    SSL_CTX *ctx = create_ssl_context();
    configure_ssl_context(ctx);

    int s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) {
        perror("Socket creation failed");
        SSL_CTX_free(ctx);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = inet_addr(BIND_ADDR); //INADDR_ANY;

    int reuse = 1;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
        perror("setsockopt failed");
        close(s);
        SSL_CTX_free(ctx);
        exit(EXIT_FAILURE);
    }


    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Bind failed");
        close(s);
        SSL_CTX_free(ctx);
        exit(EXIT_FAILURE);
    }

    if (listen(s, BACKLOG) < 0) {
        perror("Listen failed");
        close(s);
        SSL_CTX_free(ctx);
        exit(EXIT_FAILURE);
    }

    fprintf(stdout,"\e[0;93mHTTPS Server is listening on \e[96m%s\e[97m:\e[92m%d\e[0m\n", BIND_ADDR, PORT);

    while (1) {
        connection_t *connection = malloc(sizeof(connection_t));
        if (!connection) {
            perror("Memory allocation failed");
            continue;
        }

        socklen_t client_len = sizeof(connection->address);
        connection->sock = accept(s, (struct sockaddr *)&connection->address, &client_len);
        connection->ctx = ctx;

        if (connection->sock < 0) {
            perror("Accept failed");
            free(connection);
            continue;
        }

        // Spawn a new thread for handling the client
        pthread_t thread;
        if (pthread_create(&thread, NULL, handle_client, connection) != 0) {
            perror("Thread creation failed");
            close(connection->sock);
            free(connection);
        } else {
            pthread_detach(thread); // Detach the thread to avoid memory leaks
        }
    }

    fprintf(stdout,"SERVER CRASHED\n");
    close(s);
    SSL_CTX_free(ctx);
    for (int i = 0; i < files.count; i++)
        free(files.paths[i]);
    free(files.paths);
}
#endif
