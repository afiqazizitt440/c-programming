#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>
int main()
{
	int sock,val,a,val2;
	struct sockaddr_in socket1;
	
	if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
	{	perror("socket malfunction:"); exit(-1);	}
	
	socket1.sin_family=AF_INET;
	socket1.sin_port=htons(1040);
	socket1.sin_addr.s_addr=INADDR_ANY;

	unsigned int len;
	len=sizeof(struct sockaddr_in);
	
	if(bind(sock,(struct sockaddr *)&socket1,len)==-1)
	{	perror("bind malfunction:"); exit(-1);	}
	
	//setting the socket's send buffer and receiving buffer//
	
	getsockopt(sock,SOL_SOCKET,SO_SNDBUF,&val,&len);

	printf("BUFFER BEFORE EDITING:%d\n",val);
	
	val=327608;
	
	setsockopt(sock,SOL_SOCKET,SO_SNDBUF,&val,sizeof(val));

	getsockopt(sock,SOL_SOCKET,SO_SNDBUF,&val,&len);
	printf("BUFFER AFTER EDITING: %d\n",val);
		
	getsockopt(sock,SOL_SOCKET,SO_RCVBUF,&val2,&len);
	printf("RCVBUF BUFF BEFORE EDITING: %d\n",val2);
	
	val2=89098;
	setsockopt(sock,SOL_SOCKET,SO_RCVBUF,&val2,sizeof(val2));
	printf("RCV BUFF AFTER: %d\n",val2);
		
}