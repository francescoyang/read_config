#include <stdio.h>
#include "syscfg.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>


static employee_t employee;
static cfglist aplist;
int get_cfgkey(cfglist* list, const char* key, char* value){
	assert(list);
	cfgline* pNode = list->pHead;
	for(;pNode;pNode = pNode -> pNext){
		if(strncmp(key,pNode->key,strlen(key)) == 0){
			memcpy(value,pNode->value,strlen(pNode->value)+1);
			printf("got value: %s\n",value);
			return 0;
		}
	}
	return -1;
}

int analyse_arglist(){
	//char bufkey[32];
	char bufvalue[100];
	memset(bufvalue,0,sizeof(bufvalue));

	printf("get keys...\n");

	get_cfgkey(&aplist,"employeename",bufvalue);
	employee.enable=1;
	memcpy(employee.name, bufvalue, strlen(bufvalue));
	memset(bufvalue,0,sizeof(bufvalue));

	get_cfgkey(&aplist,"employeeage",bufvalue);
	employee.age = atoi(bufvalue);
	memset(bufvalue,0,sizeof(bufvalue));

	return 0;

}

int get_employeelist(employee_t *list)
{
	if (!employee.enable) {
		return -1;
	}
	memcpy(list, &employee, sizeof(employee_t));
	return 0;
}

int softwareconfig_mode_init(char *filename)
{
	//read to cfglist
	if(cfglist_read(filename,&aplist) == -1) {
		perror("cfglist_read:");
		return -1;
	}
	//analyse
	if(analyse_arglist() == -1) {
		perror("analyse_arglist:");		
		return -1;
	}
	return 0;
}

