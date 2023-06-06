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
    /*printf("after 1st\n");*/
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
    /*puts("before free lines");*/
    free_lineList(line);
    /*puts("before free label");*/
    free_labelList(label);
    /*puts("before free field");*/
    free_fieldList(field);
    /*puts("before free ent's");*/
    free_ent_list(ent_first);
    /*puts("before free ext's");*/
    free_ext_list(ext_first);
    /*puts("after all");*/
}