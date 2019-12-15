#ifndef BINARY_OPERATION_HPP
#define BINARY_OPERATION_HPP
#include <map>
#include <functional>
#include <tuple>
#include "set.hpp"

namespace ph = std::placeholders;
template<typename type1, typename type2, typename type3>
class BinaryOperation
{
    std::map<std::tuple<type1,type2>, type3> _operationalMap;

    type3 _operate_map(type1 operand1, type2 operand2)
    {
        _operationalMap[std::make_tuple(operand1, operand2)];
    }

    public:

    std::function<type3(type1, type2)> operate;

    BinaryOperation(FiniteSet<type1> Domain1, FiniteSet<type2> Domain2, FiniteSet<type3> CoDomain, \
                    type3 (*operator_fnc)(type1, type2), bool dynamic_op = false)
    {
        if(dynamic_op)
        {
            operate = std::bind(operator_fnc, ph::_1, ph::_2);
        }
        else
        {
            type1 *elms_1; type2 *elms_2;
            int n1, n2;
            Domain1.getAllElements(elms_1);
            Domain2.getAllElements(elms_2);
            n1 = Domain1.getOrder();
            n2 = Domain2.getOrder();
            _operationalMap.clear();
            for(int i = 0; i < n1; i++)
            {
                for(int j = 0; j < n2; j++)
                {
                    _operationalMap[std::make_tuple(elms_1[i], elms_2[j])] = operator_fnc(elms_1[i], elms_2[j]);
                }
            }
            operate = std::bind(_operate_map, ph::_1, ph::_2);
            delete[] elms_1;
            delete[] elms_2;
        }
    }

    template <class T>
    BinaryOperation(FiniteSet<type1> Domain1, FiniteSet<type2> Domain2, FiniteSet<type3> CoDomain, \
                    T *object, type3 (T::*operator_fnc)(type1, type2), bool dynamic_op = false)
    {
        if(dynamic_op)
        {
            operate = std::bind(operator_fnc, object, ph::_1, ph::_2);
        }
        else
        {
            type1 *elms_1; type2 *elms_2;
            int n1, n2;
            Domain1.getAllElements(elms_1);
            Domain2.getAllElements(elms_2);
            n1 = Domain1.getOrder();
            n2 = Domain2.getOrder();
            _operationalMap.clear();
            for(int i = 0; i < n1; i++)
            {
                for(int j = 0; j < n2; j++)
                {
                    _operationalMap[std::make_tuple(elms_1[i], elms_2[j])] = object -> operator_fnc(elms_1[i], elms_2[j]);
                }
            }
            operate = std::bind(_operate_map, ph::_1, ph::_2);
            delete[] elms_1;
            delete[] elms_2;
        }
    }

    BinaryOperation(FiniteSet<type1> Domain1, FiniteSet<type2> Domain2, FiniteSet<type3> CoDomain, \
                    std::map<std::tuple<type1,type2>, type3> operationalMap)
    {
        type1 *elms_1; type2 *elms_2;
        int n1, n2;
        Domain1.getAllElements(elms_1);
        Domain2.getAllElements(elms_2);
        n1 = Domain1.getOrder();
        n2 = Domain2.getOrder();
        bool valid = true;
        _operationalMap.clear();
        for(int i = 0; i < n1; i++)
        {
            for(int j = 0; j < n2; j++)
            {
                if(operationalMap.find(std::make_tuple(elms_1[i], elms_2[j])) == operationalMap.end())
                {
                    valid = false;
                    break;
                }
                else if(!(operationalMap[std::make_tuple(elms_1[i], elms_2[j])] < CoDomain))
                {
                    valid = false;
                    break;
                }
            }
            if(!valid)
            {
                break;
            }
        }
        if(valid)
        {
            _operationalMap = operationalMap;
            operate = std::bind(_operate_map, ph::_1, ph::_2);
        }
        delete[] elms_1;
        delete[] elms_2;
    }

};
#endif