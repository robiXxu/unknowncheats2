#include <iostream>
#include <Windows.h>
#include <numeric>
#include <vector>

#define char_len 128

using namespace std;

uintptr_t findAddr(HANDLE handle, uintptr_t ptr, vector<unsigned int> offsets){
  for(unsigned int i = 0; i < offsets.size(); i++) {
    const uintptr_t prevBaseAddr = ptr;
    ReadProcessMemory(handle, (BYTE*)ptr, &ptr, sizeof(ptr), 0);
    cout << "Reading from " << uppercase << hex << prevBaseAddr << " + " << offsets[i] << " = " << ptr <<  endl;
    ptr += offsets[i];
  }
  return ptr;
}

template<class T>
void readValue(HANDLE handle, uintptr_t address, T &var) {
  BOOL readProcReturn = ReadProcessMemory(handle, (LPCVOID)address, &var, (SIZE_T)sizeof(var), NULL);
  if(readProcReturn == FALSE) {
    cout << "ReadProcMemory failed -- " << dec << GetLastError() << endl;
    system("pause");
  }
}

int main() {

  int pid = 11260;

  HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
  if(handle == NULL) {
    cout << "OpenProcess failed -- " << dec << GetLastError() << endl;
    system("pause");
    return EXIT_FAILURE;
  }

  uintptr_t varIntAddr = findAddr(handle, (uintptr_t)0x7dc1bff758, { 0x00, 0x00, 0x00 });
  cout << "varIntAddr starting from ptr2ptr2: " << uppercase << hex << varIntAddr << endl;

  int intRead = 0;
  readValue<int>(handle, varIntAddr, intRead);
  cout << "intRead value : " << dec << intRead << endl;


  char arrRead[char_len];
  readValue<char[char_len]>(handle, (uintptr_t)0x7dc1bff770, arrRead);
  cout << "arrRead value: " << arrRead << endl;

  string stringRead = "";
  readValue<string>(handle, (uintptr_t)0x7dc1bff7f0, stringRead);
  cout << "stringRead value : " << stringRead << endl;


  BOOL closeHandleReturn = CloseHandle(handle);
  if(closeHandleReturn == FALSE) {
    cout << "CloseHandle failed -- " << dec << GetLastError() << endl;
    system("pause");
    return EXIT_FAILURE;
  }

  return 0;
}