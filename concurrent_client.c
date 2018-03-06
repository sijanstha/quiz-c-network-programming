#include<stdio.h>
#include<sys/types.h>//socket
#include<sys/socket.h>//socket
#include<string.h>//memset
#include<stdlib.h>//sizeof
#include<netinet/in.h>//INADDR_ANY

#define PORT 8000
#define SERVER_IP "127.0.0.1"
#define MAXSZ 1024
int main(int argc, char **argv)
{
 int sockfd;//to create socket

 struct sockaddr_in serverAddress;//client will connect on this

 int n;
 char msg1[MAXSZ];
 char msg2[MAXSZ];

 //create socket
 sockfd=socket(AF_INET,SOCK_STREAM,0);
 //initialize the socket addresses
 memset(&serverAddress,0,sizeof(serverAddress));
 serverAddress.sin_family=AF_INET;
 serverAddress.sin_addr.s_addr=inet_addr(argv[2]);
 serverAddress.sin_port=htons(atoi(argv[4]));	//atoi for char to int

 //client  connect to server on port
 connect(sockfd,(struct sockaddr *)&serverAddress,sizeof(serverAddress));
 
 //sending client nickname to server
 send(sockfd,argv[6],10,0);
 
 printf("==>>client1\n");
recv(sockfd,msg2,MAXSZ,0);
 printf("%s\n", msg2);
 //bzero(&msg2,MAXSZ);
 
 //send to sever and receive from server
 while(1)
 {
	 printf("==>>\n");
	 memset(msg2,0,strlen(msg2));
	 n=recv(sockfd,msg2,MAXSZ,0);
	if(n==0)
		break;
	
	printf(msg2);
  
  //printf("\nEnter message to send to server:\n");
  fgets(msg2,MAXSZ,stdin);
  n=strlen(msg2)+1;
  send(sockfd,msg2,n,0);

  n=recv(sockfd,msg2,MAXSZ,0);
  if(n==0)
    {
     close(sockfd);
     break;
    }
  printf("Receive message from  server::%s\n",msg2);
 }

 return 0;
}
