#ifndef LINE_READ_H
#define LINE_READ_H
#include "store.h"
#include "helper.h"
#include "analyze_str.h"
#include "line_read.h"
typedef struct line{
    int line_number;
    int address;
    char full_line[maxLineLen];
    char separate[max_line_words][max_word_len];/*separate the words in the line*/

    int word_num;
    int bfNum;

    bool is_comment;/*should ingnore these line*/
    bool is_empty;/*should ingnore these line*/
    bool is_instruct;/*הוראה*/

    bool is_ignore;
    bool has_label;

    bool is_guidance;/*הנחיה*/
    bool is_data;
    bool is_string;
    bool is_struct;
    bool is_entry;
    bool is_extern;

    bool is_First_Operand_Immediate; /* Method 0 */
    bool is_First_Operand_Direct;    /* Method 1 */
    bool is_First_Operand_access_struct;  /* Method 2 */
    bool is_First_Operand_Register_Direct;   /* Method 3 */
    bool is_First_Operand_Empty;/*don't have opperand*/

    bool is_Second_Operand_Immediate; /* Method 0 */
    bool is_Second_Operand_Direct;    /* Method 1 */
    bool is_Second_Operand_access_struct;  /* Method 2 */
    bool is_Second_Operand_Register_Direct; /* Method 3 */
    bool is_Second_Operand_Empty;/*don't have opperand*/

    bool is_unknown;
    bool have_problem;

    struct line* prev;
    struct line* next;
}line;
/*
check the type of the line
*/
void line_type(line*);
/*
check what type of is_guidance line we have
*/
void guide_type(line*);
/*
return how many words that line have
*/
int count_words(line*);
/*
create array that seperate between all the words in the line 
*/
void seperate_array_creator(line*);
/*
defualt initialize for "line" type(to avoid error)
*/
void deff_values(line*);
/*
initialize the parametrs of the line to seperate words array
char* stands for the all parametrs string
int stands for symbolize the next free place in seperate array
*/
void divide_parameters(line*,char*,int);
/*
give the "line" type the true data about himself
char* stands for the full line string
int stands for the current address of the first word in that line
*/
void values_initializer(line*,char*,int);
/*
function that add a new "line" to the lines linked list
*/
line* add_line(char*,line*,line*);
/*
combines all the function that relate to line linked list
and simplfy the call from main
*/
void create_lines_list(line*,char*);
/*
prints all the "line" linked list
*/
void print_line_nodes(line*);
/*
return how many bitfield the given "line" need for binary represestation
*/
int howManyBf(line*);
#endif
