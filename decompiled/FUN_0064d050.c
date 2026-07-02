// Function: FUN_0064d050
// Address:  0x0064d050
// Source:   batch_decompile (mass dump)
// Hash:     a2b8aa7ec18c416d


void __fastcall FUN_0064d050(int param_1)

{
  char cVar1;
  
  cVar1 = Empty();
  if (cVar1 == '\0') {
    std::allocator<std::_Container_proxy>::destroy
              ((allocator<std::_Container_proxy> *)(param_1 + 1),
               (_Container_proxy *)
               (*(uint *)(param_1 + 0xc) % 0x10 +
               *(int *)(*(int *)(param_1 + 4) + (*(uint *)(param_1 + 0xc) >> 4) * 4)));
    *(int *)(param_1 + 0xc) = *(int *)(param_1 + 0xc) + 1;
    if ((uint)(*(int *)(param_1 + 8) << 4) <= *(uint *)(param_1 + 0xc)) {
      *(undefined4 *)(param_1 + 0xc) = 0;
    }
    *(int *)(param_1 + 0x10) = *(int *)(param_1 + 0x10) + -1;
    if (*(int *)(param_1 + 0x10) == 0) {
      *(undefined4 *)(param_1 + 0xc) = 0;
    }
  }
  return;
}

