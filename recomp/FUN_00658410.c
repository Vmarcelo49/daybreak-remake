// ============================================
// Address:  0x00658410
// Original: FUN_00658410
// Status:   unreviewed
// ============================================


undefined4 __fastcall FUN_00658410(undefined4 *param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1[3] == 0) {
    iVar2 = (**(code **)(*(int *)param_1[2] + 0xc))(param_1[2],&DAT_006ab8a4,param_1 + 3,0);
    if (iVar2 < 0) {
      FUN_006583f0(&DAT_006aad30);
      uVar1 = 0;
    }
    else {
      iVar2 = (**(code **)(*(int *)param_1[3] + 0x2c))(param_1[3],&DAT_006ab5c4);
      if (iVar2 < 0) {
        FUN_006583f0(&DAT_006aad4c);
        uVar1 = 0;
      }
      else {
        iVar2 = (**(code **)(*(int *)param_1[3] + 0x34))(param_1[3],*param_1,0x16);
        if (iVar2 < 0) {
          FUN_006583f0(&DAT_006aad6c);
          uVar1 = 0;
        }
        else {
          (**(code **)(*(int *)param_1[3] + 0x1c))(param_1[3]);
          uVar1 = 1;
        }
      }
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

