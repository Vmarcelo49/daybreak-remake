// ============================================
// Address:  0x0042fe90
// Original: FUN_0042fe90
// Status:   unreviewed
// ============================================


uint __thiscall
FUN_0042fe90(uint param_1,undefined4 param_2,undefined4 param_3,allocator<char> *param_4,
            allocator<char> *param_5)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 local_4c;
  undefined1 local_24 [4];
  int local_20;
  int local_1c;
  void *local_18;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069e46b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_18 = operator_new(0x9c);
  local_8 = 0;
  if (local_18 == (void *)0x0) {
    local_4c = 0;
  }
  else {
    local_4c = FUN_0064d7a0();
  }
  local_14 = local_4c;
  local_8 = 0xffffffff;
  *(undefined4 *)(param_1 + 0x40) = local_4c;
  cVar1 = FUN_0064d940(param_2);
  if (cVar1 == '\0') {
    local_20 = *(int *)(param_1 + 0x40);
    if (local_20 != 0) {
      local_1c = local_20;
      FUN_00402010(1);
    }
    *(undefined4 *)(param_1 + 0x40) = 0;
    param_1 = param_1 & 0xffffff00;
  }
  else {
    puVar2 = (undefined4 *)FUN_006560c0(local_24,param_3);
    *(undefined4 *)(param_1 + 0x44) = *puVar2;
    uVar3 = std::allocator<char>::allocator<char>(param_4);
    puVar2 = (undefined4 *)FUN_00430630(uVar3);
    *(undefined4 *)(param_1 + 0x18) = *puVar2;
    *(undefined4 *)(param_1 + 0x1c) = puVar2[1];
    *(undefined4 *)(param_1 + 0x20) = puVar2[2];
    *(undefined4 *)(param_1 + 0x24) = puVar2[3];
    *(undefined4 *)(param_1 + 0x24) = 0x3f800000;
    uVar3 = std::allocator<char>::allocator<char>(param_5);
    puVar2 = (undefined4 *)FUN_00430630(uVar3);
    *(undefined4 *)(param_1 + 0x28) = *puVar2;
    *(undefined4 *)(param_1 + 0x2c) = puVar2[1];
    *(undefined4 *)(param_1 + 0x30) = puVar2[2];
    uVar3 = puVar2[3];
    *(undefined4 *)(param_1 + 0x34) = uVar3;
    *(undefined4 *)(param_1 + 0x34) = 0x3f800000;
    param_1 = CONCAT31((int3)((uint)uVar3 >> 8),1);
  }
  ExceptionList = local_10;
  return param_1;
}

