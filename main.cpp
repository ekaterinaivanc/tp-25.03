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

bool testPushBackOfVector(const char ** pname) {
  *pname = __func__;
  constexpr size_t size = 2ull;
  Vector< int > v(size, 10);
  v.pushBack(7);
  return v.getSize() == size + 1;
}

bool testPopBackOfVector(const char ** pname) {
  *pname = __func__;
  constexpr size_t size = 2ull;
  Vector< int > v(size, 10);
  v.popBack();
  return v.getSize() == size - 1;
}

bool testGetCapacityOfVector(const char ** pname) {
  *pname = __func__;
  Vector< int > v(5, 10);
  v.pushBack(7);
  return v.getCapacity() == 10;
}

int main() {
  using test_t = bool(*)(const char **);
  using case_t = std::pair< test_t, const char * >;
  case_t tests[] = {
    { testConstructAndDestruct, "Vector must be default constructable" },
    { testDefaultVectorIsEmpty, "Default constructed vector must be empty" },
    { testSizeOfEmptyVector, "Size of empty vector must be zero" },
    { testSizeOfNonEmptyVector, "Size of empty vector must be positive" },
    { testPushBackOfVector, "pushBack must increase size" },
    { testPopBackOfVector, "popBack must decrease size" },
    { testGetCapacityOfVector, "Capacity must double when size" }
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
