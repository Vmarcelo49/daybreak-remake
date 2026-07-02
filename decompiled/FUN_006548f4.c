// Function: FUN_006548f4
// Address:  0x006548f4
// Source:   batch_decompile (mass dump)
// Hash:     4f4c31dbc1ddb482


void FUN_006548f4(void)

{
  int iVar1;
  int unaff_EBP;
  
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
  ExceptionList = *(void **)(unaff_EBP + -0xc);
  return;
}

