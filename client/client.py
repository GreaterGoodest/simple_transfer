#!/usr/bin/python
import socket

ADDRESS = "127.1"
PORT = 1337
KB = 1024
MB = 1024*KB
CHUNK_SIZE = 2*MB

def receive_chunk(session: socket.socket):
    data = bytearray()

    while len(data) < CHUNK_SIZE:
        packet = session.recv(CHUNK_SIZE - len(data))
        if not packet:
            return data
        data.extend(packet)

    return data

def connect_and_receive():
    ''''''
    session = socket.socket()
    try:
        session.connect((ADDRESS, PORT))
    except ConnectionRefusedError:
        print('Unable to connect to server due to connection refusal')
        return
    except Exception as e:
        print(f'Unable to connect due to unknown error case: {e}')
        return

    file = open('received_file', 'wb+')
    breakpoint()
    for _ in range(2):
        data = receive_chunk(session)
        file.write(data)





if __name__ == '__main__':
    connect_and_receive()