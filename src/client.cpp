
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>    // for sockaddr_in
#include <sys/types.h>    // for socket
#include <sys/socket.h>    // for socket
#include <stdio.h>        // for printf
#include <stdlib.h>        // for exit
#include <string.h>        // for bzero
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#define MAXDATASIZE 256
#define SERVER_IP "127.0.0.1"
using namespace std;
//#define DATA  "this is a client message 客户端的信息"

int main(int argc, char **argv){
	if (argc != 5){
				perror("input error example : -l( if for file use -f) inputList(if for file use path) outPutpath port!");
				exit(1);
		}
	string sar1,sar2,sar3;
	int SERVPORT;
	sar1=argv[1];
	sar2=argv[2];
	sar3=argv[3];
	SERVPORT=atoi(argv[4]);
	if (sar1!="-l"&&sar1!="-f"){
		    perror("input error example : -l( if for file use -f) inputList(if for file use path) outPutpath!");
			exit(1);
	}
  char DATA[MAXDATASIZE];
  int sockfd, recvbytes;
  char buf[MAXDATASIZE];
  struct sockaddr_in serv_addr;
  if (( sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      perror("socket error!");
      exit(1);
    }
  bzero(&serv_addr,sizeof(serv_addr));
  serv_addr.sin_family    = AF_INET;
  serv_addr.sin_port      = htons(SERVPORT);
  serv_addr.sin_addr.s_addr= inet_addr(SERVER_IP);
  if (connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) == -1) {
      perror("connect error!");
      exit(1);
		}
	string data;
	data=sar1+' '+sar2+' '+sar3+' ';//最后一个‘ ’ 不要漏下
	if ((int)data.length() > 256 )
	{
		perror("too long !");
		exit(1);
	}
   for (unsigned int i=0;i<data.length();i++)
   {
	   DATA[i]=data[i];
   }
   write(sockfd,DATA,sizeof(DATA));
   if ((recvbytes = recv(sockfd, buf, MAXDATASIZE,0)) == -1) {
        perror("recv error!");
        exit(1);
    }
    buf[recvbytes] = '\0';
    close(sockfd);
}

