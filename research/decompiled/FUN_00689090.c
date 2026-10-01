// Function: FUN_00689090
// Address:  0x00689090
// Source:   batch_decompile (mass dump)
// Hash:     8fc113cdd5aa0c31


undefined4 FUN_00689090(int param_1)

{
  undefined4 uVar1;
  
  *(undefined4 *)(param_1 + 4) = 0;
  uVar1 = (**(code **)(**(int **)(param_1 + 8) + 0x10))();
  *(undefined4 *)(param_1 + 0xc) = uVar1;
  return 0;
}

