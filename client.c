#include<stdio.h>
#include<string.h>    
#include<sys/socket.h>
#include<arpa/inet.h> 
int main(int argc , char *argv[])
{
     int socket_desc,port;
     struct sockaddr_in server;
     char msg[100] , server_reply[2000];
     char ip[50];

     socket_desc = socket(AF_INET , SOCK_STREAM , 0);

     if (socket_desc == -1)
     {
        printf("Could not create socket");
     }

        printf("dest_ip:");
        scanf("%s",ip);
        printf("dest_port:");
        scanf("%d",&port);

     server.sin_addr.s_addr = inet_addr(ip);
     server.sin_family = AF_INET;
     server.sin_port = htons( port );

     if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
     {
        puts("connect error");
        return 1;
     }

        puts("Connected\n");

     while(1)
     {
	printf("請輸入4個數字:");
	scanf("%s",msg);

        if( send(socket_desc , msg , strlen(msg) , 0) < 0)
        {
	  puts("Send failed");
	  return 1;
        }

	  puts("Data Send\n");
	
	if( recv(socket_desc, server_reply , 2000 , 0) < 0)
	{
	  puts("recv failed");
	}

	  puts("Reply received\n");
	  puts(server_reply);
     }

          return 0;
	
}
