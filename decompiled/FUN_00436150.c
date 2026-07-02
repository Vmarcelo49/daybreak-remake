// Function: FUN_00436150
// Address:  0x00436150
// Source:   batch_decompile (mass dump)
// Hash:     47c09dea7289440e


void __fastcall FUN_00436150(int param_1)

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
    local_54 = *(int *)(param_1 + 0x130);
    if (0 < local_c[2]) {
      local_54 = *(int *)(param_1 + 0x130) % local_c[2];
    }
    if ((*local_c <= local_54) && (local_54 < local_c[1])) {
      FUN_0064e820(local_c[3],local_c[4]);
    }
  }
  std::allocator<char>::allocator<char>(local_4c);
  D3DXMatrixScaling(*(int *)(param_1 + 0x11c) + 0x5c,*(undefined4 *)(param_1 + 0x70),
                    *(undefined4 *)(param_1 + 0x74),*(undefined4 *)(param_1 + 0x78));
  if ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x1000) == 0) {
    fVar3 = (float10)FUN_0042df50(param_1 + 0x3c);
    fVar3 = (float10)FUN_004365f0((float)((float10)*(float *)(param_1 + 0x40) / fVar3));
    uVar2 = D3DXMatrixRotationZ(local_4c,(float)fVar3);
    FUN_00423780(uVar2);
    fVar3 = (float10)FUN_004235a0(*(undefined4 *)(param_1 + 0x44),*(undefined4 *)(param_1 + 0x3c));
    uVar2 = D3DXMatrixRotationY(local_4c,(float)-fVar3);
    FUN_00423780(uVar2);
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
  FUN_0064ebc0(0,0,(float)*(int *)(param_1 + 0x130) * 0.016);
  FUN_0064e580(0);
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
    FUN_0064e1a0();
    break;
  case 4:
    FUN_00651110(8);
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
  default:
    FUN_00651110(1);
    FUN_0064e1a0();
  }
  return;
}

