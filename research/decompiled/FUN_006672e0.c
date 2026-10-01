// Function: FUN_006672e0
// Address:  0x006672e0
// Source:   batch_decompile (mass dump)
// Hash:     fa416a305029e218


void __thiscall FUN_006672e0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  
  uVar1 = FUN_0068de10(param_1);
  puVar2 = (undefined4 *)FUN_00653df0(uVar1,param_3);
  uVar3 = FUN_00667440(uVar1,*puVar2);
  FUN_00667500(1);
  puVar2 = (undefined4 *)FUN_00653df0(uVar1);
  *puVar2 = uVar3;
  puVar2 = (undefined4 *)FUN_00653df0(uVar3);
  puVar2 = (undefined4 *)FUN_00663590(*puVar2);
  *puVar2 = uVar3;
  return;
}

