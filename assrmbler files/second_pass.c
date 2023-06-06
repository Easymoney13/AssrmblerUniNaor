#include "second_pass.h"
#include "analyze_str.h"
#include "first_pass.h"
#include "store.h"
#include "line_read.h"
void where_ext_found(ext_list* ext_node, field_analyze* first_field){
	int number = 0;
	field_analyze* curr_field = (field_analyze*)malloc(2*sizeof(field_analyze));
	curr_field = first_field;
	
	ext_node->found_places = (int*)malloc(number*sizeof(int));
	while(curr_field != NULL){
		if(strcmp(curr_field->name,ext_node->name) == 0){
			/*printf("%s :found ext shit in %d\n",ext_node->name,curr_field->address);*/
			number++;
			ext_node->found_places = (int*)realloc(ext_node->found_places,number*sizeof(int));
			(ext_node->found_places)[number-1] = curr_field->address;
		}
		curr_field = curr_field->next;
	}
}
void second_pass(line* line1,label* l1,ent_list* ent_head,ext_list* ext_head,field_analyze* fa_head){
	ent_list* curr_ent = ent_head;
	ext_list* curr_ext = ext_head;
	field_analyze* curr_fa = fa_head;
	int curr_address = 100;
	int start_location,i,j;
	while((line1 = line1->next) != NULL){
		ent_list* new_ent = (ent_list*)malloc(2*sizeof(ent_list));
		/*printf("line %d in while\n",line1->line_number);*/
		if(line1->is_entry == true){
			/*printf("line %d is entry\n",line1->address);*/
			if(line1->has_label == true){
				start_location=2;
			}else start_location =1;
			if(valid_entry_label((line1->separate)[start_location],l1,ext_head) == false){
				printf("invalid entry label\n");
				continue;
			}
			/*printf("line is_entry\n");
			printf("before strcpy\n");*/
			strcpy(new_ent->name,(line1->separate)[start_location]);
			/*printf("after strcpy(entry)\n");*/
			new_ent->add = get_label_address(new_ent->name,l1);
			curr_ent -> next = new_ent;
			curr_ent = curr_ent -> next;
		}else if(line1->is_extern == true){
			ext_list* new_ext = (ext_list*)malloc(2*sizeof(ext_list));
			/*printf("line is_extern\n");*/
			if(line1->has_label == true){
				start_location=2;
			}else start_location =1;
			if(valid_extern_label((line1->separate)[start_location],l1,ent_head) == false){
				printf("invalid extern label\n");
				continue;
			}
			/*printf("%s\n",(line1->separate)[start_location]);
			printf("%s\n",curr_ext->name);*/
			strcpy(new_ext->name,(line1->separate)[start_location]);
			curr_ext -> next = new_ext;
			curr_ext = curr_ext -> next;
		}else if(line1->is_string == true){
			/*printf("line is_string\n");*/
				if(line1->has_label == true) start_location = 2;/*in which word we have the "data"*/
				else start_location = 1;
				/*printf("%s\n",(line1->separate)[start_location]);*/
					if(is_opp_string((line1->separate)[start_location]) == true){
						/*printf("opp is string pass\n");*/
						for(i=1;i<strlen((line1->separate)[start_location]);i++){
							/*printf("%c\n",(line1->separate)[start_location][i]);*/
							if(i == strlen((line1->separate)[start_location])-1){/*the last char in string should be '/0'*/
			
							field_analyze* field1 = (field_analyze*)malloc(2*sizeof(field_analyze));
							strcpy(field1->name,"0");
							field1->flag = valuef;
							field1->vf.value = 0;
							field1->address = curr_address;
							curr_address++;
							curr_fa->next = field1;/*connect between the curr prev fa to the new one*/
							curr_fa = field1;
							break;
							}else{
							field_analyze* field1 = (field_analyze*)malloc(2*sizeof(field_analyze));
							/*printf("the let value: %d\n",(line1->separate)[start_location][i]);*/
							field1->flag = valuef;/*raise the flag which tell us what bf we use */
							field1->vf.value = ((line1->separate)[start_location])[i];/*assign to the bitfield to the char value*/
							field1->address = curr_address;
							curr_address++;
							curr_fa->next = field1;/*connect between the curr_fa prev fa to the new one*/
							curr_fa = field1;
							}
						}/*for*/
					}/*if*/else{
						printf("line %d: opperand should be string but it's not\n",line1->line_number);
					}
		}/*else if*/
		else if(line1->is_data == true){
			/*printf("line is data\n");*/
			if(line1->has_label == true) start_location = 2;/*in which word we have the "data"*/
			else start_location = 1;
			for(i=start_location ;i<=((line1->word_num)-1);i++){/*going over the opp in the line*/
				/*printf("%s\n",(line1->separate)[i]);*/
				if(atoi((line1->separate)[i]) == 0 && strcmp((line1->separate)[i],"0")!=0){/*this is not a valid number*/
					printf("line %d: one of the opperands is not a number\n",line1->line_number);/*****************************************/
					line1->have_problem = true;
					break;
				}else{
					field_analyze* field1 = (field_analyze*)malloc(2*sizeof(field_analyze));
					field1->flag = valuef;
					field1->address = curr_address;
					curr_address++;
					strcpy(field1->name,(line1->separate)[i]);
					field1->vf.value = atoi((line1->separate)[i]);
					curr_fa->next = field1;/*connect between the curr_fa prev fa to the new one*/
					curr_fa = field1;
				}/*else*/
			}/*for*/
		}else if(line1->is_struct == true){
			/*printf("line is struct\n");*/
			if(line1->has_label == true) start_location = 2;/*in which word we have the "data"*/
			else start_location = 1;
			for(i=start_location;i < start_location+2;i++){
				/*printf("%s\n",(line1->separate)[i]);*/
				if(is_opp_int((line1->separate)[i]) == true){/*this opperand is a number*/
					field_analyze* field1 = (field_analyze*)malloc(2*sizeof(field_analyze));
					/*printf("opp is int :%d\n",atoi((line1->separate)[i]));*/
					field1->flag = valuef;
					field1->vf.value = atoi((line1->separate)[i]);
					/*printf("%d\n",field1->vf.value);*/
					field1->address = curr_address;
					curr_address++;
					curr_fa->next = field1;/*connect between the curr_fa prev fa to the new one*/
					curr_fa = field1;
				}/*if*/
				else if(is_opp_string((line1->separate)[i]) == true){
					/*printf("opp is string\n");*/
					for(j=1;i<strlen((line1->separate)[i]);j++){/*going on the string*/
					/*printf("%c\n",(line1->separate)[i][j]);*/
					if(j == strlen((line1->separate)[i])-1){/*the last char in string should be '/0'*/
						field_analyze* field1 = (field_analyze*)malloc(2*sizeof(field_analyze));
						/*printf("last char in str\n");*/
						field1->flag = valuef;
						field1->vf.value = 0;
						field1->address = curr_address;
						curr_address++;
						curr_fa->next = field1;/*connect between the curr_fa prev fa to the new one*/
						curr_fa = field1;
						break;
						}else{
						field_analyze* field1 = (field_analyze*)malloc(2*sizeof(field_analyze));
						field1->flag = valuef;/*raise the flag which tell us what bf we use */
						field1->vf.value = ((line1->separate)[i])[j];/*assign to the bitfield to the char value*/
						field1->address = curr_address;
						curr_address++;
						curr_fa->next = field1;/*connect between the curr_fa prev fa to the new one*/
						curr_fa = field1;
						}
						}/*for*/
				}else{
					printf("line %d: unknown opperand\n",line1->line_number);
					line1->have_problem = true;
				}/*line 88*/
			}/*for*/
		}/*else if*/
		else if(line1->is_instruct == true ){
			field_analyze* field1 = (field_analyze*)malloc(2*sizeof(field_analyze));
			/*printf("line %d :: is instruct\n",line1->line_number);*/
			if(line1->has_label == true) start_location = 1;/*in which word we have the "data"*/
			else start_location = 0;
			/*printf("before new field\n");
			printf("after new field");*/
			field1->flag = lineF;
			/*printf("before check address\n");*/
			check_address(line1,l1,1);
			/*printf("between check address\n");*/
			check_address(line1,l1,2);
			/*printf("before line_valid check\n");
			printf("addressing before: %d\n",get_first_opp_method(line1));
			printf("addressing before: %d\n",get_second_opp_method(line1));*/
			if((line1->is_First_Operand_access_struct==true||line1->is_First_Operand_Direct==true||
			line1->is_First_Operand_Immediate==true||line1->is_First_Operand_Register_Direct ==true)&&
			line1->is_Second_Operand_Empty == true){
				swap_first_second_types(line1);
			}
			/*printf("second opperand direct: %d\n",line1->is_Second_Operand_Direct);*/
			if(is_line_valid(get_op_number((line1->separate)[start_location]),get_first_opp_method(line1),get_second_opp_method(line1))){
				/*printf("line is valid\n");*/
				field1->line_f.opcode = get_op_number((line1->separate)[start_location]);/*need to check if it's a valid function name*/
				field1->line_f.source = get_first_opp_method(line1);
				field1->line_f.dest = get_second_opp_method(line1);
				field1->line_f.ARE = 0;
				/*printf("now address1: %d\n",curr_address);*/
				field1->address = curr_address;
				curr_address++;
				curr_fa->next = field1;/*connect between the curr_fa prev fa to the new one*/
				curr_fa = field1;
			}else {
				printf(", invalid line %d\n",line1->line_number);
				line1->have_problem = true;
				continue;
			}
			/*printf("pass method addrsing\n");*/
			if(line1->is_First_Operand_Immediate == true){/*method 0*/
				field_analyze* field2 = (field_analyze*)malloc(2*sizeof(field_analyze));
				/*printf("First_Operand_Immediate\n");
				printf("after malloc");*/
				field2->flag = numberF;
				field2->address = curr_address;
				field2->number_f.ARE = 0;
				/*printf("%d\n",get_number((line1->separate)[start_location+1]));*/
				field2->number_f.num = get_number((line1->separate)[++start_location]);
				curr_address++;
				curr_fa->next = field2;/*connect between the curr_fa prev fa to the new one*/
				curr_fa = field2;
			}
			else if(line1->is_First_Operand_Direct == true){/*method 1*/
				field_analyze* field2 = (field_analyze*)malloc(2*sizeof(field_analyze));
				int label_add;
				/*printf("First_Operand_Direct\n");*/
				field2->flag = labelF;
				/*printf("//////////////////////////////////////here//////////////////////////////\n");*/
				label_add = get_label_address((line1->separate)[++start_location],l1);
				/*printf("%s\n",(line1->separate)[start_location]);*/
				strcpy(field2->name,(line1->separate)[start_location]);/*initilze the name of the label*/
				field2->label_f.address = label_add;
				/*printf("%d\n",label_add);*/
				field2->address = curr_address;
				if(label_add != 0)
					field2->label_f.ARE = relocatable;
				else
					field2->label_f.ARE = external;
				curr_address++;
				curr_fa->next = field2;/*connect between the curr_fa prev fa to the new one*/
				curr_fa = field2;
			}
			else if(line1->is_First_Operand_access_struct == true){/*method 2*/
				field_analyze* field2 = (field_analyze*)malloc(2*sizeof(field_analyze));
				field_analyze* field3;
				char* token;
				int label_address;
				/*printf("First_Operand_access_struct\n");
				printf("after malloc\n");*/
				field2->flag = labelF;
				field2->address = curr_address;
				/*printf("before strtok(first_operand_access_struct)\n");*/
				token = strtok((line1->separate)[++start_location],".");
				/*printf("after strtok(first_operand_access_struct)\n");
				puts(token);*/
				strcpy(field2->name,token);
				label_address = get_label_address(token,l1);
				/*printf("%d\n",label_address);*/
				field2->label_f.address = label_address;
				/*printf("after label addersing\n");*/
				if(label_address != 0){
					field2->label_f.ARE = relocatable;
					/*printf("label isn't external\n");*/
				}else
					field2->label_f.ARE = external;
				curr_address++;
				curr_fa->next = field2;/*connect between the curr_fa prev fa to the new one*/
				curr_fa = field2;

				token = strtok(NULL,".");
				/*printf("second token: %s\n",token);*/
				field3 = (field_analyze*)malloc(2*sizeof(field_analyze));
				field3->address = curr_address;
				field3->flag = numberF;
				field3->number_f.ARE = absolute;
				/*printf("%d\n",atoi(token));*/
				field3->number_f.num = atoi(token);
				curr_address++;
				curr_fa->next = field3;/*connect between the curr_fa prev fa to the new one*/
				curr_fa = field3;
			}
			else if(line1->is_First_Operand_Register_Direct == true && line1->is_Second_Operand_Register_Direct == true){
				field_analyze* field2 = (field_analyze*)malloc(2*sizeof(field_analyze));
				/*printf("both opp is rgisters\n");*/
				field2->flag = rgF;
				field2->rg_field.ARE = absolute;
				field2->rg_field.source_num = get_rg_number((line1->separate)[++start_location]);
				field2->rg_field.dest_num = get_rg_number((line1->separate)[++start_location]);
				field2->address = curr_address;
				curr_address++;
				curr_fa->next = field2;/*connect between the curr_fa prev fa to the new one*/
				curr_fa = field2;
				continue;
			}
			else if(line1->is_First_Operand_Register_Direct == true){/*method 3*/
				field_analyze* field2 = (field_analyze*)malloc(2*sizeof(field_analyze));
				/*printf("First_Operand_Register_Direct\n");*/
				field2->flag = rgF;
				field2->rg_field.ARE = absolute;
				field2->rg_field.source_num = get_rg_number((line1->separate)[++start_location]);
				field2->rg_field.dest_num = 0;
				field2->address = curr_address;
				curr_address++;
				curr_fa->next = field2;/*connect between the curr_fa prev fa to the new one*/
				curr_fa = field2;
			}else{}
			if(line1->is_Second_Operand_Immediate == true){/*method 0*/
				field_analyze* field2 = (field_analyze*)malloc(2*sizeof(field_analyze));
				/*printf("second operand is immidiate\n");*/
				field2->flag = numberF;
				field2->number_f.ARE = 0;
				field2->number_f.num = get_number((line1->separate)[++start_location]);
				field2->address = curr_address;
				curr_address++;
				curr_fa->next = field2;/*connect between the curr_fa prev fa to the new one*/
				curr_fa = field2;
			}
			else if(line1->is_Second_Operand_Direct == true){/*method 1*/
				char label_name[30];
				int label_add;
				field_analyze* field2 = (field_analyze*)malloc(2*sizeof(field_analyze));
				/*printf("second operand direct\n");*/
				strcpy(label_name,(line1->separate)[++start_location]);
				/*printf("%s\n",label_name);*/
				label_add = get_label_address((label_name),l1);
				/*printf("%d\n",label_add);*/
				field2->flag = labelF;
				field2->address = curr_address;
				strcpy(field2->name,label_name);
				field2->label_f.address = label_add;
				if(label_add != 0)
					field2->label_f.ARE = relocatable;
				else
					field2->label_f.ARE = external;
				curr_address++;
				curr_fa->next = field2;/*connect between the curr_fa prev fa to the new one*/
				curr_fa = field2;
			}
			else if(line1->is_Second_Operand_access_struct == true){/*method 2*/
				field_analyze* field2 = (field_analyze*)malloc(2*sizeof(field_analyze));
				field_analyze* field3;
				char* token;
				/*printf("second operand access_struct");*/
				field2->flag = labelF;
				token = strtok((line1->separate)[++start_location],".");
				strcpy(field2->name,token);
				field2->label_f.address = get_label_address(token,l1);
				if(get_label_address(token,l1) != 0)
					field2->label_f.ARE = relocatable;
				else
					field2->label_f.ARE = external;
				curr_address++;
				curr_fa->next = field2;/*connect between the curr_fa prev fa to the new one*/
				curr_fa = field2;

				token = strtok(NULL,".");
				field3 = (field_analyze*)malloc(2*sizeof(field_analyze));
				field3->flag = numberF;
				field3->number_f.ARE = absolute;
				field3->number_f.num = atoi(token);
				curr_address++;
				curr_fa->next = field3;/*connect between the curr_fa prev fa to the new one*/
				curr_fa = field3;
			}
			else if(line1->is_Second_Operand_Register_Direct == true){/*method 3*/
				field_analyze* field2 = (field_analyze*)malloc(2*sizeof(field_analyze));
				/*printf("second operand rigister\n");*/
				field2->flag = rgF;
				field2->rg_field.ARE = absolute;
				field2->rg_field.dest_num = get_rg_number((line1->separate)[++start_location]);
				field2->rg_field.source_num = 0;
				field2->address = curr_address;
				curr_address++;
				curr_fa->next = field2;/*connect between the curr_fa prev fa to the new one*/
				curr_fa = field2;
			}else{}

		}else{
			/*printf("line isn't nothing\n");*/
			}/*else if(is_insturct)*/
	}/*while*/

}/*function*/
bool is_word_label(char* str,label* l1){
	label* lptr = l1;
	while(lptr!=NULL){
		if(strcmp(str,lptr->name) == 0)/*compare between the curr label to the string*/
			return true;
		lptr = lptr ->next;
	}
	return false;
}
bool is_label_part(char* str,label* l1){
	label* lptr = l1;
	remove_last_char(str);
	while(lptr!=NULL){
		if(strcmp(str,lptr->name) == 0)
			return true;
		lptr = lptr ->next;
	}
	return false;
}
word_type analyze_word(char* str,label* l1){
	char* word_part = str_tok(str,'.');
	/*printf("1st line(analyze_word)\n");
	printf("%s\n",word_part);*/
	if(strcmp(str,"r0") == 0 || strcmp(str,"r1")== 0 ||strcmp(str,"r2")== 0 ||strcmp(str,"r3")== 0 ||strcmp(str,"r4")== 0 ||strcmp(str,"r5")== 0 ||strcmp(str,"r6")== 0 ||strcmp(str,"r7")== 0)
		return rg_type;/*method 3*/
	else if(strcmp(str,"mov")== 0||strcmp(str,"cmp")== 0||strcmp(str,"add")== 0||strcmp(str,"sub")== 0||strcmp(str,"not")== 0||strcmp(str,"clr")== 0||strcmp(str,"lea")== 0||strcmp(str,"inc")== 0||strcmp(str,"dec")== 0||strcmp(str,"bne")== 0||strcmp(str,"get")== 0||strcmp(str,"prn")== 0||strcmp(str,"rts")== 0||strcmp(str,"hlt")== 0)
		return opcode_type;
	else if(str[0] == '#' && atoi(str+1)!=0)
		return numbers;/*method 0*/
	else if(is_label_part(word_part,l1) == true && (strcmp(cutString(str,strlen(word_part),strlen(str)),"1")||strcmp(cutString(str,strlen(word_part),strlen(str)),"2")))
		return struct_t;/*method 2*/
	else if(is_word_label(str,l1) == true)
		return label_type;/*method 1*/
	else
		return error;
}
rigistrs get_rg_number(char* str){
	if(strcmp(str,"r0")== 0)return r0;
	if(strcmp(str,"r1")== 0)return r1;
	if(strcmp(str,"r2")== 0)return r2;
	if(strcmp(str,"r3")== 0)return r3;
	if(strcmp(str,"r4")== 0)return r4;
	if(strcmp(str,"r5")== 0)return r5;
	if(strcmp(str,"r6")== 0)return r6;
	if(strcmp(str,"r7")== 0)return r7;
	else return error_rg;
}
opcode_func get_op_number(char* str){
	/*printf("oppcode string: %s\n",str);*/
	if(strcmp(str,"mov") == 0) return mov;
	if(strcmp(str,"cmp") == 0) return cmp;
	if(strcmp(str,"add") == 0) return add;
	if(strcmp(str,"sub") == 0) return sub;
	if(strcmp(str,"not") == 0) return not;
	if(strcmp(str,"clr") == 0) return clr;
	if(strcmp(str,"lea") == 0) return lea;
	if(strcmp(str,"inc") == 0) return inc;
	if(strcmp(str,"dec") == 0) return dec;
	if(strcmp(str,"jmp") == 0) return jmp;
	if(strcmp(str,"bne") == 0) return bne;
	if(strcmp(str,"get") == 0) return get;
	if(strcmp(str,"prn") == 0) return prn;
	if(strcmp(str,"rts") == 0) return rts;
	if(strcmp(str,"hlt") == 0) return hlt;
	else{return error_op;}
}
void check_address(line *line1,label* first_label,int opperand_num){
	int analyze_1_number;
	char *str;
	if(line1->has_label == true) 
		str = (line1 -> separate)[opperand_num+1];/*first opperand*/
	else 
		str = (line1 -> separate)[opperand_num];
	if(opperand_num==1){
/*	printf("num is 1(check address)\n");
	puts(str);*/
	analyze_1_number = analyze_word(str,first_label);
	if(strcmp(str,"") == 0){
		/*printf("empty opperand 1\n");*/
		line1->is_First_Operand_Empty = true;
	}else if(str_start_hash(str) == true && str_is_number(str) == true){/*checks if opp starts with # and is number -> first_opp_immediate*/
		/*printf("operand immediate\n");*/
		line1->is_First_Operand_Immediate = true;/*number 0*/
	}else if(analyze_1_number ==rg_type){/*checks if opp is register -> first_opp_register*/
		/*printf("Operand_Register\n");*/
		line1->is_First_Operand_Register_Direct = true;/*number 3*/
	}else if(analyze_1_number == label_type){
		/*printf("Operand_direct\n");*/
		line1->is_First_Operand_Direct = true;
	}else if(analyze_1_number == struct_t){
		/*printf("operand acess struct\n");*/
		line1->is_First_Operand_access_struct = true;
	}else{
	printf("line %d: ERROR, please enter a valid first parameter", line1->line_number);
	line1->have_problem = true;
	}
	}else if(opperand_num==2){
		int analyze_2_number;
		/*printf("num is 2(check address)\n");
		puts(str);
		// printf("after puts\n");*/
		analyze_2_number = analyze_word(str,first_label);
		if(strcmp(str,"") == 0){
			/*printf("empty operand 2\n");*/
			line1->is_Second_Operand_Empty = true;
		}else if(str_start_hash(str) == true && str_is_number(str) == true){/*checks if opp starts with # and is number -> first_opp_immediate*/
			/*printf("operand immediate\n");*/
			line1->is_Second_Operand_Immediate = true;/*number 0*/
		}else if(analyze_2_number ==rg_type){/*checks if opp is register -> first_opp_register*/
			/*printf("operand Operand_Register_Direct\n");*/
			line1->is_Second_Operand_Register_Direct = true;/*number 3*/
		}else if(analyze_2_number == label_type){
			/*printf("Operand_Direct\n");*/
			line1->is_Second_Operand_Direct = true;
		}else if(analyze_2_number == struct_t){
			/*printf("Operand_access_struct\n");*/
			line1->is_Second_Operand_access_struct = true;
		}else{
			printf("line %d:Error, please enter a valid second parameter", line1->line_number);
			line1->have_problem= true;
		}
	}
}
add_method get_first_opp_method(line* lptr){
	if((lptr -> is_First_Operand_Immediate) == true)
		return immediate;
	else if((lptr -> is_First_Operand_Direct) == true)
		return direct;
	else if((lptr -> is_First_Operand_access_struct) == true)
		return access_struct;
	else if((lptr -> is_First_Operand_Register_Direct) == true)
		return register_direct;
	else if((lptr->is_First_Operand_Empty) == true)
		return empty;
	else
		return error_add_method;
}
add_method get_second_opp_method(line* lptr){
	if((lptr -> is_Second_Operand_Immediate) == true)
		return immediate;
	else if((lptr -> is_Second_Operand_Direct) == true)
		return direct;
	else if((lptr -> is_Second_Operand_access_struct) == true)
		return access_struct;
	else if((lptr -> is_Second_Operand_Register_Direct) == true)
		return register_direct;
	else if((lptr ->is_Second_Operand_Empty) == true)
		return empty;
	else
		return error_add_method;
}
void swap_first_second_types(line* l1){
	if(l1->is_First_Operand_access_struct == true){
		/*printf("it's here 1\n");*/
		l1->is_Second_Operand_access_struct = true;
		l1->is_Second_Operand_Empty = false;
		l1->is_First_Operand_access_struct = false;
		l1->is_First_Operand_Empty = true;
	}else if(l1->is_First_Operand_Direct == true){
		/*printf("it's here 2\n");*/
		l1->is_Second_Operand_Direct = true;
		l1->is_Second_Operand_Empty = false;
		l1->is_First_Operand_Direct = false;
		l1->is_First_Operand_Empty = true;
	}else if(l1->is_First_Operand_Immediate == true){
		/*printf("it's here 3\n");*/
		l1->is_Second_Operand_Immediate = true;
		l1->is_Second_Operand_Empty = false;
		l1->is_First_Operand_Immediate = false;
		l1->is_First_Operand_Empty = true;
	}else if(l1->is_First_Operand_Register_Direct == true){
		/*printf("it's here 4\n");*/
		l1->is_Second_Operand_Register_Direct = true;
		l1->is_Second_Operand_Empty = false;
		l1->is_First_Operand_Register_Direct = false;
		l1->is_First_Operand_Empty = true;
	}
}
bool is_line_valid(opcode_func of1,add_method am1,add_method am2){
	/*printf("instruct name: %d\n",of1);
	printf("addressing: %d\n",am1);
	printf("addressing: %d\n",am2);*/
	if(of1 ==mov&&(am1==0 || am1==1 || am1==2 || am1==3)&&(am2==1||am2==2||am2==3))
		return true;
	else if(of1==cmp&&(am1==0||am1==1||am1==2||am1==3)&&(am2==0||am2==1||am2==2||am2==3))
		return true;
	else if((of1==add ||of1==sub)&&(am1==0||am1==1||am1==2||am1==3)&&(am2==1||am2==2||am2==3))
		return true;
	else if((of1==not||of1==clr||of1==inc||of1==dec||of1==jmp||of1==bne||of1==get||of1==jsr) &&(am1==4)&&(am2==1||am2==2||am2==3))
		return true;
	else if(of1==prn&&(am1==4)&&(am2==0||am2==1||am2==2||am2==3))
		return true;
	else if(of1==lea &&(am1==1 ||am1==2)&&(am2==1||am2==2||am2==3))
		return true;
	else if((of1==rts||of1==hlt)&&(am1==4)&&(am2==4))
		return true;
	else
		return false;
}

int get_number(char* str){
	return atoi(str+1);
}
bool is_opp_number(char* str){
	return is_opp_int(str+1) && str[0]=='#';
}

int get_label_address(char* str,label* l1){
	label* lptr;
	/*printf("first line(get_label_address)\n");*/
	lptr = l1;
	while(lptr!=NULL){
		if(strcmp(lptr->name,str) == 0)
			return lptr->add;
		else
			lptr = lptr->next;
	}
	return -1;/*didn't find any matching label*/
}
int get_int(char* str){
	return atoi(str);
}
bool is_opp_int(char* str){
	int i;
	for(i=0;str[i] !='\0';i++){
		if(isdigit(str[i]) == 0)
			return false;
	}
	return true;
}
bool is_opp_string(char* str){
	return first_and_last_same(str) && first_str_char(str) == '"';
}
bool valid_entry_label(char* label_name,label* first_label,ext_list* first_ext){
	label* curr_label = first_label;
	ext_list* curr_ext = first_ext;
	bool in_label_table = false ,in_ext_table = false;
	while(curr_label != NULL){
		if(strcmp(curr_label->name,label_name) == 0){/*found entry label in label table - good*/
			in_label_table = true;
			break;
		}
		curr_label = curr_label->next;
	}
	if(in_label_table == false)
		printf("%s: is entry but not declared in file\n",label_name);
	while(curr_ext != NULL){
		if(strcmp(label_name,curr_ext->name) == 0){/*found entry label in extern's table - bad*/
			in_ext_table = true;
			printf("%s: declared as entry && extern\n",label_name);
			break;
		}
		curr_ext = curr_ext->next;
	}
	return in_label_table && !in_ext_table;
}
bool valid_extern_label(char* label_name,label* first_label,ent_list* first_ent){
	label* curr_label = first_label;
	ent_list* curr_ent = first_ent;
	bool in_label_table = false,in_ent_table = false;
	while(curr_label != NULL){
		if(strcmp(curr_label->name,label_name) == 0 && (curr_label->add != 0)){/*found extern label name in label table - bad*/
			in_label_table = true;
			break;
		}
		curr_label = curr_label->next;		
	}if(in_label_table == true)
		printf("%s: is extern but declared in file\n",label_name);
	while(curr_ent != NULL){
		if(strcmp(label_name,curr_ent->name) == 0){/*found extern label name in entry's table - bad*/
			in_ent_table = true;
			printf("%s: declared as entry && extern\n",label_name);
			break;
		}
		curr_ent = curr_ent->next;
	}
	return !in_label_table && !in_ent_table;
}
