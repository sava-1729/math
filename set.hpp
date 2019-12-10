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
 * @class Set
 * @brief A class representing a set, with overloaded operators for computing
 *        intersection, union, etc. It may also serve as a base class for other
 *        classes like Group, Ring, etc.
 * @tparam the type of elements that the set contains.
 */
template <class ElementType>
class Set
{
    ElementType* _elements;
    int _order;

    bool contains(ElementType x)const
    {
        bool flag = false;
        for(int i = 0; i < _order; i++)
        {
            if(_elements[i] == x)
            {
                flag = true;
            }
        }
        return flag;
    }

    public:

    Set(ElementType* elms_, int order_)
    {
        reduce(elms_, order_);
        this -> _order = order_;
        _elements = new ElementType[_order];
        for(int i = 0; i < _order; i++)
        {
            _elements[i] = elms_[i];
        }
    }
    
    void getAllElements(ElementType* &external_list)const
    {
        external_list = new ElementType[_order];
        for(int i = 0; i < _order; i++)
        {
            external_list[i] = _elements[i];
        }
    }

    int getOrder()const
    {
        return _order;
    }

    Set<ElementType> operator^(Set<ElementType> const &A)const
    {
        ElementType *a_elms, *b_elms;
        int na, nb;
        A.getAllElements(a_elms);
        getAllElements(b_elms);
        na = A.getOrder();
        nb = this -> getOrder();
        if(na > nb)
        {
            swap<ElementType>(a_elms, na, b_elms, nb);
        }
        ElementType x;
        std::vector<int> common_indices;
        for(int i = 0; i < na; i++)
        {
            x = a_elms[i];
            for(int j = 0; j < nb; j++)
            {
                if(x == b_elms[j])
                {
                    common_indices.push_back(i);
                    break;
                }
            }
        }
        int intersec_order = common_indices.size();
        ElementType* intersec_list = new ElementType[intersec_order];
        for(int i = 0; i < intersec_order; i++)
        {
            intersec_list[i] = a_elms[common_indices[i]];
        }
        Set<ElementType> intersection = Set<ElementType>(intersec_list, intersec_order);
        delete[] intersec_list;
        return intersection;
    }

    Set<ElementType> operator&(Set<ElementType> const &A)const
    {
        ElementType *a_elms, *b_elms;
        int na, nb;
        A.getAllElements(a_elms);
        getAllElements(b_elms);
        na = A.getOrder();
        nb = getOrder();
        int union_length = na + nb;
        ElementType* union_elms = new ElementType[union_length];
        for(int i = 0; i < union_length; i++)
        {
            if(i < na)
            {
                union_elms[i] = a_elms[i];
            }
            else
            {
                union_elms[i] = b_elms[i-na];
            }
        }
        //std::cout << "Merged arrays\n";
        Set<ElementType> Union = Set<ElementType>(union_elms, union_length);
        delete[] union_elms;
        return Union;
    }

    bool operator<(Set<ElementType> const &A)const
    {
        bool flag = true;
        ElementType *self_elms;
        getAllElements(self_elms);
        for(int i = 0; i < _order; i++)
        {
            flag = flag & A.contains(self_elms[i]);
        }
        return flag & (_order < A.getOrder());
    }

    bool operator>(Set<ElementType> const &A)const
    {
        return A < *(this);
    }

    bool operator==(Set<ElementType> const &A)const
    {
        return (*(this) < A) && (A < *(this));
    }

    bool operator<=(Set<ElementType> const &A)const
    {
        return (*(this) < A) || (*(this) == A);
    }

    bool operator>=(Set<ElementType> const &A)const
    {
        return A <= *(this);
    }
};

