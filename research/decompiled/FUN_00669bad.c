// Function: FUN_00669bad
// Address:  0x00669bad
// Source:   batch_decompile (mass dump)
// Hash:     0dcf01366b19e97f


void FUN_00669bad(void)

{
  int unaff_EBP;
  
  FUN_0066d2cc();
  basic_string<>("invalid string position");
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FID_conflict_runtime_error(unaff_EBP + -0x28);
  *(undefined ***)(unaff_EBP + -0x50) = &PTR_FUN_006ab38c;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(unaff_EBP + -0x50,&DAT_006b2d40);
}

