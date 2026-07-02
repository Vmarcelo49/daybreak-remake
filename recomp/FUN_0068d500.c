// ============================================
// Address:  0x0068d500
// Original: FUN_0068d500
// Status:   unreviewed
// ============================================


void __fastcall FUN_0068d500(int param_1)

{
  int *piVar1;
  
  while (piVar1 = (int *)FUN_0068dca0(), piVar1 != (int *)0x0) {
    if (piVar1 != (int *)0x0) {
      (**(code **)(*piVar1 + 0x54))(1);
    }
  }
  *(undefined4 *)(param_1 + 0x3c) = 0;
  if (*(int *)(param_1 + 0x60) != 0) {
    VirtualFree(*(LPVOID *)(param_1 + 0x60),0,0x8000);
    *(undefined4 *)(param_1 + 0x60) = 0;
  }
  return;
}

