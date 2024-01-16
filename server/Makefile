CC=clang
SOURCE = src/server.c
BINARY = server.bin

all: server.bin

$(BINARY): $(SOURCE)
	$(CC) $< -o $@

scan: $(SOURCE)
	scan-build -o $(BINARY) make

clean:
	rm -rf $(BINARY)