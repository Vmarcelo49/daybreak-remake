// ============================================
// Address:  0x0042c8e0
// Original: FUN_0042c8e0
// Status:   unreviewed
// ============================================


void __thiscall
FUN_0042c8e0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
  float10 fVar1;
  float10 fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined1 local_10 [12];
  
  fVar1 = (float10)FUN_0065d010(param_6);
  fVar2 = (float10)FUN_0065d050(param_7);
  fVar4 = (float)(fVar2 * (float10)(float)fVar1);
  fVar1 = (float10)FUN_0065d010(param_7,fVar4);
  fVar3 = (float)fVar1;
  fVar1 = (float10)FUN_0065d050(param_6,fVar3);
  fVar5 = (float)fVar1;
  fVar1 = (float10)FUN_0065d050(param_7,fVar3,fVar4,fVar5);
  FUN_00423750((float)(fVar1 * (float10)fVar5),fVar3,fVar4);
  FUN_00435990(param_2,param_3,param_4,param_5,local_10,param_1);
  return;
}

