// Numbers from command line arguments are sent to child process
// from parent process one at a time through pipe.
//
// Child process adds up numbers sent through pipe.
//
// Child process returns sum of numbers to parent process.
//
// Parent process prints sum of numbers.

#include <stdio.h>

#define NOHANG 0

int main(int argc, char **argv)
{
	int status;
	int pid;
	int list[4];
	int toPipe[2];
	int fromPipe[2];
	int num = argc - 2;

	for(int i = 0; i < num; i++)
	{
		list[i] = atoi(argv[i+1]);
	}

	// set up pipe
	pipe(toPipe);
	pipe(fromPipe);

	//printf("Pipe 1: %i, %i\nPipe 2: %i, %i\n", pipe1[0], pipe1[1], pipe2[0], pipe2[1]);

	system("clear");
	printf("CS201 - Assignment 3 Regular - Dmitri McGuckin\n");

	pid = fork();

	if (pid == 0)
	{
			// -- running in child process --
			int     sum = 0;

			printf("PARENT PID: %i\n", pid);
			
			// Receive characters from parent process via pipe
			// one at a time, and count them.

			// Return sum of numbers.
			return sum;
	}
	else
	{
			// -- running in parent process --
			int sum = 0;
			
			printf("CHILD PID: %i\n", pid);
			
			// Send numbers (datatype: int, 4 bytes) from command line arguments
			// starting with argv[1] one at a time through pipe to child process.
			
			for(int i = 0; i < num; i++)
			{
				write(toPipe,&list[i],4);
				printf("Written to pipe: %i\n",list[i]);
			}	

			// Wait for child process to return. Reap child process.
			// Receive sum of numbers via the value returned when
			// the child process is reaped.

			waitpid(pid,status,NOHANG);
			
			printf("sum = %d\n", sum);
			return 0;
		}
}
