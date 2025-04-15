#ifndef _INPUTCH_H_
#define _INPUTCH_H_

#include<graphics.h>
#include<bios.h>
#include<string.h>
#include<dos.h>
#include"GROCERY.H"
#include"MOUSE.H"

#define MAX_MEM 10

typedef struct {
    int x, y;
    char content[50];
    int cursor_pos;
} InputMemory;
 
int ch_input(char* ip,int x,int y,int lim,int color,int is_clear_memory,int is_visible);

#endif
