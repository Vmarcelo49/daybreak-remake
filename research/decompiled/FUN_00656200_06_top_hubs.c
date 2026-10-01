// Function: FUN_00656200
// Address:  0x00656200
// Source:  06_top_hubs.txt


undefined4 __thiscall FUN_00656200(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  
  cVar1 = FUN_0064d6e0(param_1);
  if (cVar1 == '\0') {
    FUN_0065d670();
    iVar3 = FUN_00656400(param_2);
    if (iVar3 != 0) {
      (**(code **)(*DAT_006d16f8 + 0x104))(DAT_006d16f8,0,0);
      FUN_00654170(0);
    }
    piVar4 = (int *)FUN_00656740(param_2);
    if (*piVar4 != 0) {
      (**(code **)(*(int *)*piVar4 + 8))(*piVar4);
      *piVar4 = 0;
    }
    FUN_0065a7f0(param_2);
    FUN_0065d6a0();
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

