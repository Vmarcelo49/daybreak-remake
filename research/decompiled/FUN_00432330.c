// Function: FUN_00432330
// Address:  0x00432330
// Source:   batch_decompile (mass dump)
// Hash:     98eeb2d9485f1547


void FUN_00432330(uint param_1,undefined4 param_2,undefined1 param_3)

{
  uint uVar1;
  int *piVar2;
  uint *puVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  
  uVar1 = FUN_0063bf40();
  if ((param_1 < uVar1) && (piVar2 = (int *)FUN_004327d0(param_1), *piVar2 != 0)) {
    uVar1 = FUN_0065d150();
    puVar3 = (uint *)FUN_004327d0(param_1);
    uVar5 = (undefined4)((ulonglong)uVar1 % (ulonglong)*puVar3);
    FUN_00432500(CONCAT31((int3)((ulonglong)uVar1 % (ulonglong)*puVar3 >> 8),param_3));
    FUN_00424230(param_1);
    puVar4 = (undefined4 *)FUN_004327d0(uVar5);
    FUN_0065b330(*puVar4,param_2);
  }
  return;
}

