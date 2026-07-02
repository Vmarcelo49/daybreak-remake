// Function: FUN_0064e760
// Address:  0x0064e760
// Source:   batch_decompile (mass dump)
// Hash:     ccd1e138689e0dd4


void __thiscall FUN_0064e760(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 local_14;
  
  local_14 = D3DXFrameFind(*(undefined4 *)(param_1 + 8),param_2);
  if (local_14 == 0) {
    local_14 = 0;
  }
  else {
    local_14 = local_14 + -0x10;
  }
  if (local_14 != 0) {
    *(undefined4 *)(local_14 + 0xa0) = param_3;
  }
  return;
}

