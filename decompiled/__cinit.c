// Function: __cinit
// Address:  0x00670fd4
// Reason:   keyword:Init


/* Library Function - Single Match
    __cinit
   
   Library: Visual Studio 2003 Release */

int __cdecl __cinit(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  
  if (PTR___fpmath_006b7800 != (undefined *)0x0) {
    (*(code *)PTR___fpmath_006b7800)(param_1);
  }
  iVar1 = 0;
  puVar2 = &DAT_006b70b0;
  do {
    if (iVar1 != 0) {
      return iVar1;
    }
    if ((code *)*puVar2 != (code *)0x0) {
      iVar1 = (*(code *)*puVar2)();
    }
    puVar2 = puVar2 + 1;
  } while (puVar2 < &DAT_006b70c8);
  if (iVar1 == 0) {
    _atexit((_func_4879 *)&LAB_00671b61);
    puVar2 = &DAT_006b7000;
    do {
      if ((code *)*puVar2 != (code *)0x0) {
        (*(code *)*puVar2)();
      }
      puVar2 = puVar2 + 1;
    } while (puVar2 < &DAT_006b70ac);
    iVar1 = 0;
  }
  return iVar1;
}

