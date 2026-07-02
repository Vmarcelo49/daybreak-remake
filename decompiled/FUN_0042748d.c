// Function: FUN_0042748d
// Address:  0x0042748d
// Source:   batch_decompile (mass dump)
// Hash:     103d988aa3b72660


void FUN_0042748d(void)

{
  int unaff_EBP;
  
  *(int *)(unaff_EBP + -0x14) = *(int *)(unaff_EBP + -0x14) + 0xc;
  if (*(int *)(unaff_EBP + -0x14) != *(int *)(unaff_EBP + 8)) {
    std::allocator<std::_Container_proxy>::destroy
              (*(allocator<std::_Container_proxy> **)(unaff_EBP + 0x14),
               *(_Container_proxy **)(unaff_EBP + -0x14));
    FUN_0042748d();
    return;
  }
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(0,0);
}

