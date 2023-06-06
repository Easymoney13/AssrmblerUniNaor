#include "analyze_str.h"
char last_str_char(char* str){
    return str[strlen(str)-1];
}
char first_str_char(char* str) {
    return str[0];
}
void remove_last_char(char* str){
    str[strlen(str)-1] = '\0';
}
bool first_and_last_same(char* str){
	return (last_str_char(str) == first_str_char(str));
}
int char_inside_string(char* str,char ch){
	int i;
	for(i=0;i<strlen(str);i++){
		if(str[i] == ch)
			return i;/*return the index we found the char*/
	}
	return -1;/*didn't find the char in the stinrg*/
}
int how_many_rows(char arr[][max_word_len]){
    char c = 1;
    int i=0;
    while(c != '\0')
    {
        c = arr[i][0];
        i++;
    }
    return i;
}
char *remove_new_lines(char* str){
    int i;
    for(i=0;i< strlen(str);i++){
        if(str[i]=='\n')
            str[i]='\0';
    }
    return str;
}
bool str_only_white_spaces(char* str) {
    int i;
    for (i = 0; i < strlen(str); i++) {
        if (str[i] == ' ' || str[i] == '\n');
        else
            return false;
    }
    return true;
}
    char* cutString(char* str,int start,int end){
    int i,j,size=0;
    char *splt = (char*)malloc(sizeof(char));
    for(i=start,j=0 ; i<=end;i++,j++){
        size++;
        splt = (char*)realloc(splt,size*sizeof(char));
        splt[j] = str[i];
    }
    splt[end-start+1] = '\0';
    return splt;
    }
    char* str_tok(char* str,char ch){
        int end_index = strlen(str)-1,i;
        for(i=0;i<strlen(str);i++){
            if(ch == str[i]){
                end_index = i;
                break;
            }
        }
        return cutString(str,0,end_index);
    }
    bool str_is_number(char* str){
    int i;
    for(i=1;i<strlen(str);i++){
        if(isdigit(str[i]) == 0 && str[i] != '-')
            return false;
    }
    return true;
}
bool str_start_hash(char* str){
    if(str[0] == '#')
        return true;
    else
        return false;
}
