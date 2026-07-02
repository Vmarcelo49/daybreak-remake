// ============================================
// Address:  0x006562c0
// Original: FUN_006562c0
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_006562c0(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  *(undefined4 *)(param_1 + 0x30) = param_2;
  cVar1 = FUN_0064d6e0();
  if (cVar1 == '\0') {
    puVar3 = (undefined4 *)FUN_00656740(param_2);
    uVar2 = *puVar3;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

