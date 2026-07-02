// Function: FUN_0040f130
// Address:  0x0040f130
// Source:   batch_decompile (mass dump)
// Hash:     47ed3b8e6bbc7067


undefined4 __fastcall FUN_0040f130(int param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint local_18;
  uint local_c;
  int local_8;
  
  cVar1 = FUN_00650f70();
  if (cVar1 != '\0') {
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,0);
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x16,1);
    iVar2 = FUN_0068de10();
    if (iVar2 != 0) {
      FUN_00655d60(0,0);
    }
    if (*(char *)(param_1 + 0x769) != '\0') {
      FUN_00651860(0,0,0x44480000,0x44160000,(uint)*(byte *)(param_1 + 0x769) << 0x18);
    }
    for (local_8 = 0; local_8 < 6; local_8 = local_8 + 1) {
      iVar2 = FUN_0068de10();
      if (iVar2 != 0) {
        FUN_00655d60(*(undefined4 *)(param_1 + 0x6ac + *(int *)(param_1 + 0x740 + local_8 * 4) * 4),
                     0x42b00000);
      }
    }
    FUN_004082f0(0x80ffffff);
    FUN_00655d60(0x41200000,0x43dc0000);
    if ((((*(char *)(param_1 + 0x759) == '\0') && (*(char *)(param_1 + 0x76b) == '\0')) &&
        (*(char *)(param_1 + 0x76c) == '\0')) &&
       ((*(int *)(param_1 + 0x760) < *(int *)(param_1 + 0x75c) &&
        ((*(int *)(param_1 + 0x75c) - *(int *)(param_1 + 0x760)) % 0x3c < 0x1e)))) {
      FUN_00655d60(0x44340000,0x44098000);
    }
    FUN_004082f0(0xff000000);
    for (local_c = 0; ((int)local_c < 0x80 && ((int)local_c < *(int *)(param_1 + 0x75c)));
        local_c = local_c + 1) {
      uVar3 = local_c & 0x8000001f;
      if ((int)uVar3 < 0) {
        uVar3 = (uVar3 - 1 | 0xffffffe0) + 1;
      }
      iVar2 = (int)(local_c + ((int)local_c >> 0x1f & 0x1fU)) >> 5;
      FUN_00655830((float)(int)(uVar3 * 0x18 + 0x17),(float)(iVar2 * 0x22 + 0x1c5),uVar3,iVar2);
    }
    FUN_004082f0(0xffffffff);
    for (local_18 = 0; ((int)local_18 < 0x80 && ((int)local_18 < *(int *)(param_1 + 0x75c)));
        local_18 = local_18 + 1) {
      uVar3 = local_18 & 0x8000001f;
      if ((int)uVar3 < 0) {
        uVar3 = (uVar3 - 1 | 0xffffffe0) + 1;
      }
      iVar2 = (int)(local_18 + ((int)local_18 >> 0x1f & 0x1fU)) >> 5;
      FUN_00655830((float)(int)(uVar3 * 0x18 + 0x14),(float)(iVar2 * 0x22 + 0x1c2),uVar3,iVar2);
    }
    if (*(char *)(param_1 + 0x76a) != '\0') {
      FUN_00651860(0,0,0x44480000,0x44160000,(uint)*(byte *)(param_1 + 0x76a) << 0x18);
      FUN_004082f0((uint)*(byte *)(param_1 + 0x76a) << 0x18 | 0xffffff);
      FUN_00655d60(0x44228000,0x44020000);
    }
    FUN_00650fd0();
  }
  return 1;
}

