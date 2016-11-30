//
//  main.c
//  lex
//
//  Created by BAZZAOUI chaymae on 11/23/16.
//  Copyright © 2016 BAZZAOUI chaymae. All rights reserved.
//

#include <stdio.h>
#include "lexem_yield.h"

FILE * file;
Lexem * listLexem = NULL;

char currentChar;

int col = -1;
int row = 0;

int max_word_len = 30;

char delimiters[] = {'(', ')', ',', '{', '}', ';', '[', ']', '.'}; //9
int lengthDelimiters = 9;

char simpleOperators[] = {'+', '%', '/', '*', '='};
int lengthSimpleOperators = 5;

char separators[] = {' ', '\t', '\n', '\0', '\r'};
int lengthSeparators = 5;

char composedOperators[] = {'<', '>'};
int lengthComposedOperators = 2;

int main(int argc, const char * argv[]) {
    
    file = fopen("/Users/bazzaouichaymae/Documents/lex/lex/test.txt", "r");
    
    // if the file is empty then exit
    checkIfFileIsEmpty(file);
    
    // ajouter la liste des erreurs
    
    
    readChar();
    
    
    while (currentChar != EOF) {
        readLexem();
    }
    
    
    Lexem * lex = listLexem;
    printf("-------------------\n");
    while (lex != NULL) {
        printf("%s\n", lex->value);
        lex = lex->next;
    }
    fclose(file);
    return 0;

}
