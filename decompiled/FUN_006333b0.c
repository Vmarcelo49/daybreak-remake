// Function: FUN_006333b0
// Address:  0x006333b0
// Source:   batch_decompile (mass dump)
// Hash:     beec9f0cb34baacd


void __fastcall FUN_006333b0(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float10 fVar4;
  allocator<char> *paVar5;
  undefined1 local_f0 [24];
  undefined1 local_d8 [48];
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  uint local_90;
  int local_8c;
  undefined1 local_88 [12];
  allocator<char> local_7c [16];
  allocator<char> local_6c [64];
  allocator<char> local_2c [16];
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  FUN_0042dfd0(&local_10,param_1 + 0x18);
  local_1c = *(float *)(param_1 + 0x18);
  local_18 = *(float *)(param_1 + 0x1c);
  local_14 = *(float *)(param_1 + 0x20);
  if (*(char *)(param_1 + 0x95) == '\0') {
    if (*(char *)(param_1 + 0x94) == '\0') {
      fVar4 = (float10)FUN_0042df50(&local_10);
      local_a8 = (float)fVar4;
      fVar4 = (float10)FUN_0042de80(local_8 * local_8 + local_10 * local_10);
      local_a0 = (float)fVar4;
      if (local_a8 < 800.0) {
        if (400.0 <= local_a8) {
          FUN_0042df10(local_a8 / 800.0);
        }
        else {
          FUN_0042df10((400.0 / local_a8) / 2.0);
          local_a8 = 400.0;
        }
      }
      local_9c = local_10;
      local_94 = local_8;
      local_98 = local_c - 120.0;
      fVar4 = (float10)FUN_0042df50(&local_9c);
      local_a4 = (float)((float10)*(float *)(param_1 + 0x78) / fVar4);
      if (1.5 < local_a4) {
        local_a4 = 1.5;
      }
      FUN_0042df10(local_a4);
      FUN_0042dec0(param_1 + 0x18);
      *(float *)(param_1 + 0x30) = local_1c - local_9c;
      *(float *)(param_1 + 0x34) = (local_a8 * 0.03 + local_18 + 140.0) - local_98;
      if ((local_18 + 200.0) - local_98 < *(float *)(param_1 + 0x34)) {
        *(float *)(param_1 + 0x34) = (local_18 + 200.0) - local_98;
      }
      *(float *)(param_1 + 0x38) = local_14 - local_94;
      *(float *)(param_1 + 0x60) = local_10;
      *(float *)(param_1 + 100) = (local_c + 20.0) - local_a8 * 0.2;
      *(float *)(param_1 + 0x68) = local_8;
    }
    else {
      for (local_8c = 0; local_8c < 2; local_8c = local_8c + 1) {
        local_90 = 0;
        while (uVar1 = FUN_0064e910(), local_90 < uVar1) {
          FUN_0064eb00(local_8c,local_90,0);
          FUN_0064eb80(local_8c,local_90,0);
          local_90 = local_90 + 1;
        }
        FUN_0064eb00(local_8c,*(undefined4 *)(param_1 + 0x7c),1);
        FUN_0064eb80(local_8c,*(undefined4 *)(param_1 + 0x7c),0x3f800000);
        FUN_0064ebc0(local_8c,*(undefined4 *)(param_1 + 0x7c),*(undefined4 *)(param_1 + 0x80));
      }
      FUN_0064e580(0);
      FUN_00423750(0x3f800000,0,0);
      std::allocator<char>::allocator<char>(local_2c);
      std::allocator<char>::allocator<char>(local_7c);
      std::allocator<char>::allocator<char>(local_6c);
      D3DXMatrixRotationY(local_6c,*(undefined4 *)(param_1 + 0x88));
      D3DXVec3Transform(local_2c,local_88,*(undefined4 *)(param_1 + 4));
      paVar5 = local_6c;
      uVar2 = std::allocator<char>::allocator<char>(local_2c);
      uVar2 = FUN_004237f0(uVar2);
      D3DXVec3Transform(local_2c,uVar2,paVar5);
      D3DXVec3Transform(local_7c,local_88,*(undefined4 *)(param_1 + 8));
      paVar5 = local_6c;
      uVar2 = std::allocator<char>::allocator<char>(local_7c);
      uVar2 = FUN_004237f0(uVar2);
      D3DXVec3Transform(local_7c,uVar2,paVar5);
      uVar2 = std::allocator<char>::allocator<char>(local_2c);
      uVar2 = FUN_004237f0(uVar2);
      puVar3 = (undefined4 *)FUN_00424180(local_d8,uVar2);
      *(undefined4 *)(param_1 + 0x30) = *puVar3;
      *(undefined4 *)(param_1 + 0x34) = puVar3[1];
      *(undefined4 *)(param_1 + 0x38) = puVar3[2];
      uVar2 = std::allocator<char>::allocator<char>(local_7c);
      uVar2 = FUN_004237f0(uVar2);
      puVar3 = (undefined4 *)FUN_00424180(local_f0,uVar2);
      *(undefined4 *)(param_1 + 0x60) = *puVar3;
      *(undefined4 *)(param_1 + 100) = puVar3[1];
      *(undefined4 *)(param_1 + 0x68) = puVar3[2];
    }
  }
  return;
}

