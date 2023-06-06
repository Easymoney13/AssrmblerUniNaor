#include "store.h"
#include "second_pass.h"
#include "first_pass.h"
#include "line_read.h"
#include "analyze_str.h"
#include "FinalCreator.h"
#include "pre_assembler.h"
#include "freecode.h"

int main(int argc,char* argv[]){
    int i;
    if(argc < 2){
        printf("please enter file names\n");
        exit(-1);
    }
    for(i=1;i<argc;i++){
        line* first_line;
        label* head_label;
        ent_list* first_ent_list;
        ext_list* first_ext_list;
        ext_list* curr_ext_node;
        FILE* open_file;
        char name_as[maxFileName];
        field_analyze* first_field_analyze;
        strcpy(name_as,argv[i]);
        strcat(name_as,endingAsFile);
        open_file = fopen(name_as,"r");
        if(open_file == NULL){
            printf("\nERROR :cannot open file %s\n\n",argv[i]);
            continue;
        }
        preAssembler(argv[i]);
        first_line = (line*)malloc(sizeof(line));
        deff_values(first_line);
        create_lines_list(first_line,argv[i]);
        head_label = (label*)malloc(sizeof(label));
        create_label_table(head_label,first_line);
        first_ent_list = (ent_list*)malloc(sizeof(ent_list));
        first_ext_list = (ext_list*)malloc(sizeof(ext_list));
       first_field_analyze = (field_analyze*)malloc(sizeof(field_analyze));        
       second_pass(first_line,head_label->next,first_ent_list,first_ext_list,first_field_analyze);
    curr_ext_node = (ext_list*)malloc(2*sizeof(ext_list));
    curr_ext_node = first_ext_list->next;
    while(curr_ext_node != NULL){
        where_ext_found(curr_ext_node,first_field_analyze);
        curr_ext_node = curr_ext_node->next;
    }
    if(does_file_have_problems(first_line) == true){
        printf("file '%s' have problems\ndon't create output\n",argv[i]);
        return 0;
    }else{
    printf("file '%s' don't have problems\n",argv[i]);
    ent_file_creator(first_ent_list,return_ent_file_name(argv[i]));
    ext_file_creator(first_ext_list,return_ext_file_name(argv[i]));
    ob_file_creator(first_field_analyze,return_ob_file_name(argv[i]));
    }
    freeAll(first_line,head_label,first_field_analyze,first_ent_list,first_ext_list);
    /*printf("after freeing\n");*/
    remove("DC.txt");
    printf("finish file '%s'\n",argv[i]);
    }
    printf("end of the program\n");
    return 0;
}
