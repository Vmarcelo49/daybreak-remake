// ============================================
// Address:  0x004249a0
// Original: FUN_004249a0
// Status:   unreviewed
// ============================================


void __thiscall FUN_004249a0(int param_1,undefined4 param_2)

{
  uint uVar1;
  char *pcVar2;
  undefined4 local_c;
  
  if (((uint)(*(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x10)) % 0x10 == 0) &&
     (*(uint *)(param_1 + 8) <= *(int *)(param_1 + 0x10) + 0x10U >> 4)) {
    FUN_00425b10(1);
  }
  uVar1 = *(int *)(param_1 + 0xc) + *(int *)(param_1 + 0x10);
  local_c = uVar1 >> 4;
  if (*(uint *)(param_1 + 8) <= local_c) {
    local_c = local_c - *(int *)(param_1 + 8);
  }
  if (*(int *)(*(int *)(param_1 + 4) + local_c * 4) == 0) {
    pcVar2 = std::allocator<char>::allocate((allocator<char> *)(param_1 + 1),0x10);
    *(char **)(*(int *)(param_1 + 4) + local_c * 4) = pcVar2;
  }
  FUN_00424a80(uVar1 % 0x10 + *(int *)(*(int *)(param_1 + 4) + local_c * 4),param_2);
  *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + 1;
  return;
}

