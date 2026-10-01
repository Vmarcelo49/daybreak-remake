// Function: FUN_00650ab0
// Address:  0x00650ab0
// Source:   batch_decompile (mass dump)
// Hash:     0e740ff0279d9fb7


void __thiscall FUN_00650ab0(int param_1,int *param_2)

{
  *(int *)(param_1 + 0x260) = *param_2;
  *(int *)(param_1 + 0x264) = param_2[1];
  *(int *)(param_1 + 0x268) = param_2[2] - *param_2;
  *(int *)(param_1 + 0x26c) = param_2[3] - param_2[1];
  *(undefined4 *)(param_1 + 0x274) = 0x3f800000;
  *(undefined4 *)(param_1 + 0x270) = 0;
  (**(code **)(*DAT_006d16f8 + 0xbc))(DAT_006d16f8,param_1 + 0x260);
  return;
}

