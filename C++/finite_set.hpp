#ifndef FINITE_SET_HPP
#define FINITE_SET_HPP
/*
 * @file finite_set.hpp
 * @brief contains basic class representing the mathematical object: FiniteSet,
 *        and the mathematical operations one can perform on a finite_set.
 * @author Vatsal Srivastava
 * @copyright (c) 2019
 */

#include <vector>
#include <tuple>
#include <iostream>
#include <algorithm>
#include <sstream>

#include "utils.hpp"

/**
 * @class FiniteSet
 * @brief A class representing a finite_set, with overloaded operators for computing
 *        intersection, union, etc. It may also serve as a base class for other
 *        classes like Group, Ring, etc.
 * @tparam datatype of the elements that the finite_set contains.
 */
template <class ElementType>
class FiniteSet
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

    FiniteSet(ElementType* elms_, int order_)
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

    FiniteSet<ElementType> operator^(FiniteSet<ElementType> const &A)const
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
        FiniteSet<ElementType> intersection = FiniteSet<ElementType>(intersec_list, intersec_order);
        delete[] intersec_list;
        delete[] a_elms;
        delete[] b_elms;
        return intersection;
    }

    FiniteSet<ElementType> operator&(FiniteSet<ElementType> const &A)const
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
        FiniteSet<ElementType> Union = FiniteSet<ElementType>(union_elms, union_length);
        delete[] union_elms;
        delete[] a_elms;
        delete[] b_elms;
        return Union;
    }

    FiniteSet<ElementType> operator-(FiniteSet<ElementType> const &A)const
    {
        FiniteSet<ElementType> intersec = (*this) ^ A;
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
        FiniteSet<ElementType> setminus = FiniteSet<ElementType>(reduced, neworder);
        delete[] elms;
        delete[] reduced;
        return setminus;    
    }

    bool operator<=(FiniteSet<ElementType> const &A)const
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

    bool operator>=(FiniteSet<ElementType> const &A)const
    {
        return A <= *(this);
    }

    bool operator<(FiniteSet<ElementType> const &A)const
    {
        return (*(this) <= A) &&  (_order < A.getOrder());
    }

    bool operator>(FiniteSet<ElementType> const &A)const
    {
        return (A <= *(this)) &&  (A.getOrder() < _order);
    }

    bool operator==(FiniteSet<ElementType> const &A)const
    {
        return (*(this) <= A) && (A <= *(this));
    }

    bool operator>(ElementType const x)const
    {
        ElementType *elms;
        getAllElements(elms);
        int n = getOrder();
        bool flag = false;
        for(int i = 0; i < n; i++)
        {
            if(elms[i] == x)
            {
                flag = true;
                break;
            }
        }
        return flag;
    }

};

template <typename type>
bool operator<(type const x, FiniteSet<type> const S)
{
    return S > x;
}

template <typename... types>
FiniteSet<std::tuple<types...>> cartesianProduct()
{
    return NULL;
}

template <typename type1>
FiniteSet<std::tuple<type1>> cartesianProduct(FiniteSet<type1> set1)
{
    type1 *elms;
    set1.getAllElements(elms);
    int n = set1.getOrder();
    std::tuple<type1> *singular = new std::tuple<type1>[n];
    for(int i = 0; i < n; i++)
    {
        singular[i] = std::make_tuple(elms[i]);
    }
    FiniteSet<std::tuple<type1>> SinFiniteSet(singular, n);
    delete[] elms;
    delete[] singular;
    return SinFiniteSet;
}

template <typename type1, typename... types>
FiniteSet<std::tuple<type1, types...>> cartesianProduct(FiniteSet<type1> set1, FiniteSet<types>... other_sets)
{
    if(sizeof...(types) > 0)
    {
        FiniteSet<std::tuple<types...>> set2 = cartesianProduct<types...>(other_sets...);
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
        FiniteSet<std::tuple<type1, types...>> product_set(product_array, n1 * n2);
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

template <typename type>
std::ostream& operator<<(std::ostream& output, FiniteSet<type> const &S)
{
    type* elms;
    S.getAllElements(elms);
    int n = S.getOrder();
    output << '{';
    for(int i = 0; i < n; i++)
    {
        output << elms[i];
        if(i < n-1)
        {
            output << ", ";
        }
    }
    output << '}';
    return output;
}

template <typename type>
std::stringstream& operator<<(std::stringstream& output, FiniteSet<type> const &S)
{
    type* elms;
    S.getAllElements(elms);
    int n = S.getOrder();
    output << '{';
    for(int i = 0; i < n; i++)
    {
        output << elms[i];
        if(i < n-1)
        {
            output << ", ";
        }
    }
    output << '}';
    return output;
}
#endif
