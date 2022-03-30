#include <iostream>
#include <stdlib.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr

//#define PORT 8000
using namespace std;
int port = 8000;
int k = 0;
int main(int argc, char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;
    char *message, server_reply[500], server_reply2[500], server_reply3[15000];
    while (1)
    {
        // Create socket
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_desc == -1)
        {
            cout << "Could not create socket\n";
            exit(EXIT_FAILURE);
        }
        // struct sockaddr_in server;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_family = AF_INET;
        server.sin_port = htons(port);

        // Connect to remote server
        //cout << port << endl;
        if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
        {
            //puts("connect error");
            port++;
            continue;
        }

        //puts("Connected\n");
        cout << "Connected: " << port << "\n\n";

        if (recv(socket_desc, server_reply, 2000, 0) < 0)
        {
            puts("recv1 failed");
        }

        if (k == 0)
        {
            puts("Reply received\n");
            puts(server_reply);
        }

        if (recv(socket_desc, server_reply2, 2000, 0) < 0)
        {
            puts("recv2 failed");
        }

        if (k == 0)
        {
            puts("Reply2 received\n");
            puts(server_reply2);
        }

        char buff[15000];
        while (1)
        {
            int i = 0;
            if (k == 0)
            {
                do
                {
                    buff[15000] = {0};
                    buff[i] = getchar();
                    cout << buff[i];
                    if (buff[i] == '\n')
                    {
                        buff[i] = 0;
                        break;
                    }
                    i++;
                } while (true);
            }
            else
            {
                k = 0;
            }

            message = buff;

            if (send(socket_desc, message, strlen(message), 0) <= 0)
            {
                //puts("Send failed");
                port++;
                break;
            }

            if ((recv(socket_desc, server_reply3, 15000, 0) <= 0))
            {
                //puts("recv3 failed");
                port++;
                k++;
                break;
            }
            puts("Reply3 received");
            puts(server_reply3);

            memset(server_reply3, 0, sizeof(server_reply3));

            if ((strcmp(message, "-q")) == 0)
            {
                puts("Do svidaniya! do widzenia!");
                return 1;
            }
            cout << endl;
        }
    }
}
