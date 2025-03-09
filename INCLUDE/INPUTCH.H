#ifndef _INPUTCH_H_
#define _INPUTCH_H_

#include<graphics.h>
#include<bios.h>
#include<string.h>
#include"MOUSE.H"

typedef struct {
    int x, y;
    char content[100];
    int cursor_pos;
} InputMemory;
 



int Input_Vis(char* ip,int x,int y,int lim,int color);
int Input_Invis(char* ip,int x,int y,int lim,int color);                      

#endif
