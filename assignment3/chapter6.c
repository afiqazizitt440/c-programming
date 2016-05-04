#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <errno.h>

int main()
{
	int identifier,on,status;
	unsigned int len;
	struct sockaddr_in servsock;
	char buffer[100],oobdata;

	if((identifier=socket(AF_INET,SOCK_STREAM,0))==-1)
	{ perror("SOCKET CREATION FAILED!");exit(-1); }
	else
	{printf("SOCKET CREATION SUCCESS!\n");}
	servsock.sin_family=AF_INET;
	servsock.sin_port=htons(3035);
	servsock.sin_addr.s_addr=INADDR_ANY; 

	len=sizeof(struct sockaddr_in);

	if((bind(identifier,(struct sockaddr *)&servsock,len))==-1)
	{ perror("BINDING FAILED!"); exit(-1); }
	else
	{ printf("SOCKET BINDING SUCCESS!\n");}
	
	status=getsockopt(identifier,SOL_SOCKET,SO_OOBINLINE,&on,&len);
	
	printf("Out of Band Status:%d\n",status);	
	
	on =1 ;
	len=sizeof(on);
	setsockopt(identifier,SOL_SOCKET,SO_OOBINLINE,&on,sizeof(on));
	status=sockatmark(identifier);
	printf("Status:%d\n",status);

	
	
}