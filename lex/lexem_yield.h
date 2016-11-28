//
//  lexem_yield.h
//  lex
//
//  Created by BAZZAOUI chaymae on 11/23/16.
//  Copyright © 2016 BAZZAOUI chaymae. All rights reserved.
//

#ifndef lexem_yield_h
#define lexem_yield_h

#include <stdio.h>

#endif /* lexem_yield_h */
#define MAX_WORD_LEN 30
#include <ctype.h>
#include <strings.h>

typedef struct Lexem {
    char value[MAX_WORD_LEN + 1];
    int col, row;
    struct Lexem * next;
} Lexem;

extern char delimiters[];
extern int lengthDelimiters;

extern char separators[];
extern int lengthSeparators;

extern char composedOperators[];
extern int lengthComposedOperators;

extern char simpleOperators[];
extern int lengthSimpleOperators;

extern FILE * file;
extern Lexem * listLexem;

extern char currentChar;

extern int row, col;




void checkIfFileIsEmpty(FILE * file);

void readChar();
void addLexem(Lexem * lexem);
Lexem * getLastLexem();
int isDigitOperator(char ch);
int isdelimiter(char ch);
void readLexem();
void readLiteral();
void readWord();
int isSeparator(char ch);
int isSimpleOp(char ch);
void readSimpleOp();
int isComposedOperator(char ch);
void readComposedOp();
