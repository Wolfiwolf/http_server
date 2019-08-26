#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define LOG(x) printf("%s\n",x)

#include "HelperFunctions.h"

const char* get_requested_file(const char* request, const char* website_dir)
{
    FILE* file = fopen(website_dir, "r");

    char* reply = (char*)malloc(4069);

    char* temp = (char*)malloc(1024);
    temp[0] = 1;
    while(temp[0] != 0)
    {
        memset(temp, 0, 1024);
        fgets(temp, 4069, file);
        reply = join_strings(reply, temp);
    }

    free(temp);

    return reply;
}

const char* http_request_reply(const char* request, const char* website_dir)
{
    const char* header = "HTTP/1.1 200 OK\n Content-Type: text/html\nContent-Lenght: ";


    const char* body = get_requested_file(request, website_dir);

    int body_lenght = strlen(body);
    char lenght_string[32];
    sprintf(lenght_string, "%d", body_lenght);


    const char* full_header = join_strings(header, lenght_string);

    full_header = join_strings(full_header, "\n\n");


    const char* reply = join_strings(full_header, body);


    return reply;
}


int main()
{

    char website_dir[50];

    printf("Something like this -> [/home/user/website/index.html)]\n");
    printf("WEBSITE FILEPATH: ");
    scanf("%s",website_dir);
    printf("Default: 50132\n");
    printf("Run on port: ");
    int port;
    scanf("%d", &port);




    //STARTING SERVER

    printf("Server started!\nURL: http://localhost:%d", port);

    int listening_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(listening_socket < 0)
    {
        LOG("Can't open socket!");
        return 0;
    }


    struct sockaddr_in address;

    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_family = AF_INET;
    address.sin_port = htons(port);


    int success = bind(listening_socket, (struct sockaddr*)&address, sizeof(address));

    if(success < 0)
    {
        LOG("Binding failed!");
        return 0;
    }

    if(listen(listening_socket, 3) < 0)
    {
        LOG("Listen failed!");
        return 0;
    }

    int addrlen = sizeof(address);



    while(1)
    {

        int client_socket = accept(listening_socket, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if(client_socket < 0)
        {
            LOG("Accept failed!");
            return 0;
        }
        printf("Request catched!\n");



        char buffer[1024];
        memset(buffer, 0, 1024);

        int num_of_bytes = read(client_socket, buffer, 1024);

        if(num_of_bytes < 0)
        {
            LOG("No bytes to read!");
        }
        printf("%s", buffer);

        const char* reply = http_request_reply(buffer, website_dir);

        write(client_socket, reply, strlen(reply));
        printf("File sent to browser!\n");

        close(client_socket);
    }

    close(listening_socket);


    return 0;
}
