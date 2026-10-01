// Function: FUN_00692f40
// Address:  0x00692f40
// Source:   batch_decompile (mass dump)
// Hash:     88ef0b0ffe10a431


undefined4 FUN_00692f40(int *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = Ordinal_2(param_2);
  *param_1 = iVar1;
  if (*param_1 == 0) {
    uVar2 = 0x8007000e;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

