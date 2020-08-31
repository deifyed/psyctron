#ifndef token_storage_h
#define token_storage_h

void allocateTokenStorage(char **, int, int);
void deallocateTokenStorage(char **, int);
void pushToken(char **, char *, int, int);
void resetBuffer(char *, int);

#endif
