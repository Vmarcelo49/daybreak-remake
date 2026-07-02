// Function: FUN_00650de0
// Address:  0x00650de0
// Source:   batch_decompile (mass dump)
// Hash:     7fb188b5415a302d


char __fastcall FUN_00650de0(int param_1)

{
  char cVar1;
  undefined4 extraout_ECX;
  undefined4 extraout_ECX_00;
  undefined4 uVar2;
  int local_10;
  int local_c;
  
  if (*(int *)(param_1 + 0x28c) == -0x7789f798) {
    cVar1 = '\0';
  }
  else {
    FUN_0065d670();
    for (local_c = 0; local_c < 10; local_c = local_c + 1) {
      if (*(int *)(param_1 + local_c * 4) != 0) {
        (**(code **)(**(int **)(param_1 + local_c * 4) + 0x114))
                  (*(undefined4 *)(param_1 + local_c * 4));
      }
    }
    FUN_00650640();
    cVar1 = FUN_00654d90();
    uVar2 = extraout_ECX;
    if (cVar1 != '\0') {
      for (local_10 = 0; local_10 < 10; local_10 = local_10 + 1) {
        if (*(int *)(param_1 + local_10 * 4) != 0) {
          (**(code **)(**(int **)(param_1 + local_10 * 4) + 0x118))
                    (*(undefined4 *)(param_1 + local_10 * 4));
        }
      }
      FUN_00650410();
      uVar2 = extraout_ECX_00;
    }
    FUN_00654170(0);
    FUN_00656300(uVar2);
    FUN_00651110(0xffffffff);
    *(undefined1 *)(param_1 + 0x59) = 0;
    FUN_0065d6a0();
  }
  return cVar1;
}

