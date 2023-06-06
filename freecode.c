#include "freecode.h"

void free_macroList(macro_node* head){
    macro_node *tmp;
    while(head!=NULL){
        tmp = head;
        head = head->next;
        free(tmp);
    }/*while*/
    head->next = NULL;
}

void free_lineList(line* head){
    line *tmp;
    while(head!=NULL){
        tmp = head;
        head = head->next;
        free(tmp);
    }/*while*/
}

void free_labelList(label* head){
    label *tmp;
    while(head!=NULL){
        tmp = head;
        head = head->next;
        free(tmp);
    }/*while*/
}

void free_fieldList(field_analyze* head){
    field_analyze *tmp;
    while(head!=NULL){
        tmp = head;
        head = head->next;
        free(tmp);
    }/*while*/
}
void free_ent_list(ent_list* ent_first){
    ent_list* curr;
    while(curr!= NULL){
        curr = ent_first;
        if(curr==NULL)
            return;
        ent_first = ent_first->next;
        free(curr);
    }
}
void free_ext_list(ext_list* ext_first){
    ext_list* curr;
    while(curr!= NULL){
        curr = ext_first;
        if(curr==NULL)
            return;
        ext_first = ext_first->next;
        free(curr);
    }
}

void freeAll(line *line, label *label, field_analyze *field,ent_list* ent_first,ext_list* ext_first){
    free_lineList(line);
    free_labelList(label);
    free_fieldList(field);
    free_ent_list(ent_first);
    free_ext_list(ext_first);
}
