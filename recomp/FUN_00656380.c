// ============================================
// Address:  0x00656380
// Original: FUN_00656380
// Status:   unreviewed
// ============================================


void FUN_00656380(undefined4 param_1,undefined4 *param_2,undefined4 *param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  undefined4 extraout_var;
  undefined4 uVar3;
  int *local_28;
  undefined1 local_24 [24];
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_0065d670();
  uVar3 = extraout_var;
  puVar2 = (undefined4 *)FUN_00656740(param_1);
  piVar1 = (int *)*puVar2;
  (**(code **)(*piVar1 + 0x48))(piVar1,0,&local_28,piVar1,uVar3);
  (**(code **)(*local_28 + 0x30))(local_28,local_24);
  *param_2 = local_c;
  *param_3 = local_8;
  (**(code **)(*local_28 + 8))(local_28);
  FUN_0065d6a0();
  return;
}

