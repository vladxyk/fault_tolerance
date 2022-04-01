#include <iostream>
#include <stdlib.h>
#include <string.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr

using namespace std;

int main(int argc, char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;
    char *message, server_reply[2000], server_reply2[2000], server_reply3[15000];
    int port = 8000;
    int k = 0;
    char buff[15000];
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
        // cout << port << endl;
        if (connect(socket_desc, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
            // puts("connect error");
            port++;
            continue;
        }
        // cout << flush;
        if (k == 0)
        {
            // puts("Connected");
            cout << "Connected: " << port << endl;
        }
        // cout << port << endl;
        // cout << "k = " << k << endl << endl;
        // cout << flush;
        if ((recv(socket_desc, server_reply, 2000, 0)) == -1)
        {
            cout << "recv1 failed" << endl;
        }
        // cout << "k = " << k << endl << endl;
        // cout << flush;
        if (k == 0)
        {
            cout << "Reply received\n"
                 << server_reply << endl;
        }
        // cout << "k = " << k << endl << endl;
        // cout << flush;
        if ((recv(socket_desc, server_reply2, 2000, 0)) == -1)
        {
            cout << "recv2 failed" << endl;
        }
        // cout << "k = " << k << endl << endl;
        // cout << flush;
        if (k == 0)
        {
            cout << "Reply2 received\n"
                 << server_reply2 << endl;
        }
        // cout << flush;
        // cout << "k = " << k << endl
        //      << endl;
        while (1)
        {
            int i = 0;
            if (k == 0)
            {
                do
                {
                    buff[15000] = {0};
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
                k = 0;
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
                k++;
                break;
            }

            if ((recv(socket_desc, server_reply3, 15000, 0) <= 0))
            {
                // puts("recv3 failed");
                // cout << endl;
                port++;
                k++;
                break;
            }
            // cout << "k2 = " << k << endl;

            cout << server_reply3 << endl;

            memset(server_reply3, 0, sizeof(server_reply3));
            memset(server_reply2, 0, sizeof(server_reply2));
            memset(server_reply, 0, sizeof(server_reply));

            if ((strcmp(message, "-q")) == 0)
            {
                // puts("Do svidaniya! do widzenia!");
                fflush(stdout);
                exit(EXIT_FAILURE);
            }
            cout << endl;
        }
    }
}
