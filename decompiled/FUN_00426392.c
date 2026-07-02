// Function: FUN_00426392
// Address:  0x00426392
// Source:   batch_decompile (mass dump)
// Hash:     6030ead3a84c5ab7


void FUN_00426392(void)

{
  undefined4 *puVar1;
  int unaff_EBP;
  
  if (*(uint *)(unaff_EBP + 0xc) < *(uint *)(unaff_EBP + -0x14)) {
    *(undefined4 *)(unaff_EBP + -0x18) = *(undefined4 *)(unaff_EBP + 8);
    puVar1 = (undefined4 *)FUN_00435f10();
    FUN_00425500(unaff_EBP + -0x1c,*puVar1);
    FUN_00426389();
    return;
  }
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(0,0);
}

