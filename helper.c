#include "helper.h"

void is_successfull_malloc(void *pointer)
{
    if (pointer == NULL){
        printf("malloc field\n");
		exit(-1);
	}
}
char* return_ob_file_name(char* name){
	char* new_name = (char*)malloc(strlen(name)+4);
	strcpy(new_name,name);
	strcat(new_name,endingOBFile);
	return new_name;
}
char* return_ent_file_name(char* name){
	char* new_name = (char*)malloc(strlen(name)+5);
	strcpy(new_name,name);
	strcat(new_name,endingENTFile);
	return new_name;
}
char* return_ext_file_name(char* name){
	char* new_name = (char*)malloc(strlen(name)+5);
	strcpy(new_name,name);
	strcat(new_name,endingEXTFile);
	return new_name;
}