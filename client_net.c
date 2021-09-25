// a simple comment to check privs!

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
  const int BUFFER_SIZE = 256;
  int socket_id, server_len, connection_response;
  struct sockaddr_in server_info;
  struct hostent *host_info;
  char input_stream[BUFFER_SIZE];
  char output_stream[BUFFER_SIZE];

  /* Check to make sure user entered an IP address and a port number...
     or at least attempted to... */
  if( argc != 3 ) {
    fprintf( stderr, "Usage: %s ServerAddress Port\n", argv[0] );
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

  /* Resolve the hostname given by the user */
  host_info = gethostbyname( argv[1] );

  /* Make sure our hostname resolved without error */
  if( host_info == NULL ) {
    fprintf( stderr, "The system encountered an error while resolving the hostname\n" );
    exit(0);
  }

  /* Clear the contents of the server_info before setting */
  bzero( (char *)&server_info, sizeof( server_info ) );

  /* Copy the resolved hostname to the server_info */
  bcopy( (char *)host_info->h_addr, (char *)&server_info.sin_addr.s_addr, host_info->h_length );

  /* Set the domain type for the server_info */
  server_info.sin_family = AF_INET;

  /* Set the port in server_info to the port given by the user */
  server_info.sin_port = htons( atoi( argv[2] ) );

  /* Set size of server_len */
  server_len = sizeof( server_info );

  /* connect the socket at the desired address and port number */
  if( connect( socket_id, (struct sockaddr *)&server_info , sizeof( server_info ) ) == -1 ) {
    fprintf( stderr, "The system encountered an error while binding to the socket\n" );
    exit(0);
  }

  /* Now that we hace connected to the socket we can start
     sending and receiving commands */
  while( 1 ) {
    printf( "Please enter the message: " );
    /* Empty the io_stream so that we can send a command from the socket */
    bzero( output_stream, BUFFER_SIZE );

    /* Read in our message to send to the server */
    fgets( output_stream, BUFFER_SIZE - 1, stdin );

    /* Send our command to the server */
    if( sendto( socket_id, output_stream, BUFFER_SIZE, 0, (struct sockaddr*)&server_info, sizeof( server_info ) ) < 0 ) {
      fprintf( stderr, "Unable to send command to socket on port %s", argv[1] );
      exit( 0 );
    }

    /* Fill our input_stream with the data received from the socket */
    connection_response = recvfrom( socket_id, input_stream, BUFFER_SIZE, 0, (struct sockaddr*)&server_info, &server_len );

    /* Check to make sure we could successfully received from the socket */
    if( connection_response < 0 ) {
      fprintf( stderr, "Unable to receive command to socket on port %s", argv[1] );
      exit( 0 );
    }

    /* Write the received command to the console */
    printf( "%s\n", input_stream );

  }
}
