#include <iostream> // std::cout

/* 
 - This code represent the copy in C = DEEP copy, for which
  different pointres can point to the same object
  but they will own DIFFERENT memory address.
- Instead in PYTHON this is different since 2 objects can own the SAME 
  memory address, so we talk about SHALLOW copy.
*/
int main(){
  int a = 5;
  int b = 5;
  int c;
 
  std::cout << "Working with VARIABLES (always different addresses)" << std::endl;
  std::cout << "&a = " << &a << std::endl;
  std::cout << "&b = " << &b << std::endl;
  std::cout << "&c = " << &c << std::endl;
  std::cout << "--------------------------------------------------------------------------" << std::endl;
  std::cout << " Working with POINTERS"  << std::endl;
  int *d = &a;
  c = a;
  std::cout << "The address of the pointer d is &d = " << &d << std::endl;
  std::cout << "The value of the object pointed by d = " << *d << std::endl;
  std::cout << "--------------------------------------------------------------------------" << std::endl;

  std::cout << "Working with POINTERS pointing to the same object"  << std::endl;
    
  int* x = new int(5);
  int* y = x;
  std::cout << "The value of the object pointed by x = " << *x << std::endl;
  std::cout << "The memory address of the pointer is &x = " << &x << std::endl;

  // Print the memory address of the element to which
  // the pointers are pointing to
  std::cout << "The memory address of the element to which the pointer is pointing to is &*x = " << &*x << std::endl;
  std::cout << "The memory address of the element to which the pointer is pointing to is &*y = " << &*y << std::endl;
  std::cout << "They are equalas expected => they're pointing to the same object" << std::endl;
  return 0;
}
