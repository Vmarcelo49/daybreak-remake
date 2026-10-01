// Function: FUN_0065acb4
// Address:  0x0065acb4
// Source:   batch_decompile (mass dump)
// Hash:     f2bd8cd5f82441d6


void FUN_0065acb4(void)

{
  int iVar1;
  int unaff_EBP;
  undefined4 *unaff_FS_OFFSET;
  
  *(undefined4 *)(unaff_EBP + -4) = 0xffffffff;
  iVar1 = FUN_0064f010();
  *(int *)(unaff_EBP + 0xc) = iVar1 + *(int *)(unaff_EBP + 0xc);
  if (*(int *)(*(int *)(unaff_EBP + -0x28) + 4) != 0) {
    FUN_006541f0(*(undefined4 *)(*(int *)(unaff_EBP + -0x28) + 4),
                 *(undefined4 *)(*(int *)(unaff_EBP + -0x28) + 8));
    deallocate(*(undefined4 *)(*(int *)(unaff_EBP + -0x28) + 4),
               *(int *)(*(int *)(unaff_EBP + -0x28) + 0xc) -
               *(int *)(*(int *)(unaff_EBP + -0x28) + 4) >> 2);
  }
  *(int *)(*(int *)(unaff_EBP + -0x28) + 0xc) =
       *(int *)(unaff_EBP + -0x20) + *(int *)(unaff_EBP + -0x18) * 4;
  *(int *)(*(int *)(unaff_EBP + -0x28) + 8) =
       *(int *)(unaff_EBP + -0x20) + *(int *)(unaff_EBP + 0xc) * 4;
  *(undefined4 *)(*(int *)(unaff_EBP + -0x28) + 4) = *(undefined4 *)(unaff_EBP + -0x20);
  *unaff_FS_OFFSET = *(undefined4 *)(unaff_EBP + -0xc);
  return;
}

