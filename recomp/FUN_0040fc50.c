// ============================================
// Address:  0x0040fc50
// Original: FUN_0040fc50
// Status:   unreviewed
// ============================================


void __fastcall FUN_0040fc50(int param_1)

{
  char cVar1;
  uint uVar2;
  
  cVar1 = Empty();
  if (cVar1 == '\0') {
    std::allocator<std::_Container_proxy>::destroy
              ((allocator<std::_Container_proxy> *)(param_1 + 1),
               (_Container_proxy *)
               (*(int *)(*(int *)(param_1 + 4) + (*(uint *)(param_1 + 0xc) >> 1) * 4) +
               (*(uint *)(param_1 + 0xc) % 2) * 8));
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
    uVar2 = *(int *)(param_1 + 8) * 2;
    if (uVar2 < *(uint *)(param_1 + 0xc) || uVar2 - *(uint *)(param_1 + 0xc) == 0) {
      *(undefined4 *)(param_1 + 0xc) = 0;
    }
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
    if (*(int *)(param_1 + 0x10) == 0) {
      *(undefined4 *)(param_1 + 0xc) = 0;
    }
  }
  return;
}

