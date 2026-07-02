// ============================================
// Address:  0x00425500
// Original: FUN_00425500
// Status:   unreviewed
// ============================================


undefined4 * __thiscall
FUN_00425500(allocator<std::_Container_proxy> *param_1,undefined4 *param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined1 local_c [4];
  _Container_proxy *local_8;
  
  FUN_0042fc40(local_c,0);
  local_8 = (_Container_proxy *)FUN_0068de10();
  if (local_8 != *(_Container_proxy **)(param_1 + 4)) {
    puVar1 = (undefined4 *)FUN_00663590(local_8);
    puVar2 = (undefined4 *)FUN_00653df0(local_8);
    puVar2 = (undefined4 *)FUN_00663590(*puVar2);
    *puVar2 = *puVar1;
    puVar1 = (undefined4 *)FUN_00653df0(local_8);
    puVar2 = (undefined4 *)FUN_00663590(local_8);
    puVar2 = (undefined4 *)FUN_00653df0(*puVar2);
    *puVar2 = *puVar1;
    std::allocator<std::_Container_proxy>::destroy(param_1,local_8);
    deallocate(local_8,1);
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + -1;
  }
  *param_2 = param_3;
  return param_2;
}

