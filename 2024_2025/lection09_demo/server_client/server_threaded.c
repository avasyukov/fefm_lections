#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct {
    int sockfd;
} thread_config_t;

void serve_connection(int sockfd) {
    // Receive something from client.
    unsigned long some_num = 0;
    recv(sockfd, &some_num, sizeof(some_num), 0);
    printf("Received from client: %lu\n", some_num);

    // We pretend that we are doing hard work here
    sleep(1);
    some_num++;

    // Send something to client.
    send(sockfd, &some_num, sizeof(some_num), 0);
    printf("Sent to client: %lu\n", some_num);
}

void* server_thread(void* arg) {
    thread_config_t* config = (thread_config_t*)arg;
    int sockfd = config->sockfd;
    free(config);

    // This cast will work for Linux, but in general casting pthread_id is not portable.
    unsigned long id = (unsigned long)pthread_self();
    printf("Thread %lu created to handle connection with socket %d\n", id, sockfd);

    serve_connection(sockfd);

    printf("Thread %lu done\n", id);

    return NULL;
}

int main() {
    // Initialize variables
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_addr;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8989);

    // Bind the socket to the address and port number.
    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Listen on the socket with 50 max connection requests queued.
    if (listen(server_socket, 50) == 0) {
        printf("Listening\n");
    } else {
        printf("Error\n");
        exit(-1);
    }

    while (1) {
        struct sockaddr peer_addr;
        socklen_t peer_addr_len = sizeof(peer_addr);

        // Extract the first connection in the queue
        int newsockfd = accept(server_socket, &peer_addr, &peer_addr_len);

        printf("Peer connected\n");

        pthread_t worker_thread;

        thread_config_t* config = malloc(sizeof(thread_config_t));
        config->sockfd = newsockfd;
        pthread_create(&worker_thread, NULL, server_thread, config);

        // Detach the thread - when it's done, its resources will be cleaned up.
        // Since the main thread lives forever, it will outlive the serving threads.
        // FIXME: we should handle server exit gracefully.
        pthread_detach(worker_thread);
    }

    return 0;
}