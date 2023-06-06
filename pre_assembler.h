#ifndef PRE_ASSEMBLER_H
#define PRE_ASSEMBLER_H
#include "store.h"
#include "analyze_str.h"
#include "helper.h"
#include "line_read.h"
#include "second_pass.h"
/*Function preAssembler gets a char* and opens two files with that name:
One file is the file that was given to the program
The other one will have data printed into by another function.
Function also creates the first macro_node node for the list of macro_node.*/
void preAssembler(char*);
/*check the validation of that macro name*/
bool valid_macro_name(char*);
/*Function make_am_file copies certain data from one file to another, Excluding macro definitions.
Whenever a name of a previously defined macro is found, function will print the data of that macro.
The rest of the file gets printed as written as the previous file.
Function make_am_file gets two FILE* parameters the one macro_node* parameter:
One FILE* parameter is the file that the data is taken from, reffered as data file.
Another FILE* parameter is the file that will get data printed into, reffered to as print file.
The macro_node* parameter is the head of the macro_node list that was created in preAssembler, reffered to as macro head.
Returns the print file.*/
FILE *make_am_file(FILE*,FILE*,macro_node*);
/*Function is_macro checks if inputted parameter is a already existing macro that was declared before
Parameter macro_node* is the head of the macro list
Parameter char* is the word suspected to be a name of a macro
Returns the macro_node* that has the same name as the char* parameter, if suspected name isn't macro returns NULL*/
macro_node* is_macro(macro_node*, char*);
#endif