#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "utils.h"

#define PORT 1337
#define MAX_CON 10
#define ADDR "127.1"

#define KB 1024
#define CHUNK_SIZE 64*KB  // Max data size per packet

#define TRANSFER_TARGET "/tmp/test_file"


int main()
{
    int retval = 0;
    int clientFD = -1;
    int serverFD = -1;
    FILE *filePtr = NULL;
    ssize_t fileSize = -1;
    struct sockaddr_in server = {0};
    struct sockaddr_in client = {0};

    serverFD = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFD < 0)
    {
        perror("Server socket creation failed.");
        retval = 1; goto cleanup;
    }

    if (setsockopt(serverFD, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
    {
        perror("Failed to setsockopt.");
        retval = 1; goto cleanup;
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(ADDR);

    if (bind(serverFD, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Bind failure.");
        retval = 1; goto cleanup;
    }

    if (listen(serverFD, MAX_CON) < 0)
    {
        perror("Listen failure.");
        retval = 1; goto cleanup;
    }

    socklen_t addrSize;
    clientFD = accept(serverFD, (struct sockaddr*)&client, &addrSize);
    if (clientFD < 0)
    {
        perror("Failed to accept client connection");
        retval = 1; goto cleanup;
    }

    puts("Got connection.");

    filePtr = fopen(TRANSFER_TARGET, "rb");
    if (NULL == filePtr)
    {
        perror("Failed to open transfer target.");
        retval = 1; goto cleanup;
    }

    fileSize = getFileSize(filePtr);
    if (fileSize < 0)
    {
        puts("getFileSize Failure.");
        retval = 1; goto cleanup;
    }

    printf("Transfering %s. File size: %zd\n", TRANSFER_TARGET, fileSize);

cleanup:
    if (clientFD)
    {
        if (close(clientFD) < 0) { perror("Failed to close clientFD."); }
    }
    if (serverFD)
    {
        if (close(serverFD) < 0) { perror("Failed to close serverFD."); }
    }
    return retval;
}