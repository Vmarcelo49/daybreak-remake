// Function: FUN_00634980
// Address:  0x00634980
// Source:   batch_decompile (mass dump)
// Hash:     3375432960b128f2


void __fastcall FUN_00634980(int param_1)

{
  int *piVar1;
  undefined4 uVar2;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  for (local_8 = 0; local_8 < 2; local_8 = local_8 + 1) {
    *(int *)(param_1 + 0x12ac + local_8 * 0xc) = local_8;
    *(undefined4 *)(param_1 + 0x12b0 + local_8 * 0xc) = 0;
    *(undefined4 *)(param_1 + 0x12b4 + local_8 * 0xc) =
         *(undefined4 *)(param_1 + 0x43c4 + local_8 * 4);
  }
  *(int *)(*(int *)(param_1 + 0x12a0) + 0xc) = param_1 + 0x12ac;
  *(undefined4 *)(*(int *)(param_1 + 0x129c) + 0xc) =
       *(undefined4 *)(*(int *)(param_1 + 0x12a0) + 0xc);
  *(int *)(*(int *)(param_1 + 0x12a8) + 0xc) = param_1 + 0x12b8;
  *(undefined4 *)(*(int *)(param_1 + 0x12a4) + 0xc) =
       *(undefined4 *)(*(int *)(param_1 + 0x12a8) + 0xc);
  *(undefined4 *)(*(int *)(param_1 + 0x12a0) + 0xaee0) = *(undefined4 *)(param_1 + 0x12b4);
  *(undefined4 *)(*(int *)(param_1 + 0x129c) + 0xaee0) =
       *(undefined4 *)(*(int *)(param_1 + 0x12a0) + 0xaee0);
  *(undefined4 *)(*(int *)(param_1 + 0x12a8) + 0xaee0) = *(undefined4 *)(param_1 + 0x12c0);
  *(undefined4 *)(*(int *)(param_1 + 0x12a4) + 0xaee0) =
       *(undefined4 *)(*(int *)(param_1 + 0x12a8) + 0xaee0);
  *(undefined4 *)(*(int *)(param_1 + 0x12a0) + 0xaee4) = *(undefined4 *)(param_1 + 0x12c0);
  *(undefined4 *)(*(int *)(param_1 + 0x129c) + 0xaee4) =
       *(undefined4 *)(*(int *)(param_1 + 0x12a0) + 0xaee4);
  *(undefined4 *)(*(int *)(param_1 + 0x12a8) + 0xaee4) = *(undefined4 *)(param_1 + 0x12b4);
  *(undefined4 *)(*(int *)(param_1 + 0x12a4) + 0xaee4) =
       *(undefined4 *)(*(int *)(param_1 + 0x12a8) + 0xaee4);
  for (local_c = 0; local_c < 4; local_c = local_c + 1) {
    for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
      if (local_10 != local_c) {
        if (**(int **)(*(int *)(param_1 + 0x129c + local_c * 4) + 0xc) ==
            **(int **)(*(int *)(param_1 + 0x129c + local_10 * 4) + 0xc)) {
          FUN_00421730(*(undefined4 *)(param_1 + 0x129c + local_10 * 4));
        }
        else {
          FUN_00421670(*(undefined4 *)(param_1 + 0x129c + local_10 * 4));
        }
      }
    }
  }
  for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1) {
    uVar2 = 1;
    piVar1 = (int *)FUN_00658a10(*(undefined4 *)(*(int *)(param_1 + 0x129c + local_14 * 4) + 0x300))
    ;
    FUN_00632e70(*piVar1 + 0x14,uVar2);
    FUN_00632ed0(*(int *)(param_1 + 0x129c + local_14 * 4) + 0x14,1);
    FUN_00633220();
    FUN_006333b0();
  }
  return;
}

