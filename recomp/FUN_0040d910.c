// ============================================
// Address:  0x0040d910
// Original: FUN_0040d910
// Status:   unreviewed
// ============================================


int __fastcall FUN_0040d910(int param_1)

{
  int iVar1;
  int iVar2;
  int local_18;
  undefined4 local_14 [4];
  
  iVar1 = (int)DAT_006cfe1d / 3;
  iVar2 = (int)DAT_006cfe1d % 3;
  if (iVar2 == 0) {
    local_14[0] = 0;
    local_14[1] = 1;
    local_14[2] = 3;
    local_14[3] = 4;
  }
  else if (iVar2 == 1) {
    local_14[0] = 0;
    local_14[1] = 4;
    local_14[2] = 1;
    local_14[3] = 3;
  }
  else if (iVar2 == 2) {
    local_14[0] = 0;
    local_14[1] = 3;
    local_14[2] = 4;
    local_14[3] = 1;
  }
  for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1) {
    iVar1 = local_18;
    if (-1 < *(int *)(param_1 + 0x3c48 + local_18 * 4)) {
      *(undefined4 *)(param_1 + 0x3c48 + local_18 * 4) = local_14[local_18];
      iVar1 = param_1;
    }
  }
  DAT_006cfe1d = DAT_006cfe1d + '\x01';
  return iVar1;
}

