#ifndef LIST_H_
#define LIST_H_

#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <time.h>

#include "_ADMIN_.H"
#include "LOGIN.H"
#include "LINKLIST.H"
#include "GROCERY.H"
#include "MESSAGE.H" 


// ÁÐ±íº¯Êý
void admin_list_info(LINKLIST *LIST, const int max, const int interval, unsigned long item_id[], FILE *fp, char *file_type,
                     char *list_mode, int search_mode, int page_change, int is_clear, char *search_str, char *search_needed);
void admin_show_ebike_manage_info(struct _EBIKE_INFO_ TEMP, const int max, const int interval, int listed_item, char *list_mode, int list_sequence);
void admin_show_user_info(USER_LOGIN_DATA TEMP, const int max, const int interval, int listed_item, int list_sequence);
void admin_show_ebike_info(LINKLIST_USER usrdat, const int max, const int interval, int listed_item, int list_sequence);
int list_ebike_manage_is_valid(struct _EBIKE_INFO_ TEMP, char *list_mode, char *search_str, char *search_needed, int search_mode);
int list_user_data_is_valid(USER_LOGIN_DATA TEMP, char *search_str, char *search_needed);
int list_ebike_info_is_valid(LINKLIST_USER usrdat, char *search_str, char *search_needed);
void list_show_page_index(unsigned int page_index, unsigned int page_count, const int max, const int interval);
void handle_list_select_line_admin(LINKLIST *LIST, unsigned long item_id[], unsigned long *selected_id, const int max, const int interval);


#endif