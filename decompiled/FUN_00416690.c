// Function: FUN_00416690
// Address:  0x00416690
// Source:   batch_decompile (mass dump)
// Hash:     a4b489b727f5fa71


undefined4 __thiscall FUN_00416690(int param_1,undefined1 *param_2)

{
  *param_2 = 10;
  param_2[1] = *(undefined1 *)(param_1 + 8);
  param_2[2] = *(undefined1 *)(param_1 + 9);
  _memcpy(param_2 + 3,(void *)(param_1 + 10),0x50);
  return 0x53;
}

