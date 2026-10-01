// Function: FUN_0064ae70
// Address:  0x0064ae70
// Source:   batch_decompile (mass dump)
// Hash:     99942b322fb0d783


void __thiscall FUN_0064ae70(int param_1,int param_2,undefined4 param_3,char param_4)

{
  undefined1 local_9;
  
  if (param_2 < 0x100) {
    if ((param_4 == '\0') || (*(char *)(param_1 + 0x54e0) == '\0')) {
      local_9 = 0;
    }
    else {
      local_9 = 1;
    }
    FUN_0065a260(*(undefined4 *)(param_1 + 0x98 + param_2 * 4),param_3,local_9);
  }
  return;
}

