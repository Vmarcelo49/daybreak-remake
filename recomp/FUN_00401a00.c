// ============================================
// Address:  0x00401a00
// Original: FUN_00401a00
// Status:   unreviewed
// ============================================


void __thiscall FUN_00401a00(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < 8; local_8 = local_8 + 1) {
    if (*(int *)(param_1 + local_8 * 4) != 0) {
      uVar1 = FUN_0064ecb0();
      FUN_00401a60(param_2,param_3,uVar1);
    }
  }
  return;
}

