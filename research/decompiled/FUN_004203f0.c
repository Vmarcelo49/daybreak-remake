// Function: FUN_004203f0
// Address:  0x004203f0
// Source:   batch_decompile (mass dump)
// Hash:     2c02ff63b51ae970


void __fastcall FUN_004203f0(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_8;
  
  FUN_0064e1a0();
  if (*(int *)(param_1 + 0x7f8) != 0) {
    puVar2 = *(undefined4 **)(param_1 + 0x380);
    puVar3 = (undefined4 *)(*(int *)(*(int *)(param_1 + 0x23c) + 0x44a8) + 0x5c);
    for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
      *puVar3 = *puVar2;
      puVar2 = puVar2 + 1;
      puVar3 = puVar3 + 1;
    }
    FUN_0064e580(0);
    FUN_0064e1a0();
  }
  if (*(int *)(param_1 + 0x82c) != 0) {
    FUN_00651110(0);
    (**(code **)(*DAT_006d16f8 + 0xe8))(DAT_006d16f8,0x1c,&local_8);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x1c,0);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x13,10);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,1);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xe,0);
    D3DXMatrixScaling(*(int *)(*(int *)(param_1 + 0x23c) + 0x44b0) + 0x5c,0x43000000,0x43000000,
                      0x43000000);
    FUN_00423780(*(undefined4 *)(param_1 + 900));
    FUN_0064e580(0);
    FUN_0064e1a0();
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x13,5);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,6);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0xe,1);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x1c,local_8);
  }
  return;
}

