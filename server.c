/*------------------------------
* server.c
* Description: HTTP server program
* CSC 361
* Instructor: Kui Wu
-------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <netdb.h>
#include <netinet/in.h>

#include <string.h>
#define MAX_REC_LEN 4096
#define MAX_STR_LEN 120         /* maximum string length */
#define SERVER_PORT_ID 9898     /* server port number */

void cleanExit();

/*---------------------main() routine--------------------------*
 * tasks for main
 * generate socket and get socket id,
 * max number of connection is 3 (maximum length the queue of pending connections may grow to)
 * Accept request from client and generate new socket
 * Communicate with client and close new socket after done
 *---------------------------------------------------------------------------*/
	struct sockaddr_in serv_addr, cli_addr;
	 char buffer[256]; 
         int newsockfd,portno,reallynewsockfd,n,clilen; /* return value of the accept() call */
	char address[MAX_STR_LEN];
main(int argc, char **argv)
{	
	
	strcpy(address,argv[2]);
	  newsockfd = socket(AF_INET, SOCK_STREAM, 0);
 	  if (newsockfd < 0) {
     		 perror("ERROR opening socket");
      		exit(1);
	   }
	 
	 bzero((char *) &serv_addr, sizeof(serv_addr));
	
	int a = atoi(argv[1]);
	if(argc > 2){
  	 portno = a;
   	}else if(argc==2){
	portno=80;	
	}
	//printf("checkkkkkk %d",portno);
  	 serv_addr.sin_family = AF_INET;
   	serv_addr.sin_addr.s_addr = INADDR_ANY;
   	serv_addr.sin_port = htons(portno);
 	   bind(newsockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
      		
	listen(newsockfd, 3);
	//if (listen(newsockfd, 3) == -1) {
            //perror("listen error");
          //  exit(1);
      //  }
//while(1){
perform_http(newsockfd,address);
//}
	
 }

/*---------------------------------------------------------------------------*
 *
 * cleans up opened sockets whe n killed by a signal.
 *
 *---------------------------------------------------------------------------*/

void cleanExit()
{
    exit(0);
}

/*---------------------------------------------------------------------------*
 *
 * Accepts a request from "sockid" and sends a response to "sockid".
 *
 *---------------------------------------------------------------------------*/

perform_http(int sockid)
{	
	int succ= 0;
	char cmd[120];
	char hostname[MAX_STR_LEN];
	char identifier[MAX_STR_LEN];
	char http[MAX_STR_LEN];
	char content[4096];
	char header[999]="HTTP/1.0 200 OK\n";
	 time_t t = time(0);
  	  struct tm *tm = localtime(&t);
   	 //printf("%s\n", asctime(tm));
	reallynewsockfd= accept(sockid, (struct sockaddr *)&cli_addr, &clilen);
	bzero(buffer,256);
  	 read( reallynewsockfd,buffer,255 );
	//printf("buffer is :%s",buffer);
	if (sscanf(buffer, "%s http://%[^/]%[^ ] %[^\n]", cmd, hostname, identifier,http) == 4) { succ = 1;}
	
	//printf("ip = \"%s\"\n", hostname);
	//printf("cmd = \"%s\"\n", cmd);
	//int y =strcmp("HTTP/1.0\r",http);
	//printf("Number = \%d\n", y);
	while (strcmp("HTTP/1.0\r",http) != 0){
	write(reallynewsockfd,"HTTP/1.0 501 Not Implemented\n",29);
	close(reallynewsockfd);
	return;
	}
	strcat(address, identifier);
	//printf("address is = \"%s\"\n", address);
	FILE *file;//opening file herererer.
	file = fopen(address, "r");
	if (file==NULL) {
	write(reallynewsockfd,"HTTP/1.0 404 Not Found\n",29);
	close(reallynewsockfd);
	return;
	}
	fseek(file, 0, SEEK_SET);
	//fgets(content, MAX_REC_LEN, file);
	fread(content, MAX_REC_LEN, 1, file);
	//fscanf(file,"%ls",content);
	fclose(file);
	//strcat(header, "HTTP/1.0 200 OK\n");
	strcat(header, "Data: ");
	strcat(header, asctime(tm));
	strcat(header, "\n");
	strcat(header, "--- Response body---\n");
	strcat(header,content);
	strcat(header, "\n");
	write(reallynewsockfd,header,1000);
	
	//printf(content);
	//write(reallynewsockfd,content,1000);
	//char haha[7]="hellop";
      	//write(reallynewsockfd,"hello world",12);
     	  close(reallynewsockfd);
}















