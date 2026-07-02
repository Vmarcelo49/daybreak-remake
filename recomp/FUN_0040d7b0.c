// ============================================
// Address:  0x0040d7b0
// Original: FUN_0040d7b0
// Status:   unreviewed
// ============================================


void __fastcall FUN_0040d7b0(int param_1)

{
  uint uVar1;
  int local_18;
  uint local_14 [4];
  
  local_14[0] = FUN_0065d150();
  local_14[0] = local_14[0] % 4;
  local_14[1] = FUN_0065d150();
  while (local_14[1] = local_14[1] % 4, local_14[1] == local_14[0]) {
    local_14[1] = FUN_0065d150();
  }
  uVar1 = FUN_0065d150();
  local_14[2] = uVar1 % 4;
  while ((local_14[2] == local_14[0] || (local_14[2] == local_14[1]))) {
    uVar1 = FUN_0065d150();
    local_14[2] = uVar1 % 4;
  }
  for (local_14[3] = 0;
      ((int)local_14[3] < 4 &&
      (((local_14[0] == local_14[3] || (local_14[1] == local_14[3])) || (local_14[2] == local_14[3])
       ))); local_14[3] = local_14[3] + 1) {
  }
  for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1) {
    if (-1 < *(int *)(param_1 + 0x3c48 + local_18 * 4)) {
      switch(local_14[local_18]) {
      case 0:
        *(undefined4 *)(param_1 + 0x3c48 + local_18 * 4) = 0;
        break;
      case 1:
        *(undefined4 *)(param_1 + 0x3c48 + local_18 * 4) = 1;
        break;
      case 2:
        *(undefined4 *)(param_1 + 0x3c48 + local_18 * 4) = 3;
        break;
      case 3:
        *(undefined4 *)(param_1 + 0x3c48 + local_18 * 4) = 4;
      }
    }
  }
  return;
}

