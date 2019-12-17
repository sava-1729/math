#ifndef BINARY_OPERATION_HPP
#define BINARY_OPERATION_HPP

#include <map>
#include <functional>
#include <tuple>
#include "set.hpp"

namespace ph = std::placeholders;
template<typename type1, typename type2, typename type3, typename T = FiniteSet<type3>>
class BinaryOperation
{
    std::map<std::tuple<type1,type2>, type3> _operationalMap;

    type3 _operate_map(type1 operand1, type2 operand2)
    {
        return _operationalMap[std::make_tuple(operand1, operand2)];
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
            FiniteSet<std::tuple<type1, type2>> cross = cartesianProduct(Domain1, Domain2);
            std::tuple<type1, type2> *elms;
            int n;
            cross.getAllElements(elms);
            n = cross.getOrder();
            _operationalMap.clear();
            for(int i = 0; i < n; i++)
            {
                type1 op1 = std::get<0>(elms[i]);
                type2 op2 = std::get<1>(elms[i]);
                type3 result = operator_fnc(op1, op2);
                _operationalMap[std::make_tuple(op1, op2)] = result;
            }
            operate = std::bind(&BinaryOperation::_operate_map, this, ph::_1, ph::_2);
            delete[] elms;
        }
    }

    BinaryOperation(FiniteSet<type1> Domain1, FiniteSet<type2> Domain2, FiniteSet<type3> CoDomain, \
                    T *object, type3 (T::*operator_fnc)(type1, type2), bool dynamic_op = false)
    {
        if(dynamic_op)
        {
            operate = std::bind(operator_fnc, object, ph::_1, ph::_2);
        }
        else
        {
            FiniteSet<std::tuple<type1, type2>> cross = cartesianProduct(Domain1, Domain2);
            std::tuple<type1, type2> *elms;
            int n;
            cross.getAllElements(elms);
            n = cross.getOrder();
            _operationalMap.clear();
            for(int i = 0; i < n; i++)
            {
                type1 op1 = std::get<0>(elms[i]);
                type2 op2 = std::get<1>(elms[i]);
                type3 result = (object ->* operator_fnc)(op1, op2);
                _operationalMap[std::make_tuple(op1, op2)] = result;
            }
            operate = std::bind(&BinaryOperation::_operate_map, this, ph::_1, ph::_2);
            delete[] elms;
        }
    }

    BinaryOperation(FiniteSet<type1> Domain1, FiniteSet<type2> Domain2, FiniteSet<type3> CoDomain, \
                    std::map<std::tuple<type1,type2>, type3> operationalMap)
    {
        FiniteSet<std::tuple<type1, type2>> cross = cartesianProduct(Domain1, Domain2);
        std::tuple<type1, type2> *elms;
        int n;
        cross.getAllElements(elms);
        n = cross.getOrder();
        bool valid = true;
        _operationalMap.clear();
        for(int i = 0; i < n; i++)
        {
            type1 op1 = std::get<0>(elms[i]);
            type2 op2 = std::get<1>(elms[i]);
            if(operationalMap.find(std::make_tuple(op1, op2)) == operationalMap.end())
            {
                valid = false;
                break;
            }
            else if(!(operationalMap[std::make_tuple(op1, op2)] < CoDomain))
            {
                valid = false;
                break;
            }
        }
        if(valid)
        {
            _operationalMap = operationalMap;
            operate = std::bind(&BinaryOperation::_operate_map, this, ph::_1, ph::_2);
        }
        delete[] elms;
    }

};
#endif