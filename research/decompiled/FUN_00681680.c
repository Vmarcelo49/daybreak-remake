// Function: FUN_00681680
// Address:  0x00681680
// Source:   batch_decompile (mass dump)
// Hash:     66a293a59d48fdc1


void FUN_00681680(float *param_1,float *param_2,int param_3,int param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  float *pfVar9;
  
  pfVar6 = param_2 + (param_3 >> 1) + -8 + (param_3 - (param_3 >> 1)) + 7;
  pfVar5 = param_2 + (param_3 >> 1) + -8;
  do {
    fVar1 = pfVar6[-1];
    fVar2 = pfVar5[6];
    fVar3 = *pfVar6;
    fVar4 = pfVar5[7];
    pfVar6[-1] = pfVar6[-1] + pfVar5[6];
    *pfVar6 = pfVar5[7] + *pfVar6;
    pfVar5[6] = (fVar1 - fVar2) * *param_1 + (fVar3 - fVar4) * param_1[1];
    pfVar7 = param_1 + param_4;
    pfVar5[7] = (fVar3 - fVar4) * *param_1 - (fVar1 - fVar2) * param_1[1];
    fVar1 = pfVar6[-3];
    fVar2 = pfVar5[4];
    fVar3 = pfVar6[-2];
    fVar4 = pfVar5[5];
    pfVar6[-3] = pfVar5[4] + pfVar6[-3];
    pfVar6[-2] = pfVar6[-2] + pfVar5[5];
    pfVar5[4] = (fVar1 - fVar2) * *pfVar7 + (fVar3 - fVar4) * pfVar7[1];
    pfVar8 = pfVar7 + param_4;
    pfVar5[5] = (fVar3 - fVar4) * *pfVar7 - (fVar1 - fVar2) * pfVar7[1];
    fVar1 = pfVar6[-5];
    fVar2 = pfVar5[2];
    fVar3 = pfVar6[-4];
    fVar4 = pfVar5[3];
    pfVar6[-5] = pfVar5[2] + pfVar6[-5];
    pfVar6[-4] = pfVar5[3] + pfVar6[-4];
    pfVar5[2] = (fVar1 - fVar2) * *pfVar8 + (fVar3 - fVar4) * pfVar8[1];
    pfVar9 = pfVar8 + param_4;
    pfVar5[3] = (fVar3 - fVar4) * *pfVar8 - (fVar1 - fVar2) * pfVar8[1];
    fVar1 = pfVar6[-7];
    fVar2 = *pfVar5;
    fVar3 = pfVar6[-6];
    fVar4 = pfVar5[1];
    pfVar6[-7] = *pfVar5 + pfVar6[-7];
    pfVar6[-6] = pfVar6[-6] + pfVar5[1];
    pfVar7 = pfVar5 + -8;
    pfVar6 = pfVar6 + -8;
    *pfVar5 = (fVar1 - fVar2) * *pfVar9 + (fVar3 - fVar4) * pfVar9[1];
    param_1 = pfVar9 + param_4;
    pfVar5[1] = (fVar3 - fVar4) * *pfVar9 - (fVar1 - fVar2) * pfVar9[1];
    pfVar5 = pfVar7;
  } while (param_2 <= pfVar7);
  return;
}

