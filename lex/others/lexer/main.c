#include "lexer.h"

int main(int argc, char *argv[])                                                                                                                  
{
	init(argv[1]);
	TokenNode *node;
	node = getTokenList();
	printTokenList(node);
	return 0;
}   
