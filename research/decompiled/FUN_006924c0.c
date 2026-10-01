// Function: FUN_006924c0
// Address:  0x006924c0
// Source:   batch_decompile (mass dump)
// Hash:     d6ecfb632e87c8d0


int FUN_006924c0(ushort *param_1,ushort *param_2)

{
  ushort uVar1;
  
  do {
    if (*param_1 != *param_2) {
      return (uint)*param_1 - (uint)*param_2;
    }
    uVar1 = *param_1;
    param_1 = param_1 + 1;
  } while ((uVar1 != 0) && (uVar1 = *param_2, param_2 = param_2 + 1, uVar1 != 0));
  return 0;
}

