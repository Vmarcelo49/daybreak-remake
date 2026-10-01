// Function: FUN_00655f70
// Address:  0x00655f70
// Source:   batch_decompile (mass dump)
// Hash:     c6bd8e2c38dea15a


void __thiscall
FUN_00655f70(undefined4 *param_1,float param_2,float param_3,float param_4,float param_5)

{
  param_1[1] = param_2 - 0.5;
  param_1[2] = param_3 - 0.5;
  param_1[8] = param_4 - 0.5;
  param_1[9] = param_3 - 0.5;
  param_1[0xf] = param_2 - 0.5;
  param_1[0x10] = param_5 - 0.5;
  param_1[0x16] = param_4 - 0.5;
  param_1[0x17] = param_5 - 0.5;
  FUN_00656300(*param_1);
  (**(code **)(*DAT_006d16f8 + 0x170))(DAT_006d16f8,0);
  (**(code **)(*DAT_006d16f8 + 0x164))(DAT_006d16f8,0x144);
  FUN_006517e0(5,2,param_1 + 1,0x1c);
  return;
}

