// ============================================
// Address:  0x00424840
// Original: FUN_00424840
// Status:   unreviewed
// ============================================


void __thiscall FUN_00424840(int param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  uVar1 = FUN_004258e0();
  uVar2 = FUN_004258a0();
  if (uVar1 < uVar2) {
    uVar3 = FUN_00425a90(*(undefined4 *)(param_1 + 8),1,param_2);
    *(undefined4 *)(param_1 + 8) = uVar3;
  }
  else {
    puVar4 = (undefined4 *)FUN_00654670(local_8);
    FUN_00425920(local_c,*puVar4,param_2);
  }
  return;
}

