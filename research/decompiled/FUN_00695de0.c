// Function: FUN_00695de0
// Address:  0x00695de0
// Source:   batch_decompile (mass dump)
// Hash:     c28bfab99a8a3bff


undefined4 FUN_00695de0(undefined4 param_1,undefined8 *param_2,undefined8 *param_3)

{
  undefined8 uVar1;
  
  if (param_2 != (undefined8 *)0x0) {
    uVar1 = FUN_00697fc0();
    *param_2 = uVar1;
  }
  if (param_3 != (undefined8 *)0x0) {
    uVar1 = FUN_00697fc0();
    *param_3 = uVar1;
  }
  return 0;
}

