// Function: FUN_00650c30
// Address:  0x00650c30
// Source:   batch_decompile (mass dump)
// Hash:     f0050521ffd5cf8c


void __thiscall FUN_00650c30(undefined4 param_1,int param_2)

{
  if (DAT_006b77b0 != param_2) {
    switch(param_2) {
    case 0:
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x13,5);
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,6);
      break;
    case 1:
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x13,5);
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,2);
      break;
    case 2:
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x13,1);
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,4);
      break;
    case 3:
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x13,9,param_2,param_1);
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,1);
    }
    DAT_006b77b0 = param_2;
  }
  return;
}

