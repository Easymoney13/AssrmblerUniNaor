#include "line_read.h"
#include "store.h"
#include "analyze_str.h"
#include "second_pass.h"

int howManyBf(line*);

/*create new line and add it to the list*/
line* add_line(char* str,line* curr,line* head){
    /*int i;*/
    line* new_line = (line*)malloc(sizeof(line));
    static int line_num = 1;/*giving each line a line_number*/
    deff_values(new_line);
    if(curr==NULL){
        head = new_line;/*removed & from new_line*/
        curr = new_line;/*removes & from new_line*/
        values_initializer(new_line,str,100);
    }
    else
    {
        curr->next = new_line;
        values_initializer(new_line,str,curr->address + curr->bfNum);
        curr = new_line;
    }
    /*printf("end\n");
    for(i=0;i<curr->word_num;i++){
        printf("%s\t",(curr->separate)[i]);
    }*/
    new_line->bfNum = howManyBf(new_line);
    new_line->line_number = line_num;
    line_num++;
    return new_line;
}
/*initialize the line struct values
  address , is_label , full_line , word_num , is_ingnore,
*/
void values_initializer(line* l1,char* str,int add){
    l1->address = add;
    strcpy((l1->full_line),str);/*copying all the line data to the data structure*/
    seperate_array_creator(l1);/*create the seperate word array*/
    line_type(l1);/*decide which line types the new line is*/
    if(l1->is_comment==true || l1->is_empty==true || l1->is_unknown==true)
        l1->is_ignore = true;    
}

int count_words(line* l1){
    int rows = how_many_rows(l1->separate);
    /*printf("rows = %d\n",rows);*/
    if(l1->has_label){
        rows--;
    }
    return rows;
}
void line_type(line* l1){
    int i;
    int opcode_times = 0;
    /*printf("/////////////////////////1st line(line_type)/////////////////////////////\n");*/
    if(str_only_white_spaces(l1->full_line)){
        l1->is_empty =true;
        return;
    }
    else if((l1->separate[0][0]) == ';'){
        l1->is_comment = true;
        return;
    }
    else
    {
        /*printf("in the else one(line_type)\n");*/
        for(i=0;i<2;i++)
        {
            if(strcmp(l1->separate[i],".data") == 0){
                /*printf("////////////////////////line is data/////////////////////////////\n");
                printf("word: %s\n",l1->separate[i]);*/
                l1->is_data = true;
                l1->is_guidance = true;
            }
            else if(strcmp(l1->separate[i],".string") == 0){
                /*printf("////////////////////////line is string/////////////////////////////\n");
                printf("word: %s\n",l1->separate[i]);*/
                l1->is_string = true;
                l1->is_guidance = true;
            }
            else if(strcmp(l1->separate[i],".struct") == 0){
                /*printf("////////////////////////line is struct/////////////////////////////\n");
                printf("word: %s\n",l1->separate[i]);*/
                l1->is_struct = true;
                l1->is_guidance = true;
            }
            else if(strcmp(l1->separate[i],".entry") == 0){
                /*printf("////////////////////////line is entry/////////////////////////////\n");
                printf("word: %s\n",l1->separate[i]);*/
                l1->is_entry = true;
                l1->is_guidance = true;
            }
            else if(strcmp(l1->separate[i],".extern") == 0){
                /*printf("////////////////////////line is extern/////////////////////////////\n");
                printf("word: %s\n",l1->separate[i]);*/
                l1->is_extern = true;
                l1->is_guidance = true;
            }
	        else if(strcmp(l1->separate[i],"mov")== 0||strcmp(l1->separate[i],"cmp")== 0||strcmp(l1->separate[i],"add")== 0||strcmp(l1->separate[i],"sub")== 0||strcmp(l1->separate[i],"not")== 0||strcmp(l1->separate[i],"clr")== 0||strcmp(l1->separate[i],"lea")== 0||strcmp(l1->separate[i],"inc")== 0||strcmp(l1->separate[i],"jmp")== 0||strcmp(l1->separate[i],"dec")== 0||strcmp(l1->separate[i],"bne")== 0||strcmp(l1->separate[i],"get")== 0||strcmp(l1->separate[i],"prn")== 0||strcmp(l1->separate[i],"rts")== 0||strcmp(l1->separate[i],"hlt")== 0){
		        /*printf("////////////////////////line is instruct/////////////////////////////\n");*/
                opcode_times++;
                /*printf("word: %s\n",l1->separate[i]);*/
                l1->is_instruct = true;
            }
        }/*for loop*/
        /*printf("before the long long if\n");*/
        if((l1->is_guidance&&l1->is_instruct)||
        (l1->is_entry&&(l1->is_extern||l1->is_string||l1->is_data||l1->is_struct))||
        ((l1->is_string)&&(l1->is_extern||l1->is_struct||l1->is_data))||
        ((l1->is_data)&&(l1->is_extern||l1->is_struct))||
        (((l1->is_struct)&&l1->is_extern )|| opcode_times ==2)){
            printf("line %d :line types incompatible\n",l1->line_number);
            l1->have_problem = true;
        }
        /*printf("after the long long if\n");*/
    }/*else*/
}
void seperate_array_creator(line* l1){
    char line_data[maxLineLen];
    int separate_times,j;/*how many times we check the "space"*/
    char s[2]=" ";/*s is space*/
    /*char token[max_word_len] = "";*/
    char* token;
    strcpy(line_data,l1->full_line);
    token = strtok(line_data,s);
    while(strcmp(token,s) == 0){
        /*This makes sure that even if the first word has spaces before, it will get to the first word*/
        token = strtok(NULL,s);
    }/*while*/
    if(last_str_char(token) == ':'){/*checks if words is label*/
        l1->has_label = true;
        separate_times = 2;/*The amount of space checking depends on the label*/
    }else
        separate_times=1;
    strcpy((l1->separate)[0],token);/*putting the first word into the separate array: either label or opcode/guidance*/
    l1->word_num++;
    for(j=1;j<=separate_times;j++)
    {
        if(j==separate_times){/*checks if we reached the parameters*/
            token = strtok(NULL,"\n");/*token will be the parameters*/
            divide_parameters(l1,token,j);
            break;
        }
        do{/*skip all the spaces until the string is not empty*/
            token = strtok(NULL,s);
        }while(strcmp(token,s) == 0);
        l1->word_num++;
        strcpy((l1->separate)[j],token);/*putting the rest of the words into the array*/
    }/*for*/
}

void divide_parameters(line *l1,char* full_param,int j) {
    char param_after_clean[maxLineLen];
    const char s[2] = ",";
    char *token;
    if(full_param ==NULL)
        return;
    strcpy(param_after_clean, remove_white_spaces(remove_new_lines(full_param)));
    
    token = strtok(param_after_clean, s);
    if (token == NULL){/*we dont have ','*/
        if(param_after_clean[0] == '\0')/*have no params*/
            return;
        else{/*have one param*/
            strcpy(((l1->separate)[j]), param_after_clean);
            l1->word_num++;
            j++;
            return;
	    }
    }
        while (token != NULL) {
            l1->word_num++;
              strcpy(((l1->separate)[j]), token);
              j++;
              token = strtok(NULL, s);
            }
}
int howManyBf(line* line1){
    int times = line1->word_num;
    int first_opp_index = 1;
    char* operand_copy = (char*)malloc(max_word_len);
    char* token;
    if(line1->is_empty == true || line1->is_comment == true ||line1->is_entry ==true || line1->is_extern){
        times = 0;/*there are 0 bitfields needed to that line*/
        return times;
    }
    if(line1->is_guidance == true){
        times--;
    }
    if(line1->has_label == true){
        times--;
        first_opp_index = 2;
    }
    if(get_rg_number((line1->separate)[first_opp_index]) != error_rg && get_rg_number((line1->separate)[first_opp_index+1]) != error_rg)
        {
            times--;
        }
    if(str_only_white_spaces((line1->separate)[first_opp_index]) != true){
        strcpy(operand_copy,(line1->separate)[first_opp_index]);
        token = strtok(operand_copy,".");
        if(strcmp(token,(line1->separate)[first_opp_index]) != 0){
            token = strtok(NULL,".");
            if(strcmp(token,"1") == 0 || strcmp(token,"2") == 0){
                times++;
            }
        }
    }
    /*printf("%s\n",(line1->separate)[first_opp_index+1]);*/
    if(str_only_white_spaces((line1->separate)[first_opp_index+1]) != true){
    strcpy(operand_copy,(line1->separate)[first_opp_index+1]);
    /*printf("%s\n",operand_copy);*/
    token = strtok(operand_copy,".");
    /*printf("%s\n",token);*/
    if(strcmp(token,(line1->separate)[first_opp_index+1]) != 0){/*this means operand is access struct*/
        token = strtok(NULL,".");
        if(strcmp(token,"1") == 0 || strcmp(token,"2") == 0)
            times++;
    }
    }
    if(is_opp_string((line1->separate)[first_opp_index]) == true)
        times += strlen((line1->separate)[first_opp_index]) - 2;/*need bitfield for each char*/
    if(is_opp_string((line1->separate)[first_opp_index+1]) == true)
        times += strlen((line1->separate)[first_opp_index+1]) - 2;/*need bitfield for each char*/
    return times;
}
    void deff_values(line* l1){
        l1->prev = NULL;
        l1->next = NULL;
        l1->address = 100;
        strcpy(l1->full_line,"");
        l1->have_problem = false;
        l1->word_num = 0 ;
        l1->bfNum = 0;
        l1->is_comment = false;
        l1->is_empty = false;
        l1->is_instruct = false;
        l1->is_guidance = false;
        l1->is_ignore = false;
        l1->has_label = false;
        l1->is_data = false;
        l1->is_string = false;
        l1->is_struct = false;
        l1->is_entry = false;
        l1->is_extern = false;
        l1->is_First_Operand_Immediate = false;
        l1->is_First_Operand_Direct = false;
        l1->is_First_Operand_access_struct = false;
        l1->is_First_Operand_Register_Direct = false;
        l1->is_Second_Operand_Immediate = false;
        l1->is_Second_Operand_Direct = false;
        l1->is_Second_Operand_access_struct = false;
        l1->is_Second_Operand_Register_Direct = false;
        l1->is_unknown = false;
    }
    void create_lines_list(line* first,char* name){
        char line_data[maxLineLen];
        FILE* fp;
        line* curr;
        char copy_name[maxFileName];
        strcpy(copy_name,name);
        strcat(copy_name,endingAmFile);/*connect between the name and the ending (.am)*/
        fp = fopen(copy_name,"r");/*open file for reading*/
        if(fp==NULL)
            printf("error\n");
        curr = first;
        do{
            /*if(curr==NULL) printf("curr is null\n");
            else printf("\nnot null\n");*/
            fgets(line_data,maxLineLen,fp);/*read the next line from the file*/
            curr = add_line(line_data,curr,first);/*send to add_line function that new line*/
        }while(!feof(fp));
    }
    void print_line_nodes(line* first){
        int i;
        line* curr_line = (line*)malloc(sizeof(line));
        curr_line = first;
        while(curr_line != NULL){
            for(i=0;i<curr_line->word_num;i++){
                printf("%s\t",(curr_line->separate)[i]);
            }
            printf(" fields :%d\t",curr_line->bfNum);
            printf(" line number: %d\n",curr_line->line_number);
            curr_line = curr_line->next;
        }
    }