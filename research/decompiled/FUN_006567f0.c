// Function: FUN_006567f0
// Address:  0x006567f0
// Source:   batch_decompile (mass dump)
// Hash:     cb840a030bbbf523


void __thiscall FUN_006567f0(int param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  uVar1 = FUN_0064f010();
  uVar2 = FUN_0065aa30();
  if (uVar1 < uVar2) {
    uVar3 = FUN_00654640(*(undefined4 *)(param_1 + 8),1,param_2);
    *(undefined4 *)(param_1 + 8) = uVar3;
  }
  else {
    puVar4 = (undefined4 *)FUN_00654670(local_8);
    FUN_00656860(local_c,*puVar4,param_2);
  }
  return;
}

