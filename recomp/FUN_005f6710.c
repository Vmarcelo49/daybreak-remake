// ============================================
// Address:  0x005f6710
// Original: FUN_005f6710
// Status:   unreviewed
// ============================================


void __fastcall FUN_005f6710(int param_1)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  allocator<char> *paVar4;
  float10 fVar5;
  allocator<char> local_84 [64];
  allocator<char> local_44 [64];
  
  std::allocator<char>::allocator<char>(local_44);
  std::allocator<char>::allocator<char>(local_84);
  FUN_00423890(local_44);
  fVar5 = (float10)FUN_0042df50(param_1 + 0x3c);
  if ((float10)0.0 == fVar5) {
    puVar1 = (undefined4 *)
             D3DXMatrixRotationZ(local_84,(*(float *)(param_1 + 0x6c) * 3.1415927) / 180.0);
    paVar4 = local_44;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined4 *)paVar4 = *puVar1;
      puVar1 = puVar1 + 1;
      paVar4 = paVar4 + 4;
    }
  }
  else {
    fVar5 = (float10)FUN_0042df50(param_1 + 0x3c);
    fVar5 = (float10)FUN_004365f0((float)((float10)*(float *)(param_1 + 0x40) / fVar5));
    puVar1 = (undefined4 *)D3DXMatrixRotationZ(local_84,(float)fVar5);
    paVar4 = local_44;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined4 *)paVar4 = *puVar1;
      puVar1 = puVar1 + 1;
      paVar4 = paVar4 + 4;
    }
  }
  uVar2 = D3DXMatrixRotationY(local_84,(-(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 100)) *
                                       3.1415927) / 180.0);
  FUN_00423780(uVar2);
  uVar2 = D3DXMatrixTranslation
                    (local_84,*(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x18),
                     *(undefined4 *)(param_1 + 0x1c));
  FUN_00423780(uVar2);
  D3DXVec3Transform(param_1 + 0xc4,*(int *)(param_1 + 0x10) + 0xc,local_44);
  D3DXVec3Transform(param_1 + 0xd4,*(int *)(param_1 + 0x10) + 0x18,local_44);
  return;
}

