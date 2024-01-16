#pragma once

#include <unistd.h>
#include <stdio.h>

#define KB 1024
#define MB 1024*KB  
#define TRANSFER_TARGET "/tmp/test_file"

int transferFile(int clientFD);