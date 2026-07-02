// Function: FUN_0042c7b0
// Address:  0x0042c7b0
// Source:   batch_decompile (mass dump)
// Hash:     4834ce5dbf312fa6


ushort __fastcall FUN_0042c7b0(int param_1)

{
  undefined4 local_c;
  undefined2 local_8;
  
  local_8 = 0;
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    local_8 = local_8 | *(ushort *)(param_1 + 0x88 + local_c * 2);
  }
  return local_8;
}

