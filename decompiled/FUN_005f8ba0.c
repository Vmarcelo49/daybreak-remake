// Function: FUN_005f8ba0
// Address:  0x005f8ba0
// Source:   batch_decompile (mass dump)
// Hash:     8b9a5e8729301560


void __thiscall
FUN_005f8ba0(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 *param_6,int param_7)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 local_34;
  undefined1 local_30 [8];
  undefined1 local_28;
  undefined1 local_27;
  int local_24;
  undefined2 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  DAT_006b7630 = DAT_006b7630 + 2;
  if (DAT_006cfdb0 == '\x01') {
    FUN_005f8ec0();
    local_28 = *(undefined1 *)(param_1[0xb] + 8);
    local_27 = *(undefined1 *)(param_7 + 8);
    local_24 = DAT_006b7630;
    local_20 = (undefined2)param_2;
    local_1c = param_3;
    local_18 = param_4;
    local_14 = param_5;
    local_10 = *param_6;
    local_c = param_6[1];
    local_8 = param_6[2];
    FUN_00415d30(0,local_30,0,0x88);
  }
  FUN_0065d670();
  uVar1 = FUN_00423750(param_3,param_4,param_5);
  local_34 = (**(code **)(*param_1 + 8))(param_2,uVar1,param_6,param_7);
  FUN_00435e60(&local_34);
  puVar2 = (undefined4 *)FUN_00667280();
  (**(code **)(*(int *)*puVar2 + 0x10))();
  FUN_0065d6a0();
  return;
}

