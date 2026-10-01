// Function: FUN_00651110
// Address:  0x00651110
// Source:   batch_decompile (mass dump)
// Hash:     6e2fef7c3e92f0f3


void __thiscall FUN_00651110(int param_1,int param_2)

{
  if (param_2 != DAT_006b77b4) {
    switch(param_2) {
    case 0:
      *(code **)(param_1 + 0x2c) = FUN_006519f0;
      break;
    case 1:
      *(code **)(param_1 + 0x2c) = FUN_00652220;
      *(undefined4 *)(param_1 + 0x28) = 0;
      break;
    case 2:
      *(code **)(param_1 + 0x2c) = FUN_00652880;
      break;
    case 3:
      *(code **)(param_1 + 0x2c) = FUN_00652af0;
      *(undefined4 *)(param_1 + 0x28) = 3;
      break;
    case 4:
      *(code **)(param_1 + 0x2c) = FUN_00652af0;
      *(undefined4 *)(param_1 + 0x28) = 4;
      break;
    case 5:
      *(code **)(param_1 + 0x2c) = FUN_00652e40;
      *(undefined4 *)(param_1 + 0x28) = 5;
      break;
    case 6:
      *(code **)(param_1 + 0x2c) = FUN_00652e40;
      *(undefined4 *)(param_1 + 0x28) = 6;
      break;
    case 7:
      *(code **)(param_1 + 0x2c) = FUN_00652220;
      *(undefined4 *)(param_1 + 0x28) = 7;
      break;
    case 8:
      *(code **)(param_1 + 0x2c) = FUN_00651ce0;
      *(undefined4 *)(param_1 + 0x28) = 8;
      break;
    case 9:
      *(code **)(param_1 + 0x2c) = FUN_00651f80;
      *(undefined4 *)(param_1 + 0x28) = 9;
      break;
    default:
      *(undefined4 *)(param_1 + 0x2c) = 0;
    }
    if (DAT_006b77b4 == 2) {
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xe,1);
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x13,5);
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,6);
      (**(code **)(*DAT_006d16f8 + 0x94))(DAT_006d16f8,0,*(undefined4 *)(param_1 + 0x27c));
      (**(code **)(*DAT_006d16f8 + 0x9c))(DAT_006d16f8,*(undefined4 *)(param_1 + 0x280));
    }
    if (param_2 == 2) {
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x1c,0);
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x13,2);
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,1);
      (**(code **)(*DAT_006d16f8 + 0x94))(DAT_006d16f8,0,DAT_006d1644);
      (**(code **)(*DAT_006d16f8 + 0x9c))(DAT_006d16f8,DAT_006d1648);
      (**(code **)(*DAT_006d16f8 + 0xac))(DAT_006d16f8,0,0,3,0xff000000,0x3f800000,0);
    }
    else if ((param_2 == 3) || (param_2 == 4)) {
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xe,1);
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x16,3);
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,1,4,0xff000000);
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,1,1,4);
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,1,2,4);
    }
    else if ((param_2 == 5) || (param_2 == 6)) {
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,1,4,0xff000000);
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,1,1,4);
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,1,2,4);
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xe,0);
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x16,1);
    }
    else if (param_2 == 1) {
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xe,1);
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,1,1,3);
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,1,2,3);
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,2,4,0xff000000);
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,2,1,4);
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,2,2,4);
    }
    else if (param_2 == 9) {
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,1,1,1);
      (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,1,2,1);
    }
  }
  DAT_006b77b4 = param_2;
  return;
}

