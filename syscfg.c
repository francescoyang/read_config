#include <unistd.h>
#include <string.h>
#include "syscfg.h"
#include <fcntl.h>
#include <stdlib.h>
#include <assert.h>

int cfglist_read(const char* filename, cfglist* list)
{
	FILE* fp = fopen(filename,"r+");
	if(!fp){
		perror("File open error");
		return -1;
	}

	char bufkey[32];
	char bufvalue[100];
	char bufline[100];

	list->pHead = NULL;
	list->pTail = NULL;

	cfgline* pNode = NULL;

	for(;;){
		memset(bufkey,0,sizeof(bufkey));
		memset(bufvalue,0,sizeof(bufvalue));
		memset(bufline,0,sizeof(bufline));
		if(fgets(bufline,sizeof(bufline),fp)) {
			if(bufline[0] == '\n' || bufline[0] == '#'){
				pNode = (cfgline*)malloc(sizeof(cfgline));
				memset(pNode,0,sizeof(cfgline));
				bufline[strlen(bufline) - 1] = '\0';
				sprintf(pNode->line,"%s",bufline);
				if(list->pTail){
					list->pTail->pNext = pNode;
				}
				else{
					list->pHead = pNode;
				}
				list->pTail = pNode;
				list->number++;
			}
			else{
				bufline[strlen(bufline) - 1] = '\0';
				sscanf(bufline,"%[^=]=\"%[^\"]",bufkey,bufvalue);
				pNode = (cfgline*)malloc(sizeof(cfgline));
				memset(pNode,0,sizeof(cfgline));
				sprintf(pNode->key,"%s",bufkey);
				sprintf(pNode->value,"%s",bufvalue);
				pNode->line[0] = '\\';
				//printf("key = %s\tvalue = %s\n",pNode->key,pNode->value);
				if(list->pTail){
					list->pTail->pNext = pNode;
				}
				else{
					list->pHead = pNode;
				}
				list->pTail = pNode;
				list->number++;
			}
		}
		else break;
	}

	if(fp){
		fclose(fp);
		fp = NULL;
	}
	return 0;
}

int cfglist_write(const char* filename, cfglist* list){
	FILE* fp = fopen(filename,"w+");
	if(!fp){
		perror("creat file error");
		return -1;
	}
	
	cfgline* pNode = NULL;

	for(pNode = list->pHead;pNode;pNode = pNode->pNext){
		if(pNode->line[0] != '\\'){
			fprintf(fp,"%s\n",pNode->line);
		} else {
			if(!strlen(pNode->value)){
				sprintf(pNode->value,"N/A");
			}
			fprintf(fp,"%s=\"%s\"\n",pNode->key,pNode->value);
		}
	}

	fflush(fp);

	if(fp){
		fclose(fp);
		fp = NULL;
	}
	return 0;
}
