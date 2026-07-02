// ============================================
// Address:  0x00686920
// Original: FUN_00686920
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_00686920(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_00687190(param_1,param_2);
  if ((((iVar1 == 1) && (iVar1 = FUN_00687190(param_1 + 0x10,param_2 + 0x10), iVar1 == 1)) &&
      (iVar1 = FUN_00687190(param_1 + 0x2c,param_2 + 0x2c), iVar1 == 1)) &&
     ((*(int *)(param_1 + 0x40) == *(int *)(param_2 + 0x40) &&
      ((*(int *)(param_1 + 0x40) == 0 ||
       (iVar1 = _memcmp(*(void **)(param_1 + 0x44),*(void **)(param_2 + 0x44),
                        *(size_t *)(param_1 + 0x40)), iVar1 == 0)))))) {
    return 1;
  }
  return 0;
}

