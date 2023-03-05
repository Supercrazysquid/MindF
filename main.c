/*
 * By Joe Peterson
 *
 * Started on March 1st, 2023
 *
 * Commands:
 * 	>  Adds 1 to the pointer value
 * 	<  Removes 1 from the pointer value
 * 	+  Adds 1 to the value of the pointer
 * 	-  Removes 1 from the value of the pointer
 * 	#  Prints the integer value of a given pointer's value
 * 	@  Prints the character value of a given pointer's value
 *	*  Multiplies the current pointer's value by the one in front of it
 *	~  Sets the current pointer's value to 0
 *
 */

#include <stdio.h>

int *arrptr;
int array[256];

char* version = "1.0";

void interpret(char command) {
	switch(command) {
		case '>':
			arrptr++;
			break;

		case '<':
			arrptr--;
			break;

		case '+':
			(*arrptr)++;
			break;

		case '-':
			(*arrptr)--;
			break;

		case '#':
			printf("%d", *arrptr);
			break;

		case '@':
			printf("%c", *arrptr);
			break;

		case '*':
			arrptr++;
			int multiplier = *arrptr;
			arrptr--;

			*arrptr *= multiplier;
			break;

		case '~':
			*arrptr = 0;

			break;

		default:
			break;

	}
}

void command() {
	char *cmdptr;
	char command[1024] = {'\0'};

	printf("> ");
	scanf("%1023s", command);
	
	cmdptr = command;

	while(*cmdptr != '\0') { // Iterating through the command array until we reach a null terminator
		interpret(*cmdptr);
	
		cmdptr++;
	}

	printf("\n");
}

int main(int argc, char** argv) {
	arrptr = array;

	if(argc == 1) {
		printf("MindF CLI %s\nDisclaimer: Modifications to the array are saved between commands!\n", version);

		while(1) command();
	} else {
		// Checking if the argument is a file
		FILE *file;

		char* command = "\0";

		if((file = fopen(argv[1], "r")) != NULL) {
			// File is valid

			char buffer[1024];
			
			fread(buffer, 1025, 1, file);
		
			command = buffer;
		}
	
		char *cmdptr;

		if(command == "\0") command = argv[1];
	
		cmdptr = command;
	
		while(*cmdptr != '\0') {
			interpret(*cmdptr);
	
			cmdptr++;
		}
	}

	return 0;
}
