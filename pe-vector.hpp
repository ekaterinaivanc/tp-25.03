#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <cstddef>

namespace knk {
  template< class T >
  class Vector {
   public:
    Vector();
    ~Vector();
    Vector(const Vector< T >& rhs) = delete;
    Vector< T >& operator=(const Vector< T >& rhs) = delete;
    Vector(size_t size, const T& value);
    explicit Vector(size_t size);

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    void pushBack(const T&); //homework
    void popBack(); //homework
  
   private:
    T* data_;
    size_t size_, capacity_;
  };
}

template< class T >
knk::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}

template< class T >
knk::Vector< T >::Vector(size_t size, const T& value):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i)
  {
    data_[i] value;
  }
}

template< class T >
size_t knk::Vector< T >::getSize() const noexcept {
  return size_;
}

template< class T >
bool knk::Vector< T >::isEmpty() const noexcept {
  return !size_;
}

template< class T >
knk::Vector< T >::~Vector() {
  delete [] data_;
}

template< class T >
knk::Vector< T >::Vector() :
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

#endif
