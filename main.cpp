#include "pe-vector.hpp"
#include <iostream>
#include <cstring>

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
  constexpr size_t size = 2;
  Vector< int > v(size, 10);
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

bool testCopyConstructor(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  Vector< int > yav = v;
  if (v.isEmpty() && yav.isEmpty()) {
    throw std::logic_error("Vectors expected to be non-empty");
  }
  bool isEqual = yav.getSize() == v.getSize();
  for (size_t i = 0; isEqual && i < v.getSize(); ++i) {
    try {
      isEqual = v.at(i) == yav.at(i);
    } catch (...) {
      return false;
    }
  }
  return isEqual;
}

bool testElementCheckedAccess(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(2);
  try {
    int & r = v.at(0);
    return r == 2; 
  } catch (...) {
    return false;
  }
}

bool testElementCheckedConstAccess(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(2);
  const Vector< int >& rv = v;
  try {
    const int & r = rv.at(0);
    return r == 2; 
  } catch (...) {
    return false;
  }
}

bool testElementCheckedOutOfBoundAccess(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (std::out_of_range& e) {
    const char * text = e.what();
    return !std::strcmp("id out of bound", text);
    return true;
  } catch (...) {
    return false;
  }
}

bool testElementCheckedOutOfBoundConstAccess(const char ** pname) {
  *pname = __func__;
  const Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (std::out_of_range& e) {
    const char * text = e.what();
    return !std::strcmp("id out of bound", text);
  } catch (...) {
    return false;
  }
}

bool testCopyAssignment(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  Vector< int > yav;
  yav.pushBack(1);
  yav.pushBack(2);
  try {
    yav = v;
  } catch (...) {
    return false;
  }
  if (v.isEmpty() || yav.isEmpty()) {
    throw std::logic_error("Vectors must be non-empty");
  }
  bool isEqual = yav.getSize() == v.getSize();
  for (size_t i = 0; isEqual && i < v.getSize(); ++i) {
    try {
      isEqual = v.at(i) == yav.at(i);
    } catch (...) {
      return false;
    }
  }
  return isEqual;
}

bool testMoveAssignment(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  Vector< int > yav;
  yav.pushBack(3);
  yav.pushBack(4);
  yav.pushBack(5);
  yav = std::move(v);
  return yav.getSize() == 2 && yav[0] == 1 && v.isEmpty();
}

bool testMoveConstructor(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  Vector< int > yav = std::move(v);
  return yav.getSize() == 2 && yav[0] == 1 && v.isEmpty();
}

bool testSwap(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  Vector< int > yav;
  yav.pushBack(4);
  yav.pushBack(5);
  v.swap(yav);
  return v.getSize() == 2 && v[0] == 4 && yav.getSize() == 3 && yav[0] == 1;
}

bool testBracketAccess(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v[0] = 10;
  return v[0] == 10 && v[1] == 2;
}

bool testConstBracketAccess(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  const Vector< int > & r = v;
  return r[0] == 1 && r[1] == 2;
}

bool testAtAccess(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.at(0) = 10;
  return v.at(0) == 10 && v.at(1) == 2;
}

bool testConstAtAccess(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  const Vector< int > & r = v;
  return r.at(0) == 1 && r.at(1) == 2;
}

bool testInsert(const char ** pname) {
  *pname = __func__;
  Vector<int> v;
  v.pushBack(10);
  v.pushBack(30);
  try {
    v.insert(1, 20);
    return v.getSize() == 3 && v[0] == 10 && v[1] == 20 && v[2] == 30;
  } catch (...) {
    return false;
  }
}

bool testInsertOutOfRange(const char ** pname) {
  *pname = __func__;
  Vector<int> v(2, 10);
  try {
    v.insert(5, 99);
    return false;
  } catch (const std::out_of_range&) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testInsertRange(const char ** pname) {
  *pname = __func__;
  Vector<int> v;
  v.pushBack(10);
  v.pushBack(50);
  Vector<int> toInsert;
  toInsert.pushBack(20);
  toInsert.pushBack(30);
  toInsert.pushBack(40);
  try {
    v.insert(1, toInsert, 0, 3);
    return v.getSize() == 5 && v[1] == 20 && v[2] == 30 && v[3] == 40;
  } catch (...) {
    return false;
  }
}

bool testErase(const char ** pname) {
  *pname = __func__;
  Vector<int> v;
  for (int i = 0; i < 5; ++i) {
    v.pushBack(i);
  }
  try {
    v.erase(2);
    return v.getSize() == 4 && v[2] == 3;
  } catch (...) {
    return false;
  }
}

bool testEraseOutOfRange(const char ** pname) {
  *pname = __func__;
  Vector<int> v(2, 10);
  try {
    v.erase(5);
    return false;
  } catch (const std::out_of_range&) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testEraseRange(const char ** pname) {
  *pname = __func__;
  Vector<int> v;
  for (int i = 0; i < 10; ++i) {
    v.pushBack(i);
  }
  try {
    v.erase(3, 7);
    return v.getSize() == 6 && v[0] == 0 && v[1] == 1 && v[2] == 2 && v[3] == 7 && v[4] == 8 && v[5] == 9;
  } catch (...) {
    return false;
  }
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
    { testGetCapacityOfEmptyVector, "Capacity of empty vector must be zero" },
    { testElementCheckedAccess, "Inbound access must return lvalue reference to indexed value" },
    { testElementCheckedOutOfBoundAccess, "Out of bound access must generate exception with specific text" },
    { testCopyConstructor, "Copied vector must be equal to original" },
    { testElementCheckedConstAccess, "Same as ElementCheckedAccess, but const" },
    { testElementCheckedOutOfBoundConstAccess, "Same as ElementCheckedOutOfBoundAccess, but const" },
    { testCopyAssignment, "Copy assignment must create equal vector" },
    { testMoveAssignment, "Move assignment must transfer vector" },
    { testMoveConstructor, "Move constructor must transfer vector" },
    { testSwap, "Swap must exchange contents of vectors"},
    { testBracketAccess, "operator[] must return lvalue reference" },
    { testConstBracketAccess, "const operator[] must return const lvalue reference" },
    { testAtAccess, "at() must return reference" },
    { testConstAtAccess, "const at() must return const reference" },
    { testInsert, "Insert must add element at specified position" },
    { testInsertOutOfRange, "Insert out of range must throw exception" },
    { testInsertRange, "Insert range must add multiple elements" },
    { testErase, "Erase must remove element at specified position" },
    { testEraseOutOfRange, "Erase must throw exception when index is out of range" },
    { testEraseRange, "Erase range must remove elements" }
};
  constexpr size_t count = sizeof(tests) / sizeof(case_t);
  size_t failed = 0;
  for (size_t i = 0; i < count; ++i) {
    const char * testName = nullptr;
    bool r = false;
    try {
      r = tests[i].first(&testName);
    } catch (const std::logic_error& e) {
      std::cout << "[NOT RUN]" << testName << "\n";
      std::cout << "\t" << "reason: " << e.what() << "\n";
      ++failed;
      continue;
    }
    if (!r) {
      ++failed;
      std::cout << "[FAIL] " << testName << "\n";
      std:: cout << "\t" << tests[i].second << "\n";
    }
  }
  std::cout << "Summary:\n\t" << (count - failed) << " passed\n";
  std::cout << "\t" << count << " total\n";
}
