#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/**
 * The main function establishes a TCP connection to a server using a socket.
 * It sends an HTTP GET request to the server and receives the response.
 *
 * Returns:
 *     0 if the connection was successful and the message was received from the server.
 *
 * Side Effects:
 *     - Creates a socket using the socket() function.
 *     - Sets up the server address using the sockaddr_in structure.
 *     - Converts the IP address from string format to binary using inet_pton().
 *     - Connects to the server using the connect() function.
 *     - Sends an HTTP GET request to the server using the send() function.
 *     - Receives the response from the server using the recv() function.
 *     - Prints the received message to the console using printf().
 *
 * Usage:
 *     main();
 */

int main()
{
  // Create a socket
  int socketFD = socket(AF_INET, SOCK_STREAM, 0);
  if (socketFD == -1)
  {
    perror("Socket creation failed");
    exit(EXIT_FAILURE);
  }

  // Set up the server address
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_port = htons(80);
  if (inet_pton(AF_INET, "142.250.188.46", &address.sin_addr) <= 0)
  {
    perror("Invalid address/ Address not supported");
    exit(EXIT_FAILURE);
  }

  // Connect to the server
  if (connect(socketFD, (struct sockaddr *)&address, sizeof(address)) < 0)
  {
    perror("Connection failed");
    exit(EXIT_FAILURE);
  }

  // Send an HTTP GET request
  char *message = "GET / HTTP/1.1\r\nHost: google.com\r\n\r\n";
  if (send(socketFD, message, strlen(message), 0) < 0)
  {
    perror("Send failed");
    exit(EXIT_FAILURE);
  }

  // Receive the response from the server
  char buffer[1024];
  if (recv(socketFD, buffer, sizeof(buffer), 0) < 0)
  {
    perror("Receive failed");
    exit(EXIT_FAILURE);
  }

  // Print the received message
  printf("Message received from server: %s\n", buffer);

  return 0;
}
