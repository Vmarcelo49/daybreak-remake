// ============================================
// Address:  0x00651f80
// Original: FUN_00651f80
// Status:   unreviewed
// ============================================


void FUN_00651f80(int param_1,int param_2)

{
  undefined4 uVar1;
  int local_60;
  undefined1 local_5c [68];
  uint local_18;
  uint local_14;
  int *local_10;
  int local_c;
  uint local_8;
  
  if (param_1 == 0) {
    local_60 = 0;
  }
  else {
    local_60 = param_1 + -4;
  }
  local_c = local_60;
  local_10 = *(int **)(&DAT_006d13c0 + DAT_006d13e8 * 4);
  if (*(int *)(local_60 + 0x20) == 0) {
    if (param_2 == 0) {
      param_2 = 0;
    }
    else {
      param_2 = param_2 + -0x10;
    }
    FUN_00423850(local_5c,&DAT_006d1510);
    (**(code **)(*local_10 + 0x98))(local_10,"mTransform",local_5c,param_2);
    uVar1 = FUN_006531e0(2);
    (**(code **)(*local_10 + 0x80))(local_10,&DAT_006aaae8,uVar1);
    (**(code **)(*local_10 + 0xfc))(local_10,&local_14,0);
    for (local_8 = 0; local_8 < local_14; local_8 = local_8 + 1) {
      (**(code **)(*local_10 + 0x100))(local_10,local_8);
      for (local_18 = 0; local_18 < *(uint *)(local_c + 0x18); local_18 = local_18 + 1) {
        uVar1 = FUN_00662890(local_18);
        (**(code **)(*local_10 + 0xd0))(local_10,&DAT_006aaaec,uVar1);
        (**(code **)(*local_10 + 0x104))(local_10);
        (**(code **)(**(int **)(local_c + 0xc) + 0xc))(*(undefined4 *)(local_c + 0xc),local_18);
      }
      (**(code **)(*local_10 + 0x108))(local_10);
    }
    (**(code **)(*local_10 + 0x10c))(local_10);
  }
  else {
    (**(code **)(*local_10 + 0x98))(local_10,"mTransform",&DAT_006d1510);
    uVar1 = FUN_006531e0(2);
    (**(code **)(*local_10 + 0x80))(local_10,&DAT_006aaad0,uVar1);
    (**(code **)(*local_10 + 0xfc))(local_10,&local_14,0);
    for (local_8 = 0; local_8 < local_14; local_8 = local_8 + 1) {
      (**(code **)(*local_10 + 0x100))(local_10,local_8);
      for (local_18 = 0; local_18 < *(uint *)(local_c + 0x38); local_18 = local_18 + 1) {
        uVar1 = FUN_00662890(*(undefined4 *)(*(int *)(local_c + 0x34) + local_18 * 0x14));
        (**(code **)(*local_10 + 0xd0))(local_10,&DAT_006aaad4,uVar1);
        (**(code **)(*local_10 + 0x104))(local_10);
        (**(code **)(**(int **)(local_c + 0xc) + 0xc))
                  (*(undefined4 *)(local_c + 0xc),
                   *(undefined4 *)(*(int *)(local_c + 0x34) + local_18 * 0x14));
      }
      (**(code **)(*local_10 + 0x108))(local_10);
    }
    (**(code **)(*local_10 + 0x10c))(local_10);
  }
  return;
}

