# Simple client used to interact with concurrent servers.
#
# Launches N concurrent client connections, each executing a pre-set sequence of
# sends to the server, and logs what was received back.
#
# Slightly adapted from the implementation by:
# Eli Bendersky [https://eli.thegreenplace.net]
# This code is in the public domain.

import argparse
import logging
import socket
import sys
import threading
import time
import struct


def make_new_connection(name, host, port):
    """Creates a single socket connection to the host:port.

    Sets a pre-set sequence of messages to the server with pre-set delays; in
    parallel, reads from the socket in a separate thread.
    """
    t1 = time.time()

    sockobj = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sockobj.connect((host, port))
    logging.info('{0} connected...'.format(name))

    num = 42
    logging.info('{0} sending {1}'.format(name, num))
    sockobj.send(num.to_bytes(8, 'little', signed=False))

    buf = sockobj.recv(8)
    rec_num = int.from_bytes(buf, 'little', signed=False)
    logging.info('{0} received {1}'.format(name, rec_num))

    sockobj.close()
    logging.info('{0} disconnecting'.format(name))

    print('Elapsed:', time.time() - t1)


def main():
    argparser = argparse.ArgumentParser('Simple TCP client')
    argparser.add_argument('host', help='Server host name')
    argparser.add_argument('port', type=int, help='Server port')
    argparser.add_argument('-n', '--num_concurrent', type=int,
                           default=1,
                           help='Number of concurrent connections')
    args = argparser.parse_args()

    logging.basicConfig(
        level=logging.DEBUG,
        format='%(levelname)s:%(asctime)s:%(message)s')

    connections = []
    for i in range(args.num_concurrent):
        name = 'conn{0}'.format(i)
        tconn = threading.Thread(target=make_new_connection,
                                 args=(name, args.host, args.port))
        tconn.start()
        connections.append(tconn)

    for conn in connections:
        conn.join()


if __name__ == '__main__':
    main()
