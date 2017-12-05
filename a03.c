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
#include <sys/wait.h>

#define BSIZE 4
#define REGEXIT 65280

int main(int argc, char **argv)
{
	pid_t pid;
	int pipeIntoChild[2], pipeOutOfChild[2];

	// set up pipe
	pipe(pipeIntoChild);
	pipe(pipeOutOfChild);

	// Redefine all of the pipe ends before compile time
	#define ParentRead      pipeOutOfChild[0]
	#define ParentWrite     pipeIntoChild[1]
	#define ChildRead       pipeIntoChild[0]
	#define ChildWrite      pipeOutOfChild[1]

	system("clear");
	printf("CS201 - Assignment 3 Regular - Dmitri McGuckin\n");

	// Set up the fork
	pid = fork();

	if (pid < 0) // Error in the child forking
	{
		printf("The child process for PID(%i) did not fork correctly!\n", pid);
		exit(-1);
	}
	else if (pid == 0)
	{
		// The Child Process
		int sum = 0, count = 0, temp;

		// Close unused pipe ends
		close(ParentRead);
		close(ParentWrite);

		do // Read in arguments passed from the shell via the pipe untill it reads a zero
		{
			read(ChildRead, &temp, BSIZE);
			sum += temp;
			count++; // Count the number of arguments that were passed in
		} while(temp != 0);

		count--; // Decrement the counter to disclude zero

		// If the shell passed in an odd number of arguments, kill the child
		if((count % 2) != 0)
		{
			printf("Error in the data\n");
			return -1;
		}

		// Calculate the average of the inputs
		sum /= count;

		// Write the average back into the pipe
		write(ChildWrite, &sum, BSIZE);

		// Close the rest of the pipe ends
		close(ChildRead);
		close(ChildWrite);

		// printf("RETURNING(%i)\n", sum); // Optional Debug Info

		return sum; // Return sum of numbers
	}
	else
	{
		// The Parrent Process
		int list[argc], average, status;

		// Close unused pipe ends
		close(ChildRead);
		close(ChildWrite);

		// Convert all of the shell arguments from characters to ints
		// Then write in all of the arguments into the pipe
		for (int i = 1; i < argc; i++)
		{
			list[i] = atoi(argv[i]);
			write(ParentWrite, &list[i], BSIZE);
		}

		// Reap the child process and record the status
		waitpid(pid, &status, 0);

		// printf("The child process for PID(%i) was reaped with status(%i)\n", pid, status); // Optional Debug Info

		read(ParentRead, &average, BSIZE);

		if(status != REGEXIT) // If the child exited normally, print the average
		{
			printf("average = %d\n", average);
		}

		// Close the rest of the pipe ends
		close(ParentRead);
		close(ParentWrite);

		return 0;
	}
}
