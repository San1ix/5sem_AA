#include "menu.h"
#include "constants.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) 
{
    int choice = -1;
    int *raw_array = NULL;
    int *sorted_array = NULL;
    int current_size = 0;

    while (choice != MENU_EXIT) 
    {
        print_main_menu();
        printf("Выбор: ");

        while (scanf("%d", &choice) != 1) 
        {
            scanf("%*s");
            printf("Пожалуйста, введите число: ");
        }

        if (choice != MENU_EXIT)
            handle(choice, &raw_array, &sorted_array, &current_size);
    }

    free(raw_array);
    free(sorted_array);
    
    printf("Завершение работы программы\n");
    return 0;
}