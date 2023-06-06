#include "pre_assembler.h"

char *remove_white_spaces(char *str)
{
    int i = 0, j = 0;
    while (str[i])
    {
        if (str[i] != ' ')
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    return str;
}

void preAssembler(char* file_name)
{/*x --> x.as*/

            FILE *fpam, *fpas;/*new and original files*/
            char name_am[maxFileName+10]="";/*name storers for each file*/
            char name_as[maxFileName+10]="";
            macro_node *head = malloc(sizeof(macro_node));
            head->macro_name ="none";
            head->macro_name = "none";
            head->next = NULL;
            strcpy(name_am,file_name);
            strcpy(name_as,file_name);
            strcat(name_am,endingAmFile);
            strcat(name_as,endingAsFile);
            fpam = fopen(name_am,"w+");/*opening files*/
            fpas = fopen(name_as,"r");
            if(fpas == NULL || fpam == NULL){
                printf("File didn't open: %s\n",file_name);
                exit(-1);
            }/*if*/
            make_am_file(fpas,fpam,head);
        /*for*/
    /*else*/
}

FILE *make_am_file(FILE *og_file, FILE *new_file, macro_node *node){
    char line[maxLineLen];
    char tmp_line[maxLineLen];
    char line_cpy[maxLineLen];
    char *token;
    char s[2] = " ";
    char n[2] = "\n";
    while(!feof(og_file)){
        char* m_name;
        macro_node *new_node = malloc(sizeof(macro_node));
        macro_node *curr_node = malloc(sizeof(macro_node));
        curr_node=node;
        fgets(line,maxLineLen,og_file);
        strcpy(line_cpy,line);
        token = strtok(line_cpy, s);
        /*puts(token);*/
        while(strcmp(token,s) == 0){
            /*find first word if there is space before*/
            token = strtok(NULL,s);
        }/*skip space while*/
        strcpy(tmp_line,line);/*preparing second word on the list for macro name*/
        if(tmp_line[strlen(tmp_line)-1] != '\n'){
            strcat(tmp_line,"\n");
        }
        if((is_macro(node,tmp_line))){
            fprintf(new_file,(is_macro(node,tmp_line)->all_macro_data));/*print macro data*/
            continue;
        }/*if*/
        if(strcmp(token,"macro") == 0){/*check if declaration of macro*/
            strcpy(new_node->all_macro_data,"");
            new_node->macro_name = (char*)malloc(sizeof(char)*max_word_len);
            m_name = strtok(NULL,n);
            m_name = strcat(m_name,"\n");
            strcpy(new_node->macro_name,remove_white_spaces(m_name)); /*copy macro name*/
            fgets(line,maxLineLen,og_file);
            while(strcmp(line,"endmacro\n") != 0 && !feof(og_file)){/*copy macro data*/
                strcat(new_node->all_macro_data,line);
                fgets(line,maxLineLen,og_file);
            }/*while*/


            /*connect to the list*/
            while(curr_node->next != NULL)/*finding the current node*/
                curr_node = curr_node->next;
            curr_node->next = new_node;/*connecting to the list*/
            continue;
        }/*if*/
        else{
            fprintf(new_file,line);
        }
    }/*while*/
    fclose(og_file);
    fclose(new_file);
    return new_file;
}

macro_node* is_macro(macro_node* head, char* str){/*checks if str is existing macro name*/
    char *new_str = (char*)malloc(strlen(str)+2);
    macro_node* curr = (macro_node*)malloc(sizeof(macro_node));
    curr = head;
    strcpy(new_str,str);
    for(;curr != NULL; curr = curr->next){
        if(strcmp(new_str,curr->macro_name) == 0){
            return curr;
        }
    }
    return NULL;
}
