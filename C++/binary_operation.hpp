/*
 * @file binary_operation.hpp
 * @brief contains a class representing a generic binary operation
 * @author Vatsal Srivastava
 * @copyright (c) 2019
 */

#ifndef BINARY_OPERATION_HPP
#define BINARY_OPERATION_HPP

#include <map>
#include <functional>
#include <tuple>
#include <sstream>
#include "finite_set.hpp"

namespace ph = std::placeholders;

/**
 * @class BinaryOperation
 * @brief A generic base class representing a binary operation, i.e., a 
 *        mathematical function which takes in two elements as input and gives an output.         
 * @detail There are broadly two ways in which an object of this class can be used.
 *         (a) As a static map: This way, the result of any operation is PREDETERMINED,
 *                              and stored as a map.
 *         (b) As an active function: This way, the result of any operation is determined
 *                                    dynamically at runtime.
 * @tparam type1: datatype of the left operand
 * @tparam type2: datatype of the right operand
 * @tparam type3: datatype of the output
 * @tparam X: class of which operator_fnc (constructor parameter) is a member function
 */
template<typename type1, typename type2 = type1, typename type3 = type1, typename X = FiniteSet<type3>>
class BinaryOperation
{
    std::map<std::tuple<type1,type2>, type3> _operationalMap;
    //^ a map that stores the result of all possible operations, if this 
    //  static mode is being used.

    /**
     * @fn _operate_static_map
     * @brief this is a private helper function, that takes in two operands,
     *        and returns the predetermined result of the binary operation
     *        as stored in the _operationalMap
     * @param operand1: the left operand
     * @param operand2: the right operand
     */
    type3 _operate_static_map(type1 operand1, type2 operand2)
    {
        return _operationalMap[std::make_tuple(operand1, operand2)];
    }

    public:
    /**
     * @fn_obj operate
     * @brief this is the main operate function which is defined according to
     *        the mode ((a) or (b) in the @detail of the class) in which the class
     *        is being used. This should be called whenever a binary operation has
     *        to be computed.
     * @detail for eg, if this class is instantiated using constructor_3, then this
     *        function will be bound to _operate_static map, using std::bind.
     */
    std::function<type3(type1, type2)> operate;

    /**
     * @constructor_1
     * @brief This constructor should be used if the user wants their own static function to
     *        compute the result of the binary operation. Domain1, Domain2 and CoDomain must
     *        all be FiniteSets
     * @param Domain1: the domain of the left operand
     * @param Domain2: the domain of the right operand
     * @param CoDomain: the CoDomain of the binary operation
     * @param operator_fnc: the user function which will be used to compute the result of the operation
     * @param dynamic_op: an optional flag
     *                    If TRUE, the operate function is bound to operator_fnc, i.e., whenever operate
     *                    function is called during runtime, it will sort of patch the call to the user specified operator_fnc,
     *                    and consequently that will be called 
     *                    If FALSE, the result of all possible operations will be pre determined and stored in the
     *                    _operationalMap above. And, the operate function will be bound to the _operate_static_map, i.e.,
     *                    whenever the operate function is called during runtime, it will patch the call to _operate_static_map.
     */
    BinaryOperation(FiniteSet<type1> Domain1, FiniteSet<type2> Domain2, FiniteSet<type3> CoDomain, \
                    type3 (*operator_fnc)(type1, type2), bool dynamic_op = false);

    /**
     * @constructor_2
     * @brief This constructor should be used if the user wants a member function of a class to
     *        compute the result of the binary operation. Domain1, Domain2 and CoDomain must
     *        all be FiniteSets
     * @param Domain1: the domain of the left operand
     * @param Domain2: the domain of the right operand
     * @param CoDomain: the CoDomain of the binary operation
     * @param object: the object of the class on which operator_fnc must be called
     * @param operator_fnc: the user function which will be used to compute the result of the operation
     * @param dynamic_op: same as in constructor_1
     */
    BinaryOperation(FiniteSet<type1> Domain1, FiniteSet<type2> Domain2, FiniteSet<type3> CoDomain, \
                    X *object, type3 (X::*operator_fnc)(type1, type2), bool dynamic_op = false);

    /**
     * @constructor_3
     * @brief This constructor should be used if the user wants to specify the whole map, i.e., every
     *        possible result of the binary operation. Domain1, Domain2 and CoDomain must
     *        all be FiniteSets
     * @param Domain1: the domain of the left operand
     * @param Domain2: the domain of the right operand
     * @param CoDomain: the CoDomain of the binary operation
     * @param operationalMap: the map from all possible pairs of operands to the result of binary operation on them.
     */
    BinaryOperation(FiniteSet<type1> Domain1, FiniteSet<type2> Domain2, FiniteSet<type3> CoDomain, \
                    std::map<std::tuple<type1,type2>, type3> operationalMap);

    /**
     * @constructor_4
     * @brief This constructor should be used if the user wants their own static function to
     *        compute the result of the binary operation.
     * @param operator_fnc: the user function which will be used to compute the result of the operation
     */
    BinaryOperation(type3 (*operator_fnc)(type1, type2))
    {
        operate = std::bind(operator_fnc, ph::_1, ph::_2);
    }

    /**
     * @constructor_5
     * @brief This constructor should be used if the user wants a member function of a class to
     *        compute the result of the binary operation.
     * @param object: the object of the class on which operator_fnc must be called
     * @param operator_fnc: the user function which will be used to compute the result of the operation
     */
    BinaryOperation(X *object, type3 (X::*operator_fnc)(type1, type2))
    {
        operate = std::bind(operator_fnc, object, ph::_1, ph::_2);
    }
};

template<typename type1, typename type2, typename type3, typename X>
BinaryOperation<type1, type2, type3, X>:: \
    BinaryOperation(FiniteSet<type1> Domain1, FiniteSet<type2> Domain2, FiniteSet<type3> CoDomain, \
                        type3 (*operator_fnc)(type1, type2), bool dynamic_op)
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
            if(CoDomain.contains(result))
            {
                _operationalMap[std::make_tuple(op1, op2)] = result;
            }
            else
            {
                std::stringstream error_msg;
                error_msg << "(" << op1 << " * " << op2 << ") does not belong to " << CoDomain;
                throw std::invalid_argument(error_msg);
            }
        }
        operate = std::bind(&BinaryOperation::_operate_static_map, this, ph::_1, ph::_2);
        delete[] elms;
    }
}

template<typename type1, typename type2, typename type3, typename X>
BinaryOperation<type1, type2, type3, X>:: \
    BinaryOperation(FiniteSet<type1> Domain1, FiniteSet<type2> Domain2, FiniteSet<type3> CoDomain, \
                        X *object, type3 (X::*operator_fnc)(type1, type2), bool dynamic_op)
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
        operate = std::bind(&BinaryOperation::_operate_static_map, this, ph::_1, ph::_2);
        delete[] elms;
    }
}

template<typename type1, typename type2, typename type3, typename X>
BinaryOperation<type1, type2, type3, X>:: \
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
        operate = std::bind(&BinaryOperation::_operate_static_map, this, ph::_1, ph::_2);
    }
    delete[] elms;
}

#endif
