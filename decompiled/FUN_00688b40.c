// Function: FUN_00688b40
// Address:  0x00688b40
// Source:   batch_decompile (mass dump)
// Hash:     37a4be90e7deea6b


undefined4 FUN_00688b40(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = (**(code **)(**(int **)(param_1 + 0xc) + 0x14))();
  *(undefined4 *)(param_1 + 0x10) = uVar1;
  uVar1 = (**(code **)(**(int **)(param_1 + 0xc) + 0x18))();
  *(undefined4 *)(param_1 + 8) = uVar1;
  *(undefined4 *)(param_1 + 4) = 0;
  FUN_00693630();
  return 0;
}

