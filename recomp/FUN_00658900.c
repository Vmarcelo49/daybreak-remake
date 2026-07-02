// ============================================
// Address:  0x00658900
// Original: FUN_00658900
// Status:   unreviewed
// ============================================


void __thiscall FUN_00658900(int param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  uVar1 = FUN_0064f010();
  uVar2 = FUN_0065aa30();
  if (uVar1 < uVar2) {
    uVar3 = FUN_00654640(*(undefined4 *)(param_1 + 8),1,param_2);
    *(undefined4 *)(param_1 + 8) = uVar3;
  }
  else {
    puVar4 = (undefined4 *)FUN_00654670(local_8);
    FUN_00658bc0(local_c,*puVar4,param_2);
  }
  return;
}

