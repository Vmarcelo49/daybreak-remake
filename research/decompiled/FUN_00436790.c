// Function: FUN_00436790
// Address:  0x00436790
// Source:   batch_decompile (mass dump)
// Hash:     3af13baf0bfe7fbd


void __thiscall
FUN_00436790(undefined4 *param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4,
            int param_5,int param_6,undefined1 param_7)

{
  int iVar1;
  undefined4 uVar2;
  void *local_4c;
  void *local_48;
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e5fb;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  param_1[6] = param_2;
  *param_1 = param_3;
  param_1[4] = param_4;
  param_1[1] = param_5;
  param_1[2] = param_6;
  *(undefined1 *)(param_1 + 5) = param_7;
  iVar1 = (param_5 + 1) * param_6;
  local_48 = operator_new(iVar1 * 0x10);
  local_8 = 0;
  if (local_48 == (void *)0x0) {
    local_48 = (void *)0x0;
  }
  else {
    _vector_constructor_iterator_(local_48,0x10,iVar1,std::allocator<char>::allocator<char>);
  }
  local_8 = 0xffffffff;
  param_1[0xc] = local_48;
  iVar1 = param_5 * param_6 * 2 + 2;
  local_4c = operator_new(iVar1 * 0x1c);
  local_8 = 1;
  if (local_4c == (void *)0x0) {
    local_4c = (void *)0x0;
  }
  else {
    _vector_constructor_iterator_(local_4c,0x1c,iVar1,FUN_0068d8d0);
  }
  local_8 = 0xffffffff;
  param_1[0xd] = local_4c;
  uVar2 = FUN_00430750(*param_3,param_3[1],param_3[2],0x3f800000);
  FUN_00437210(param_5 + 4,uVar2);
  for (local_14 = 0; local_14 < param_5 * param_6 * 2 + 2; local_14 = local_14 + 1) {
    *(undefined4 *)(param_1[0xd] + 0x10 + local_14 * 0x1c) = 0xffffffff;
  }
  for (local_18 = 0; local_18 <= param_5 * param_6; local_18 = local_18 + 1) {
    *(undefined4 *)(param_1[0xd] + 0x14 + local_18 * 0x38) = 0;
    *(undefined4 *)(param_1[0xd] + 0x14 + (local_18 * 2 + 1) * 0x1c) = 0x3f800000;
    *(undefined4 *)(param_1[0xd] + 0x18 + (local_18 * 2 + 1) * 0x1c) = 0;
    *(undefined4 *)(param_1[0xd] + 0x18 + local_18 * 0x38) = 0;
  }
  param_1[3] = 0xffffffff;
  ExceptionList = local_10;
  return;
}

