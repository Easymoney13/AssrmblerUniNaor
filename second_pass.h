#ifndef SECOND_PASS_H
#define SECOND_PASS_H
#include "store.h"
#include "line_read.h"
#include "first_pass.h"
typedef enum{r0=0,r1,r2,r3,r4,r5,r6,r7,error_rg}rigistrs;
typedef enum{mov,cmp,add,sub,not,clr,lea,inc,dec,jmp,bne,get,prn,jsr,rts,hlt,error_op}opcode_func;
typedef enum{rg_type,opcode_type,label_type,numbers,struct_t,empty_type,error}word_type;

typedef enum{absolute=0,external,relocatable}AREN;
typedef enum{immediate =0,direct,access_struct,register_direct,empty,error_add_method}add_method;
typedef enum{lineF=0,labelF,numberF,rgF,valuef}field_types;
typedef struct field_analyze{
	int address;
	char name[max_word_len];
	field_types flag;
	struct{
	unsigned int ARE : 2;
	unsigned int dest : 2;
	unsigned int source : 2;
	unsigned int opcode : 4;
}line_f;
	struct{
	unsigned int ARE:2;
	unsigned int address: 8;
}label_f;
	struct{
	unsigned int ARE:2;
	unsigned int num : 8;
}number_f;
	struct{
	unsigned int ARE :2;
	unsigned int dest_num : 4;
	unsigned int source_num : 4;
}rg_field;
	struct{
	unsigned int value :10;
}vf;
	struct field_analyze* next;
}field_analyze;

typedef struct ent_list{
	char name[30];
	int add;
	struct ent_list* next;
}ent_list;
typedef struct ext_list{
	char name[30];
	int* found_places;
	struct ext_list* next;
}ext_list;
/*returns the first/second oppernd addresing methods */
add_method get_first_opp_method(line*);
add_method get_second_opp_method(line*);
/*return if the given strign is a integer*/
bool is_opp_int(char*);
/*return if the given string starts and end with '"'*/
bool is_opp_string(char*);
/*return the word_type(rg_type/opcode_type/label_type/numbers/struct_t/empty_type/error)of the given stringn*/
word_type analyze_word(char*,label*);
/*check and return if the given string found in the label table
char* -  is the string
label* -  is the first label node in the linked list of labels
*/
bool is_word_label(char*,label*);
/*return the address of the given string from the label table
char* - is the name of the label
label* - is thr first label node of the label table
*/
int get_label_address(char*,label*);
/*return the number of the string that start with '#'
for example : string: "#23" will return the number 23*/
int get_number(char*);
/*return if the given string is a rigister and if it is the value of the
rigister will return*/
rigistrs get_rg_number(char*);
/*return if the name is a valid name for being a extern label
char* - is the name
label* - is the first label node of the label table
ent_list* - is the first node of the entry's
*/
bool valid_extern_label(char*,label*,ent_list*);
/*return if the name is a valid name for being a entry label
char* - is the name
label* - is the first label node of the label table
ext_list* - is the first node of the extern's
*/
bool valid_entry_label(char*,label*,ext_list*);
/*function check the addressing method of each operand(according to the given number)
line* - is the pointer to the wanted line
label* - pointer to the first label node in linked list
int - symbolyze which opperand we want to check
*/
void check_address(line*,label*,int);
/*return if the line is valid(on the asspect of addressing methods 
and insruction methods)
opcode_func - is the method number
1) add_method - is the first addressing method of the line
2) add_method - is the second addressing method of the line
*/
bool is_line_valid(opcode_func,add_method,add_method);
/*function that combains all the related methods to the seoncd pass 
and create a "field_analyze" linked list that contians address, bit represantion
and names of labels
line* - is the first line in the linked list
ent_list* - is the entry's linked list
ext_list* - is the extern's linked list
field_analyze* - is the first node that we will connect all the others to
*/
void second_pass(line*,label*,ent_list*,ext_list*,field_analyze*);
/*checks where in program a external label were found
	ext_list* - is the pointer for the extern label
	field_analyze* - is the head field_analyze node
*/
void where_ext_found(ext_list*, field_analyze*);
/*help to check the validation of line by somethimes swap between addressing methods in the given line*/
void swap_first_second_types(line*);
/*get the opcode function number if the given string*/
opcode_func get_op_number(char*);
#endif 