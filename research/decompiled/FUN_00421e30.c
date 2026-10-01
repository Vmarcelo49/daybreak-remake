// Function: FUN_00421e30
// Address:  0x00421e30
// Source:   batch_decompile (mass dump)
// Hash:     7b9015054e1f06d0


void __thiscall FUN_00421e30(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int *piVar2;
  
  *(undefined4 *)(param_1 + 0x300) = param_2;
  *(undefined4 *)(param_1 + 0x30c) = 0xf;
  puVar1 = (undefined4 *)FUN_00658a10(*(undefined4 *)(param_1 + 0x300));
  *(undefined4 *)(param_1 + 0x38) = *puVar1;
  puVar1 = (undefined4 *)FUN_00658a10(*(undefined4 *)(param_1 + 0x300));
  *(undefined4 *)(param_1 + 0x308) = *puVar1;
  *(undefined4 *)(param_1 + 0x304) = 0xffffffff;
  piVar2 = (int *)FUN_00658a10(0);
  if (*(int *)(param_1 + 0x308) == *(int *)(*piVar2 + 0x308)) {
    *(undefined4 *)(param_1 + 0x848) = 0xb4;
    if (*(char *)(param_1 + 0x845) == '\0') {
      FUN_0064ae10(*(undefined4 *)(param_1 + 8),0xe);
    }
    else {
      FUN_0064ae10(*(undefined4 *)(param_1 + 8),0xf);
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x848) = 0;
    FUN_0064ae10(*(undefined4 *)(param_1 + 8),0xd);
  }
  return;
}

