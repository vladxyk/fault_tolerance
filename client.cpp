#include<iostream>
#include<stdlib.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h>    //inet_addr

using namespace std;

int main(int argc , char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;
    char *message, server_reply[500], server_reply2[500], server_reply3[15000];
    //int port = atoi(argv[1]);
    int port = 8000;
    while(1){
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        cout << "Could not create socket";
    }    
    //struct sockaddr_in server;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    //socklen_t len = sizeof(server);
    //cout << getsockname(socket_desc, (struct sockaddr *)&server, &len) << endl;
    //Connect to remote server
    cout << port << endl;
    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        //return 1;
        port++;
        continue;
    }
    //cout << port << endl;
    puts("Connected\n");

    if( recv(socket_desc, server_reply , 2000 , 0) < 0){
        puts("recv1 failed");
    }
    puts("Reply received\n");
    puts(server_reply);
    
    
    if( recv(socket_desc, server_reply2 , 2000 , 0) < 0){
        puts("recv2 failed");
    }
    puts("Reply2 received\n");
    puts(server_reply2);
    
    
    while(1){
        int k = 3;
        char buff[15000] = {0};
        //scanf("%199[^\n]",buff);
        int i = 0;
        do{
            buff[i] = getchar(); 
            cout << buff[i];
            if (buff[i] == '\n'){
                buff[i] = 0;
                break;
            }
            i++;
        } while (true);
        //cin >> buff;
        message = buff;
        if( send(socket_desc , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
        if( (recv(socket_desc, server_reply3 , 15000 , 0) < 0))
        {
            puts("recv3 failed");
            fflush(stdout);
		    exit(EXIT_FAILURE);
        }
        puts("Reply3 received");
        puts(server_reply3);
        
        memset(server_reply3, 0, sizeof(server_reply3));
        
        if((strcmp(message, "-q")) == 0){
            puts("BLYAAAA");
            return 1;
        }
        cout << endl;
        
    }
    //return 0;
    }
}