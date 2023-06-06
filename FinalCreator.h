#include "first_pass.h"
#include "store.h"
#include "second_pass.h"
#include "line_read.h"
#include "analyze_str.h"
/*create the .ob file
field_analyze* is the first field_analyze(bitfield)
char* is the name of the new file we need to create
*/
void ob_file_creator(field_analyze*,char*);
/*create the .ent file
field_analyze* is the first ent_list(.entry node)
char* is the name of the new file we need to create
*/
void ent_file_creator(ent_list*,char*);
/*create the .ob file
field_analyze* is the first ext_list(.extern node)
char* is the name of the new file we need to create
*/
void ext_file_creator(ext_list*,char*);
/*
return the integer number of the binary reprsntation of each field_analyze(bitfield)
field_analyze* if a pointer that point to the curr "bitfield"
*/
int fieldAnalyze_add_create(field_analyze*);
/*
return if we have found problems through the program in the given .as file 
and according to the that return we consider creating these files or
continue the program
*/
bool does_file_have_problems(line*);
/*count and return how many "instruction fields" that program contains
field_analyze is the first node in that linked list and qw will walk thourgh
that to explore each "field_analyze" type
*/
int IC_counter(field_analyze* head_field);
/*count and return how many "data fields" that program contains
field_analyze is the first node in that linked list and qw will walk thourgh
that to explore each "field_analyze" type
*/
int DC_counter(field_analyze* head_field);
/*this function print to the given FILE the given number on base 32*/
void dec_to_thirtyTwo(int,FILE*);