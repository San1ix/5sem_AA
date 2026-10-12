#ifndef MENU_H
#define MENU_H

void print_main_menu(void);
void print_input_menu(void);
void print_search_menu(void);

void run_automated_benchmarks(void);
void handle(int choice, int **raw_arr, int **sorted_arr, int *size);

#endif