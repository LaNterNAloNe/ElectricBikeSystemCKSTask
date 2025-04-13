#ifndef RANDOM_H
#define RANDOM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void rand_id(char *output);
void rand_license(char *output);
void rand_location(char *output);
void rand_ebike_id(char *output);
void rand_ebike_license(char *output);
void rand_time(long *output, int is_past_year);
void rand_violations(int *output);

#endif