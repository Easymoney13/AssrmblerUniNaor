#include "first_pass.h"

/*l1 - first line in linked list(of lists)
label_first*/
void remove_two_dots(char* str){
    int i;

    for(i=0;i<strlen(str);i++){
        if(str[i] == ':')
            str[i] = '\0';
    }
}
    void create_label_table(label* label_first,line* l1){
    label* curr_label = label_first;
    line* curr_line = l1;

    while((curr_line = curr_line ->next) != NULL){
        /*printf("first word in line :%s\n",curr_line->separate[0]);
        printf("in while\n");*/
        if(curr_line->is_extern == true){/*chekc if the current line is extern*/
            label* new_label = (label*)malloc(sizeof(label));
            /*puts("line is_extern(first pass while)\n");*/
            curr_label->next = new_label;
            strcpy(new_label->name,(curr_line->separate)[1]);/*assign the new label name from the seperate table*/
            new_label->add = 0;/*assign label address to 0*/
            curr_label = new_label;
            curr_label ->next = NULL;
        }
        if(curr_line->has_label){
            label* new_label = (label*)malloc(sizeof(label));
            if(curr_line->is_entry || curr_line->is_extern){/*if delered label in .entry/.extern line*/
                /*printf("line %d: invalid label declration\n",curr_line->line_number);*/
                curr_line->have_problem = true;
                continue;
            }
            if(is_valid_label_name(curr_line->separate[0])==false){/*check if the name is a valid name*/
                printf("line %d: invalid label name\n",curr_line->line_number);
                curr_line->have_problem = true;
                continue;
            }
            /*printf("line have label\n");*/
            curr_label -> next = new_label;
  /*          printf("before strcpy\n");*/
            remove_two_dots((curr_line->separate)[0]);/*remove the ':' from the label name*/
            strcpy(new_label -> name,(curr_line->separate)[0]);/*assign the label name to the label table*/
      /*      printf("after strcpy string: %s\n",new_label->name);*/
            new_label -> add = curr_line->address;/*assign its address*/
            if(curr_line->is_data == true)
                new_label->lm = label_data;
            else if(curr_line->is_string == true)
                new_label->lm = label_string;
            else if(curr_line->is_struct == true)
                new_label->lm = true;
            /*printf("before connect curr is: %s\n",curr_label->name);*/
            curr_label = new_label;
            /*printf("after connect new label name :%s ,add: %d\n",curr_label->name,curr_label->add);*/
            curr_label ->next = NULL;
        }
    }/*while*/  
}
void printLabels(label* head_label){
    label* curr_label = (label*)malloc(sizeof(label));
    curr_label = head_label;
    while(curr_label != NULL){
        /*printf("%s , %d\n",curr_label->name,curr_label->add);*/
        curr_label = curr_label->next;
    }
}
bool is_valid_label_name(char* label_name){
    int i;
    if(!isalpha(label_name[0]))
        return false;
    for(i=1;i<strlen(label_name)-1;i++){
        if((isalpha(label_name[i]) || isdigit(label_name[i]))&&strlen(label_name)<30);/*check if each char is digit/num and also check the length*/
        else
            return false;
    }
    return true;
}