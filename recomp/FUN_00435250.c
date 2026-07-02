// ============================================
// Address:  0x00435250
// Original: FUN_00435250
// Status:   unreviewed
// ============================================


void __thiscall
FUN_00435250(int param_1,int param_2,int param_3,float param_4,undefined4 param_5,float param_6,
            float param_7,undefined4 param_8)

{
  char cVar1;
  undefined4 uVar2;
  float10 fVar3;
  float10 fVar4;
  float fVar5;
  float fVar6;
  undefined1 local_28 [12];
  float local_1c;
  float local_18;
  undefined4 local_14;
  float local_c;
  float local_8;
  
  fVar3 = (float10)FUN_0065d010(param_8);
  local_c = (float)fVar3;
  fVar3 = (float10)FUN_0065d050(param_8);
  local_8 = (float)fVar3;
  fVar3 = (float10)FUN_0065d010(param_7 + *(float *)(*(int *)(param_1 + 0x20) + 0x5c) +
                                *(float *)(*(int *)(param_1 + 0x20) + 100));
  fVar6 = (float)(fVar3 * (float10)local_8);
  fVar5 = local_c;
  fVar3 = (float10)FUN_0065d050(param_7 + *(float *)(*(int *)(param_1 + 0x20) + 0x5c) +
                                *(float *)(*(int *)(param_1 + 0x20) + 100),local_c,fVar6);
  FUN_00423750((float)(fVar3 * (float10)local_8),fVar5,fVar6);
  std::allocator<char>::allocator<char>((allocator<char> *)&local_1c);
  if (param_2 != 0) {
    uVar2 = FUN_00423750(0,0,0);
    D3DXVec3Transform(&local_1c,uVar2,param_2);
  }
  fVar3 = (float10)FUN_0065d050(*(float *)(*(int *)(param_1 + 0x20) + 0x5c) +
                                *(float *)(*(int *)(param_1 + 0x20) + 100));
  fVar4 = (float10)FUN_0065d010(*(float *)(*(int *)(param_1 + 0x20) + 0x5c) +
                                *(float *)(*(int *)(param_1 + 0x20) + 100));
  local_1c = (float)(((float10)(float)(fVar3 * (float10)param_4) - fVar4 * (float10)param_6) +
                    (float10)local_1c);
  fVar3 = (float10)FUN_0065d010(*(float *)(*(int *)(param_1 + 0x20) + 0x5c) +
                                *(float *)(*(int *)(param_1 + 0x20) + 100));
  fVar6 = (float)(fVar3 * (float10)param_4);
  fVar3 = (float10)FUN_0065d050(*(float *)(*(int *)(param_1 + 0x20) + 0x5c) +
                                *(float *)(*(int *)(param_1 + 0x20) + 100),fVar6);
  local_18 = (float)(fVar3 * (float10)param_6 + (float10)fVar6 + (float10)local_18);
  if (*(int *)(*(int *)(param_1 + 0xf4) + 8 + param_3 * 0xc) < 0) {
    (**(code **)(*(int *)(param_1 + 0xac) + 0xc))
              (param_3,local_1c,local_18,local_14,local_28,
               *(undefined4 *)(*(int *)(param_1 + 0x20) + 0x38));
  }
  else {
    cVar1 = FUN_00435920();
    if (cVar1 != '\0') {
      (**(code **)(*(int *)(param_1 + 0xac) + 0xc))
                (param_3,local_1c,local_18,local_14,local_28,
                 *(undefined4 *)(*(int *)(param_1 + 0x20) + 0x38));
    }
  }
  return;
}

