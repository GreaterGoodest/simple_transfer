CC=clang
SOURCE = src/server.c src/transfer.c
BINARY = server.bin
INCLUDE = -Iinclude

all: server.bin

$(BINARY): $(SOURCE) 
	$(CC) $(SOURCE) -o $@ $(INCLUDE)

scan: $(SOURCE)
	scan-build -o $(BINARY) make

clean:
	rm -rf $(BINARY)