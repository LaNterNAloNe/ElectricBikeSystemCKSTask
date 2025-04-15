#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include "GROCERY.H"
#include "DEBUG.H"
#include "HZ.H"

typedef struct _MESSAGE_ {
    long sender_id;
    char sender_username[15];
    long receiver_id;
    char receiver_username[15];
    char title[64];
    char message[512];
    long time;
    int is_read;
    long message_id;
} MESSAGE;

void message_display(MESSAGE msg, int _x, int _y, int _listed_item, int _max, int _interval, int list_sequence);
void message_topic_display(int _x, int _y, int _width, char *_text);
void message_text_display(int _x, int _y, int _width, char *_text);
int message_get(FILE *fp, MESSAGE *msg, char *search_str, char *search_needed);
int message_is_valid(MESSAGE msg, char *search_str, char *search_needed);
int message_if_found(int __is_read);

#endif