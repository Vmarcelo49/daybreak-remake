// Function: FUN_005f60b0
// Address:  0x005f60b0
// Source:   batch_decompile (mass dump)
// Hash:     8fecb8b218feb5b0


void __fastcall FUN_005f60b0(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  float10 fVar3;
  allocator<char> *paVar4;
  int local_54;
  uint local_50;
  allocator<char> local_4c [64];
  int *local_c;
  undefined4 local_8;
  
  FUN_0064e860();
  for (local_50 = 0; uVar1 = FUN_0063bf40(), local_50 < uVar1; local_50 = local_50 + 1) {
    local_c = (int *)FUN_00424230(local_50);
    local_54 = *(int *)(param_1 + 0x154);
    if (0 < local_c[2]) {
      local_54 = *(int *)(param_1 + 0x154) % local_c[2];
    }
    if ((*local_c <= local_54) && (local_54 < local_c[1])) {
      FUN_0064e820(local_c[3],local_c[4]);
    }
  }
  std::allocator<char>::allocator<char>(local_4c);
  D3DXMatrixScaling(*(int *)(param_1 + 0x120) + 0x5c,*(undefined4 *)(param_1 + 0x70),
                    *(undefined4 *)(param_1 + 0x74),*(undefined4 *)(param_1 + 0x78));
  if (*(int *)(param_1 + 0x140) == 0) {
    uVar2 = D3DXMatrixRotationYawPitchRoll
                      (local_4c,(*(float *)(param_1 + 0x2c) * 3.1415927) / 180.0,
                       (*(float *)(param_1 + 0x30) * 3.1415927) / 180.0,
                       (*(float *)(param_1 + 0x34) * 3.1415927) / 180.0);
    FUN_00423780(uVar2);
    if ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x1000) == 0) {
      if ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x4000) == 0) {
        fVar3 = (float10)FUN_0042df50(param_1 + 0x3c);
        if ((float10)0.0 == fVar3) {
          uVar2 = D3DXMatrixRotationZ(local_4c,(*(float *)(param_1 + 0x6c) * 3.1415927) / 180.0);
          FUN_00423780(uVar2);
        }
        else {
          fVar3 = (float10)FUN_0042df50(param_1 + 0x3c);
          fVar3 = (float10)FUN_004365f0((float)((float10)*(float *)(param_1 + 0x40) / fVar3));
          uVar2 = D3DXMatrixRotationZ(local_4c,(float)fVar3);
          FUN_00423780(uVar2);
        }
        uVar2 = D3DXMatrixRotationY(local_4c,(-(*(float *)(param_1 + 0x5c) +
                                               *(float *)(param_1 + 100)) * 3.1415927) / 180.0);
        FUN_00423780(uVar2);
      }
    }
    else {
      paVar4 = local_4c;
      uVar2 = FUN_00423750(0x3f800000,0,0);
      uVar2 = FUN_00661a20(uVar2,paVar4);
      FUN_00423780(uVar2);
    }
    uVar2 = D3DXMatrixTranslation
                      (local_4c,*(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x18),
                       *(undefined4 *)(param_1 + 0x1c));
    FUN_00423780(uVar2);
  }
  else {
    FUN_00423780(*(undefined4 *)(param_1 + 0x140));
  }
  FUN_0064ebc0(0,0,(float)*(int *)(param_1 + 0x154) * 0.016);
  FUN_0064e580(0);
  if (*(int *)(param_1 + 0x13c) != 0) {
    FUN_00436ed0();
  }
  switch(*(undefined4 *)(*(int *)(param_1 + 0x10) + 0x7c)) {
  case 1:
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x16,3);
    FUN_00651110(0);
    FUN_0064e1a0();
    break;
  case 2:
    FUN_00651110(0);
    (**(code **)(*DAT_006d16f8 + 0xe8))(DAT_006d16f8,0x1c,&local_8);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x1c,0);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x16,1);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xe,0);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,2);
    FUN_0064e1a0();
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xe,1);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,6);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x1c,local_8);
    break;
  case 3:
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x16,3);
    FUN_00651110(8);
    if (*(int *)(param_1 + 0x120) != 0) {
      FUN_0064ec00(*(undefined1 *)(param_1 + 0x144),*(undefined1 *)(param_1 + 0x145),
                   *(undefined1 *)(param_1 + 0x146),*(undefined1 *)(param_1 + 0x147));
    }
    FUN_0064e1a0();
    break;
  case 4:
    FUN_00651110(8);
    (**(code **)(*DAT_006d16f8 + 0xe8))(DAT_006d16f8,0x1c,&local_8);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x1c,0);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x16,1);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xe,0);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,2);
    if (*(int *)(param_1 + 0x120) != 0) {
      FUN_0064ec00(*(undefined1 *)(param_1 + 0x144),*(undefined1 *)(param_1 + 0x145),
                   *(undefined1 *)(param_1 + 0x146),*(undefined1 *)(param_1 + 0x147));
    }
    FUN_0064e1a0();
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xe,1);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,6);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x1c,local_8);
    break;
  default:
    if (DAT_006cfcec == '\0') {
      FUN_00651110(0);
    }
    else {
      FUN_00651110(1);
    }
    FUN_0064e1a0();
  }
  if (*(int *)(param_1 + 0x13c) != 0) {
    FUN_00436ab0();
  }
  return;
}

