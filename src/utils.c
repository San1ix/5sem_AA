#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

int* generate_array(int size) 
{
    if (size <= 0) 
        return NULL;
    int *arr = (int*)malloc(size * sizeof(int));
    if (!arr) 
        return NULL;

    arr[0] = (rand() % MAX_RANDOM_STEP) + 1;
    for (int i = 1; i < size; ++i)
        arr[i] = arr[i - 1] + (rand() % MAX_RANDOM_STEP) + 1;

    for (int i = size - 1; i > 0; --i) 
    {
        int j = rand() % (i + 1);
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
    return arr;
}

int* input_array(int size) 
{
    if (size <= 0) 
        return NULL;
    int *arr = (int*)malloc(size * sizeof(int));
    if (!arr) 
        return NULL;

    printf("Введите %d элементов массива:\n", size);
    for (int i = 0; i < size; ++i) 
    {
        printf("[%d]: ", i);
        while (scanf("%d", &arr[i]) != 1) 
        {
            scanf("%*s");
            printf("Введите число [%d]: ", i);
        }
    }
    return arr;
}

int* copy_array(const int *src, int size) 
{
    if (!src || size <= 0) 
        return NULL;
    int *dst = (int*)malloc(size * sizeof(int));
    if (!dst) 
        return NULL;

    for (int i = 0; i < size; ++i) 
        dst[i] = src[i];
    return dst;
}

void print_array(const int *arr, int size) 
{
    if (!arr || size <= 0) 
    {
        printf("[Пустой массив]\n");
        return;
    }

    printf("Массив: [ ");
    for (int i = 0; i < size; ++i)
        printf("%d ", arr[i]);
    printf("]\n");
}

static void quick_sort_impl(int *arr, int left, int right) 
{
    if (left >= right) 
        return;

    int pivot = arr[left + (right - left) / 2];
    int i = left, j = right;

    while (i <= j) 
    {
        while (arr[i] < pivot) i++;
        while (arr[j] > pivot) j--;

        if (i <= j) 
        {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;

            i++;
            j--;
        }
    }

    quick_sort_impl(arr, left, j);
    quick_sort_impl(arr, i, right);
}

void sort_array(int *arr, int size) 
{
    if (!arr || size <= 1) 
        return;
    quick_sort_impl(arr, 0, size - 1);
}