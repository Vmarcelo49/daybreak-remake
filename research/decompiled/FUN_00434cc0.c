// Function: FUN_00434cc0
// Address:  0x00434cc0
// Source:   batch_decompile (mass dump)
// Hash:     21f5cd9bbc253265


void __thiscall FUN_00434cc0(int param_1,int param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  if (*(int *)(param_1 + 0x10 + param_2 * 4) != 0) {
    std::allocator<char>::allocator<char>((allocator<char> *)&local_14);
    if (*(int *)(param_1 + 0x18 + param_2 * 4) < 0) {
      uVar2 = *(undefined4 *)(param_1 + 0x10 + param_2 * 4);
      uVar1 = FUN_00423750(0,0,0);
      D3DXVec3Transform(&local_14,uVar1,uVar2);
    }
    else {
      D3DXVec3Transform(&local_14,
                        *(int *)(param_1 + 0x18 + param_2 * 4) * 0xc + *(int *)(param_1 + 8),
                        *(undefined4 *)(param_1 + 0x10 + param_2 * 4));
    }
    *param_3 = local_14;
    param_3[1] = local_10;
    param_3[2] = local_c;
  }
  return;
}

