// Function: write_multi_char
// Address:  0x006722d9
// Reason:   keyword:char


/* Library Function - Single Match
    _write_multi_char
   
   Library: Visual Studio 2003 Release */

void __cdecl write_multi_char(undefined4 param_1,int param_2)

{
  int *in_EAX;
  
  do {
    if (param_2 < 1) {
      return;
    }
    param_2 = param_2 + -1;
    write_char();
  } while (*in_EAX != -1);
  return;
}

