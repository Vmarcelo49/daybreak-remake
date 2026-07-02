// ============================================
// Address:  0x0065a260
// Original: FUN_0065a260
// Status:   unreviewed
// ============================================


void __thiscall FUN_0065a260(int param_1,undefined4 param_2,undefined4 *param_3,char param_4)

{
  char cVar1;
  undefined4 *puVar2;
  uint uVar3;
  
  cVar1 = FUN_0064d6e0();
  if (cVar1 == '\0') {
    if (param_4 == '\0') {
      puVar2 = (undefined4 *)FUN_0065a850(param_2);
      FUN_00667d90(*puVar2);
      FUN_00667ed0(0);
      uVar3 = *(int *)(param_1 + 0x3e0) + 1U & 0x8000001f;
      if ((int)uVar3 < 0) {
        uVar3 = (uVar3 - 1 | 0xffffffe0) + 1;
      }
      *(uint *)(param_1 + 0x3e0) = uVar3;
    }
    else {
      puVar2 = (undefined4 *)FUN_0065a850(param_2);
      FUN_00667860(*puVar2);
      FUN_006677f0(*param_3,param_3[1],param_3[2]);
      FUN_00667ed0(0);
      uVar3 = *(int *)(param_1 + 0x3e4) + 1U & 0x8000001f;
      if ((int)uVar3 < 0) {
        uVar3 = (uVar3 - 1 | 0xffffffe0) + 1;
      }
      *(uint *)(param_1 + 0x3e4) = uVar3;
    }
  }
  return;
}

