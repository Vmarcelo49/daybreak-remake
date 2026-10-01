// Function: FUN_00646110
// Address:  0x00646110
// Source:   batch_decompile (mass dump)
// Hash:     6dd96652662c0356


void __thiscall FUN_00646110(int param_1,int param_2,undefined4 param_3,undefined1 param_4)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined1 local_10 [4];
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_0065d670();
  switch(param_4) {
  case 0:
    FUN_00647000(param_1 + 0xdf6 + param_2 * 9,param_3,0);
    FUN_00656200(*(undefined4 *)(param_1 + 0x13c));
    uVar3 = *(undefined4 *)(param_1 + 0x144);
    uVar1 = FUN_00647130(uVar3);
    puVar2 = (undefined4 *)FUN_00656190(local_10,uVar1,uVar3);
    *(undefined4 *)(param_1 + 0x13c) = *puVar2;
    FUN_00655af0(*(undefined4 *)(param_1 + 0x13c),0,0,300,0x200);
    FUN_00655690(*(undefined4 *)(param_1 + 0x13c),0,0,300,0x10);
    break;
  case 1:
    FUN_00656200(*(undefined4 *)(param_1 + 0x114 + param_2 * 4));
    puVar2 = (undefined4 *)FUN_00656190(local_c,param_3,*(undefined4 *)(param_1 + 0x144));
    *(undefined4 *)(param_1 + 0x114 + param_2 * 4) = *puVar2;
    FUN_00655af0(*(undefined4 *)(param_1 + 0x114 + param_2 * 4),0,0,400,0x20);
    *(undefined4 *)(param_1 + 0xdd4 + param_2 * 4) = 600;
    break;
  case 2:
  case 3:
    FUN_00647000(param_1 + 0xdf6 + param_2 * 9,param_3,1);
    FUN_00656200(*(undefined4 *)(param_1 + 0x13c));
    uVar3 = *(undefined4 *)(param_1 + 0x144);
    uVar1 = FUN_00647130(uVar3);
    puVar2 = (undefined4 *)FUN_00656190(local_8,uVar1,uVar3);
    *(undefined4 *)(param_1 + 0x13c) = *puVar2;
    FUN_00655af0(*(undefined4 *)(param_1 + 0x13c),0,0,300,0x200);
    FUN_00655690(*(undefined4 *)(param_1 + 0x13c),0,0,300,0x10);
  }
  FUN_0065d6a0();
  return;
}

