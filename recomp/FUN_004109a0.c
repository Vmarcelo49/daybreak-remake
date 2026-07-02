// ============================================
// Address:  0x004109a0
// Original: FUN_004109a0
// Status:   unreviewed
// ============================================


void __thiscall FUN_004109a0(allocator<char> *param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  uint local_1c;
  void *pvStack_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069dd20;
  pvStack_10 = ExceptionList;
  local_1c = param_2 | 0xf;
  ExceptionList = &pvStack_10;
  uVar1 = FID_conflict_max_size();
  if (uVar1 < local_1c) {
    local_1c = param_2;
  }
  else if (local_1c / 3 < *(uint *)(param_1 + 0x18) >> 1) {
    uVar1 = *(uint *)(param_1 + 0x18);
    iVar2 = FID_conflict_max_size();
    if (*(uint *)(param_1 + 0x18) <= iVar2 - (uVar1 >> 1)) {
      local_1c = (*(uint *)(param_1 + 0x18) >> 1) + *(int *)(param_1 + 0x18);
    }
  }
  local_8 = 0;
  std::allocator<char>::allocate(param_1,local_1c + 1);
  FUN_00410a90();
  return;
}

