// Function: FUN_0068e790
// Address:  0x0068e790
// Source:   batch_decompile (mass dump)
// Hash:     4c3dc6ecfa97533d


undefined4 FUN_0068e790(int param_1,undefined4 param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  if (param_3 == (undefined4 *)0x0) {
    uVar1 = 0x80004003;
  }
  else {
    uVar5 = 0;
    uVar4 = 0;
    uVar3 = 0;
    uVar1 = FUN_0068de10(param_2,0,0,0);
    iVar2 = FUN_00693000(uVar1,param_2,uVar3,uVar4,uVar5);
    if (iVar2 == 0x102) {
      *param_3 = *(undefined4 *)(param_1 + 8);
      uVar1 = 0x40237;
    }
    else {
      *param_3 = *(undefined4 *)(param_1 + 8);
      uVar1 = 0;
    }
  }
  return uVar1;
}

