// Numbers from command line arguments are sent to child process
// from parent process one at a time through pipe.
//
// Child process adds up numbers sent through pipe.
//
// Child process returns sum of numbers to parent process.
//
// Parent process prints sum of numbers.

#include <stdio.h>
#include <sys/types.h>

#define NOHANG 0
#define BSIZE 4

int main(int argc, char **argv)
{
	pid_t pid;
	int status, pipeIntoChild[2], pipeOutOfChild[2];

	// set up pipe
	pipe(pipeIntoChild);
	pipe(pipeOutOfChild);

	system("clear");
	printf("CS201 - Assignment 3 Regular - Dmitri McGuckin\n");

	// set up fork
	pid = fork();

	if (pid < 0)
	{
		// -- child return error --
		perror("There was a fork error!\na03p will now exit!\n");
		exit(-1);
	}
	else if (pid == 0)
	{
			// -- running in child process --
			int in, out, sum = 0;
			printf("\nPARENT PID: %d\n-->CHILD PID: %d\n", getppid(), getpid());

			close(pipeOutOfChild[0]);
			in = pipeIntoChild[0];
			out = pipeOutOfChild[1];
			close(pipeIntoChild[1]);

			// Receive characters from parent process via pipe
			// one at a time, and count them.

			int temp;
			printf("Begin Reading!\n");
			read(in,&temp, BSIZE);
			printf("Read: %c\n", temp);


			close(in);
			close(out);

			// Return sum of numbers.
			return sum;
	}
	else
	{
			// -- running in parent process --
			int in, out, sum = 0;
			printf("\n-->PARENT PID: %d\nCHILD PID: %d\n", getpid(), pid);

			int list[argc];

			for (int i = 1; i < argc; i++)
			{
				list[i] = atoi(argv[i]);
				printf("Converted Parameter: %i\n", list[i]);
			}

			close(pipeIntoChild[0]);
			in = pipeOutOfChild[0];
			out = pipeIntoChild[1];
			close(pipeOutOfChild[1]);

			// Send numbers (datatype: int, 4 bytes) from command line arguments
			// starting with argv[1] one at a time through pipe to child process.

			for (int i = 1; i < argc; i++)
			{
				write(out, list[i], BSIZE);
				printf("Written to Pipe: %i\n", list[i]);
			}

			// Wait for child process to return. Reap child process.
			// Receive sum of numbers via the value returned when
			// the child process is reaped.
			waitpid(pid,status,NOHANG);

			close(in);
			close(out);

			printf("sum = %d\n", sum);
			return 0;
		}
}
