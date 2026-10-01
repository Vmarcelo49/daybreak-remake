// Function: FUN_006507c0
// Address:  0x006507c0
// Source:   batch_decompile (mass dump)
// Hash:     01d534bf9351fc9d


void __fastcall FUN_006507c0(int param_1)

{
  undefined4 uVar1;
  float10 fVar2;
  undefined1 *puVar3;
  allocator<char> *paVar4;
  undefined1 local_164 [64];
  undefined1 local_124 [64];
  undefined1 local_e4 [64];
  undefined1 local_a4 [12];
  undefined1 local_98 [12];
  allocator<char> local_8c [68];
  float local_48;
  allocator<char> local_44 [64];
  
  std::allocator<char>::allocator<char>(local_44);
  std::allocator<char>::allocator<char>(local_8c);
  FUN_00661770();
  (**(code **)(*DAT_006d16f8 + 0xb0))(DAT_006d16f8,3,param_1 + 0x110);
  (**(code **)(*DAT_006d16f8 + 0xb0))(DAT_006d16f8,2,param_1 + 0x60);
  FUN_00423750(0x447a0000,0x49742400,0x48f42400);
  uVar1 = FUN_0042dfd0(local_a4,local_98);
  fVar2 = (float10)FUN_0042df50(uVar1);
  local_48 = (float)fVar2;
  D3DXMatrixLookAtLH(param_1 + 400,local_98,param_1 + 0xe0,param_1 + 0xf8);
  D3DXMatrixPerspectiveFovLH
            (param_1 + 0x1d0,0x3a89421f,0x3f800000,local_48 - 300.0,local_48 + 800.0);
  FUN_00423890(local_44);
  fVar2 = (float10)FUN_00423580(*(float *)(param_1 + 0xf4) - *(float *)(param_1 + 0xe8),
                                *(float *)(param_1 + 0xec) - *(float *)(param_1 + 0xe0));
  D3DXMatrixRotationZ(local_8c,(float)(-fVar2 - (float10)0.7853982));
  FUN_00423780(local_8c);
  D3DXMatrixScaling(local_8c,0x3f666666,0x3f666666,0x3f800000);
  FUN_00423780(local_8c);
  D3DXMatrixTranslation(local_8c,0x3f333333,0xbf333333,0);
  FUN_00423780(local_8c);
  uVar1 = FUN_00423850(local_e4,param_1 + 0x110);
  FUN_0064ee60(uVar1);
  paVar4 = local_44;
  puVar3 = local_164;
  FUN_00423850(local_124,param_1 + 0x1d0);
  uVar1 = FUN_00423850(puVar3,paVar4);
  FUN_0064ee60(uVar1);
  return;
}

