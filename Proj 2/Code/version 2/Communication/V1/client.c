#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include "comm.h"

/* -------------------------Main function for the client ----------------------*/
void main(int argc, char * argv[]) {

	int pipe_user_reading_from_server[2], pipe_user_writing_to_server[2];
	char buf[MAX_MSG];

	if(connect_to_server("YOUR_UNIQUE_ID", argv[1], pipe_user_reading_from_server, pipe_user_writing_to_server) == -1) {
		exit(-1);
	}
	else
	{
		printf("%s is connnected to Server\n", argv[1]);
		print_prompt(argv[1]);
	}

	/* -------------- YOUR CODE STARTS HERE -----------------------------------*/

	// poll pipe retrieved and print it to sdiout
	if (fcntl(pipe_user_reading_from_server[0], F_SETFL, O_NONBLOCK) < 0 || fcntl(0, F_SETFL, O_NONBLOCK)){
		printf("O_NONBLOCK error 3\n");
		exit(2);
	}

	// Poll stdin (input from the terminal) and send it to server (child process) via pipe
	while (1)
	{
		if(read(0, buf, MAX_MSG) != -1){
			write(pipe_user_writing_to_server[1], buf, MAX_MSG);
			memset(buf,'\0', MAX_MSG);
			print_prompt(argv[1]);
		}

		if(read(pipe_user_reading_from_server[0], buf, MAX_MSG) != -1){
			printf("\nUSER: %s", buf);
			memset(buf,'\0', MAX_MSG);
			print_prompt(argv[1]);
		}
	}

	/* -------------- YOUR CODE ENDS HERE -----------------------------------*/
}

/*--------------------------End of main for the client --------------------------*/
