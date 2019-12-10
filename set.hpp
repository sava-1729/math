#include <vector>

template <class ElementType>
class Set
{
    ElementType* _elements;
    int _order;

    public:

    Set(ElementType* elms_, int order_)
    {
        if(_order > 0)
        {
            this -> _order = order_;
            _elements = new ElementType[_order];
            for(int i = 0; i < _order; i++)
            {
                _elements[i] = elms[i];
            }
        }
        else
        {
            this -> _order = 0;
            _elements = new ElementType[_order];
        }
    }
    
    const void getAll_elements(ElementType* &external_list)const
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
        A.getAll_elements(a_elms);
        getAll_elements(b_elms);
        na = A.getOrder();
        nb = this -> getOrder();
        if(na > nb)
        {
            int y = na;
            na = nb;
            nb = y;
            ElementType* c;
            c = a_elms;
            a_elms = b_elms;
            b_elms = c;
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
        delete intersec_list;
        return intersection;
    }
};

// template <class ElementType>
// Set<ElementType> operator&(Set<ElementType> A, Set<ElementType> B)
// {
//     ElementType* a_elms, b_elms;
//     int na, nb;
//     A.getAll_elements(a_elms);
//     B.getAll_elements(b_elms);
//     na = A.getOrder();
//     nb = B.getOrder();
    
// }