/** @file traceback.c
 *  @brief The traceback function
 *
 *  This file contains the traceback function for the traceback library
 *
 *  @author Harry Q. Bovik (hqbovik)
 *  @bug Unimplented
 */

#include "traceback_internal.h"
#include <signal.h>
#include <setjmp.h>
#include <string.h>

extern void **get_bp();
jmp_buf buff;

void seg_handle(int s){
	longjmp(buff,1);
}

int get_index(void *addr){
	for(int i = 0; i < FUNCTS_MAX_NUM; i++){
		if(functions[i].addr == addr){
			return i;
		}
	}
	return -1;
}

int get_nxt_func(void **bp){
	int i = 0;
	int index;
	void *addr = *(bp+1);
	while(i < MAX_FUNCTION_SIZE_BYTES){
		if((index = get_index(addr-i)) != -1) return index;
		i++;
	}
	return -1;
}

void traceback(FILE *fp)
{

	signal(SIGSEGV, seg_handle);

	void **bp = get_bp();
	int index = -1;

	do{

		index = get_nxt_func(bp);
		if(!strcmp(functions[index].name,"__libc_start_main")){
			printf("__libc_start_main(void) \n");
			return;
		}
		bp = *bp; //Set bp for next function

		if(index == -1){
			printf("Error func no found! \n");
		}

		printf("%s(",functions[index].name);
		int i = 0;
		int argof;

		while(functions[index].args[i].offset != 0){

			argof = functions[index].args[i].offset/4;

			if(!setjmp(buff)){

				switch(functions[index].args[i].type){
					case TYPE_CHAR:
					printf("char %s='%c'",functions[index].args[i].name,*((char*)(bp+argof)));
					break;
					case TYPE_INT:
					printf("int %s=%d",functions[index].args[i].name,*((int*)(bp+argof)));
					break;
					case TYPE_FLOAT:
					printf("float %s=%f",functions[index].args[i].name,*((double*)(bp+argof)));
					break;
					case TYPE_DOUBLE:
					printf("double %s=%f",functions[index].args[i].name,*((double*)(bp+argof)));
					break;
					case TYPE_STRING:
					printf("char *%s='%s'",functions[index].args[i].name,*((char**)(bp+argof)));
					break;
					case TYPE_STRING_ARRAY:
					printf("char **%s=%p",functions[index].args[i].name,*(bp+argof));
					break;
					case TYPE_UNKNOWN:
					printf("unknown %s=%p",functions[index].args[i].name,*(bp+argof));
					break;
				}
		}else{
			printf("arg out of bounds'");
		}
		i++;
		if(functions[index].args[i].offset != 0){
			printf(", ");
		}
	}
		if(i == 0){
			printf("void) in\n");
		}else{
			printf(") in \n");
		}

	}while(1);
}
