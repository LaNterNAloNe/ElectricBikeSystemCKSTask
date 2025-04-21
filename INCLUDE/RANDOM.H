#ifndef RANDOM_H
#define RANDOM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LINKLIST.H"
#include "_ADMIN_.H"


void rand_id(char *output);
void rand_exist_id(char *output, LINKLIST *LIST);
void rand_license(char *output);
void rand_location(char *output, int gate_needed);
void rand_ebike_id(char *output, LINKLIST *LIST);
void rand_ebike_license(char *output);
void rand_time(long *output, int is_past_year, int is_today);
void rand_violations(int *output);
int rand_io_comment();

long rand_int(long min, long max);
void rand_io_data(LINKLIST *LIST);

#endif