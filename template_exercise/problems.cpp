#include <iostream>

template<class T, class S>
struct is_same {
  static const bool value = false;
};

template <class T>
struct is_same<T, T> {
  static const bool value = true;
};

template <class T>
struct is_array {
  static const bool value = false;
};

template <class T, int S>
struct is_array<T[S]> {
  static const bool value = true;
};


/* Are Equal A and B: equal(A, B) {return !(A-B);} */

template <int T, int S>
struct equal {
  static const bool value = false;
};

template <int T>
struct equal<T, T> {
  static const bool value = true;
};


template <class T>
struct is_pointer {
  static const bool value = false;
};

template <class T>
struct is_pointer<T*> {
  static const bool value = true;
};

template <class T>
struct is_pointer<T[]> {
  static const bool value = true;
};


template<bool, int A, int B>
struct helper_max {
  static const int value = A;
};

template<true, int A, int B>
struct helper_max {
  static const int value = A;
};

template<false, int A, int B>
struct helper_max {
  static const int value = B;
};

template <int A, int B>
struct get_max {
  static const int value = helper_max< A>B, A, B>::value;
}


int main() {
  std::cout << "is_same<int, int>: " << is_same<int, int>::value << std::endl;
  std::cout << "is_same<int, long>: " << is_same<int, long>::value << std::endl;

  std::cout << "is_array<int>: " << is_array<int>::value << std::endl;
  std::cout << "is_array<int[15]>: " << is_array<int[15]>::value << std::endl;

  std::cout << "equal<4, 5>: " << equal<4, 5>::value << std::endl;
  std::cout << "equal<5, 5>: " << equal<5, 5>::value << std::endl;

  std::cout << "is_pointer<int>: " << is_pointer<int>::value << std::endl;
  std::cout << "is_pointer<int*>: " << is_pointer<int*>::value << std::endl;
  std::cout << "is_pointer<int[]>: " << is_pointer<int[]>::value << std::endl;

  return 0;
}