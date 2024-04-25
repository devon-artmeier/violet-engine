#ifndef VIOLET_ENGINE_TYPES_HPP
#define VIOLET_ENGINE_TYPES_HPP

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace Violet
{
    typedef unsigned char       uchar;
    typedef signed char         schar;
    typedef unsigned short      ushort;
    typedef unsigned int        uint;
    typedef unsigned long       ulong;
    typedef long long           longlong;
    typedef unsigned long long  ulonglong;
    
    template<typename T>
    class Pointer
    {
        public:
            Pointer(T* raw_pointer)
            {
                this->raw_pointer = raw_pointer;
                if (raw_pointer != nullptr) {
                    this->reference = new Reference();
                    this->reference->Add();
                }
            }
        
            Pointer(const Pointer<T>& other)
            {
                this->CopyPointer(other);
            }
            
            ~Pointer()
            {
                this->RemoveReference();
            }

            T* Raw() const
            {
                return this->raw_pointer;
            }
        
            T& operator*() const
            {
                return *this->raw_pointer;
            }
            
            T* operator->() const
            {
                return this->raw_pointer;
            }
            
            Pointer<T>& operator=(T* other)
            {
                this->RemoveReference();
                this->raw_pointer = other;
                if (other != nullptr) {
                    this->reference = new Reference();
                    this->reference->Add();
                } else {
                    this->reference = nullptr;
                }
                return *this;
            }
            
            Pointer<T>& operator=(const Pointer<T>& other)
            {
                if (this != &other) {
                    this->RemoveReference();
                    this->CopyPointer(other);
                }
                return *this;
            }
            
            bool operator==(const Pointer<T>& other) const
            {
                return this->raw_pointer == other.raw_pointer;
            }
            
            bool operator!=(const Pointer<T>& other) const
            {
                return this->raw_pointer != other.raw_pointer;
            }
            
            bool operator<=(const Pointer<T>& other) const
            {
                return this->raw_pointer <= other.raw_pointer;
            }
            
            bool operator>=(const Pointer<T>& other) const
            {
                return this->raw_pointer >= other.raw_pointer;
            }
            
            bool operator<(const Pointer<T>& other) const
            {
                return this->raw_pointer < other.raw_pointer;
            }
            
            bool operator>(const Pointer<T>& other) const
            {
                return this->raw_pointer > other.raw_pointer;
            }
            
            bool operator==(const void* const other) const
            {
                return this->raw_pointer == other;
            }
            
            bool operator!=(const void* const other) const
            {
                return this->raw_pointer != other;
            }
            
            bool operator<=(const void* const other) const
            {
                return this->raw_pointer <= other;
            }
            
            bool operator>=(const void* const other) const
            {
                return this->raw_pointer >= other;
            }
            
            bool operator<(const void* const other) const
            {
                return this->raw_pointer < other;
            }
            
            bool operator>(const void* const other) const
            {
                return this->raw_pointer > other;
            }
            
            Pointer<T>& operator++()
            {
                this->raw_pointer++;
                return *this;
            }
            
            Pointer<T> operator++(int)
            {
                Pointer<T> old = *this;
                this->raw_pointer++;
                return old;
            }
            
            Pointer<T>& operator--()
            {
                this->raw_pointer--;
                return *this;
            }
            
            Pointer<T> operator--(int)
            {
                Pointer<T> old = *this;
                this->raw_pointer--;
                return old;
            }
            
            Pointer<T>& operator+=(const size_t offset)
            {
                this->raw_pointer += offset;
                return *this;
            }
            
            Pointer<T>& operator-=(const size_t offset)
            {
                this->raw_pointer -= offset;
                return *this;
            }
            
            T& operator[](const size_t index)
            {
                return this->raw_pointer[index];
            }
            
            const T& operator[](const size_t index) const
            {
                return this->raw_pointer[index];
            }
        
        private:
            class Reference
            {
                public:
                    uint GetCount() { return this->count; }
                    void Add     () { this->count++; }
                    void Remove  () { this->count--; }
                
                private:
                    uint count{ 0 };
            };

            void CopyPointer(const Pointer<T>& other)
            {
                this->raw_pointer = other.raw_pointer;
                this->reference   = other.reference;
                if (other.reference != nullptr) {
                    this->reference->Add();
                }
            }
            
            void RemoveReference()
            {
                if (this->reference != nullptr) {
                    this->reference->Remove();
                    if (this->reference->GetCount() == 0) {
                        delete this->raw_pointer;
                        delete this->reference;
                    }
                }
            }
            
            T*         raw_pointer{ nullptr };
            Reference* reference  { nullptr };
    };
}

#endif // VIOLET_ENGINE_TYPES_HPP