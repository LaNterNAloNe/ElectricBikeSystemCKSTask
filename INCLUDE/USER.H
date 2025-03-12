#ifndef _USER_H_
#define _USER_H_

#include <stdio.h>
#include <graphics.h>
#include <string.h>
#include <conio.h>
#include <DOS.H>
#include <ctype.h>
#include <stdlib.H>
#include"GROCERY.H"
#include"MOUSE.H"
#include"INPUTCH.H"
#include"HZ.H"

#define BIKE_REGISTER_X1 0
#define BIKE_REGISTER_X2 150
#define BIKE_REGISTER_Y1 60
#define BIKE_REGISTER_Y2 110
#define BIKE_LICENSE_X1 0
#define BIKE_LICENSE_X2 150
#define BIKE_LICENSE_Y1 115
#define BIKE_LICENSE_Y2 165
#define BIKE_ANUAL_X1 0
#define BIKE_ANUAL_X2 150
#define BIKE_ANUAL_Y1 170
#define BIKE_ANUAL_Y2 220
#define BIKE_WROTEOUT_X1 0
#define BIKE_WROTEOUT_X2 150
#define BIKE_WROTEOUT_Y1 225
#define BIKE_WROTEOUT_Y2 275
#define USER_INFO_X1 0
#define USER_INFO_X2 150
#define USER_INFO_Y1 280
#define USER_INFO_Y2 330
#define USER_MESSAGE_X1 0
#define USER_MESSAGE_X2 150
#define USER_MESSAGE_Y1 335
#define USER_MESSAGE_Y2 385
#define USER_DATAGRAPH_X1 0
#define USER_DATAGRAPH_X2 150
#define USER_DATAGRAPH_Y1 390
#define USER_DATAGRAPH_Y2 440
#define USER_BACK_X1 575
#define USER_BACK_X2 635
#define USER_BACK_Y1 10
#define USER_BACK_Y2 50
#define USER_EXIT_X1 10
#define USER_EXIT_X2 50
#define USER_EXIT_Y1 10
#define USER_EXIT_Y2 50

#define ACTIVE_NONE 0
#define ACTIVE_BIKE_REGISTER 1
#define ACTIVE_BIKE_LICENSE 2
#define ACTIVE_BIKE_ANUAL 3
#define ACTIVE_BIKE_WROTEOUT 4
#define ACTIVE_USER_INFO 5
#define ACTIVE_USER_MESSAGE 6
#define ACTIVE_USER_DATAGRAPH 7

void user_main(void);
void drawgraph_user_main(void);
void flushUserGraph(int *tag,int *page);
#endif