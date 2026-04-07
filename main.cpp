#include "pe-vector.hpp"
#include <iostream>

using   knk::Vector;

bool testConstructAndDestruct(const char ** pname) {
  *pname = __func__;
  knk::Vector< int > v;
  return true;
}

bool testDefaultVectorIsEmpty(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  return v.isEmpty();
}

bool testSizeOfEmptyVector(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  return !v.getSize();
}

bool testSizeOfNonEmptyVector(const char ** pname) {
  *pname = __func__;
  constexpr size_t size = 2ull;
  Vector< int > v(2ull, 10);
  return v.getSize() == size;
}

bool testPushBackOfNoneEmptyVector(const char ** pname) {
  *pname = __func__;
  constexpr size_t size = 2ull;
  Vector< int > v(size, 10);
  v.pushBack(7);
  return v.getSize() == size + 1;
}

bool testPushBackOfEmptyVector(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(7);
  return v.getSize() == 1;
}

bool testPopBackOfNoneEmptyVector(const char ** pname) {
  *pname = __func__;
  constexpr size_t size = 2ull;
  Vector< int > v(size, 10);
  v.popBack();
  return v.getSize() == size - 1;
}

bool testPopBackOfEmptyVector(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.popBack();
  return v.getSize() == 0 && v.isEmpty();
}

bool testGetCapacityOfNoneEmptyVector(const char ** pname) {
  *pname = __func__;
  Vector< int > v(5, 10);
  v.pushBack(7);
  return v.getCapacity() == 10;
}

bool testGetCapacityOfEmptyVector(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  return v.getCapacity() == 0;
}

int main() {
  using test_t = bool(*)(const char **);
  using case_t = std::pair< test_t, const char * >;
  case_t tests[] = {
    { testConstructAndDestruct, "Vector must be default constructable" },
    { testDefaultVectorIsEmpty, "Default constructed vector must be empty" },
    { testSizeOfEmptyVector, "Size of empty vector must be zero" },
    { testSizeOfNonEmptyVector, "Size of empty vector must be positive" },
    { testPushBackOfNoneEmptyVector, "pushBack must increase size" },
    { testPopBackOfNoneEmptyVector, "popBack must decrease size" },
    { testGetCapacityOfNoneEmptyVector, "Capacity must double when size" },
    { testPushBackOfEmptyVector, "pushBack on empty vector must increase size" },
    { testPopBackOfEmptyVector, "popBack on empty vector must do nothing" },
    { testGetCapacityOfEmptyVector, "Capacity of empty vector must be zero" }
};
  constexpr size_t count = sizeof(tests) / sizeof(case_t);
  size_t failed = 0;
  for (size_t i = 0; i < count; ++i) {
    const char * testName = nullptr;
    bool r = tests[i].first(&testName);
    if (!r) {
        ++failed;
      std::cout << "Failed: " << testName << "\n";
      std:: cout << "\t" << tests[i].second << "\n";
    }
  }
  std::cout << "Summary:\n\t" << (count - failed) << " passed\n";
  std::cout << "\t" << count << " total\n";
}
