#!/usr/bin/python
import socket
from Cryptodome.Cipher import AES

ADDRESS = "127.1"
PORT = 1337
KB = 1024
MB = 1024*KB
CHUNK_SIZE = 2*MB

key = bytes.fromhex('36864200e0eaf5284d884a0e77d31646')
iv = bytes.fromhex('00112233445566778899aabbccddeeff')
cipher = AES.new(key, AES.MODE_GCM, iv)

def decrypt(chunk: bytes) -> bytes:
    ''''''
    return cipher.decrypt(chunk[:-len(iv)])

def receive_chunk(session: socket.socket) -> bytes:
    data = bytearray()

    while len(data) < CHUNK_SIZE - len(iv):
        packet = session.recv(CHUNK_SIZE - len(data))
        if not packet:
            return data
        data.extend(decrypt(packet))

    return data

def connect_and_receive():
    session = socket.socket()
    try:
        session.connect((ADDRESS, PORT))
    except ConnectionRefusedError:
        print('Unable to connect to server due to connection refusal')
        return
    except Exception as e:
        print(f'Unable to connect due to unknown error case: {e}')
        return

    file = open('received_file', 'wb')
    while True:
        data = receive_chunk(session)
        file.write(data)
        if len(data) < CHUNK_SIZE - len(iv):
            break
        print('chunk')


if __name__ == '__main__':
    connect_and_receive()