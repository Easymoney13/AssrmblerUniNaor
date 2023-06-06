#ifndef STORE_H
#define STORE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#define endingAsFile ".as"
#define endingAmFile ".am"
#define endingOBFile ".ob"
#define endingEXTFile ".ext"
#define endingENTFile ".ent"
#define maxLineLen 80
#define maxFileName 30
#define max_line_words 40
#define max_word_len 10 
#define maxFileRowsmaxLineLen 200
#define starting_address 100
typedef enum{
  lable_struct = 0,
  label_string =1,
  label_data=2
}label_method;

typedef enum {
  false = 0,
  true = 1
}bool;
typedef struct macro_node{
    char* macro_name;
    char all_macro_data[maxFileRowsmaxLineLen];
    struct macro_node *next;
}macro_node;
#endif