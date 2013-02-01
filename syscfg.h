/***********************
 *      ITC-IMAGE	   *
 *                     *
 *  Author: Chen.M     *
 *  Date: Sep.19 2012  *
 *					   *
 ***********************/

#ifndef __CFGRW_H
#define __CFGRW_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct tag_cfgline{
	char line[100];
	char key[32];
	char value[100];
	struct tag_cfgline* pNext;
}cfgline;

typedef struct tag_cfglist{
	cfgline* pHead;
	cfgline* pTail;
	unsigned int number;
}cfglist;

typedef struct __employee{
	int enable;
	int age;
	char name[32];
}employee_t;

int cfglist_append(cfglist*, const char*, const char*);
int cfglist_clear(cfglist*);
int cfglist_read(const char*, cfglist*);
int cfglist_write(const char*, cfglist*);

int get_cfgkey(cfglist*, const char*, char*);
int set_cfgkey(cfglist*, const char*, const char*);

#ifdef __cplusplus
}
#endif

#endif
