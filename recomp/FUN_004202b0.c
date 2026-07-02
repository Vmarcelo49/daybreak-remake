// ============================================
// Address:  0x004202b0
// Original: FUN_004202b0
// Status:   unreviewed
// ============================================


void __fastcall FUN_004202b0(int param_1)

{
  undefined4 uVar1;
  float10 fVar2;
  
  if (*(int *)(param_1 + 0xa0) == 0) {
    if (*(char *)(param_1 + 0xaecc) == '\0') {
      fVar2 = (float10)FUN_0065d050(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 0x60) +
                                    *(float *)(param_1 + 100));
      *(float *)(param_1 + 0x3c) = (float)(fVar2 * (float10)*(float *)(param_1 + 0x54));
      *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x3c);
      *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_1 + 0x40);
      fVar2 = (float10)FUN_0065d010(*(float *)(param_1 + 0x5c) + *(float *)(param_1 + 0x60) +
                                    *(float *)(param_1 + 100));
      *(float *)(param_1 + 0x44) = (float)(fVar2 * (float10)*(float *)(param_1 + 0x54));
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x44);
      uVar1 = FUN_00423750(*(undefined4 *)(param_1 + 0x48),0,*(undefined4 *)(param_1 + 0x50));
      FUN_0042cb50(uVar1);
      FUN_0042c970(param_1 + 0x4c);
      FUN_0042dd90();
      if (*(float *)(param_1 + 0x18) < -1000.0) {
        *(undefined4 *)(param_1 + 0x14) = 0xc47a0000;
        *(undefined4 *)(param_1 + 0x18) = 0x447a0000;
        *(undefined4 *)(param_1 + 0x1c) = 0xc47a0000;
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x3c) = 0;
      *(undefined4 *)(param_1 + 0x40) = 0;
      *(undefined4 *)(param_1 + 0x44) = 0;
      *(undefined1 *)(param_1 + 0x84) = 0;
    }
  }
  return;
}

