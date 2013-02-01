#include <stdio.h>
#include "syscfg.h"

employee_t employeelist;

int printf_f(employee_t *list)
{
	printf("employee name is %s\n",list->name);
	printf("employee age  is %d\n",list->age);
	return 0;
}

void main(int argc,char *argv[])
{

	char bufkey[32];
	char bufvalue[100];
	char bufline[100];

	FILE* fp = fopen(argv[1],"r+");

	memset(bufkey,0,sizeof(bufkey));
	memset(bufvalue,0,sizeof(bufvalue));
	memset(bufline,0,sizeof(bufline));

	while(1) {
		if(fgets(bufline,sizeof(bufline),fp)){
			bufline[strlen(bufline) - 1] = '\0';
			printf("oen bufile is %s\n",bufline);
			sscanf(bufline,"%[^=]=\"%[^\"]",bufkey,bufvalue);
			printf("tow bufkey is %s\n",bufkey);
			printf("threed bufvalue is %s\n",bufvalue);
	
		}else break;
	}

	softwareconfig_mode_init(argv[1]);
	get_employeelist(&employeelist);
	printf_f(&employeelist);

}
