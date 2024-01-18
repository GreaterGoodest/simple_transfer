Just a basic file transfer implementation

# Setup

```python
pip install pycryptodomex #needed for GCM mode
```

Get clang-tools (Debian based instructions only). This gives you scan-build for static analysis.
```shell
apt install clang-tools
```

Setup mbedtls

```shell
git submodule update --init
cd server/libs/mbedtls; make
```

Build from project root

```shell
cd server; make
```

# Run

Place file to transfer at /tmp/test_file

In window A:

```shell
cd server; ./server.bin
```

In window B:

```shell
cd client; ./client.py
```


File will be encrypted and transfered then decrypted and dumped to disk.


# Static analysis

Uses clang's scan-build

```shell
cd server; make scan
```