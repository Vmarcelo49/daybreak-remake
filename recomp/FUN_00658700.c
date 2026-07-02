// ============================================
// Address:  0x00658700
// Original: FUN_00658700
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_00658700(int param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  
  if (param_2 < (int)(uint)*(byte *)(param_1 + 0x120)) {
    puVar1 = (undefined4 *)FUN_00658a10(param_2);
    uVar2 = *puVar1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

