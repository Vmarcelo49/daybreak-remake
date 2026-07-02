// Function: FUN_00646b00
// Address:  0x00646b00
// Source:   batch_decompile (mass dump)
// Hash:     cbca5f38166d4315


void __thiscall FUN_00646b00(int param_1,float param_2,float param_3)

{
  int iVar1;
  undefined4 uVar2;
  float fVar3;
  float fVar4;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_8;
  
  iVar1 = FUN_0068de10();
  if (iVar1 != 0) {
    FUN_00655d60(param_2 + 48.0,param_3 + 13.0);
    iVar1 = *(int *)(param_1 + 0x1278);
    local_8 = iVar1 + -8;
    if (local_8 < 0) {
      local_8 = 0;
    }
    local_14 = 0;
    for (local_10 = local_8; local_10 < iVar1; local_10 = local_10 + 1) {
      fVar4 = (float)local_14 * 32.0 + param_3;
      fVar3 = param_2;
      uVar2 = FUN_00647310(local_10);
      FUN_00646db0(uVar2,fVar3,fVar4);
      local_14 = local_14 + 1;
    }
  }
  return;
}

