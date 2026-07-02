// ============================================
// Address:  0x00421aa0
// Original: FUN_00421aa0
// Status:   unreviewed
// ============================================


void __thiscall
FUN_00421aa0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,undefined4 param_6,undefined4 param_7)

{
  float10 fVar1;
  float10 fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined1 local_34 [8];
  undefined1 local_2c;
  undefined2 local_2a;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  
  fVar1 = (float10)FUN_0065d010(param_6);
  fVar2 = (float10)FUN_0065d050(param_7);
  fVar4 = (float)(fVar2 * (float10)(float)fVar1);
  fVar1 = (float10)FUN_0065d010(param_7,fVar4);
  fVar3 = (float)fVar1;
  fVar1 = (float10)FUN_0065d050(param_6,fVar3);
  fVar5 = (float)fVar1;
  fVar1 = (float10)FUN_0065d050(param_7,fVar3,fVar4,fVar5);
  FUN_00423750((float)(fVar1 * (float10)fVar5),fVar3,fVar4);
  if (DAT_006cfdb0 == '\x01') {
    FUN_00423960();
    local_2c = *(undefined1 *)(param_1 + 8);
    local_2a = (undefined2)param_2;
    local_28 = param_3;
    local_24 = param_4;
    local_20 = param_5;
    local_1c = local_10;
    local_18 = local_c;
    local_14 = local_8;
    FUN_00415d30(0,local_34,0,8);
  }
  FUN_00435990(param_2,param_3,param_4,param_5,&local_10,param_1);
  return;
}

