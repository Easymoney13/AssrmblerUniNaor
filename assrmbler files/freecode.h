#ifndef FREECODE_H
#define FREECODE_H
#include "store.h"
#include "line_read.h"
#include "first_pass.h"
#include "second_pass.h"
/*free macro linked list - get the first "macro" node*/
void free_macroList(macro_node*);
/*free "line" linked list - get the first "line" node*/
void free_lineList(line*);
/*free "label" linked list - get the first "label" node*/
void free_labelList(label*);
/*free "field_analyze" linked list - get the first "field_analyze" node*/
void free_fieldList(field_analyze*);
/*combain all the "free" methods into one and free all*/
void freeAll(line*,label*,field_analyze*,ent_list*,ext_list*);
/*free "ext_list" linked list - get the first node of externs*/
void free_ext_list(ext_list*);
/*free "ent list" linked list - get the firs node of entrys */
void free_ent_list(ent_list*);
#endif
