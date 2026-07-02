// Function: FUN_00401b80
// Address:  0x00401b80
// Source:   batch_decompile (mass dump)
// Hash:     2722dd8248dd3b52


void __fastcall FUN_00401b80(int *param_1)

{
  (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x16,3);
  (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xf,0);
  (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x1c,1);
  if ((char)param_1[0xb] == '\0') {
    FUN_00651110(0);
  }
  else {
    FUN_00651110(3);
  }
  if (param_1[1] != 0) {
    FUN_0064e1a0();
  }
  if (param_1[5] != 0) {
    FUN_0064e1a0();
  }
  if (*(char *)((int)param_1 + 0x2d) != '\0') {
    FUN_00651110(0);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xe,0);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x13,9);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,1);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x1c,0);
    if (param_1[4] != 0) {
      FUN_0064e1a0();
    }
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x1c,1);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xe,1);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x13,5);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,6);
    if ((char)param_1[0xb] == '\0') {
      FUN_00651110(0);
    }
    else {
      FUN_00651110(3);
    }
    if (param_1[3] != 0) {
      FUN_0064e1a0();
    }
  }
  (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,0,5,1);
  (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,0,6,1);
  (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,0,7,1);
  (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xf,1);
  if (param_1[6] != 0) {
    FUN_0064e1a0();
  }
  if (param_1[2] != 0) {
    FUN_0064e1a0();
  }
  (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,0,5,2);
  (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,0,6,2);
  (**(code **)(*DAT_006d16f8 + 0x114))(DAT_006d16f8,0,7,2);
  (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xf,0);
  FUN_00651110(0);
  (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x1c,0);
  if (*param_1 != 0) {
    FUN_0064e1a0();
  }
  return;
}

