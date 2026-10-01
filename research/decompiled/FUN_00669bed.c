// Function: FUN_00669bed
// Address:  0x00669bed
// Source:   batch_decompile (mass dump)
// Hash:     48b38b4790007f56


void FUN_00669bed(void)

{
  int unaff_EBP;
  
  FUN_0066d2cc();
  basic_string<>("string too long");
  *(undefined4 *)(unaff_EBP + -4) = 0;
  FID_conflict_runtime_error(unaff_EBP + -0x28);
  *(undefined ***)(unaff_EBP + -0x50) = &PTR_FUN_006ab380;
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(unaff_EBP + -0x50,&DAT_006b1da0);
}

