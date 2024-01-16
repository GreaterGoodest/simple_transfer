#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <sys/socket.h>

#include "transfer.h"

const long CHUNK_SIZE = 2*MB;

ssize_t getFileSize(FILE *filePtr)
{
    ssize_t fileSize = -1;

    if (fseek(filePtr, 0L, SEEK_END) < 0)
    {
        perror("Fseek failure."); return -1;
    }

    fileSize = ftell(filePtr);
    if (fileSize < 0)
    {
        perror("Failed to retrive file size."); return -1;
    }

    rewind(filePtr);

    return fileSize;
}

int sendChunk(FILE *filePtr, int clientFD, uint8_t* buffer)
{
    int retval = 0;
    int chunksRead = 0;

    chunksRead = fread(buffer, sizeof(uint8_t), CHUNK_SIZE, filePtr);
    if (send(clientFD, buffer, chunksRead, 0) < 0)
    {
        perror("Failed to send data to client.");
        retval = 1; goto cleanup;
    }

cleanup:
    memset(buffer, 0, CHUNK_SIZE);
    return retval;
}

__attribute__((flatten)) int transferFile(int clientFD)
{
    int retval = 0;
    FILE *filePtr = NULL;
    ssize_t fileSize = -1;
    uint8_t *buffer = NULL;
    
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

    long chunks = 1;
    int currentChunk = 0;
    if (fileSize > CHUNK_SIZE) 
    {
        chunks = (fileSize + CHUNK_SIZE - 1) / CHUNK_SIZE; //round up after dividing
    }

    buffer = calloc(CHUNK_SIZE, sizeof(uint8_t));
    while (currentChunk < chunks)
    {
        if (sendChunk(filePtr, clientFD, buffer) != 0)
        {
            puts("sendChunk Failure.");
            retval = 1; goto cleanup;
        }
        currentChunk++;
    }

cleanup:
    return retval;
}