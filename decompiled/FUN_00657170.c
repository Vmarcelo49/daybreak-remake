// Function: FUN_00657170
// Address:  0x00657170
// Source:   batch_decompile (mass dump)
// Hash:     a8f4b9d58d2882ed


int __thiscall FUN_00657170(undefined4 param_1,undefined4 param_2,int param_3,undefined4 *param_4)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  int iVar4;
  undefined1 local_c [4];
  undefined4 local_8;
  
  uVar2 = *(uint *)(param_3 + 0x140);
  uVar1 = (*(int *)(param_3 + 0x134) + *(int *)(param_3 + 0x138)) * *(int *)(param_3 + 0x144);
  bVar3 = 0;
  iVar4 = 0;
  if (1 < uVar2) {
    for (uVar2 = uVar2 - 1; uVar2 != 1; uVar2 = uVar2 >> 1) {
      bVar3 = bVar3 + 1;
    }
    uVar2 = 2 << (bVar3 & 0x1f);
  }
  if (1 < uVar1) {
    for (uVar1 = uVar1 - 1; uVar1 != 1; uVar1 = uVar1 >> 1) {
      iVar4 = iVar4 + 1;
    }
    uVar1 = 2 << ((byte)iVar4 & 0x1f);
  }
  FUN_0065d670(param_1,0x8876086c,iVar4,uVar2,uVar1);
  iVar4 = D3DXCreateTexture(DAT_006d16f8,uVar2,uVar1,1,0,0x15,1,param_4);
  FUN_0065d6a0();
  if (-1 < iVar4) {
    FUN_0065d670(param_1);
    iVar4 = (**(code **)(*(int *)*param_4 + 0x4c))(*param_4,0,local_c,0,0);
    if (iVar4 == 0) {
      FUN_0065dad0(param_2,local_8,uVar2,uVar1,0x20);
      (**(code **)(*(int *)*param_4 + 0x50))(*param_4,0);
    }
    FUN_0065d6a0();
  }
  return iVar4;
}

