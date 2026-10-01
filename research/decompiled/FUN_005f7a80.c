// Function: FUN_005f7a80
// Address:  0x005f7a80
// Source:   batch_decompile (mass dump)
// Hash:     bb65ab8ac67c5cf1


void __thiscall FUN_005f7a80(undefined4 param_1,uint param_2)

{
  uint uVar1;
  undefined1 *puVar2;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  uVar1 = FUN_0064f010(param_1);
  if (uVar1 <= param_2) {
    FUN_005f7ad0();
  }
  puVar2 = local_c;
  FUN_00654620(local_8);
  iterator__operator_(puVar2,param_2);
  FUN_00654770();
  return;
}

