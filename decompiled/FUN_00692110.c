// Function: FUN_00692110
// Address:  0x00692110
// Source:   batch_decompile (mass dump)
// Hash:     89947544c5506636


undefined4 __thiscall FUN_00692110(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00693350();
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = *(undefined4 *)(param_1 + 0xc);
    }
    uVar2 = 1;
  }
  return uVar2;
}

