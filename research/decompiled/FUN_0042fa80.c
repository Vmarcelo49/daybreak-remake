// Function: FUN_0042fa80
// Address:  0x0042fa80
// Source:   batch_decompile (mass dump)
// Hash:     adcfcc1ab3ad7a3e


void FUN_0042fa80(void)

{
  char cVar1;
  int *piVar2;
  undefined1 local_18 [4];
  undefined4 *local_14;
  undefined4 *local_10;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_0065d670();
  FUN_00653d10(local_8);
  FUN_00654620(local_c);
  while (cVar1 = const_iterator__operator__(local_c), cVar1 != '\0') {
    piVar2 = (int *)FUN_00653d70();
    local_14 = (undefined4 *)*piVar2;
    local_10 = local_14;
    if (local_14 != (undefined4 *)0x0) {
      (**(code **)*local_14)(1);
    }
    FUN_0042fc40(local_18,0);
  }
  FUN_004261d0();
  FUN_0065d6a0();
  return;
}

