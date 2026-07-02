// ============================================
// Address:  0x00432450
// Original: FUN_00432450
// Status:   unreviewed
// ============================================


void FUN_00432450(uint param_1,undefined4 param_2,undefined1 param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  
  uVar1 = FUN_0063bf40();
  if (param_1 < uVar1) {
    FUN_00424230(param_1);
    iVar2 = FUN_0063bf40();
    if (iVar2 != 0) {
      uVar1 = FUN_0065d150();
      FUN_00424230(param_1);
      uVar3 = FUN_0063bf40();
      uVar5 = (undefined4)((ulonglong)uVar1 % (ulonglong)uVar3);
      FUN_00432500(CONCAT31((int3)((ulonglong)uVar1 % (ulonglong)uVar3 >> 8),param_3));
      uVar1 = (uint)DAT_006cfd00;
      FUN_00424230(param_1);
      puVar4 = (undefined4 *)FUN_004327d0(uVar5);
      FUN_0065b420(*puVar4,uVar1,param_2);
    }
  }
  return;
}

