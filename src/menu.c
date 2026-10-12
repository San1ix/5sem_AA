#include "menu.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "algorithms_ext.h"
#include "constants.h"

void print_main_menu(void) 
{
    printf("<|>-----------------------------------<|>\n");
    printf(" |-------------<> МЕНЮ <>--------------|\n");
    printf("<|>-----------------------------------<|>\n");
    printf(" | 1 - Задать массив (Генерация/Ввод)  |\n");
    printf(" | 2 - Показать текущие массивы        |\n");
    printf(" | 3 - Поиск элемента                  |\n");
    printf(" | 4 - Автозамеры сравнений для отчета |\n");
    printf(" | 0 - Выход                           |\n");
    printf("<|>-----------------------------------<|>\n");
}

void print_input_menu(void) 
{
    printf("<|>-----------------------------------<|>\n");
    printf(" |----------<> Ввод массива <>---------|\n");
    printf("<|>-----------------------------------<|>\n");
    printf(" | 1 - Сгенерировать                   |\n");
    printf(" | 2 - Ввести вручную                  |\n");
    printf(" | 0 - Назад                           |\n");
    printf("<|>-----------------------------------<|>\n");
}

void print_search_menu(void) 
{
    printf("<|>-----------------------------------<|>\n");
    printf(" |--------<> Выбор алгоритма <>--------|\n");
    printf("<|>-----------------------------------<|>\n");
    printf(" | 1 - Линейный поиск полным перебором |\n");
    printf(" | 2 - Бинарный нерек. поиск версия А  |\n");
    printf(" | 3 - Бинарный нерек. поиск версия Б  |\n");
    printf(" | 4 - Бинарный рекурсивный поиск      |\n");
    printf(" | 0 - Назад                           |\n");
    printf("<|>-----------------------------------<|>\n");
}

typedef search_result_t (*search_func_ext_t)(const int*, int, int);

static void run_benchmark_for_algo(int algo_id, const char *algo_name) 
{
    printf("\n=== %s ===\n", algo_name);
    printf("%-7s | %-12s | %-12s | %-12s\n", "N", "Лучший", "Произвольный", "Худший");
    printf("<|>----------------------------------------------<|>\n");

    for (int N = BENCHMARK_START; N <= BENCHMARK_END; N += BENCHMARK_STEP) 
    {
        int *raw = generate_array(N);
        int *sorted = copy_array(raw, N);
        sort_array(sorted, N);

        int target_best, target_rand, target_worst;
        const int *arr;
        search_func_ext_t func = NULL;

        target_worst = sorted[N - 1] + 100;

        if (algo_id == ALG_LINEAR) 
        {
            arr = raw;
            func = linear_search_ext;
            target_best = raw[0];
            target_rand = raw[N / 3];
        } 
        else 
        {
            arr = sorted;
            target_best = sorted[(N - 1) / 2];
            target_rand = sorted[N / 3]; 
            if (algo_id == ALG_BINARY_A)
                func = binary_search_ver_a_ext;
            else if (algo_id == ALG_BINARY_B) 
                func = binary_search_ver_b_ext;
            else if (algo_id == ALG_BINARY_REC) 
                func = binary_search_recursive_ext;
        }

        search_result_t res_best = func(arr, N, target_best);
        search_result_t res_rand = func(arr, N, target_rand);
        search_result_t res_worst = func(arr, N, target_worst);

        printf("%-7d | %-12d | %-12d | %-12d\n", N, res_best.comp_count, res_rand.comp_count, res_worst.comp_count);

        free(raw);
        free(sorted);
    }
}

void run_automated_benchmarks(void) 
{
    printf("=================================================================\n\n");
    run_benchmark_for_algo(ALG_LINEAR, "1. Линейный поиск полным перебором");
    run_benchmark_for_algo(ALG_BINARY_A, "2. Бинарный поиск (Версия А)");
    run_benchmark_for_algo(ALG_BINARY_B, "3. Бинарный поиск (Версия Б - Branchless)");
    run_benchmark_for_algo(ALG_BINARY_REC, "4. Бинарный поиск (Рекурсивный)");
    printf("=================================================================\n\n");
}

void handle(int choice, int **raw_arr, int **sorted_arr, int *size) 
{
    if (choice == MENU_INPUT) 
    {
        print_input_menu();
        int inp_choice;
        printf("Выбор: ");
        while (scanf("%d", &inp_choice) != 1) 
        {
            scanf("%*s");
            printf("Введите пункт меню: ");
        }

        if (inp_choice == INPUT_GENERATE || inp_choice == INPUT_MANUAL) 
        {
            int n;
            printf("Введите размер массива (N): ");
            while (scanf("%d", &n) != 1 || n <= 0) 
            {
                scanf("%*s");
                printf("Размер должен быть > 0. Повторите: ");
            }

            free(*raw_arr);
            free(*sorted_arr);
            *raw_arr = NULL;
            *sorted_arr = NULL;
            *size = n;

            if (inp_choice == INPUT_GENERATE) 
                *raw_arr = generate_array(n);
            else
                *raw_arr = input_array(n);

            *sorted_arr = copy_array(*raw_arr, n);
            sort_array(*sorted_arr, n);

            printf("Массивы успешно подготовлены\n");
        }
    } 
    else if (choice == MENU_PRINT) 
    {
        if (*raw_arr == NULL) 
        {
            printf("Массивы еще не созданы\n");
            return;
        }
        printf("\n<|>--- ИСХОДНЫЙ МАССИВ ---<|>\n");
        print_array(*raw_arr, *size);
        printf("\n<|>--- ОТСОРТИРОВАННЫЙ МАССИВ ---<|>\n");
        print_array(*sorted_arr, *size);
        printf("\n");
    } 
    else if (choice == MENU_SEARCH) 
    {
        if (*raw_arr == NULL) 
        {
            printf("Сначала создайте массив (Пункт 1)\n");
            return;
        }

        int target;
        printf("Введите искомое число X: ");
        while (scanf("%d", &target) != 1) 
        {
            scanf("%*s");
            printf("Введите целое число: ");
        }

        print_search_menu();
        int alg_choice;
        printf("Выбор алгоритма: ");
        while (scanf("%d", &alg_choice) != 1) 
        {
            scanf("%*s");
            printf("Выберите номер алгоритма: ");
        }

        search_result_t res;
        switch (alg_choice) 
        {
            case ALG_LINEAR:
                res = linear_search_ext(*raw_arr, *size, target);
                break;
            case ALG_BINARY_A:
                res = binary_search_ver_a_ext(*sorted_arr, *size, target);
                break;
            case ALG_BINARY_B:
                res = binary_search_ver_b_ext(*sorted_arr, *size, target);
                break;
            case ALG_BINARY_REC:
                res = binary_search_recursive_ext(*sorted_arr, *size, target);
                break;
            case ALG_BACK:
                return;
            default:
                printf("Неверный выбор\n");
                return;
        }

        printf("\n=== РЕЗУЛЬТАТ ПОИСКА ===\n");
        if (res.index != INDEX_NOT_FOUND)
            printf("Элемент найден. Индекс: %d\n", res.index);
        else
            printf("Элемент НЕ НАЙДЕН\n");
        printf("Количество сравнений ключей: %d\n", res.comp_count);
        printf("========================\n\n");
    }
    else if (choice == MENU_BENCHMARK)
        run_automated_benchmarks();
}