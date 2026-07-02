// ============================================
// Address:  0x00426bd0
// Original: FUN_00426bd0
// Status:   unreviewed
// ============================================


void __fastcall FUN_00426bd0(int param_1)

{
  uint uVar1;
  char cVar2;
  uint local_c;
  
  cVar2 = Empty();
  if (cVar2 == '\0') {
    uVar1 = *(int *)(param_1 + 0x10) + -1 + *(int *)(param_1 + 0xc);
    local_c = uVar1 >> 4;
    if (*(uint *)(param_1 + 8) <= local_c) {
      local_c = local_c - *(int *)(param_1 + 8);
    }
    std::allocator<std::_Container_proxy>::destroy
              ((allocator<std::_Container_proxy> *)(param_1 + 1),
               (_Container_proxy *)(uVar1 % 0x10 + *(int *)(*(int *)(param_1 + 4) + local_c * 4)));
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
    if (*(int *)(param_1 + 0x10) == 0) {
      *(undefined4 *)(param_1 + 0xc) = 0;
    }
  }
  return;
}

