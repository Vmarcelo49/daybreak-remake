// Function: FUN_00661f60
// Address:  0x00661f60
// Source:   batch_decompile (mass dump)
// Hash:     0af8c478276e8c57


int FUN_00661f60(int *param_1,undefined4 param_2,int *param_3,void *param_4,undefined4 param_5,
                uint param_6,void *param_7,int *param_8,int *param_9)

{
  int iVar1;
  void *pvVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int local_60;
  int local_5c;
  void *local_58;
  uint local_54;
  int local_50;
  uint local_2c;
  uint local_24;
  int iVar7;
  int *local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  pvVar2 = ExceptionList;
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f23b;
  local_10 = ExceptionList;
  iVar7 = 0;
  ExceptionList = &local_10;
  *param_9 = 0;
  if (*param_3 != 1) {
    ExceptionList = pvVar2;
    return -0x7fffbffb;
  }
  local_18 = (int *)param_3[1];
  iVar1 = (**(code **)(*local_18 + 0x18))(local_18);
  if (iVar1 == 0) {
    ExceptionList = local_10;
    return -0x7fffbffb;
  }
  iVar1 = (**(code **)(*local_18 + 0x10))(local_18);
  pvVar2 = operator_new(0x4c);
  local_8 = 0;
  if (pvVar2 == (void *)0x0) {
    local_50 = 0;
  }
  else {
    local_50 = FUN_00662550();
  }
  local_8 = 0xffffffff;
  local_14 = local_50;
  if (local_50 == 0) {
    ExceptionList = local_10;
    return -0x7ff8fff2;
  }
  FUN_00662810(param_2);
  *(undefined4 *)(local_50 + 8) = 1;
  *(int *)(local_50 + 0x2c) = param_1[1];
  if (param_8 == (int *)0x0) {
    iVar7 = (**(code **)(*local_18 + 0x68))(local_18,0x3000000,0,0,0,0,local_50 + 0xc);
    local_18 = *(int **)(local_50 + 0xc);
  }
  uVar3 = (**(code **)(*local_18 + 0x18))(local_18);
  if ((uVar3 & 0x10) == 0) {
    uVar3 = (**(code **)(*local_18 + 0x18))(local_18,DAT_006d16f8,local_50 + 0xc);
    uVar4 = (**(code **)(*local_18 + 0x24))(local_18,uVar3 | 0x10);
    iVar7 = (**(code **)(*local_18 + 0x2c))(local_18,uVar4);
    if (iVar7 < 0) goto LAB_00662410;
    local_18 = *(int **)(local_50 + 0xc);
    D3DXComputeNormals(local_18,0);
  }
  else {
    *(int **)(local_50 + 0xc) = local_18;
    (**(code **)(*local_18 + 4))(local_18);
  }
  if (param_6 == 0) {
    local_54 = 1;
  }
  else {
    local_54 = param_6;
  }
  *(uint *)(local_50 + 0x18) = local_54;
  pvVar2 = operator_new(*(int *)(local_50 + 0x18) * 0x48);
  *(void **)(local_50 + 0x10) = pvVar2;
  pvVar2 = operator_new(*(int *)(local_50 + 0x18) << 2);
  *(void **)(local_50 + 0x28) = pvVar2;
  pvVar2 = operator_new(iVar1 * 0xc);
  *(void **)(local_50 + 0x1c) = pvVar2;
  if ((*(int *)(local_50 + 0x1c) == 0) || (*(int *)(local_50 + 0x10) == 0)) {
    iVar7 = -0x7ff8fff2;
    goto LAB_00662410;
  }
  _memcpy(*(void **)(local_50 + 0x1c),param_7,iVar1 * 0xc);
  if (param_6 == 0) {
    *(undefined4 *)(*(int *)(local_50 + 0x10) + 0x44) = 0;
    **(undefined4 **)(local_50 + 0x28) = 0xffffffff;
    _memset(*(void **)(local_50 + 0x10),0,0x44);
    **(undefined4 **)(local_50 + 0x10) = 0x3f800000;
    *(undefined4 *)(*(int *)(local_50 + 0x10) + 4) = 0x3f800000;
    *(undefined4 *)(*(int *)(local_50 + 0x10) + 8) = 0x3f800000;
    puVar5 = *(undefined4 **)(local_50 + 0x10);
    iVar1 = *(int *)(local_50 + 0x10);
    *(undefined4 *)(iVar1 + 0x20) = *puVar5;
    *(undefined4 *)(iVar1 + 0x24) = puVar5[1];
    *(undefined4 *)(iVar1 + 0x28) = puVar5[2];
    *(undefined4 *)(iVar1 + 0x2c) = puVar5[3];
  }
  else {
    _memcpy(*(void **)(local_50 + 0x10),param_4,param_6 * 0x48);
    for (local_24 = 0; local_24 < param_6; local_24 = local_24 + 1) {
      if (*(int *)(*(int *)(local_50 + 0x10) + 0x44 + local_24 * 0x48) == 0) {
        *(undefined4 *)(*(int *)(local_50 + 0x28) + local_24 * 4) = 0xffffffff;
      }
      else {
        FUN_0064ecd0(*(undefined4 *)(*(int *)(local_50 + 0x10) + 0x44 + local_24 * 0x48),
                     *(int *)(local_50 + 0x28) + local_24 * 4);
        *(undefined4 *)(*(int *)(local_50 + 0x10) + 0x44 + local_24 * 0x48) = 0;
      }
    }
  }
  if (param_8 != (int *)0x0) {
    *(int **)(local_50 + 0x20) = param_8;
    (**(code **)(*param_8 + 4))(param_8);
    *(int **)(local_50 + 0x30) = local_18;
    (**(code **)(*local_18 + 4))(local_18);
    uVar3 = (**(code **)(*param_8 + 0x24))(param_8);
    local_58 = operator_new(uVar3 << 6);
    local_8 = 1;
    if (local_58 == (void *)0x0) {
      local_58 = (void *)0x0;
    }
    else {
      _vector_constructor_iterator_(local_58,0x40,uVar3,std::allocator<char>::allocator<char>);
    }
    local_8 = 0xffffffff;
    *(void **)(local_50 + 0x44) = local_58;
    if (*(int *)(local_50 + 0x44) == 0) {
      iVar7 = -0x7ff8fff2;
      goto LAB_00662410;
    }
    for (local_2c = 0; local_2c < uVar3; local_2c = local_2c + 1) {
      puVar5 = (undefined4 *)
               (**(code **)(**(int **)(local_50 + 0x20) + 0x44))
                         (*(undefined4 *)(local_50 + 0x20),local_2c);
      puVar6 = (undefined4 *)(*(int *)(local_50 + 0x44) + local_2c * 0x40);
      for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar6 = *puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar6 + 1;
      }
    }
    iVar7 = FUN_0064df20(local_50);
    if (iVar7 < 0) goto LAB_00662410;
  }
  if (local_50 == 0) {
    local_5c = 0;
  }
  else {
    local_5c = local_50 + 4;
  }
  *param_9 = local_5c;
  (**(code **)(*local_18 + 8))(local_18);
  local_14 = 0;
LAB_00662410:
  if (local_14 != 0) {
    if (local_14 == 0) {
      local_60 = 0;
    }
    else {
      local_60 = local_14 + 4;
    }
    (**(code **)(*param_1 + 0xc))(param_1,local_60);
  }
  ExceptionList = local_10;
  return iVar7;
}

