// ============================================
// Address:  0x0068f0b0
// Original: FUN_0068f0b0
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_0068f0b0(int *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  
  if (param_1[0x2b] != 0) {
    (**(code **)(*(int *)param_1[0x2b] + 8))(param_1[0x2b]);
    param_1[0x2b] = 0;
  }
  iVar2 = FUN_0068da80();
  if (iVar2 == 0) {
    uVar3 = 1;
  }
  else {
    if ((param_1[5] != 0) && (cVar1 = FUN_00691a60(), cVar1 == '\0')) {
      return 0x80040224;
    }
    FUN_0068fde0(0);
    (**(code **)(*param_1 + 100))();
    (**(code **)(*param_1 + 0x70))();
    param_1[0x18] = 0;
    if (param_1[5] == 2) {
      (**(code **)(*param_1 + 0x80))();
    }
    uVar3 = 0;
  }
  return uVar3;
}

