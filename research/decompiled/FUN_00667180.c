// Function: FUN_00667180
// Address:  0x00667180
// Source:   batch_decompile (mass dump)
// Hash:     8601da77be298098


undefined4 __thiscall FUN_00667180(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined4 *puVar2;
  int *piVar3;
  DWORD dwMilliseconds;
  undefined1 local_18 [4];
  undefined1 local_14 [4];
  undefined1 local_10 [4];
  undefined4 local_c;
  undefined4 local_8;
  
  FUN_004248b0(param_1);
  FUN_004248b0();
  FUN_0065d670();
  puVar2 = (undefined4 *)FUN_00653d10(local_10);
  local_8 = *puVar2;
  puVar2 = (undefined4 *)FUN_00654620(local_14);
  local_c = *puVar2;
  while ((cVar1 = const_iterator__operator__(&local_c), cVar1 != '\0' &&
         (piVar3 = (int *)FUN_00653d70(), *piVar3 != param_2))) {
    FUN_0042fc40(local_18,0);
  }
  FUN_0065d6a0();
  cVar1 = const_iterator__operator__(&local_c);
  if (cVar1 != '\0') {
    dwMilliseconds = 0xffffffff;
    puVar2 = (undefined4 *)FUN_00653d70();
    WaitForSingleObject((HANDLE)*puVar2,dwMilliseconds);
  }
  return 0;
}

