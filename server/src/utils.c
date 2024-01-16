#include <stdio.h>
#include <unistd.h>

#include "utils.h"

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