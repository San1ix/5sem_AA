#include "algorithms.h"

int linear_search(const int *arr, int size, int target) 
{
    for (int i = 0; i < size; ++i)
        if (arr[i] == target) 
            return i;
    return INDEX_NOT_FOUND;
}

int binary_search_ver_a(const int *arr, int size, int target) 
{
    int left = 0;
    int right = size - 1;

    while (left <= right) 
    {
        int med = left + (right - left) / 2;
        if (arr[med] == target)
            return med;
        else if (arr[med] < target)
            left = med + 1;
        else
            right = med - 1;
    }
    return INDEX_NOT_FOUND;
}

int binary_search_ver_b(const int *arr, int size, int target) 
{
    int n = size;
    int base = 0;

    while (n > 1) 
    {
        int half = n / 2;
        base += (arr[base + half] < target) * half;
        n -= half;
    }
    base += (arr[base] < target);

    if (base < size && arr[base] == target) 
        return base;
    return INDEX_NOT_FOUND;
}

static int recursive_impl(const int *arr, int target, int left, int right) 
{
    if (left > right) 
        return INDEX_NOT_FOUND;
    int med = left + (right - left) / 2;

    if (arr[med] == target)
        return med;
    else if (arr[med] < target)
        return recursive_impl(arr, target, med + 1, right);
    else
        return recursive_impl(arr, target, left, med - 1);
}

int binary_search_recursive(const int *arr, int size, int target) 
{
    return recursive_impl(arr, target, 0, size - 1);
}