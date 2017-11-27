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

int main(int argc, char **argv)
{
	int list[4];
	int pipe1[2];
	int pipe2[2];
	int num = argc - 2;

	for(int i = 0; i < num; i++)
	{
		list[i] = atoi(argv[i+1]);
		//printf("%i ",list[i]);
	}
	//printf("\n");

	// set up pipe
	pipe(pipe1);
	pipe(pipe2);

	//printf("Pipe 1: %i, %i\nPipe 2: %i, %i\n", pipe1[0], pipe1[1], pipe2[0], pipe2[1]);

	// call fork()
	int pid = fork();

	printf("CS201 - Assignment 3 Regular - Dmitri McGuckin\n");

	if (pid == 0)
	{
			// -- running in child process --
			int     sum = 0;

			printf("Congratulations! You're in the child process now!\n");
			dup2(pipe1[1],STDOUT_FILENO);
			close(pipe1[1]);
			close(pipe1[0]);
			dup2(pipe2[0],STDIN_FILENO);
			// Receive characters from parent process via pipe
			// one at a time, and count them.

			// Return sum of numbers.
			return sum;
	}
	else
	{
			// -- running in parent process --
			int sum = 0;

			// Send numbers (datatype: int, 4 bytes) from command line arguments
			// starting with argv[1] one at a time through pipe to child process.

			// Wait for child process to return. Reap child process.
			// Receive sum of numbers via the value returned when
			// the child process is reaped.

			printf("sum = %d\n", sum);
			return 0;
		}
}
