// ============================================
// Address:  0x00420880
// Original: FUN_00420880
// Status:   unreviewed
// ============================================


void __fastcall FUN_00420880(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  allocator<char> local_14 [16];
  
  if (DAT_006cfdb0 != '\x02') {
    FUN_0065d670();
    FUN_00420b30();
    if (*(char *)(param_1 + 0xaecc) != '\0') {
      std::allocator<char>::allocator<char>(local_14);
      uVar2 = *(undefined4 *)(*(int *)(param_1 + 0xaed0) + 0xaed4);
      uVar1 = FUN_00423750(0,0,0);
      D3DXVec3Transform(local_14,uVar1,uVar2);
      uVar2 = std::allocator<char>::allocator<char>(local_14);
      puVar3 = (undefined4 *)FUN_004237f0(uVar2);
      *(undefined4 *)(param_1 + 0x14) = *puVar3;
      *(undefined4 *)(param_1 + 0x18) = puVar3[1];
      *(undefined4 *)(param_1 + 0x1c) = puVar3[2];
    }
    uVar2 = *(undefined4 *)(param_1 + 0x380);
    uVar1 = FUN_00423750(0,0,0);
    D3DXVec3Transform(param_1 + 0xa4,uVar1,uVar2);
    uVar2 = *(undefined4 *)(param_1 + 900);
    uVar1 = FUN_00423750(0xc1c80000,0,0);
    D3DXVec3Transform(param_1 + 0xb4,uVar1,uVar2);
    uVar2 = std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0xa4));
    puVar3 = (undefined4 *)FUN_004237f0(uVar2);
    *(undefined4 *)(param_1 + 0x2c0) = *puVar3;
    *(undefined4 *)(param_1 + 0x2c4) = puVar3[1];
    *(undefined4 *)(param_1 + 0x2c8) = puVar3[2];
    uVar2 = std::allocator<char>::allocator<char>((allocator<char> *)(param_1 + 0xb4));
    puVar3 = (undefined4 *)FUN_004237f0(uVar2);
    *(undefined4 *)(param_1 + 0x2cc) = *puVar3;
    *(undefined4 *)(param_1 + 0x2d0) = puVar3[1];
    *(undefined4 *)(param_1 + 0x2d4) = puVar3[2];
    D3DXVec3Transform(param_1 + 0xc4,*(int *)(param_1 + 0x10) + 0xc,
                      **(undefined4 **)(param_1 + 0x10));
    D3DXVec3Transform(param_1 + 0xd4,*(int *)(param_1 + 0x10) + 0x18,
                      **(undefined4 **)(param_1 + 0x10));
    FUN_00434840();
    FUN_0065d6a0();
  }
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x14);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x18);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x1c);
  *(undefined1 *)(param_1 + 0x118) = 1;
  fVar4 = (float10)FUN_0065d010(*(undefined4 *)(param_1 + 0x5c));
  fVar6 = (float)(fVar4 * (float10)5.0 + (float10)*(float *)(param_1 + 0x1c));
  fVar5 = *(float *)(param_1 + 0x18) + 145.0;
  fVar4 = (float10)FUN_0065d050(*(undefined4 *)(param_1 + 0x5c),fVar5,fVar6);
  uVar2 = FUN_00423750((float)(fVar4 * (float10)5.0 + (float10)*(float *)(param_1 + 0x14)),fVar5,
                       fVar6);
  FUN_00423830(uVar2);
  if (*(int *)(param_1 + 0xaeb4) != 0) {
    fVar4 = (float10)FUN_0065d010(*(undefined4 *)(param_1 + 0x5c));
    fVar6 = (float)(fVar4 * (float10)5.0 + (float10)*(float *)(param_1 + 0x1c));
    fVar5 = *(float *)(param_1 + 0x18) + 145.0;
    fVar4 = (float10)FUN_0065d050(*(undefined4 *)(param_1 + 0x5c),fVar5,fVar6);
    uVar2 = FUN_00423750((float)(fVar4 * (float10)5.0 + (float10)*(float *)(param_1 + 0x14)),fVar5,
                         fVar6);
    FUN_00423830(uVar2);
  }
  return;
}

