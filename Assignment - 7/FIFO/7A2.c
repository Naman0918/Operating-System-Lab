#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main()
{
    int f1 = 0, f2 = 0, i = 0, ret;
    char readSentence[100], buffer[300];
    int numChar = 0, numWords = 0, numLines = 0, numLetters = 0;
    FILE *fp;

    ret = mkfifo("myfifo", 0666);
    if ((ret < 0) && (errno != EEXIST))
    {
        printf("\nERROR WHILE CREATING THE FIFO!");
        return;
    }

    if (errno == EEXIST)
    {
        printf("\nFIFO ALREADY EXISTS!");
    }

    printf("\nWAITING FOR OUTPUT FROM FIFO1...\n");
    sleep(5);

    f1 = open("myfifo", O_RDONLY);
    read(f1, readSentence, 100); // read the data from FIFO and store it in readSentence[] array until '\0' is encountered
    printf("\n\n%s\n\n", readSentence);// print the data read from FIFO
    // \n\n%s\n\n - to print the data in a new line
    
    int w = 0;
    for (i = 0; readSentence[i] != '\0'; i++) // loop to count the number of characters, words, lines and letters
    {
        if ((readSentence[i] == '.') || (readSentence[i] == '!') || (readSentence[i] == '?'))
        {
            numLines++;
        }

        if ((readSentence[i] == ' ') || (readSentence[i] == ','))
        {
            numWords++;
        }

        if ((readSentence[i] == ' ') || (readSentence[i] == ',') || (readSentence[i] == '.') || (readSentence[i] == '!') || (readSentence[i] == '?'))
        {
            w++;
        }
    }
    numChar = i - 1;
    numLetters = i - w - 1;

    fp = fopen("7b.txt", "w");
    fprintf(fp, "\nNO. OF CHARACTERS = %d\n", numChar);
    fprintf(fp, "NO. OF LETTERS = %d\n", numLetters);
    fprintf(fp, "NO. OF WORDS = %d\n", numWords + 1);
    fprintf(fp, "NO. OF LINES = %d\n", numLines);
    fprintf(fp, "%c", EOF);
    fclose(fp);

    fp = fopen("7b.txt", "r");
    i = 0;
    while (fscanf(fp, "%c", &buffer[i++]) != EOF) // read the file character by character
    {                                             // and store it in buffer[] array
        buffer[i] = '\0';                         // NULL character
    }                                             // while loop ends when EOF is reached
    fclose(fp);                                   // close the file

    printf("\nWRITING THE OUTPUT TO FIFO2...\n");
    f2 = open("myfifo", O_WRONLY);
    write(f2, buffer, (strlen(buffer) + 1));
    sleep(5);
    unlink("myfifo");
    return 0;
}
