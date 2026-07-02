// ============================================
// Address:  0x00686c20
// Original: FUN_00686c20
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_00686c20(int param_1,uint param_2)

{
  LPVOID pvVar1;
  undefined4 uVar2;
  
  if (*(uint *)(param_1 + 0x40) == param_2) {
    uVar2 = *(undefined4 *)(param_1 + 0x44);
  }
  else {
    pvVar1 = CoTaskMemAlloc(param_2);
    if (pvVar1 == (LPVOID)0x0) {
      if (*(uint *)(param_1 + 0x40) < param_2) {
        uVar2 = 0;
      }
      else {
        uVar2 = *(undefined4 *)(param_1 + 0x44);
      }
    }
    else {
      if (*(int *)(param_1 + 0x40) != 0) {
        CoTaskMemFree(*(LPVOID *)(param_1 + 0x44));
      }
      *(uint *)(param_1 + 0x40) = param_2;
      *(LPVOID *)(param_1 + 0x44) = pvVar1;
      uVar2 = *(undefined4 *)(param_1 + 0x44);
    }
  }
  return uVar2;
}

