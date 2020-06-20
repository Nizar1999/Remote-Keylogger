#include "stdio.h"
#include "winsock2.h"

#pragma comment(lib, "ws2_32.lib")

int main()
{
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server , client;
    int c;
    char key[10];

    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
    
    printf("Initialised.\n");
    
    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    printf("Socket created.\n");
    
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(31415);
    
    //Bind
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
    }
    
    puts("Bind done");
    

    //Listen to incoming connections
    listen(s , 3);
    
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    
    c = sizeof(struct sockaddr_in);
    int recv_size;
    FILE *log;

    connect:
        new_socket = accept(s , (struct sockaddr *)&client, &c);
        while(1) {
            recv_size = recv(new_socket, key, sizeof(key), 0);
            if(recv_size != -1) {
                log = fopen("log.txt", "a");
                printf("%d", recv_size);
                fputs(key, log);
                fclose(log);
            } else {
                fclose(log);
                goto connect;
            }
        }

    getch();
    if (new_socket == INVALID_SOCKET)
    {
        printf("accept failed with error code : %d" , WSAGetLastError());
    }
    
    puts("Connection accepted");

    closesocket(s);
    WSACleanup();

    return 0;
}