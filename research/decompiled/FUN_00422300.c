// Function: FUN_00422300
// Address:  0x00422300
// Source:   batch_decompile (mass dump)
// Hash:     5e0d601d356bc4f5


void __thiscall
FUN_00422300(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined1 param_5
            )

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
  FUN_004322b0(param_2,param_3,param_4,param_5);
  if (DAT_006cfdb0 == '\x01') {
    FUN_00423cc0();
    local_10 = *(undefined1 *)(param_1 + 8);
    local_f = (undefined1)param_2;
    local_e = (undefined1)param_3;
    local_c = (undefined2)param_4;
    local_a = param_5;
    FUN_00415d30(0,local_18,0,8);
  }
  return;
}

