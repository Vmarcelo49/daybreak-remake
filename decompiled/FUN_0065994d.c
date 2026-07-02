// Function: FUN_0065994d
// Address:  0x0065994d
// Source:   batch_decompile (mass dump)
// Hash:     932899bab4357929


void FUN_0065994d(void)

{
  int unaff_EBP;
  
  *(int *)(unaff_EBP + -0x14) = *(int *)(unaff_EBP + -0x14) + 0x50;
  if (*(int *)(unaff_EBP + -0x14) != *(int *)(unaff_EBP + 8)) {
    std::allocator<std::_Container_proxy>::destroy
              (*(allocator<std::_Container_proxy> **)(unaff_EBP + 0x14),
               *(_Container_proxy **)(unaff_EBP + -0x14));
    FUN_0065994d();
    return;
  }
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(0,0);
}

