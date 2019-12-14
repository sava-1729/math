#include <map>
#include <functional>
#include "set.hpp"

namespace ph = std:: placeholders;
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
                    type3 (*operator_fnc)(type1, type2))
    {
        operate = std::bind(operator_fnc, ph::_1, ph::_2);
    }

    template <class T>
    BinaryOperation(FiniteSet<type1> Domain1, FiniteSet<type2> Domain2, FiniteSet<type3> CoDomain, \
                    T *object, type3 (T::*operator_fnc)(type1, type2))
    {
        operate = std::bind(operator_fnc, object, ph::_1, ph::_2);
    }

    BinaryOperation(FiniteSet<type1> Domain1, FiniteSet<type2> Domain2, FiniteSet<type3> CoDomain, \
                    std::map<std::tuple<type1,type2>, type3> operationalMap)
    {
        operate = std::bind(_operate_map, ph::_1, ph::_2);
    }

};