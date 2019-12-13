/*
 * @file set.hpp
 * @class Set
 * @brief contains basic class representing the mathematical object: Set,
 *        and the mathematical operations one can perform on a set.
 * @author Vatsal Srivastava
 * @copyright (c) 2019
 */

#include <vector>
#include <tuple>
#include <iostream> //should be removed after completion of this file.
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
        delete[] a_elms;
        delete[] b_elms;
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
        delete[] a_elms;
        delete[] b_elms;
        return Union;
    }

    Set<ElementType> operator-(Set<ElementType> const &A)const
    {
        Set<ElementType> intersec = (*this) ^ A;
        ElementType *elms, *reduced;
        getAllElements(elms);
        int neworder = _order - intersec.getOrder();
        reduced = new ElementType[neworder];
        for(int i = 0, j = 0; i < _order && j < neworder; i++)
        {
            if(!intersec.contains(elms[i]))
            {
                reduced[j] = elms[i];
                j++;
            }
        }
        Set<ElementType> setminus = Set<ElementType>(reduced, neworder);
        delete[] elms;
        delete[] reduced;
        return setminus;    
    }

    bool operator<=(Set<ElementType> const &A)const
    {
        bool flag = true;
        ElementType *self_elms;
        getAllElements(self_elms);
        for(int i = 0; i < _order; i++)
        {
            flag = flag & A.contains(self_elms[i]);
        }
        return flag;
    }

    bool operator>=(Set<ElementType> const &A)const
    {
        return A <= *(this);
    }

    bool operator<(Set<ElementType> const &A)const
    {
        return (*(this) <= A) &&  (_order < A.getOrder());
    }

    bool operator>(Set<ElementType> const &A)const
    {
        return (A <= *(this)) &&  (A.getOrder() < _order);
    }

    bool operator==(Set<ElementType> const &A)const
    {
        return (*(this) <= A) && (A <= *(this));
    }
};

template <typename... types>
Set<std::tuple<types...>> cartesianProduct()
{
    return NULL;
}

template <typename type1>
Set<std::tuple<type1>> cartesianProduct(Set<type1> set1)
{
    type1 *elms;
    set1.getAllElements(elms);
    int n = set1.getOrder();
    std::tuple<type1> *singular = new std::tuple<type1>[n];
    for(int i = 0; i < n; i++)
    {
        singular[i] = std::make_tuple(elms[i]);
    }
    Set<std::tuple<type1>> SinSet(singular, n);
    delete[] elms;
    delete[] singular;
    return SinSet;
}

template <typename type1, typename... types>
Set<std::tuple<type1, types...>> cartesianProduct(Set<type1> set1, Set<types>... other_sets)
{
    if(sizeof...(types) > 0)
    {
        Set<std::tuple<types...>> set2 = cartesianProduct<types...>(other_sets...);
        type1 *elms1;
        set1.getAllElements(elms1);
        std::tuple<types...> *elms2;
        set2.getAllElements(elms2);
        int n1 = set1.getOrder();
        int n2 = set2.getOrder();
        std::tuple<type1, types...> *product_array = new std::tuple<type1, types...>[n1 * n2];
        for(int i = 0; i < n1; i++)
        {
            for(int j = 0; j < n2; j++)
            {
                product_array[j + i * n2] = \
                         std::tuple_cat(std::make_tuple(elms1[i]), elms2[j]);
            }
        }
        Set<std::tuple<type1, types...>> product_set(product_array, n1 * n2);
        delete[] product_array;
        delete[] elms1;
        delete[] elms2;
        return product_set;
    }
    else
    {
        return cartesianProduct(set1, other_sets...);
    }
}
