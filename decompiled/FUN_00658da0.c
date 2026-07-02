// Function: FUN_00658da0
// Address:  0x00658da0
// Source:   batch_decompile (mass dump)
// Hash:     2a962fc7c787d1a2


undefined4 * __thiscall
FUN_00658da0(int param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = const_iterator__operator__(&param_4);
  if (cVar1 != '\0') {
    uVar2 = FUN_006595d0(param_4,*(undefined4 *)(param_1 + 8),param_3);
    FUN_00658e10(uVar2,*(undefined4 *)(param_1 + 8));
    *(undefined4 *)(param_1 + 8) = uVar2;
  }
  *param_2 = param_3;
  return param_2;
}

