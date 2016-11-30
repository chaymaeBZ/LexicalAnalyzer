//
//  lexem_yield.c
//  lex
//
//  Created by BAZZAOUI chaymae on 11/23/16.
//  Copyright © 2016 BAZZAOUI chaymae. All rights reserved.
//
#include <stdlib.h>
#include "lexem_yield.h"


void checkIfFileIsEmpty(FILE * file){
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0){
        printf("This file is empty");
        exit(1);
    } else {
        rewind(file);
    }
}


void readChar(){
    currentChar = fgetc(file);
    if(currentChar == '\n'){
        row++;
        col = -1;
    } else {
        col++;
    }
}

void addLexem(Lexem * lexem){
    lexem->next = NULL;
    
    if (listLexem == NULL){
        listLexem = lexem;
    } else {
        Lexem * tmp = listLexem;
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = lexem;
    }
}

Lexem * getLastLexem() {
    Lexem * tmp = listLexem;
    while(tmp->next != NULL) {
        tmp = tmp->next;
    }
    return tmp;
}

int isdelimiter(char ch){
    int i;
    for (i=0; i<lengthDelimiters; i++) {
        if (ch == delimiters[i]){
            return 1;
        }
    }
    return 0;
}


void readLiteral(){
    int charCounter = 0;
    int varCol = col; // col counted from the beginning of lexem
    Lexem * lexem = (Lexem *) malloc(sizeof(Lexem));
   
    lexem->col = varCol;
    lexem->row = row;
    
    int isFloat = 0;
    
    while (isdigit(currentChar) || (currentChar == '.')) {
       
        lexem->value[charCounter] = currentChar;
        if (currentChar == '.') {
            isFloat++;
        }
        if (isFloat == 2) {
            printf("Invalid '.' at col: %d, row: %d\n", col, row);
            fclose(file);
            exit(1);
        }
        charCounter++;
        readChar();
    }
    if (isalpha(currentChar)) { // case of 123salim
        printf("Invalid variable format in col: %d , row: %d\n", varCol, row);
        fclose(file);
        exit(1);
    }
    addLexem(lexem);
    
}


void readWord() {
    
    int charCounter = 0;
    int varCol = col; // col counted from the beginning of lexem
    Lexem * lexem = (Lexem *) malloc(sizeof(Lexem));
   
    lexem->col = varCol;
    lexem->row = row;
    
    lexem->value[charCounter] = currentChar;
    charCounter++;
    readChar();
    
    while(isalnum(currentChar)){
        
        if(charCounter < MAX_WORD_LEN)
            lexem->value[charCounter] = currentChar;
        
        charCounter++;
        readChar();
    }
    addLexem(lexem);
}


int isSeparator(char ch){
    int i;
    for (i=0; i < lengthSeparators; i++) {
        if (ch == separators[i])
            return 1;
    }
    return 0;
}


int isSimpleOp(char ch){
    int i;
    for (i = 0; i < lengthSimpleOperators; i++) {
        if(ch == simpleOperators[i]){
            return 1;
        }
    }
    return 0;
}


void readSimpleOp(){
    Lexem * lexem = (Lexem *) malloc(sizeof(Lexem));
    
    lexem->col = col;
    lexem->row = row;
    
    lexem->value[0] = currentChar;
    
    readChar();
    addLexem(lexem);

}


void readDelimiter(){
    Lexem * lexem = (Lexem *) malloc(sizeof(Lexem));
    
    lexem->col = col;
    lexem->row = row;
    
    lexem->value[0] = currentChar;
    
    readChar();
    addLexem(lexem);
}


int isComposedOperator(char ch){
    int i;
    for (i = 0; i < lengthComposedOperators; i++) {
        if(ch == composedOperators[i]){
            return 1;
        }
    }
    return 0;
}


void readComposedOp(){
    Lexem * lexem = (Lexem *) malloc(sizeof(Lexem));
    int varCol = col;
    lexem->col = varCol;
    lexem->row = row;
    
    lexem->value[0] = currentChar;
    
    readChar();
    if (currentChar == '=') {
        lexem->value[1] = currentChar;
        readChar();
    }
    
    addLexem(lexem);
}

void readLexem() {
    if (isalpha(currentChar)) {
        readWord();
    }
    else if (isSeparator(currentChar)) {
        readChar();
    }
    else if (isdigit(currentChar)){
        readLiteral();
    }
    else if (isdelimiter(currentChar)){
        readDelimiter();
    }
    else if (isSimpleOp(currentChar)){
        readSimpleOp();
    }
    else if (isComposedOperator(currentChar)){
        readComposedOp();
    }
    
}
