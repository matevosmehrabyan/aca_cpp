#include <iostream>
#include <vector>
#include <string>

template <class T>
void print(const std::vector<T>& elements) {
  std::cout << "[";
  for (unsigned i = 0; i < elements.size(); i++) {
    std::cout << elements[i];
    if (i != elements.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]" << std::endl;
}

template <>
void print<std::string>(const std::vector<std::string>& elements) {
  std::cout << "[";
  for (unsigned i = 0; i < elements.size(); i++) {
    std::cout << "\"" << elements[i] << "\"";
    if (i != elements.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]" << std::endl;
}

template <>
void print<char>(const std::vector<char>& elements) {
  std::cout << "[";
  for (unsigned i = 0; i < elements.size(); i++) {
    std::cout << "'" << elements[i] << "'";
    if (i != elements.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]" << std::endl;
}


template <class T, class R>
void print(const std::vector<std::pair<T, R>>& elements) {
  std::cout << "[";
  for (unsigned i = 0; i < elements.size(); i++) {
    std::cout << "(" << elements[i].first << ":" << elements[i].second << ")";
    if (i != elements.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]" << std::endl;
}


int main() {
  std::vector<int> ints = {10, 20, 30, 40};
  std::cout << "print int: ";
  print(ints);

  std::vector<std::string> strings = {"Hello", "C++", "Templates"};
  std::cout << "print strings: ";
  print(strings);

  std::vector<char> chars = {'a', 'b', 'c', 'd'};
  std::cout << "print chars: ";
  print(chars);

  std::vector<std::pair<std::string, int>> pairs = {{"help", 1}, {"me", 2}, {"please", 3}};
  std::cout << "print pairs: ";
  print(pairs);

  return 0;
}