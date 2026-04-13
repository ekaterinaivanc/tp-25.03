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
    explicit Vector(size_t size);
    Vector(size_t size, const T& value);
  
    Vector(const Vector< T >& rhs); // дописать тесты
    Vector(Vector< T >&& rhs) noexcept; //дописать тесты

    Vector< T >& operator=(const Vector< T >& rhs); //дописать тесты
    Vector< T >& operator=(Vector< T >&& rhs) noexcept; //дописать тесты

    T& operator[](size_t id) noexcept; //дописать тесты
    const T& operator[](size_t id) const noexcept; //дописать тесты

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;
    void pushBack(const T&);
    void popBack();
    void pushFront(const T& v);

    void swap(Vector< T >& rhs) noexcept; //дописать тесты
    T& at(size_t id); //дописать тесты
    const T& at(size_t id) const; //дописать тесты

   private:
    T* data_;
    size_t size_, capacity_;
  };
}

template< class T >
knk::Vector< T >::Vector() :
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T >
knk::Vector< T >::~Vector() {
  delete [] data_;
}

template< class T >
knk::Vector< T >::Vector(size_t size) :
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

//дописать тесты
template< class T >
knk::Vector< T >::Vector(const Vector< T >& rhs):
  Vector(rhs.getSize())
  {
    for (size_t i = 0; i < rhs.getSize(); ++i) {
      data_[i] = rhs.data_[i];
    }
  }

//дописать тесты
template< class T >
knk::Vector< T >::Vector(Vector< T >&& rhs) noexcept:
  Vector() {
    swap(rhs);
  }

template< class T > 
knk::Vector< T >& knk::Vector< T >::operator=(const Vector< T >& rhs) {
  if (this == std::addressof(rhs)) {
    return *this;
  }
  Vector< T > cpy(rhs);
  sawp(cpy);
  return *this;
}

//дописать тесты
template< class T >
knk::Vector< T >& knk::Vector< T >::operator=(Vector< T >&& rhs) noexcept {
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

//дописать тесты
template< class T > 
T& knk::Vector< T >::operator[](size_t id) noexcept {
  return const_cast< T >((*static_cast< const Vector< T >* >(this))[id]);
}

//дописать тесты
template< class T > 
const T& knk::Vector< T >::operator[](size_t id) const noexcept {
  return data_[id];
}

template< class T >
bool knk::Vector< T >::isEmpty() const noexcept {
  return !size_;
}

template< class T >
size_t knk::Vector< T >::getSize() const noexcept {
  return size_;
}

template< class T >
size_t knk::Vector< T >::getCapacity() const noexcept {
  return capacity_;
}

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
void knk::Vector< T >::pushFront(const T& t) {
  Vector< T > v(getSize() + 1);
  v[0] = t;
  for (size_t i = 1; i < v.getSize(); ++i) {
    v[i] = (*this)[i - 1];
  }
  swap(v);
}

//дописать тесты
template< class T >
void knk::Vector< T >::swap(Vector< T >& rhs) noexcept {
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
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

//copy-and-swap + тесты
//void insert(size_t id, const T& t)
//void insert(size_t id, const Vector< T >& rhs, size_t beg, size_t end)
//void erase(size_t id)
//void erase(size_t beg, size_t end)

//итераторы вектора(const и не const, random access (без тестов))
//придумать еще 3 erase insert с итераторами (всего 6) например:
//struct VectorIteraor {}
//template< class FwdIterator >
//void insert(VectorIterator pos, FwdIterator begin, FwdIterator end)

#endif
