#ifndef lexer_h
#define lexer_h
typedef enum {
	item,
	operation
} TokenType;

typedef struct {
	TokenType type;
	char value[100];
} Token;
#endif
