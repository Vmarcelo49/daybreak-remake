// Function: FUN_00437270
// Address:  0x00437270
// Source:   batch_decompile (mass dump)
// Hash:     809acfa899ac7917


undefined4 * __thiscall FUN_00437270(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  uVar1 = *param_1;
  uVar2 = param_1[1];
  iterator__operator__();
  *param_2 = uVar1;
  param_2[1] = uVar2;
  return param_2;
}

