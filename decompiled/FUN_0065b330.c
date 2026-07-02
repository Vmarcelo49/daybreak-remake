// Function: FUN_0065b330
// Address:  0x0065b330
// Source:   batch_decompile (mass dump)
// Hash:     f46387f4288b0c65


void __thiscall FUN_0065b330(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  undefined4 *puVar5;
  
  cVar1 = FUN_0064d6e0();
  if (cVar1 != '\0') {
    return;
  }
  if ((param_3 - *(char *)(param_1 + 0x58) < *(int *)(param_1 + 0x54)) &&
     (iVar2 = FUN_0068de10(), iVar2 != 0)) {
    if (*(char *)(param_1 + 0x50) == '\0') {
      uVar3 = FUN_00667f50();
      piVar4 = (int *)FUN_0065a850(*(undefined4 *)(param_1 + 0x4c));
      if (uVar3 < *(uint *)(*piVar4 + 0x18)) {
        return;
      }
    }
    else {
      uVar3 = FUN_00667f50();
      piVar4 = (int *)FUN_0065a850(*(undefined4 *)(param_1 + 0x4c));
      if (uVar3 < *(uint *)(*piVar4 + 0x18)) {
        return;
      }
    }
  }
  FUN_00667f20();
  puVar5 = (undefined4 *)FUN_0065a850(param_2);
  FUN_00667d90(*puVar5);
  FUN_00667ed0(0);
  *(int *)(param_1 + 0x54) = param_3;
  *(undefined4 *)(param_1 + 0x4c) = param_2;
  *(undefined1 *)(param_1 + 0x50) = 0;
  return;
}

