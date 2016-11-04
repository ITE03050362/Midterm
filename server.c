#include<stdio.h>
#include<stdlib.h>
#include<string.h>    
#include<sys/socket.h>
#include<arpa/inet.h> 
#include<unistd.h>    

int main(int argc , char *argv[])
{
	time_t mytime;
	mytime=time(NULL);

	int socket_desc,new_socket,c;
	int answer[8];
	int count_a,count_b,countA,countB;

	struct sockaddr_in server,client;
	char *msg;
	char reply[8],compare[8],msg2[50];

	
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);

	if (socket_desc == -1)
	{
	     printf("Could not create socket");
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( 8787 );

	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
	     puts("bind failed");
	     return 1;
	}

	puts("bind done");

	listen(socket_desc , 3);

	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);  
  
    while( (new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
	    puts("Connection accepted");
	    countA=0; countB=0;
	    srand( time(NULL) );
 
		for(count_a=0;count_a<4;count_a++)
		{
  		   answer[count_a]=rand()%10; 

  		   for(count_b=0;count_b<count_a;count_b++) 
  		   { 
     			if(answer[count_a]==answer[count_b]) 
     			{	
     				count_a--; 
     			} 
  		   }
		} 
         

	     printf("Answer:%d%d%d%d\n",answer[0],answer[1],answer[2],answer[3]);


        //傳回client

	while(1)
	{
		bzero(reply,8);
		read(new_socket,reply,8);
		compare[0]=(reply[0]-'0');
		compare[1]=(reply[1]-'0');
		compare[2]=(reply[2]-'0');
		compare[3]=(reply[3]-'0');
	
		for(count_a=0;count_a<4;count_a++)
		{
		   if(answer[count_a]==compare[count_a]) 
		   {
			countA+=1;
		   }
		}
	
		for(count_b=0;count_b<=3;count_b++)
		{
		   for(count_a=0;count_a<=3;count_a++)
		   {
			if(compare[count_a]==answer[count_b] && count_a!=count_b)
			{
			     countB++;
			}
		   }
		}

		if(countA==4)
		{
			msg="Congratulations!!";
			write(new_socket , msg, strlen(msg)+1);
			return 1;
		}

		else
		{
			sprintf(msg2,"%dA%dB",countA,countB);
			write(new_socket , msg2, strlen(msg2)+1);
			countA=0;countB=0;
		}

	        if (new_socket<0)
	        {
		      perror("accept failed");
		      return 1;
	        }
		      return 0;
	}
	
    }
	
}

