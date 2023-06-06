#include "FinalCreator.h"

void ent_file_creator(ent_list* first_ent,char *name){
    FILE* ent_new_file;
    ent_list* curr_ent_list = (ent_list*)malloc(2*sizeof(ent_list));
    curr_ent_list = first_ent->next;
    if(curr_ent_list == NULL){/*there is no .entry so don't create this file*/
        printf("don't create .ent file\n");
        return;
    }
    ent_new_file = fopen(name,"w");/*open new file for .entry*/
    while(curr_ent_list!= NULL){/*going thourgh all ent linked list*/
        fprintf(ent_new_file,"%s\t",curr_ent_list->name);/*print to the .enr file the current name*/
        dec_to_thirtyTwo(curr_ent_list->add,ent_new_file);/*print to the .enr file the current address*/
        fprintf(ent_new_file,"\n");
        curr_ent_list = curr_ent_list->next;
    }
}
void ext_file_creator(ext_list* first_ext,char* name){
        ext_list* curr_ext_list;
        int i,size;
        FILE* ext_new_file;
        /*printf("first row(ext)\n");*/
        curr_ext_list = (ext_list*)malloc(2*sizeof(ext_list));
        curr_ext_list = first_ext->next;
        if(curr_ext_list == NULL){/*there is no .extern so don't create this file*/
            printf("don't create .ext file\n");
            return;
        }
        ext_new_file = fopen(name,"w");/*open new file for externs*/
        while(curr_ext_list != NULL){
            size = sizeof(curr_ext_list->found_places)/4;/*how many times this extern label have found*/
            for(i=0;i<size;i++){/*loop that go through the places that found*/
                if((curr_ext_list->found_places)[i] != 0){/*check that is't a valid address*/
                fprintf(ext_new_file,"%s\t",curr_ext_list->name);/*print to .ext file the extern name*/
                dec_to_thirtyTwo((curr_ext_list->found_places)[i],ext_new_file);/*print it's found places*/
                fprintf(ext_new_file,"\n");
                }
            }
            curr_ext_list = curr_ext_list->next;
        }
}
int IC_counter(field_analyze* head_field){
    int IC = 0;
    field_analyze* curr_field = (field_analyze*)malloc(sizeof(field_analyze));
    curr_field = head_field;
    while(curr_field != NULL){
        if(curr_field->flag != valuef)
            IC++;
        curr_field = curr_field->next;
    }
    return IC;
}
int DC_counter(field_analyze* head_field){
    int DC = 0;
    field_analyze* curr_field = (field_analyze*)malloc(sizeof(field_analyze));
    curr_field = head_field;
    while(curr_field != NULL){
        if(curr_field->flag == valuef)
            DC++;
        curr_field = curr_field->next;
    }
    return DC;
}
void ob_file_creator(field_analyze* head_field,char* name){
    char ch;
    FILE* data_image_file;
    FILE* ob_new_file;
    FILE* to_read;
    field_analyze* curr_field;
    int IC_NUMBER,DC_NUMBER;
    IC_NUMBER = IC_counter(head_field->next);/*how many insructions fields do we have*/
    DC_NUMBER = DC_counter(head_field->next);/*how many data fields do we have*/
    data_image_file = fopen("DC.txt","w");
    ob_new_file = fopen(name,"w");
    curr_field = (field_analyze*)malloc(2*sizeof(field_analyze));
    curr_field = head_field->next;
    dec_to_thirtyTwo(IC_NUMBER,ob_new_file);/*print to .ob file the IC*/
    dec_to_thirtyTwo(DC_NUMBER,ob_new_file);/*print to .ob file the DC*/
    fprintf(ob_new_file,"\n");
    while(curr_field != NULL){
        if(curr_field->flag != valuef){
            dec_to_thirtyTwo(curr_field->address,ob_new_file);/*print to .ob the address(base 32)*/
            dec_to_thirtyTwo(fieldAnalyze_add_create(curr_field),ob_new_file);/*print to .ob the bitfield value (base 32)*/
            fprintf(ob_new_file,"\n");
       }else{
            dec_to_thirtyTwo(curr_field->address,data_image_file);/*print to data_image FILE the address(base 32)*/
            dec_to_thirtyTwo(fieldAnalyze_add_create(curr_field),data_image_file);/*print to data_image FILE the bitfield value (base 32)*/
            fprintf(data_image_file,"\n");
        }
        curr_field = curr_field->next;/*implement*/
    }
    fseek(data_image_file,0,SEEK_SET);/*set data_image_file to the start of the FILE*/
    to_read = fopen("DC.txt","r");/*open data_image_file for start reading from it*/
    while( ( ch = fgetc(to_read) ) != EOF ){/*copying all the data from data_image_file to .ob file*/
       fprintf(ob_new_file,"%c",ch);
    }
}
int fieldAnalyze_add_create(field_analyze* f1){
    int bf;
    if(f1->flag == lineF){/*checking on what field are we operating and doing bitwise according*/
        bf = ((f1->line_f.opcode) << 6)
    |((f1->line_f.source) << 4)
    | ((f1->line_f.dest) << 2)
    | ((f1->line_f.ARE) <<0);
    }else if((f1->flag) == labelF){
       bf = ((f1->label_f.address) << 2)
        | ((f1->label_f.ARE) << 0);
    }else if((f1->flag) == numberF){
        bf = ((f1->number_f.num) << 2)
        |((f1->number_f.ARE)<<2);
    }else if((f1->flag) == rgF){
        bf = ((f1->rg_field.source_num) << 6)
    | ((f1->rg_field.dest_num)<< 2)
    | ((f1->rg_field.ARE) << 0);
    }else if((f1->flag) == valuef){
        bf = (f1->vf.value);
    }
    return bf;/*return the value of the whole bitfield*/
}
bool does_file_have_problems(line* head_line){
    line* curr_line = (line*)malloc(sizeof(line));
    /*printf("in func(does_file_have_problems)\n");*/
    curr_line = head_line;
    while(curr_line!=NULL){
        if(curr_line->have_problem == true){/*checks if curr_line "have_problem" flag is on*/
            return true;
        }
        curr_line = curr_line->next;/*implemntation*/
    }
    return false;
}
void dec_to_thirtyTwo(int dec,FILE* file){
 /*   setting the two parts of 5 bits*/
    unsigned half1 = (dec >> 5) & 0x1F;
    unsigned half2 = (dec >> 0) & 0x1F;/*The 0x1F makes sure only half of the bits matther by shutting down the other 5 if they are active/
    char array for the conversion of numbers*/
    char table[] = {'!','@','#','$','%','^','&','*','<','>','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v'};
    /*printing the final number represented in thirty two form*/
    fprintf(file,"%c%c\t",table[half1],table[half2]);
}
