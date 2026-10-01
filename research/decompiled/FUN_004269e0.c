// Function: FUN_004269e0
// Address:  0x004269e0
// Source:   batch_decompile (mass dump)
// Hash:     20132e3fa2308d34


void FUN_004269e0(void)

{
  int iVar1;
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  iVar1 = FUN_004258e0();
  *(int *)(unaff_EBP + 0xc) = iVar1 + *(int *)(unaff_EBP + 0xc);
  if (*(int *)(*(int *)(unaff_EBP + -0x30) + 4) != 0) {
    FUN_00426840(*(undefined4 *)(*(int *)(unaff_EBP + -0x30) + 4),
                 *(undefined4 *)(*(int *)(unaff_EBP + -0x30) + 8));
    deallocate(*(undefined4 *)(*(int *)(unaff_EBP + -0x30) + 4),
               (*(int *)(*(int *)(unaff_EBP + -0x30) + 0xc) -
               *(int *)(*(int *)(unaff_EBP + -0x30) + 4)) / 0xc);
  }
  *(int *)(*(int *)(unaff_EBP + -0x30) + 0xc) =
       *(int *)(unaff_EBP + -0x20) * 0xc + *(int *)(unaff_EBP + -0x28);
  *(int *)(*(int *)(unaff_EBP + -0x30) + 8) =
       *(int *)(unaff_EBP + 0xc) * 0xc + *(int *)(unaff_EBP + -0x28);
  *(undefined4 *)(*(int *)(unaff_EBP + -0x30) + 4) = *(undefined4 *)(unaff_EBP + -0x28);
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0xc);
  return;
}

