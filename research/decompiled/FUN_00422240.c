// Function: FUN_00422240
// Address:  0x00422240
// Source:   batch_decompile (mass dump)
// Hash:     ba39a903c1a1a84e


void __thiscall FUN_00422240(int param_1,undefined4 param_2,undefined4 param_3,undefined1 param_4)

{
  undefined1 local_18 [8];
  undefined1 local_10;
  undefined1 local_f;
  undefined1 local_e;
  undefined2 local_c;
  undefined1 local_a;
  int local_8;
  
  local_8 = param_1 + 0xae1c;
  if ((((*(char *)(param_1 + 0x845) != '\0') || (*(char *)(param_1 + 0x846) != '\0')) ||
      (*(char *)(param_1 + 0x844) != '\0')) && (*(int *)(param_1 + 0xaeb4) != 0)) {
    local_8 = *(int *)(param_1 + 0xaeb4);
  }
  FUN_00432330(param_2,param_3,param_4);
  if (DAT_006cfdb0 == '\x01') {
    FUN_00423cc0();
    local_10 = *(undefined1 *)(param_1 + 8);
    local_f = (undefined1)param_2;
    local_e = 0xff;
    local_c = (undefined2)param_3;
    local_a = param_4;
    FUN_00415d30(0,local_18,0,8);
  }
  return;
}

