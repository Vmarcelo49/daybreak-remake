// Function: FUN_00426af6
// Address:  0x00426af6
// Source:   batch_decompile (mass dump)
// Hash:     255b193f5b5777f8


void FUN_00426af6(void)

{
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  *(int *)(*(int *)(unaff_EBP + -0x30) + 8) =
       *(int *)(unaff_EBP + 0xc) * 0xc + *(int *)(*(int *)(unaff_EBP + -0x30) + 8);
  FUN_004271d0(*(undefined4 *)(unaff_EBP + 8),
               *(int *)(*(int *)(unaff_EBP + -0x30) + 8) + *(int *)(unaff_EBP + 0xc) * -0xc,
               unaff_EBP + -0x1c);
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0xc);
  return;
}

