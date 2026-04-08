#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP
#include <cstddef>
#include <stdexcept>

namespace knk {
  template< class T >
  class Vector {
   public:
    Vector();
    ~Vector();
    Vector(const Vector< T >& rhs);
    Vector< T >& operator=(const Vector< T >& rhs) = delete;
    Vector(size_t size, const T& value);
    explicit Vector(size_t size);

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    void pushBack(const T&);
    void popBack();
    size_t getCapacity() const noexcept;

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

   private:
    T* data_;
    size_t size_, capacity_;
  };
}

template< class T >
knk::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
  {
    for (size_t i = 0; i < rhs.getSize(); ++i) {
      data_[i] = rhs.data_[i];
    }
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
    data_[i] = value;
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

template< class T >
void knk::Vector< T >::pushBack(const T& rhs) {
  if (size_ >= capacity_) {
    size_t newCapacity = (capacity_ == 0) ? 1 : capacity_ * 2;
    T* newData = new T[newCapacity];
    try {
      for (size_t i = 0; i < size_; ++i) {
        newData[size_] = rhs;
      }
    } catch (...) {
      delete[] newData;
      throw;
    }
    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
  }
  data_[size_++] = rhs;
}


template< class T >
void knk::Vector< T >::popBack() {
  if (size_) {
    --size_;
  }
}

template< class T >
size_t knk::Vector< T >::getCapacity() const noexcept {
  return capacity_;
}

template< class T >
T& knk::Vector< T >::at(size_t id) {
  const Vector< T >* cthis = this;
  const T& cr = cthis->at(id);
  T& r = const_cast< T& >(cr);
  return r;
}

template< class T >
const T& knk::Vector< T >::at(size_t id) const {
  if (id < getSize()) {
    return (*this)[id];
  }
  throw std::out_of_range("id out of bound");
}

//дописать тесты
template< class T > 
const T& knk::Vector< T >::operator[](size_t id) const noexcept {
  return data_[id];
}

//дописать тесты
template< class T > 
T& knk::Vector< T >::operator[](size_t id) noexcept {
  return const_cast< T >((*static_cast< const Vector< T >* >(this))[id]);
}

#endif
