#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "main.cpp"

using namespace std;

int main(int argc, char *argv[])
{
    int port = 8000;
    int main_port = 8000;
    bool tmp = true;
    char buff[2000];
    char *message, server_reply[100], server_reply2[100], server_reply3[2000];
    vector<int> socket_desc;
    int i = 0;
    int serv = 0;
    while (1)
    {
        vector<struct sockaddr_in> server;

        socket_desc.push_back(socket(AF_INET, SOCK_STREAM, 0));

        server.resize(5);

        server[0].sin_addr.s_addr = INADDR_ANY;
        server[0].sin_family = AF_INET;
        server[0].sin_port = htons(port);

        while ((connect(socket_desc[i], (struct sockaddr *)&server[i], sizeof(server[i]))) == 0)
        {
            port++;
            i++;
            socket_desc.push_back(socket(AF_INET, SOCK_STREAM, 0));
            server[i].sin_addr.s_addr = INADDR_ANY;
            server[i].sin_family = AF_INET;
            server[i].sin_port = htons(port);
        }
        serv = i;
        i = 0;

        cout << "Connected: " << main_port << endl;
        
        if ((recv(socket_desc[0], server_reply, 100, 0)) == -1)
        {
            cout << "recv1 failed" << endl;
        }
        if (tmp)
        {
            cout << server_reply << endl;
        }

        while (1)
        {
            int j = 0;

            do
            {
                buff[2000] = {0};
                buff[j] = getchar();
                // cout << buff[i];
                if (buff[j] == '\n')
                {
                    buff[j] = 0;
                    break;
                }
                j++;
            } while (true);

            message = buff;

            if (((strncmp(message, "-q", 2)) != 0) && ((strncmp(message, "-h", 2)) != 0) && ((strncmp(message, "--help", 3)) != 0) && ((strncmp(message, "-mf", 3)) != 0) && ((strncmp(message, "-rmf", 4)) != 0) && ((strncmp(message, "-cf", 3)) != 0) && ((strncmp(message, "-ssf", 4)) != 0))
            {
                cout << "Ne ta knopka!" << endl;
                continue;
            }

            int servsync = serv;
            while (serv > 0)
            {
                cout << serv << endl;
                if ((send(socket_desc[i], message, strlen(message), 0) <= 0))
                {
                    cout << "Send failed" << endl;
                }
                cout << "i = " << i << endl;
                if ((recv(socket_desc[i], server_reply3, 2000, 0) <= 0))
                {
                    puts("recv3 failed");
                    socket_desc.erase(socket_desc.begin() + i);
                    server.erase(server.begin() + i);
                    servsync--;
                    i = -1;
                }
                i++;
                serv--;
            }
            serv = servsync;

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
            i = 0;
        }
    }
}
