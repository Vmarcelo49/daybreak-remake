// ============================================
// Address:  0x00638fd0
// Original: FUN_00638fd0
// Status:   unreviewed
// ============================================


void FUN_00638fd0(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  float fVar6;
  undefined4 uVar7;
  float fVar8;
  char local_5;
  
  if ((((*(int *)(param_1 + 8) != *(int *)(param_2 + 8)) ||
       ((*(uint *)(*(int *)(param_1 + 0x10) + 0x2c) & 0x10000) != 0)) &&
      (*(short *)(param_1 + 0x88 + *(int *)(param_2 + 8) * 2) == 0)) &&
     ((0 < *(int *)(param_1 + 0x90 + *(int *)(param_2 + 8) * 4) &&
      ((*(uint *)(*(int *)(param_2 + 0x10) + 0x28) & 0x10000) == 0)))) {
    if (*(int *)(*(int *)(param_2 + 0x10) + 8) == 0) {
      fVar8 = (float)*(int *)(*(int *)(param_2 + 0x10) + 0x24);
      uVar1 = std::allocator<char>::allocator<char>((allocator<char> *)(param_2 + 0xc4));
      uVar1 = FUN_004237f0(uVar1);
      fVar6 = (float)*(int *)(*(int *)(param_1 + 0x10) + 0x24);
      uVar5 = std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0xc4));
      uVar5 = FUN_004237f0(uVar5);
      local_5 = FUN_0063b470(uVar5,fVar6,uVar1,fVar8);
    }
    else {
      fVar8 = (float)*(int *)(*(int *)(param_2 + 0x10) + 0x24);
      uVar1 = std::allocator<char>::allocator<char>((allocator<char> *)(param_2 + 0xd4));
      puVar2 = (undefined4 *)FUN_004237f0(uVar1);
      uVar1 = *puVar2;
      uVar5 = puVar2[1];
      uVar7 = puVar2[2];
      uVar3 = std::allocator<char>::allocator<char>((allocator<char> *)(param_2 + 0xc4));
      uVar3 = FUN_004237f0(uVar3);
      fVar6 = (float)*(int *)(*(int *)(param_1 + 0x10) + 0x24);
      uVar4 = std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0xc4));
      uVar4 = FUN_004237f0(uVar4);
      local_5 = FUN_0063b4d0(uVar4,fVar6,uVar3,uVar1,uVar5,uVar7,fVar8);
    }
    if (local_5 != '\0') {
      *(undefined2 *)(param_2 + 0x88 + *(int *)(param_1 + 8) * 2) = 0x100;
    }
  }
  return;
}

