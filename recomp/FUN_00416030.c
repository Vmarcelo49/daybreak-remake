// ============================================
// Address:  0x00416030
// Original: FUN_00416030
// Status:   unreviewed
// ============================================


void __thiscall FUN_00416030(int param_1,int param_2)

{
  int iVar1;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  iVar1 = param_2 + 1;
  for (local_c = 0; local_c < 8; local_c = local_c + 1) {
    *(bool *)(param_1 + local_c + 8) = *(char *)(iVar1 + local_c) != '\0';
  }
  for (local_10 = 0; local_10 < 8; local_10 = local_10 + 1) {
    for (local_14 = 0; local_14 < 9; local_14 = local_14 + 1) {
      *(undefined1 *)(param_1 + 0x10 + local_10 * 9 + local_14) =
           *(undefined1 *)(param_2 + 9 + local_10 * 9 + local_14);
    }
  }
  for (local_18 = 0; local_18 < 8; local_18 = local_18 + 1) {
    *(undefined1 *)(param_1 + local_18 + 0x58) = *(undefined1 *)(iVar1 + local_18 + 0x50);
  }
  for (local_1c = 0; local_1c < 4; local_1c = local_1c + 1) {
    *(undefined1 *)(param_1 + local_1c + 0x60) = *(undefined1 *)(iVar1 + local_1c + 0x58);
  }
  for (local_20 = 0; local_20 < 4; local_20 = local_20 + 1) {
    *(undefined1 *)(param_1 + local_20 + 100) = *(undefined1 *)(iVar1 + local_20 + 0x5c);
  }
  *(bool *)(param_1 + 0x68) = *(char *)(param_2 + 0x61) != '\0';
  *(undefined1 *)(param_1 + 0x69) = *(undefined1 *)(param_2 + 0x62);
  return;
}

