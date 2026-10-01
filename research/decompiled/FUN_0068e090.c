// Function: FUN_0068e090
// Address:  0x0068e090
// Source:   batch_decompile (mass dump)
// Hash:     e51c391b0ad60136


undefined4 FUN_0068e090(int *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  if (param_2 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    *param_2 = param_1;
    (**(code **)(*param_1 + 4))(param_1);
    uVar1 = 0;
  }
  return uVar1;
}

