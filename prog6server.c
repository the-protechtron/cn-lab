#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

int main(){
	char buffer[1024];
	int ef=0,cf,lf,server,client,win=4,flag=0,count=0;
	struct sockaddr_in addr;
	
	server = socket(AF_INET,SOCK_STREAM,0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	bind(server,(struct sockaddr*)&addr,sizeof(addr));
	listen(server,5);
	client=accept(server,NULL,NULL);
	
	printf("Connected to client\n");
	
	while(1){
		if(count==win){
			count=0;
			flag=0;
		}
		
		memset(buffer,0,sizeof(buffer));
	
		recv(client,buffer,sizeof(buffer),0);
		count++;
	
		if(strcmp(buffer,"exit")==0){
			printf("Closing connection\n");
			break;
		}
		
		sscanf(buffer,"Frame %d",&cf);
		if(cf==ef){
			printf("Frame %d received\n",cf);
			lf=cf;
			ef++;
			flag=0;
			
		}
		else{
			printf("Received an out of order frame %d, Discarding frame...\n",cf);
			if(flag==0){
			send(client,&lf,sizeof(lf),0);
			//printf("ack sent for frame %d\n",lf);
			flag=1;}

		}
		
		if(flag==0){
		send(client,&lf,sizeof(lf),0);
		//printf("ack sent for frame %d\n",lf);
		}
		
	}
	close(client);
	close(server);
	
return 0;
}