#include <iostream>
#include <stdlib.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr

using namespace std;

int main(int argc, char *argv[])
{
    int port = 8000;
    bool tmp = true;
    char buff[2000];
    while (1)
    {
        int socket_desc;
        struct sockaddr_in server;
        char *message, server_reply[100], server_reply2[100], server_reply3[2000];

        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_desc == -1)
        {
            cout << "Could not create socket\n";
            exit(EXIT_FAILURE);
        }

        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_family = AF_INET;
        server.sin_port = htons(port);

        if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
            // puts("connect error");
            port++;
            continue;
        }

        if (tmp)
        {
            cout << "Connected: " << port << endl;
        }

        if ((recv(socket_desc, server_reply, 100, 0)) == -1)
        {
           cout << "recv1 failed" << endl;
        }
        if (tmp)
        {
            cout << server_reply << endl;
        }
        
        if ((recv(socket_desc, server_reply2, 100, 0)) == -1)
        {
            cout << "recv2 failed" << endl;
        }
        if (tmp)
        {
            cout << server_reply2 << endl;
        }

        while (1)
        {
            int i = 0;
            if (tmp)
            {
                do
                {
                    buff[2000] = {0};
                    buff[i] = getchar();
                    // cout << buff[i];
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
                tmp = true;
            }

            message = buff;
            if (((strncmp(message, "-q", 2)) != 0) && ((strncmp(message, "-h", 2)) != 0) && ((strncmp(message, "--help", 3)) != 0) && ((strncmp(message, "-mf", 3)) != 0) && ((strncmp(message, "-rmf", 4)) != 0) && ((strncmp(message, "-cf", 3)) != 0) && ((strncmp(message, "-ssf", 4)) != 0))
            {
                cout << "Ne ta knopka!" << endl;
                continue;
            }

            if ((send(socket_desc, message, strlen(message), 0) <= 0))
            {
                cout << "Send failed" << endl;
                port++;
                tmp = false;
                break;
            }

            if ((recv(socket_desc, server_reply3, 2000, 0) <= 0))
            {
                // puts("recv3 failed");
                // cout << endl;
                port++;
                tmp = false;
                break;
            }
            // cout << "k2 = " << k << endl;

            cout << server_reply3 << endl;

            memset(server_reply3, 0, sizeof(server_reply3));
            memset(server_reply2, 0, sizeof(server_reply2));
            memset(server_reply, 0, sizeof(server_reply));

            if ((strcmp(message, "-q")) == 0)
            {
                fflush(stdout);
                exit(EXIT_FAILURE);
            }
            cout << endl;
        }
    }
}
