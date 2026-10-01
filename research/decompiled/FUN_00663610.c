// Function: FUN_00663610
// Address:  0x00663610
// Source:   batch_decompile (mass dump)
// Hash:     d841909022c8cdc2


void __thiscall FUN_00663610(int param_1,_Container_proxy *param_2)

{
  _Container_proxy *p_Var1;
  char *pcVar2;
  undefined4 *puVar3;
  
  while( true ) {
    pcVar2 = (char *)FUN_00663560(param_2);
    if (*pcVar2 != '\0') break;
    puVar3 = (undefined4 *)FUN_00654020(param_2);
    FUN_00663610(*puVar3);
    puVar3 = (undefined4 *)FUN_00663590(param_2);
    p_Var1 = (_Container_proxy *)*puVar3;
    std::allocator<std::_Container_proxy>::destroy
              ((allocator<std::_Container_proxy> *)(param_1 + 1),param_2);
    deallocate(param_2,1);
    param_2 = p_Var1;
  }
  return;
}

