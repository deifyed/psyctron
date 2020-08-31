#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "token_storage.h"

int getFileSize(FILE *file) {
	int size;

	fseek(file, 0L, SEEK_END);
	size = ftell(file);
	rewind(file);

	return size;
}

int readFile(FILE * file, char * result, int size) {
	int c;

	int index = 0;
	while(index < size) {
		c = fgetc(file);

		result[index] = c;

		index++;
	}

	return 0;
}

int loadFile(char *path) {
	int size;
	FILE *file = fopen(path, "r");

	size = getFileSize(file);
	char result[size];

	readFile(file, result, size);

	printf("%s", result);

	fclose(file);

	return 0;
}

void tokenize(char * data) {
	int max_tokens = 100;
	int max_token_length = 100;
	char * tokens[max_tokens];

	allocateTokenStorage(tokens, max_tokens, max_token_length);
	char * token_buffer = malloc(sizeof(char) * max_token_length);

	int token_count = 0;
	int buffer_index = 0;
	char c = ' ';

	char string_mode = 0;

	for (int data_index = 0; c != '\0'; data_index++) {
		c = data[data_index];

		if (string_mode != 0) {
			token_buffer[buffer_index] = c;
			buffer_index += 1;

			if (c == string_mode) {
				string_mode = 0;

				pushToken(tokens, token_buffer, token_count++, max_token_length);
				resetBuffer(token_buffer, max_token_length);
				buffer_index = 0;
			}

			continue;
		}

		switch (c) {
			case 32: // space
				pushToken(tokens, token_buffer, token_count++, max_token_length);
				resetBuffer(token_buffer, max_token_length);
				buffer_index = 0;
				break;
			case 9: // tab
			case 10: // newline
			case 40: // (
			case 41: // )
			case 58: // :
				if (buffer_index != 0) {
					pushToken(tokens, token_buffer, token_count++, max_token_length);
					resetBuffer(token_buffer, max_token_length);
					buffer_index = 0;
				}

				token_buffer[buffer_index] = c;
				pushToken(tokens, token_buffer, token_count++, max_token_length);
				resetBuffer(token_buffer, max_token_length);
				buffer_index = 0;
				break;
			case 34: // "
			case 39: // '
				string_mode = c;

				token_buffer[buffer_index] = c;
				buffer_index += 1;
				break;
			/*
			case 32: // space
			case 34: // "
			case 39: // '
				continue;
			*/
			default:
				token_buffer[buffer_index] = c;
				buffer_index += 1;
		}
	}

	for (int index = 0; index < token_count; index++)
		printf("token: \"%s\"\n", tokens[index]);

	free(token_buffer);
	deallocateTokenStorage(tokens, max_tokens);
}


int main() {
	FILE * file = fopen("hw.psy", "r");
	int size = getFileSize(file);

	char * data = malloc(sizeof(char) * size);
	memset(data, '\0', sizeof(char) * size);

	readFile(file, data, size);

	tokenize(data);

	free(data);
}
