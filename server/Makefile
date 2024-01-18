CC=clang
SOURCE = src/server.c src/transfer.c src/crypto.c
HEADERS = include/crypto.h include/transfer.h
BINARY = server.bin
INCLUDE = -Iinclude -Ilibs/mbedtls/include
LIBS_PATH = -Llibs/mbedtls/library
LIBS = -lmbedtls -lmbedcrypto -lmbedx509

all: server.bin

$(BINARY): $(SOURCE) 
	$(CC) $(SOURCE) -o $@ $(INCLUDE) $(LIBS_PATH) $(LIBS)

scan: $(SOURCE)
	scan-build -o $(BINARY) make
	clang-tidy $(SOURCE) -- $(INCLUDE)

clean:
	rm -rf $(BINARY)