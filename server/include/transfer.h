#pragma once

#include <unistd.h>
#include <stdio.h>

#define TRANSFER_TARGET "/tmp/test_file"

int transfer_file(int clientFD);