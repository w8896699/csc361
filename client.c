/*------------------------------
* client.c
* Description: HTTP client program
* CSC 361
* Instructor: Kui Wu
-------------------------------*/

/* define maximal string and reply length, this is just an example.*/
/* MAX_RES_LEN should be defined larger (e.g. 4096) in real testing. */
#define MAX_STR_LEN 120
#define MAX_RES_LEN 120
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include<string.h>

/* --------- Main() routine ------------
 * three main task will be excuted:
 * accept the input URI and parse it into fragments for further operation
 * open socket connection with specified sockid ID
 * use the socket id to connect sopecified server
 * don't forget to handle errors
 */

main(int argc, char **argv)
{
    char uri[MAX_STR_LEN];
    char hostname[MAX_STR_LEN];
    char identifier[MAX_STR_LEN];
    int sockid, port;
    

   // printf("Open URI:  ");
   // scanf("%s", uri);

	strcpy(uri,argv[1]);
	//uri=argv[1];
	printf("web: %s",uri);
    parse_URI(uri, hostname, &port, identifier);
	//printf("ip1 = \"%s\"\n", identifier);;

    sockid = open_connection(hostname, port);
	
    perform_http(sockid, uri,hostname,identifier);
}

/*------ Parse an "uri" into "hostname" and resource "identifier" --------*/

parse_URI(char *uri, char *hostname, int *port, char *identifier)
{
	int succ= 0;
  		*port=80;

      if (sscanf(uri, "http://%99[^:]:%i/%199[^\n]", hostname, port, identifier) == 3) { succ = 1;}
      else if (sscanf(uri, "http://%99[^/]/%199[^\n]", hostname, identifier) == 2) { succ = 1;}
      else if (sscanf(uri, "%99[^:]:%i/%199[^\n]", hostname, port, identifier) == 3) { succ = 1;}
      else if (sscanf(uri, "%99[^/]/%199[^\n]", hostname, identifier) == 2) { succ = 1;}
	 if (succ!=1) {
		printf("Error. \n"); 
}
	//printf("ip1 = \"%s\"\n", hostname);
}	
/*http://www.google.ca/index.html

/* http://www.csc.uvic.ca/index.htm
/*------------------------------------*
* connect to a HTTP server using hostname and port,
* and get the resource specified by identifier
*--------------------------------------*/

perform_http(int sockid, char *uri, char *host, char *identifier)
{	
	 char recvline[4096];
	char haha[MAX_STR_LEN]="GET ";
	int bytes;
	/* connect to server and retrieve response */
 	printf("\n---Request begin---\n");
	strcat(haha,"http://");
	strcat(haha,host);
	strcat(haha,"/");
	strcat(haha,identifier);
	strcat(haha," HTTP/1.0\r\n\r\n");
	
	printf("%s",haha);
	printf("Host: ");
	printf("%s",host);
	bzero( recvline, sizeof recvline);
	//printf("%s",haha);
	write(sockid,haha,strlen(haha)+1);
	read(sockid,recvline, 4096);
	printf("\nConnection: Keep-Alive\n");
	printf("\n---Request end---\n");
	printf("HTTP request sent, awaiting response...\n");
	printf("\n---Response header---\n");
	printf("%s",recvline);
	//printf("\n--- Response body---\n");
	//printf("%s",recvline);
 	 //close(sockid,identifier);
}
/*---------------------------------------------------------------------------*
 *
 * open_conn() routine. It connects to a remote server on a specified port.
 *
 *---------------------------------------------------------------------------*/
int open_connection(char *hostname, int port)
{
	struct sockaddr_in serv_addr;

	struct hostent *server_ent;
  	int sockfd;
	
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if (sockfd < 0) error("ERROR opening socket");
	bzero(&serv_addr,sizeof serv_addr);
	server_ent= gethostbyname(hostname);
	memcpy(&serv_addr.sin_addr, server_ent->h_addr, server_ent->h_length);
	
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(port);
	
	
	
	connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
		// error("ERROR connecting");

  /* generate socket
   * connect socket to the host address
   */	
  return sockfd;
}
