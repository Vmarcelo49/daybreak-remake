// Function: FUN_0067c970
// Address:  0x0067c970
// Source:   batch_decompile (mass dump)
// Hash:     469d53941bd98058


/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_0067c970(int *param_1,undefined4 param_2,int param_3,undefined4 param_4,float param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 auStack_38 [2];
  undefined1 auStack_30 [4];
  int aiStack_2c [5];
  undefined1 auStack_18 [4];
  undefined4 uStack_14;
  
  iVar1 = param_1[10];
  iVar2 = *param_1;
  uStack_14 = 0x67c98f;
  iVar3 = iVar1 * -4;
  puVar5 = (undefined4 *)(&stack0xfffffff0 + iVar3);
  param_5 = param_5 + *(float *)(param_1[1] + 4);
  iVar4 = 0;
  if (0 < iVar1) {
    do {
      *puVar5 = 0xc61c3c00;
      iVar4 = iVar4 + 1;
      puVar5 = puVar5 + 1;
    } while (iVar4 < param_1[10]);
  }
  if (param_5 < *(float *)(param_1[1] + 8)) {
    param_5 = *(float *)(param_1[1] + 8);
  }
  iVar4 = 0;
  if (0 < iVar2) {
    do {
      iVar4 = iVar4 + 1;
      *(float *)(param_3 + -4 + iVar4 * 4) = param_5 + *(float *)(param_1[4] + -4 + iVar4 * 4);
    } while (iVar4 < iVar2);
  }
  (&uStack_14)[-iVar1] = param_4;
  *(undefined1 **)(auStack_18 + iVar3) = &stack0xfffffff0 + iVar3;
  iVar2 = param_1[2];
  aiStack_2c[4 - iVar1] = param_3;
  aiStack_2c[3 - iVar1] = param_2;
  aiStack_2c[2 - iVar1] = iVar2;
  aiStack_2c[1 - iVar1] = (int)param_1;
  aiStack_2c[-iVar1] = 0x67c9f9;
  FUN_0067ca10();
  aiStack_2c[-iVar1] = param_3;
  *(undefined1 **)(auStack_30 + iVar3) = &stack0xfffffff0 + iVar3;
  auStack_38[1 - iVar1] = param_1;
  auStack_38[-iVar1] = 0x67ca04;
  FUN_0067cbc0();
  return;
}

