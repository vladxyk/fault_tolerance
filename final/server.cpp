#include <iostream>
#include <cstdlib>
#include <string.h> //strlen
#include <cstring>
#include <stdlib.h> //strlen
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>	   //write
//#include "lab2.hpp"
#include "main.cpp"
#include <pthread.h> //for threading , link with lpthread

using namespace std;
/*
struct tcpservak : public sockaddr_in
{
	int new_sock;
	~tcpservak()
	{
		write(new_sock, "d", 1);
		cout << endl;
	}
};
*/
void *connection_handler(void *);

int port = 8000;
int main_port = 8000;
int main(int argc, char *argv[])
{
	// string str = "8000";
	// const char *cstr = str.c_str();

	while (1)
	{
		int socket_desc, socket_desc1, new_socket, new_socket1, c;
		const char *message;
		int *new_sock = new int;
		// Create socket
		socket_desc = socket(AF_INET, SOCK_STREAM, 0);
		if (socket_desc == -1)
		{
			cout << "Could not create socket\n";
			exit(EXIT_FAILURE);
		}
		// Prepare the sockaddr_in structure
		struct sockaddr_in server, client, server1;

		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons(port);
		// Bind
		if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
		{
			//puts("bind failed");
			port++;
			continue;
		}
		c = sizeof(struct sockaddr_in);

		cout << to_string(port) << endl;
		puts("bind done");

		//string prt = "mkdir " + to_string(port);
		//const char *cstr = prt.c_str();
		//system(cstr);

		// Listen
		listen(socket_desc, 3);

		if (port == main_port)
		{
			cout << "Im main server" << endl;
		}
		else
		{
			cout << "Im reserve server" << endl;
		}

		// Accept and incoming connection
		puts("Waiting for incoming connections...");

		while ((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c)))
		{
			// server.new_sock = new_socket;
			puts("Connection accepted");

			if (port == main_port)
			{
				// Reply to the client
				// cout << "Im main server" << endl;
				message = "Hello Client, I have received your connection. Use -h or --help for help or -q for exit\n";
				write(new_socket, message, strlen(message));

				pthread_t sniffer_thread;
				*new_sock = new_socket;

				if (pthread_create(&sniffer_thread, NULL, connection_handler, (void *)new_sock) < 0)
				{
					perror("could not create thread");
					return 1;
				}

				// Now join the thread , so that we dont terminate before the thread
				// pthread_join( sniffer_thread , NULL);
				puts("Handler assigned");
			}
			else
			{
				// message = "Hello Rezv serv\n";
				// write(new_socket, message, strlen(message));
				// cout << "Im reserve server" << endl;
				pthread_t sniffer_thread;
				*new_sock = new_socket;

				if (pthread_create(&sniffer_thread, NULL, connection_handler, (void *)new_sock) < 0)
				{
					perror("could not create thread");
					return 1;
				}

				// Now join the thread , so that we dont terminate before the thread
				// pthread_join( sniffer_thread , NULL);
				puts("Handler assigned");
			}
		}

		if (new_socket < 0)
		{
			perror("accept failed");
			return 1;
		}
	}
	return 0;
}

/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
	// Get the socket descriptor
	int sock = *(int *)socket_desc;
	int read_size;
	char client_message[2000];
	const char *message;
	char *m;
	string cstr = to_string(port);
	string p1;
	p1 = cstr + '/';
	char *p2 = new char[sizeof(p1) + 1];
	strcpy(p2, p1.c_str());

	// FFFsystem("ls -d 80* | xargs -n 1 cp 1.txt");
	while (client_message != "-q")
	{
		read_size = recv(sock, client_message, 2000, 0);

		// FFFsystem("rm 80*/*.txt");
		if (read_size == 0)
		{
			puts("Client disconnected");
			// FFFsystem("rm -r 80*");
			fflush(stdout);
			exit(EXIT_FAILURE);
		}
		else if (read_size == -1)
		{
			perror("recv failed");
			fflush(stdout);
			exit(EXIT_FAILURE);
		}
		message = start(client_message);
		memset(client_message, 0, sizeof(client_message));
		write(sock, message, strlen(message));

		// FFFsystem("ls -d 80* | xargs -n 1 cp *.txt");
		cout << endl;
	}

	free(socket_desc);

	return 0;
}