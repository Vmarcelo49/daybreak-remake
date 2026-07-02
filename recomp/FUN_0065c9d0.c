// ============================================
// Address:  0x0065c9d0
// Original: FUN_0065c9d0
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_0065c9d0(int param_1)

{
  int iVar1;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  if (*(int *)(param_1 + 0x20) != 0) {
    do {
      iVar1 = (**(code **)(**(int **)(param_1 + 0x20) + 0x20))
                        (*(undefined4 *)(param_1 + 0x20),&local_10,&local_8,&local_c,0);
      if (iVar1 < 0) {
        return 1;
      }
      (**(code **)(**(int **)(param_1 + 0x20) + 0x30))
                (*(undefined4 *)(param_1 + 0x20),local_10,local_8,local_c);
    } while (local_10 != 1);
  }
  return 0;
}

