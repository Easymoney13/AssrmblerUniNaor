#ifndef ANALYE_STR_H
#define ANALYZE_STR_H
#include "store.h"
/*return the last char in the given string*/
char last_str_char(char*);
/*return the first char in the given string*/
char first_str_char(char*);
/*return a new string without white spaces from the given string*/
char* remove_all_white_spaces(char*);
/*return how many rows does a given array have*/
int how_many_rows(char[][max_word_len]);
/**/
char* remove_white_spaces(char*);
/*remove "\n" for the given string and return the new one*/
char* remove_new_lines(char*);
/*return if the given string contain only white spaces*/
bool str_only_white_spaces(char*);
/*our new strtok function
char* - stands for the string we want to divide
char - stands for the delimiter that we splitt the string with
*/
char* str_tok(char*,char);
/*cut the given string from given index to the ending index*/
char* cutString(char*,int,int);
/*return the index the a char found in a string
char* - is the string, char - is the char we are looking for
*/
int char_inside_string(char*,char);
/*remove the last char in a given string and return the new one*/
void remove_last_char(char*);
/*return if the given string is a number*/
bool str_is_number(char*);
/*return if the given string starts with '#'*/
bool str_start_hash(char*);
/*return if the given string have their first and last char the same*/
bool first_and_last_same(char*);
#endif 
