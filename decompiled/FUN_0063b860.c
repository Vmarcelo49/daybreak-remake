// Function: FUN_0063b860
// Address:  0x0063b860
// Source:   batch_decompile (mass dump)
// Hash:     c04b55f1b81d02e3


void __thiscall FUN_0063b860(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined1 *puVar3;
  undefined1 local_14 [8];
  undefined1 local_c [8];
  
  puVar3 = local_14;
  FUN_00425ae0(local_c);
  puVar2 = (undefined4 *)FUN_004372b0(puVar3,param_2);
  uVar1 = puVar2[1];
  *(undefined4 *)(param_1 + 0x18) = *puVar2;
  *(undefined4 *)(param_1 + 0x1c) = uVar1;
  return;
}

