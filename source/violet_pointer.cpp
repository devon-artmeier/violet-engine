#include "violet_types.hpp"

namespace Violet
{
    uint PointerReference::GetCount()
    {
        return this->count;
    }
    
    void PointerReference::Add()
    {
        this->count++;
    }
    
    void PointerReference::Remove()
    {
        this->count--;
    }
}