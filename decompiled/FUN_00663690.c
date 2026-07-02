// Function: FUN_00663690
// Address:  0x00663690
// Source:   batch_decompile (mass dump)
// Hash:     449ce2445e8ea1ce


undefined4 __thiscall
FUN_00663690(int param_1,undefined4 param_2,char param_3,int param_4,undefined4 param_5)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  char *pcVar5;
  int *piVar6;
  undefined1 *puVar7;
  undefined1 local_5c [28];
  undefined1 local_40 [40];
  int local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f288;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar2 = FUN_00663d00();
  if (*(uint *)(param_1 + 8) < iVar2 - 1U) {
    local_14 = FUN_00664120(*(undefined4 *)(param_1 + 4),param_4,*(undefined4 *)(param_1 + 4),
                            param_5,0);
    *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + 1;
    if (param_4 == *(int *)(param_1 + 4)) {
      piVar3 = (int *)FUN_00663b30();
      *piVar3 = local_14;
      piVar3 = (int *)FUN_00663af0();
      *piVar3 = local_14;
      piVar3 = (int *)FUN_00663b10();
      *piVar3 = local_14;
    }
    else if (param_3 == '\0') {
      piVar3 = (int *)FUN_00654020(param_4);
      *piVar3 = local_14;
      piVar3 = (int *)FUN_00663b10();
      if (param_4 == *piVar3) {
        piVar3 = (int *)FUN_00663b10();
        *piVar3 = local_14;
      }
    }
    else {
      piVar3 = (int *)FUN_00663590(param_4);
      *piVar3 = local_14;
      piVar3 = (int *)FUN_00663af0();
      if (param_4 == *piVar3) {
        piVar3 = (int *)FUN_00663af0();
        *piVar3 = local_14;
      }
    }
    local_18 = local_14;
    while( true ) {
      puVar4 = (undefined4 *)FUN_00653df0(local_18);
      pcVar5 = (char *)FUN_00663ce0(*puVar4);
      if (*pcVar5 != '\0') break;
      piVar3 = (int *)FUN_00653df0(local_18);
      puVar4 = (undefined4 *)FUN_00653df0(local_18);
      puVar4 = (undefined4 *)FUN_00653df0(*puVar4);
      piVar6 = (int *)FUN_00663590(*puVar4);
      if (*piVar3 == *piVar6) {
        puVar4 = (undefined4 *)FUN_00653df0(local_18);
        puVar4 = (undefined4 *)FUN_00653df0(*puVar4);
        puVar4 = (undefined4 *)FUN_00654020(*puVar4);
        uVar1 = *puVar4;
        pcVar5 = (char *)FUN_00663ce0(uVar1);
        if (*pcVar5 == '\0') {
          puVar4 = (undefined4 *)FUN_00653df0(local_18);
          puVar7 = (undefined1 *)FUN_00663ce0(*puVar4);
          *puVar7 = 1;
          puVar7 = (undefined1 *)FUN_00663ce0(uVar1);
          *puVar7 = 1;
          puVar4 = (undefined4 *)FUN_00653df0(local_18);
          puVar4 = (undefined4 *)FUN_00653df0(*puVar4);
          puVar7 = (undefined1 *)FUN_00663ce0(*puVar4);
          *puVar7 = 0;
          puVar4 = (undefined4 *)FUN_00653df0(local_18);
          piVar3 = (int *)FUN_00653df0(*puVar4);
          local_18 = *piVar3;
        }
        else {
          puVar4 = (undefined4 *)FUN_00653df0(local_18);
          piVar3 = (int *)FUN_00654020(*puVar4);
          if (local_18 == *piVar3) {
            piVar3 = (int *)FUN_00653df0(local_18);
            local_18 = *piVar3;
            FUN_00663ec0(local_18);
          }
          puVar4 = (undefined4 *)FUN_00653df0(local_18);
          puVar7 = (undefined1 *)FUN_00663ce0(*puVar4);
          *puVar7 = 1;
          puVar4 = (undefined4 *)FUN_00653df0(local_18);
          puVar4 = (undefined4 *)FUN_00653df0(*puVar4);
          puVar7 = (undefined1 *)FUN_00663ce0(*puVar4);
          *puVar7 = 0;
          puVar4 = (undefined4 *)FUN_00653df0(local_18);
          puVar4 = (undefined4 *)FUN_00653df0(*puVar4);
          FUN_00663ff0(*puVar4);
        }
      }
      else {
        puVar4 = (undefined4 *)FUN_00653df0(local_18);
        puVar4 = (undefined4 *)FUN_00653df0(*puVar4);
        puVar4 = (undefined4 *)FUN_00663590(*puVar4);
        uVar1 = *puVar4;
        pcVar5 = (char *)FUN_00663ce0(uVar1);
        if (*pcVar5 == '\0') {
          puVar4 = (undefined4 *)FUN_00653df0(local_18);
          puVar7 = (undefined1 *)FUN_00663ce0(*puVar4);
          *puVar7 = 1;
          puVar7 = (undefined1 *)FUN_00663ce0(uVar1);
          *puVar7 = 1;
          puVar4 = (undefined4 *)FUN_00653df0(local_18);
          puVar4 = (undefined4 *)FUN_00653df0(*puVar4);
          puVar7 = (undefined1 *)FUN_00663ce0(*puVar4);
          *puVar7 = 0;
          puVar4 = (undefined4 *)FUN_00653df0(local_18);
          piVar3 = (int *)FUN_00653df0(*puVar4);
          local_18 = *piVar3;
        }
        else {
          puVar4 = (undefined4 *)FUN_00653df0(local_18);
          piVar3 = (int *)FUN_00663590(*puVar4);
          if (local_18 == *piVar3) {
            piVar3 = (int *)FUN_00653df0(local_18);
            local_18 = *piVar3;
            FUN_00663ff0(local_18);
          }
          puVar4 = (undefined4 *)FUN_00653df0(local_18);
          puVar7 = (undefined1 *)FUN_00663ce0(*puVar4);
          *puVar7 = 1;
          puVar4 = (undefined4 *)FUN_00653df0(local_18);
          puVar4 = (undefined4 *)FUN_00653df0(*puVar4);
          puVar7 = (undefined1 *)FUN_00663ce0(*puVar4);
          *puVar7 = 0;
          puVar4 = (undefined4 *)FUN_00653df0(local_18);
          puVar4 = (undefined4 *)FUN_00653df0(*puVar4);
          FUN_00663ec0(*puVar4);
        }
      }
    }
    puVar4 = (undefined4 *)FUN_00663b30();
    puVar7 = (undefined1 *)FUN_00663ce0(*puVar4);
    *puVar7 = 1;
    FUN_0064f300(local_14);
    ExceptionList = local_10;
    return param_2;
  }
  basic_string<>("map/set<T> too long");
  local_8 = 0;
  FID_conflict_length_error(local_5c);
                    /* WARNING: Subroutine does not return */
  __CxxThrowException_8(local_40,&DAT_006b1da0);
}

