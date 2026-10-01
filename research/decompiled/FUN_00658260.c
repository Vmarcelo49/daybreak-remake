// Function: FUN_00658260
// Address:  0x00658260
// Source:   batch_decompile (mass dump)
// Hash:     15b1cd04c6e27f00


undefined4 __thiscall FUN_00658260(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  *param_1 = param_2;
  param_1[1] = param_3;
  if (param_1[2] == 0) {
    iVar2 = DirectInput8Create(param_1[1],0x800,&DAT_006ab944,param_1 + 2,0);
    if (iVar2 < 0) {
      FUN_006583f0(&DAT_006aacfc);
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

