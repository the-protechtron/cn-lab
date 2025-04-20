#include<stdio.h>
#include<unistd.h>

#include<fcntl.h>
int main(){
	char buffer[100];
	int fd,fd1,fd2,n;
	mkfifo("fifo1",0600);
	mkfifo("fifo2",0600);
	fd1 = open("fifo1",O_RDONLY);
	fd2 = open("fifo2",O_WRONLY);	
	printf("Both fifos openend\n");
	write(fd2,"hello",6);
	read(fd1,buffer,sizeof(buffer));
	printf("Requested file %s\n",buffer);
	fd=open(buffer,O_RDONLY);
	if(fd<0){
		printf("No Such file exists\n");
		exit(0);
	}
	
	n=read(fd,buffer,sizeof(buffer));
	printf("Value of n is %d\n",n);
	printf("File content: %s\n",buffer);
	write(fd2,buffer,n);
	close(fd);
	close(fd1);
	close(fd2);
}
