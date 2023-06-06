#ifndef FIRST_PASS_H
#define FIRST_PASS_H
#include "store.h"
#include "line_read.h"
#include "analyze_str.h"
#include "helper.h"
/*
new type of label that contian name,address,label method and a pointer to the next one
*/
typedef struct label{
    char name[30];
    int add;
    label_method lm;
    struct label* next;
}label;

/*
create the total label table to a linked list
label* - stands for the first label node of the linked list - we will connect all the other
new nodes to that first one
line* - stands for the first "line" type of the file which will help us create label table 
*/
void create_label_table(label*,line*);
/*
print all the labels
label* - stands for the first label of the linked list
*/
void printLabels(label*);
/*
return if the name is valid as a name for label 
char* - stands for the string that contain the name 
*/
bool is_valid_label_name(char*);
#endif