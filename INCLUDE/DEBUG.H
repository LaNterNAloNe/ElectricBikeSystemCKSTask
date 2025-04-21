#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <dos.h>
#include <time.h>
#include <alloc.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include "GROCERY.H"


unsigned long get_used_memory();
void display_memory_usage(int x, int y);

void show_num(int x, int y, long value, int color);
void show_text(int x, int y, char *text, int color);

#endif