/*
 * @file set.hpp
 * @class Set
 * @brief contains basic class representing the mathematical object: Set,
 *        and the mathematical operations one can perform on a set.
 * @author Vatsal Srivastava
 * @copyright (c) 2019
 */

#include <vector>
#include <iostream>
#include <algorithm>

#include "utils.hpp"

/**
 * @class Tuple
 * @brief A class representing a tuple
 * @tparam the type of elements that the set contains.
 */
template <class... types>
class Tuple
{
    Tuple(types elms)
    {
        for(int i = 0; i < elms.length; i++)
        {
            std::cout << elms[i] << endl;
        }
    }
};