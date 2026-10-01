// Function: FUN_004221e0
// Address:  0x004221e0
// Source:   batch_decompile (mass dump)
// Hash:     c687fb62b380e713


void __thiscall FUN_004221e0(int param_1,undefined4 param_2)

{
  undefined1 local_14 [8];
  undefined4 local_c;
  undefined4 local_8;
  
  *(undefined4 *)(param_1 + 0x828) = param_2;
  if (DAT_006cfdb0 == '\x01') {
    FUN_00423c10();
    local_c = *(undefined4 *)(param_1 + 8);
    local_8 = *(undefined4 *)(param_1 + 0x828);
    FUN_00415d30(0,local_14,0,8);
  }
  return;
}

