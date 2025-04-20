#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
	char buffer[100];
	int fd,fd1,fd2,n;
	fd1 = open("fifo1",O_WRONLY);
	fd2 = open("fifo2",O_RDONLY);	
	printf("Both fifos openend\n");
	read(fd2,buffer,sizeof(buffer));
	printf("Server says %s\n",buffer);
	write(fd1,"text.txt",9);
	printf("Requested for a file\n");
	n=read(fd2,buffer,sizeof(buffer));
	printf("n value is : %d\n",n);
	buffer[n]='\0';
	printf("File content: %s\n",buffer);
	fd=open("recvd.txt",O_CREAT|O_RDWR);
	write(fd,buffer,n);
	close(fd1);
	close(fd2);
}
