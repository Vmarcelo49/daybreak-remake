// Function: FUN_006430f0
// Address:  0x006430f0
// Source:   batch_decompile (mass dump)
// Hash:     999ee136a5816d61


void FUN_006430f0(void)

{
  int local_8;
  
  for (local_8 = 0; local_8 < 2; local_8 = local_8 + 1) {
    if ((&DAT_006c78e0)[local_8] != 0) {
      (&DAT_006c78e0)[local_8] = (&DAT_006c78e0)[local_8] + -1;
    }
    if (*(float *)(&DAT_006c78f0 + local_8 * 4) <
        (float)*(int *)(*(int *)(&DAT_006c78d8 + local_8 * 4) + 4)) {
      *(float *)(&DAT_006c78f0 + local_8 * 4) = *(float *)(&DAT_006c78f0 + local_8 * 4) + 0.5;
    }
    if ((float)*(int *)(*(int *)(&DAT_006c78d8 + local_8 * 4) + 4) <
        *(float *)(&DAT_006c78f0 + local_8 * 4)) {
      *(float *)(&DAT_006c78f0 + local_8 * 4) = *(float *)(&DAT_006c78f0 + local_8 * 4) - 0.5;
    }
  }
  return;
}

