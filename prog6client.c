#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<string.h>

int main(){
	char buffer[1024];
	int nf=0,base=0,win=4,ea=0,ra,fc=10,err,server;
	struct sockaddr_in addr;
	
	server = socket(AF_INET,SOCK_STREAM,0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = INADDR_ANY;
	
	while(connect(server,(struct sockaddr*)&addr,sizeof(addr)));
	
	
	printf("Connected to server\n\n");
	
	while(base<fc){
		while(nf<base+win && nf<fc){
			printf("Induce error in frame %d? (1||0): ",nf);
			scanf("%d",&err);
			if(err){
				printf("Sent frame %d with error\n",nf);
				
			}
			else{
				sprintf(buffer,"Frame %d",nf);
				send(server,buffer,sizeof(buffer),0);
				printf("Sent frame %d\n",nf);
			}
			
			nf++;
		}
		
		recv(server,&ra,sizeof(ra),0);
		//printf("Received ack was %d\n",ra);
		if(ra==ea){
			printf("Received ack for frame %d\n",ra);
			ea++;
			ra=0;
		}
		else{
			printf("ack for frame %d TIMEOUT!\n",ea);
			nf=ea;
			ra=0;
		}
		if(ea>base){
			base=ea-1;
		}
		if(base==9){send(server,"exit",sizeof("exit"),0);break;}
	
	}
		close(server);	
return 0;
}
