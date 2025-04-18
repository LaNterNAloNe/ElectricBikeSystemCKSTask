#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include "GROCERY.H"
#include "DEBUG.H"
#include "HZ.H"
#include "_ADMIN_.H"
#include "MOUSE.H"

#define ANNOUNCEMENT 1
#define PRIVATE_MESSAGE 2

typedef struct _MESSAGE_ {
    long sender_id;
    char sender_username[15];
    long receiver_id;
    char receiver_username[15];
    char title[64];
    char message[512];
    long time;
    int is_read;
    int is_replied;
    long message_id;
    int message_type;
} MESSAGE;

void message_display(MESSAGE *msg);
void message_reply(int *is_return, MESSAGE *msg);

void message_list(MESSAGE msg, int _x, int _y, int _listed_item, int _max, int _interval, int list_sequence);
void message_topic_display(int _x, int _y, int _width, char *_text, int _text_color, int _hz_font_size, int _asc_font_size, int _is_light);
void message_text_display(int _x, int _y, int _width, char *_text, int _text_color);
int message_get(FILE *fp, MESSAGE *msg, char *search_str, char *search_needed);
int message_overwrite(FILE *fp, MESSAGE *msg, char *search_str, char *search_needed);
int message_is_valid(MESSAGE msg, char *search_str, char *search_needed);
int message_if_found(int __is_read);

void message_handle_click_event(int *is_return, MESSAGE *msg);
void message_list_click(int _x, int _y, int _listed_item, int _max, int _interval, int _item_id[], long *_selected_id);

void message_display_draw_bg();
void message_reply_draw_bg(MESSAGE *prev_msg);

#endif