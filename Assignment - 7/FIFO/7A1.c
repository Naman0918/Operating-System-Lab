// FIFOs: Full duplex communication between two independent processes.
// First process accepts sentences and writes on one pipe to be read by
// second process and second process counts  number of characters, number
// of words and number of lines in accepted sentences, writes this output
// in a text file and writes the contents of the file on second pipe to be
// read by first process and displays on standard output.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

// Compile and run the program as follows:

// gcc Writer.c -o Writer_Program -1
// ./Writer_Program -2

// gcc Reader.c -o Reader_Program -3
// ./Reader_Program -4

int main()
{
	int f1 = 0, ret = 0; // ret- used to stor the return value of system calls.
	char sentence[100];

	// Create a named pipe (FIFO)
	printf("CREATING NAMED PIPE (FIFO)...\n");
	ret = mkfifo("myfifo", 0666); // Permission is set to '0666', 0666 is the default permission for a file.

	if (ret < 0 && errno != EEXIST)
	{ // it checks whether the error code is EEXIST indicating that the FIFO already exists.
		perror("ERROR WHILE CREATING THE FIFO");
		return 1; // Return an error code to indicate an error.
	}

	if (errno == EEXIST)
	{
		printf("FIFO ALREADY EXISTS!\n");
	}

	printf("ENTER A SENTENCE: ");
	fgets(sentence, sizeof(sentence), stdin); // fgets function is used to read a line of text

	// Open the FIFO for writing
	f1 = open("myfifo", O_WRONLY); // O_WRONLY - Open for writing only.

	if (f1 == -1)
	{
		perror("ERROR OPENING FIFO FOR WRITING");
		return 1; // Return an error code to indicate an error.
	}

	// Write the sentence to the FIFO
	write(f1, sentence, strlen(sentence) + 1); // why +1?
	// The +1 is to include the NULL character in the string.
	printf("WRITTEN THE SENTENCE TO FIFO 1...\n");

	// Close the FIFO for writing
	close(f1);

	return 0; // Return 0 to indicate successful execution.
}
