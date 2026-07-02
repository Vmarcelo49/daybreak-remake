// Function: FUN_00668c90
// Address:  0x00668c90
// Source:   batch_decompile (mass dump)
// Hash:     fcade97d25f8acbd


/* WARNING: Removing unreachable block (ram,0x00668df0) */
/* WARNING: Removing unreachable block (ram,0x00668e01) */
/* WARNING: Removing unreachable block (ram,0x00668e0b) */
/* WARNING: Removing unreachable block (ram,0x00668e1c) */
/* WARNING: Removing unreachable block (ram,0x00668e26) */

int __fastcall FUN_00668c90(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_168 [8];
  int local_148;
  undefined1 local_144 [12];
  uint local_138;
  int *local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  local_8 = 2;
  local_c = 2;
  *(undefined4 *)(param_1 + 0x160) = 0;
  if (*(char *)(param_1 + 0x168) == '\0') {
    iVar1 = FUN_00669440();
    *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(iVar1 + 0x34);
    uVar2 = FUN_00403aa0(*(undefined4 *)(iVar1 + 0x38));
    *(undefined4 *)(param_1 + 0x174) = uVar2;
    *(uint *)(param_1 + 0x178) = *(int *)(param_1 + 0x170) * 3 + 3U & 0xfffffffc;
  }
  else {
    iVar1 = FUN_00669440();
    *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(iVar1 + 0x4c);
    uVar2 = FUN_00403aa0(*(undefined4 *)(iVar1 + 0x50));
    *(undefined4 *)(param_1 + 0x174) = uVar2;
    *(uint *)(param_1 + 0x178) = *(int *)(param_1 + 0x170) * 3 + 3U & 0xfffffffc;
  }
  _memset(local_144,0,0x130);
  (**(code **)(*DAT_006d16f8 + 0x1c))(DAT_006d16f8,local_144);
  if ((local_138 & 0x20000000) != 0) {
    *(undefined4 *)(param_1 + 0x16c) = 1;
  }
  local_8 = *(undefined4 *)(param_1 + 0x170);
  local_c = *(undefined4 *)(param_1 + 0x174);
  *(undefined4 *)(param_1 + 0x16c) = 0;
  local_148 = -0x7fff0001;
  if ((*(int *)(param_1 + 0x16c) != 0) &&
     (local_148 = (**(code **)(*DAT_006d16f8 + 0x5c))
                            (DAT_006d16f8,local_8,local_c,1,0,0x16,0,param_1 + 0x160,0),
     local_148 < 0)) {
    *(undefined4 *)(param_1 + 0x16c) = 0;
  }
  if (*(int *)(param_1 + 0x16c) == 0) {
    local_148 = (**(code **)(*DAT_006d16f8 + 0x5c))
                          (DAT_006d16f8,local_8,local_c,1,0,0x16,1,param_1 + 0x160,0);
  }
  if (-1 < local_148) {
    _memset(local_168,0,0x20);
    local_148 = (**(code **)(**(int **)(param_1 + 0x160) + 0x44))
                          (*(undefined4 *)(param_1 + 0x160),0,local_168);
    if (-1 < local_148) {
      local_148 = (**(code **)(**(int **)(param_1 + 0x160) + 0x48))
                            (*(undefined4 *)(param_1 + 0x160),0,&local_10);
      if (-1 < local_148) {
        (**(code **)(*local_10 + 0x30))(local_10,local_168);
        (**(code **)(*local_10 + 8))(local_10);
      }
      *(undefined4 *)(param_1 + 0x164) = local_168[0];
      if ((*(int *)(param_1 + 0x164) == 0x16) || (*(int *)(param_1 + 0x164) == 0x19)) {
        local_148 = 0;
      }
      else {
        local_148 = -0x7ffbfdd6;
      }
    }
  }
  return local_148;
}

