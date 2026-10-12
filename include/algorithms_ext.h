#ifndef ALGORITHMS_EXT_H
#define ALGORITHMS_EXT_H

#include "types.h"

search_result_t linear_search_ext(const int *arr, int size, int target);
search_result_t binary_search_ver_a_ext(const int *arr, int size, int target);
search_result_t binary_search_ver_b_ext(const int *arr, int size, int target);
search_result_t binary_search_recursive_ext(const int *arr, int size, int target);

#endif