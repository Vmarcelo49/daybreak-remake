// Function: FUN_0063c060
// Address:  0x0063c060
// Source:   batch_decompile (mass dump)
// Hash:     2aa34ee153f035d4


void __fastcall FUN_0063c060(allocator<std::_Container_proxy> *param_1)

{
  char cVar1;
  int local_8;
  
  while( true ) {
    cVar1 = Empty();
    if (cVar1 != '\0') break;
    FUN_0063c1e0();
  }
  local_8 = *(int *)(param_1 + 8);
  while (local_8 != 0) {
    local_8 = local_8 + -1;
    if (*(int *)(*(int *)(param_1 + 4) + local_8 * 4) != 0) {
      deallocate(*(undefined4 *)(*(int *)(param_1 + 4) + local_8 * 4),1);
    }
    std::allocator<std::_Container_proxy>::destroy
              (param_1,(_Container_proxy *)(*(int *)(param_1 + 4) + local_8 * 4));
  }
  if (*(int *)(param_1 + 4) != 0) {
    deallocate(*(undefined4 *)(param_1 + 4),*(undefined4 *)(param_1 + 8));
  }
  *(undefined4 *)(param_1 + 8) = 0;
  *(undefined4 *)(param_1 + 4) = 0;
  return;
}

