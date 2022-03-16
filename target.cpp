#include <iostream>
#include <Windows.h>

#define char_len 128

using namespace std;

template<class T> 
void printVar(string prefix, T &var) {
  cout << prefix << " (" << &var << hex << uppercase << ") = " << dec << var << endl;
}

int main() {
  int varInt = 123456;
  string varString = "DefaultString";
  char varChar[char_len] = "Long char array right there ->";

  int* ptr2int = &varInt;
  int** ptr2ptr = &ptr2int;
  int*** ptr2ptr2 = &ptr2ptr;

  while(true) {
    cout << string(30, '-') << endl;
    cout << "Process ID: " << GetCurrentProcessId() << endl;
    cout << string(30, '-') << endl;
    printVar("varInt", varInt);
    printVar("varString", varString);
    printVar("varChar", varChar);
    cout << string(10, '-') << endl;
    printVar("ptr2int", ptr2int);
    printVar("ptr2ptr", ptr2ptr);
    printVar("ptr2ptr2", ptr2ptr2);

    cout << "Press ENTER to print again!" << endl;
    cout << string(30, '-') << endl;
    system("pause > null");
  }

  return 0; 
}