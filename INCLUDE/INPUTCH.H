#ifndef _INPUTCH_H_
#define _INPUTCH_H_

#include<graphics.h>
#include<bios.h>
#include<string.h>
#include<dos.h>
#include"GROCERY.H"
#include"MOUSE.H"

//  ‰»ÎøÚ
#define INPUTBAR_NO_CLEAR 0
#define INPUTBAR_CLEAR 1
#define INPUTBAR_CLEAR_CONTINUE 2


#define MAX_MEM 10

typedef struct {
    int x, y;
    char content[50];
    int cursor_pos;
} InputMemory;
 
int ch_input(char* ip,int x,int y,int lim,int color,int is_clear_memory,int is_visible);

#endif
