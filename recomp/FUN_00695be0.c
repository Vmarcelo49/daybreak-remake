// ============================================
// Address:  0x00695be0
// Original: FUN_00695be0
// Status:   unreviewed
// ============================================


undefined4
FUN_00695be0(undefined4 param_1,undefined4 *param_2,int param_3,undefined4 param_4,
            undefined4 param_5,int param_6)

{
  int iVar1;
  undefined4 uVar2;
  
  if (param_2 != (undefined4 *)0x0) {
    if (((param_3 == 0) || (iVar1 = FUN_006871b0(param_3,&DAT_006ad154), iVar1 != 0)) &&
       ((param_6 == 0 || (iVar1 = FUN_006871b0(param_6,&DAT_006ad154), iVar1 != 0)))) {
      *param_2 = param_4;
      param_2[1] = param_5;
      uVar2 = 0;
    }
    else {
      uVar2 = 0x80070057;
    }
    return uVar2;
  }
  return 0x80004003;
}

