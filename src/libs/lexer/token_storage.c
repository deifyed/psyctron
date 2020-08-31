#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void allocateTokenStorage(char ** storage, int max_tokens, int max_token_length) {
	for (int index = 0; index < max_token_length; index++)
		storage[index] = malloc(sizeof(char) * max_token_length);
}
void deallocateTokenStorage(char ** storage, int max_tokens) {
	for (int index = 0; index < max_tokens; index++)
		free(storage[index]);
}

void pushToken(char ** storage, char * token, int index, int max_token_length) {
	strncpy(storage[index], token, max_token_length);
}

void resetBuffer(char * buffer, int buffer_size) {
	memset(buffer, '\0', buffer_size);
}
