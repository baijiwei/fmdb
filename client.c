#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
	 int sockfd;
	 int len;
	 struct sockaddr_in address;
	 int result;
	 char ch = 'A';

	 sockfd = socket(AF_INET, SOCK_STREAM, 0);
	 address.sin_family = AF_INET;
	 address.sin_addr.s_addr = inet_addr("127.0.0.1");
	 address.sin_port = htons(58617);
	 len = sizeof(address);
	 result = connect(sockfd, (struct sockaddr *)&address, len);

	 if (result == -1)
	 {
		  perror("oops: client1");
		  return -1;
	 }
     printf("connect done: sockFd%d", result);
	 write(sockfd, &ch, 1);
     printf("Write one char: %c", ch);
	 read(sockfd, &ch, 1);
     printf("read one char: %c", ch);
	 printf("char from server = %c\n", ch);
	 close(sockfd);
	 return 0;
}
