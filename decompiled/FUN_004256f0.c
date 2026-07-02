// Function: FUN_004256f0
// Address:  0x004256f0
// Source:   batch_decompile (mass dump)
// Hash:     3ce3b48afcce5de0


void __fastcall FUN_004256f0(int param_1)

{
  _Container_proxy *p_Var1;
  
  FUN_004261d0();
  p_Var1 = (_Container_proxy *)FUN_00663590(*(undefined4 *)(param_1 + 4));
  std::allocator<std::_Container_proxy>::destroy
            ((allocator<std::_Container_proxy> *)(param_1 + 1),p_Var1);
  p_Var1 = (_Container_proxy *)FUN_00653df0(*(undefined4 *)(param_1 + 4));
  std::allocator<std::_Container_proxy>::destroy
            ((allocator<std::_Container_proxy> *)(param_1 + 1),p_Var1);
  deallocate(*(undefined4 *)(param_1 + 4),1);
  *(undefined4 *)(param_1 + 4) = 0;
  return;
}

