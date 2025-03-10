#ifndef _INPUTCH_H_
#define _INPUTCH_H_

#include<graphics.h>
#include<bios.h>
#include<string.h>
#include<dos.h>
#include"GROCERY.H"
#include"MOUSE.H"

typedef struct {
    int x, y;
    char content[50];
    int cursor_pos;
} InputMemory;
 
int Input_Vis(char* ip,int x,int y,int lim,int color,int *page);
int Input_Invis(char* ip,int x,int y,int lim,int color,int *page);                      

#endif
