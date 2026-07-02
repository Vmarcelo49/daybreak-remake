// ============================================
// Address:  0x00663b50
// Original: FUN_00663b50
// Status:   unreviewed
// ============================================


void __fastcall FUN_00663b50(int param_1)

{
  undefined4 *puVar1;
  _Container_proxy *p_Var2;
  undefined4 uVar3;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  puVar1 = (undefined4 *)FUN_00654620(local_8);
  uVar3 = *puVar1;
  puVar1 = (undefined4 *)FUN_00663240(local_c);
  FUN_00663d20(local_10,*puVar1,uVar3);
  p_Var2 = (_Container_proxy *)FUN_00663590(*(undefined4 *)(param_1 + 4));
  std::allocator<std::_Container_proxy>::destroy
            ((allocator<std::_Container_proxy> *)(param_1 + 2),p_Var2);
  p_Var2 = (_Container_proxy *)FUN_00653df0(*(undefined4 *)(param_1 + 4));
  std::allocator<std::_Container_proxy>::destroy
            ((allocator<std::_Container_proxy> *)(param_1 + 2),p_Var2);
  p_Var2 = (_Container_proxy *)FUN_00654020(*(undefined4 *)(param_1 + 4));
  std::allocator<std::_Container_proxy>::destroy
            ((allocator<std::_Container_proxy> *)(param_1 + 2),p_Var2);
  deallocate(*(undefined4 *)(param_1 + 4),1);
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}

