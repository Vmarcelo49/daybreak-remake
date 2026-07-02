// Function: FUN_00690980
// Address:  0x00690980
// Source:   batch_decompile (mass dump)
// Hash:     94bf23e93c17431a


void __thiscall FUN_00690980(int param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = param_2 / 10000;
  if ((1000 < (int)local_8) || ((int)local_8 < -1000)) {
    if (*(int *)(param_1 + 0x124) < 2) {
      local_8 = 0;
    }
    else if ((int)local_8 < 1) {
      local_8 = 0xfffffc18;
    }
    else {
      local_8 = 1000;
    }
  }
  if (1 < *(int *)(param_1 + 0x124)) {
    uVar1 = *(uint *)(param_1 + 0x128);
    *(uint *)(param_1 + 0x128) = local_8 + *(uint *)(param_1 + 0x128);
    *(uint *)(param_1 + 300) =
         *(int *)(param_1 + 300) + ((int)local_8 >> 0x1f) + (uint)CARRY4(local_8,uVar1);
    local_8 = local_8 * local_8;
    uVar1 = *(uint *)(param_1 + 0x130);
    *(uint *)(param_1 + 0x130) = local_8 + *(uint *)(param_1 + 0x130);
    *(uint *)(param_1 + 0x134) =
         *(int *)(param_1 + 0x134) + ((int)local_8 >> 0x1f) + (uint)CARRY4(local_8,uVar1);
  }
  if (2 < *(int *)(param_1 + 0x124)) {
    local_c = param_3 / 10000;
    if ((1000 < (int)local_c) || ((int)local_c < 0)) {
      local_c = 1000;
    }
    uVar2 = local_c * local_c;
    uVar1 = *(uint *)(param_1 + 0x140);
    *(uint *)(param_1 + 0x140) = uVar2 + *(uint *)(param_1 + 0x140);
    *(uint *)(param_1 + 0x144) =
         *(int *)(param_1 + 0x144) + ((int)uVar2 >> 0x1f) + (uint)CARRY4(uVar2,uVar1);
    uVar1 = *(uint *)(param_1 + 0x148);
    *(uint *)(param_1 + 0x148) = local_c + *(uint *)(param_1 + 0x148);
    *(uint *)(param_1 + 0x14c) =
         *(int *)(param_1 + 0x14c) + ((int)local_c >> 0x1f) + (uint)CARRY4(local_c,uVar1);
  }
  *(int *)(param_1 + 0x124) = *(int *)(param_1 + 0x124) + 1;
  return;
}

