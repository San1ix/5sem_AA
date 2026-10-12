#include "algorithms_ext.h"
#include "constants.h"

search_result_t linear_search_ext(const int *arr, int size, int target) 
{
    search_result_t res = {INDEX_NOT_FOUND, 0};
    for (int i = 0; i < size; ++i) 
    {
        res.comp_count++;
        if (arr[i] == target) 
        {
            res.index = i;
            return res;
        }
    }
    return res;
}

search_result_t binary_search_ver_a_ext(const int *arr, int size, int target) 
{
    search_result_t res = {INDEX_NOT_FOUND, 0};
    int left = 0;
    int right = size - 1;

    while (left <= right) 
    {
        int med = left + (right - left) / 2;
        res.comp_count++;
        if (arr[med] == target) 
        {
            res.index = med;
            return res;
        }

        res.comp_count++;
        if (arr[med] < target) 
            left = med + 1;
        else 
            right = med - 1;
    }
    return res;
}

search_result_t binary_search_ver_b_ext(const int *arr, int size, int target) 
{
    search_result_t res = {INDEX_NOT_FOUND, 0};
    int n = size;
    int base = 0;

    while (n > 1) 
    {
        int half = n / 2;
        res.comp_count++;
        base += (arr[base + half] < target) * half;
        n -= half;
    }
    res.comp_count++;
    base += (arr[base] < target);

    res.comp_count++;
    if (base < size && arr[base] == target)
        res.index = base;

    return res;
}

static search_result_t recursive_ext_impl(const int *arr, int target, int left, int right, int cur_comps) 
{
    if (left > right) 
        return (search_result_t){INDEX_NOT_FOUND, cur_comps};
    int med = left + (right - left) / 2;

    cur_comps++;
    if (arr[med] == target) 
        return (search_result_t){med, cur_comps};

    cur_comps++;
    if (arr[med] < target)
        return recursive_ext_impl(arr, target, med + 1, right, cur_comps);
    else
        return recursive_ext_impl(arr, target, left, med - 1, cur_comps);
}

search_result_t binary_search_recursive_ext(const int *arr, int size, int target) 
{
    return recursive_ext_impl(arr, target, 0, size - 1, 0);
}