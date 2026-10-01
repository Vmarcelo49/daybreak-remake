// Function: FUN_0042c800
// Address:  0x0042c800
// Source:   batch_decompile (mass dump)
// Hash:     127576ad1b38e80c


void __thiscall FUN_0042c800(int param_1,undefined2 param_2)

{
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
    *(undefined2 *)(param_1 + 0x88 + local_8 * 2) = param_2;
  }
  return;
}

