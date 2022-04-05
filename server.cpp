#include <iostream>
#include <cstdlib>
#include <string.h> //strlen
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

int main(int argc, char *argv[])
{
	int port = 8000;

	while (1)
	{
		int socket_desc, new_socket, c;
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
		struct sockaddr_in server, client;

		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons(port);
		// cout << port << endl;
		// Bind
		if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
		{
			// puts("bind failed");
			port++;
			// cout << port << endl;
			//  return 1;
			continue;
		}

		puts("bind done");
		cout << port << endl;
		// serv[i] = serv;
		// Listen
		listen(socket_desc, 3);

		// Accept and incoming connection
		puts("Waiting for incoming connections...");
		/*if(*/ /*== 0){
			port++;
			//continue;
		}*/
				/*
					int optval;
					socklen_t optlen = sizeof(optval);
					if(getsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
					  perror("getsockopt()");
					  close(socket_desc);
					  exit(EXIT_FAILURE);
				   }
				   printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));
		
					optval = 1;
				   optlen = sizeof(optval);
				   if(setsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
					  perror("setsockopt()");
					  close(socket_desc);
					  exit(EXIT_FAILURE);
				   }
				   printf("SO_KEEPALIVE set on socket\n");
		
		
				   if(getsockopt(socket_desc, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
					  perror("getsockopt()");
					  close(socket_desc);
					  exit(EXIT_FAILURE);
				   }
				   printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));
				*/

		c = sizeof(struct sockaddr_in);
		while ((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c)))
		{
			// server.new_sock = new_socket;
			puts("Connection accepted");

			// Reply to the client
			message = "Hello Client, I have received your connection. And now I will assign a handler for you\n";
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

	// Send some messages to the client
	message = "Greetings! I am your connection handler. Use -h or --help for help or -q for exit\n";
	write(sock, message, strlen(message));

	while (client_message != "-q")
	{
		// Receive a message from client
		// cout << message << endl;
		read_size = recv(sock, client_message, 2000, 0);
		if (read_size == 0)
		{
			puts("Client disconnected");
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
		cout << endl;
	}

	// if (message == "-q")
	// {
	// 	puts("client is over");
	// 	fflush(stdout);
	// 	exit(EXIT_FAILURE);
	// }
	// Free the socket pointer
	free(socket_desc);

	return 0;
}