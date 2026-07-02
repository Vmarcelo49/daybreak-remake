// Function: FUN_00416230
// Address:  0x00416230
// Source:   batch_decompile (mass dump)
// Hash:     0b7b54fb06966af9


bool __thiscall FUN_00416230(int param_1,int param_2)

{
  bool bVar1;
  
  FUN_0065d670();
  bVar1 = *(uint *)(param_1 + 0x78 + param_2 * 4) < 0x10;
  if (bVar1) {
    FUN_0065d6a0();
  }
  else {
    FUN_0065d6a0();
  }
  return !bVar1;
}

