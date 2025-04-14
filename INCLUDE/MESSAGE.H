#ifndef MESSAGE_H
#define MESSAGE_H

#include <graphics.h>
#include "GROCERY.H"
#include "DEBUG.H"
#include "HZ.H"

typedef struct _MESSAGE_ {
    long sender_id;
    char sender_username[15];
    long reciever_id;
    char receiver_username[15];
    char message[512];
    long time;
    int is_read;
} MESSAGE;

void message_display(int x, int y, char *text);

#endif