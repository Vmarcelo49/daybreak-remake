// Function: FUN_00404a50
// Address:  0x00404a50
// Source:   batch_decompile (mass dump)
// Hash:     c988afd83c2f1744


undefined4 __fastcall FUN_00404a50(int param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  char *pcVar4;
  int local_18;
  int local_14;
  int local_10;
  int local_8;
  
  cVar1 = FUN_00650f70();
  if (cVar1 != '\0') {
    (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,7,0);
    FUN_00655d60(0,0);
    FUN_00655d60(0x43200000,0x42c00000);
    for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
      iVar3 = local_8 * 0x34;
      pcVar4 = &DAT_006cfe20 + iVar3;
      if (*pcVar4 == -1) {
        for (local_10 = 0; local_10 < 0xc; local_10 = local_10 + 1) {
          if (-1 < *(int *)(&DAT_006cfe24 + local_10 * 4 + iVar3)) {
            uVar2 = *(uint *)(&DAT_006cfe24 + local_10 * 4 + iVar3) & 0x8000000f;
            if ((int)uVar2 < 0) {
              uVar2 = (uVar2 - 1 | 0xfffffff0) + 1;
            }
            FUN_00655830((float)local_8 * 64.0 + 272.0 + 64.0,(float)local_10 * 32.0 + 128.0,uVar2,
                         (int)(*(int *)(&DAT_006cfe24 + local_10 * 4 + iVar3) +
                              (*(int *)(&DAT_006cfe24 + local_10 * 4 + iVar3) >> 0x1f & 0xfU)) >> 4)
            ;
          }
        }
      }
      else if (-1 < *pcVar4) {
        for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1) {
          uVar2 = (int)*pcVar4 & 0x80000007;
          if ((int)uVar2 < 0) {
            uVar2 = (uVar2 - 1 | 0xfffffff8) + 1;
          }
          FUN_00655830((float)local_8 * 64.0 + 272.0 + 64.0,(float)local_14 * 32.0 + 128.0,
                       ((int)((int)*pcVar4 + ((int)*pcVar4 >> 0x1f & 7U)) >> 3) + local_14,uVar2);
        }
        for (local_18 = 4; local_18 < 0xc; local_18 = local_18 + 1) {
          if (-1 < *(int *)(&DAT_006cfe24 + local_18 * 4 + iVar3)) {
            FUN_00655830((float)local_8 * 64.0 + 272.0 + 64.0,(float)local_18 * 32.0 + 128.0,
                         *(undefined4 *)(&DAT_006cfe24 + local_18 * 4 + iVar3),(int)*pcVar4);
          }
        }
      }
    }
    if (*(int *)(param_1 + 0x5c0) == 0) {
      if (*(int *)(param_1 + 0x5b8) == 4) {
        FUN_00655d60(0x43200000,0x42c00000);
      }
      else {
        FUN_00655830((float)*(int *)(param_1 + 0x5b8) * 64.0 + 256.0 + 64.0,0x42c00000,
                     *(undefined4 *)(param_1 + 0x5b8),0);
      }
      FUN_00655830(0x42e00000,0x44080000,0,0);
    }
    else if ((*(int *)(param_1 + 0x5c0) == 1) && (*(int *)(param_1 + 0x5bc) < 0xc)) {
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,2);
      FUN_00655d60((float)*(int *)(param_1 + 0x5b8) * 64.0 + 272.0 + 64.0,
                   (float)*(int *)(param_1 + 0x5bc) * 32.0 + 128.0);
      (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8,0x14,6);
      FUN_00655830(0x43300000,0x44080000,0,*(int *)(param_1 + 0x5bc) + 1);
    }
    FUN_00650fd0();
  }
  return 1;
}

