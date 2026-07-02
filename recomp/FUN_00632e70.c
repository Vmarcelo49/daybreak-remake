// ============================================
// Address:  0x00632e70
// Original: FUN_00632e70
// Status:   unreviewed
// ============================================


void __thiscall FUN_00632e70(int param_1,undefined4 *param_2,char param_3)

{
  *(undefined4 *)(param_1 + 0x3c) = *param_2;
  *(undefined4 *)(param_1 + 0x40) = param_2[1];
  *(undefined4 *)(param_1 + 0x44) = param_2[2];
  if ((param_3 != '\0') || (*(char *)(param_1 + 0x94) != '\0')) {
    *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_1 + 0x40);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x44);
  }
  return;
}

