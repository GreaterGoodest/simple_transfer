#include <stdio.h>
#include <unistd.h>

#include "transfer.h"


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

__attribute__((flatten)) int transfer_file(int clientFD)
{
    int retval = 0;
    ssize_t fileSize = -1;
    FILE *filePtr = NULL;
    
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
    return retval;
}