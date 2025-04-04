#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <alloc.h>
#include <graphics.h>
#include "GROCERY.H"
#include <stdio.h>
#include <stdlib.h>

unsigned long get_used_memory();
void display_memory_usage(int x, int y);

void show_num(int x, int y,unsigned long value, int color);
void show_text(int x, int y, char *text, int color);

#endif