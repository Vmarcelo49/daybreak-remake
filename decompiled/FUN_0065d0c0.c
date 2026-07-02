// Function: FUN_0065d0c0
// Address:  0x0065d0c0
// Source:   batch_decompile (mass dump)
// Hash:     6401b0f6aba9b3ee


void FUN_0065d0c0(undefined4 param_1)

{
  DAT_006d31d0 = param_1;
  for (DAT_006b77bc = 1; DAT_006b77bc < 0x270; DAT_006b77bc = DAT_006b77bc + 1) {
    (&DAT_006d31d0)[DAT_006b77bc] =
         (*(uint *)(DAT_006b77bc * 4 + 0x6d31cc) >> 0x1e ^ *(uint *)(DAT_006b77bc * 4 + 0x6d31cc)) *
         0x6c078965 + DAT_006b77bc;
    (&DAT_006d31d0)[DAT_006b77bc] = (&DAT_006d31d0)[DAT_006b77bc];
  }
  return;
}

