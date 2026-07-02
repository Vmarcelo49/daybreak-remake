// ============================================
// Address:  0x00426604
// Original: FUN_00426604
// Status:   unreviewed
// ============================================


void FUN_00426604(void)

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

