#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <math.h>

/*
 * @file utils.hpp
 * @brief contains utility functions for simplifying internal computations
 * @author Vatsal Srivastava
 * @copyright (c) 2019
 */


/**
 * @brief private util function to reduce an array by removing multiple
 *        occurences of an element.
 * @param arr: contains the array to be reduced, and is updated with the reduced array
 *             (the elements are updated, the pointer still points to the same array)
 * @param len: contains the length of arr, and is updated with the length of the
 *             reduced array (since len is passed by reference)
 */
template <typename type>
void reduce(type* arr, int &len)
{
    std::vector<type> reduced;
    typename std::vector<type>::iterator it;
    for(int i = 0; i < len; i++)
    {
        it = std::find(reduced.begin(), reduced.end(), arr[i]);
        if(it == reduced.end())
        {
            reduced.push_back(arr[i]);
        }
    }
    len = reduced.size();
    for(int i = 0; i < reduced.size(); i++)
    {
        arr[i] = reduced[i];
    }
}

/**
 * @brief private util function to reduce an array by removing multiple
 *        occurences of an element.
 * @param arr1: points to an array1, and is changed so as to point to array2
 * @param len1: contains length of array1, updated to length of array2
 * @param arr2: points to an array2, and is changed so as to point to array1
 * @param len: contains length of array2, updated to length of array1
 */
template <typename type>
void swap(type* &arr1, int &len1, type* &arr2, int &len2)
{
    int y = len1;
    len1 = len2;
    len2 = len1;
    type* c;
    c = arr1;
    arr1 = arr2;
    arr2 = c;
}
#endif