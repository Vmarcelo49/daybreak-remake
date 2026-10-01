// Function: _ValidateRead
// Address:  0x00673ab5
// Reason:   keyword:Read


/* Library Function - Single Match
    int __cdecl _ValidateRead(void const *,unsigned int)
   
   Library: Visual Studio 2003 Release */

int __cdecl _ValidateRead(void *param_1,uint param_2)

{
  BOOL BVar1;
  
  BVar1 = IsBadReadPtr(param_1,param_2);
  return (uint)(BVar1 == 0);
}

