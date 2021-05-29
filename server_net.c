#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>

/* Creates a stream server. The port number is passed as an argument.
   This server runs forever */

int main( int argc, char *argv[] ) {
  const int IO_BUFFER_SIZE = 1024;
  const int RESPONSE_BUFFER_SIZE = 256;
  int socket_id, client_id, client_len, connection_response;
  struct sockaddr_in server_info, client_info;
  struct utsname version_info;
  char io_stream[IO_BUFFER_SIZE];
  char response_stream[RESPONSE_BUFFER_SIZE];

  /* Check to make sure user entered a port number...
     or at least attempted to... */
  if( argc != 2 ) {
    fprintf( stderr, "Usage: %s Port\n", argv[0] );
    exit(0);
  }

  /* Create a new socket using the following parameters
        Domain: Address Family
        Socket Type: tcp because why would we use udp...
        Protocol: We can use 0 because it's automatic for udp and tcp */
  socket_id = socket( AF_INET, SOCK_STREAM, 0 );

  /* If the socket returns -1 throw an error */
  if( socket_id == -1 ) {
    fprintf( stderr, "The system encountered an error while opening the socket\n" );
    exit(0);
  }

  /* Clear the contents of the server_info before setting */
  bzero( (char *)&server_info, sizeof( server_info ) );

  /* Set the domain type for the server_info */
  server_info.sin_family = AF_INET;

  /* Set the address to 0.0.0.0 for the server_info */
  server_info.sin_addr.s_addr = INADDR_ANY;

  /* Set the port in server_info to the port given by the user */
  server_info.sin_port = htons( atoi( argv[1] ) );

  /* Bind the socket at the desired address range and port number */
  if( bind( socket_id, (struct sockaddr *)&server_info , sizeof( server_info ) ) == -1 ) {
    fprintf( stderr, "The system encountered an error while binding to the socket\n" );
    exit(0);
  }

  /* Set the socket to listen for a connection on the address */
  if( listen(socket_id, 1) == -1 ) {
    fprintf( stderr, "The system encountered an error while listening on 0.0.0.0:%s", argv[1] );
    exit( 0 );
  }

  /* Set size of client_info */
  client_len = sizeof( client_info );

  /* Accept incoming connection from a client */
  client_id = accept( socket_id, (struct sockaddr*)&client_info, &client_len );

  /* If the client_id returns -1 throw an error */
  if( client_id == -1 ) {
    fprintf( stderr, "The system encountered an error while accepting connection from client\n");
    exit( 0 );
  }

  /* Now that we hace accepted a connection to the socket we can start
     sending and receiving commands */
  while( 1 ) {
    /* Empty the io_stream so that we can receive a command from the socket */
    bzero( io_stream, IO_BUFFER_SIZE );

    /* Fill our io_stream with the data received from the socket */
    connection_response = recv( client_id, io_stream, IO_BUFFER_SIZE, 0 );

    /* Check to make sure we could successfully received from the socket */
    if( connection_response < 0 ) {
      fprintf( stderr, "Unable to receive command to socket on port %s", argv[1] );
      exit( 0 );
    }

    /* Write the received command to the console */
    printf( "Here is the message: %s", io_stream );

    /* Let the client know we received their command and our status */
    if( send( client_id, "I got your message", 18, 0 ) < 0 ) {
      fprintf( stderr, "Unable to send command to socket on port %s", argv[1] );
      exit( 0 );
    }
  }
}
