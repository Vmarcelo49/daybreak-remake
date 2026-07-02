// ============================================
// Address:  0x0067da80
// Original: FUN_0067da80
// Status:   unreviewed
// ============================================

void FUN_0067da80(float param_1, float param_2, float *param_3, float *param_4)

{
    float fVar1;
    float fVar2;
    int iVar3;

    iVar3 = (uint)(ABS(*param_4) < ABS(*param_3)) - (uint)(ABS(*param_3) < ABS(*param_4));
    if (iVar3 == 0)
    {
        iVar3 = (uint)(ABS(param_2) < ABS(param_1)) * 2 + -1;
    }
    if (iVar3 == 1)
    {
        if (*param_3 <= 0.0)
        {
            *param_4 = *param_4 - *param_3;
        }
        else
        {
            *param_4 = *param_3 - *param_4;
        }
    }
    else
    {
        fVar1 = *param_4;
        if (*param_4 <= 0.0)
        {
            fVar2 = *param_4 - *param_3;
        }
        else
        {
            fVar2 = *param_3 - *param_4;
        }
        *param_4 = fVar2;
        *param_3 = fVar1;
    }
    if (ABS(*param_3) * 1.9999 < *param_4)
    {
        *param_4 = ABS(*param_3) * -2.0;
        *param_3 = -*param_3;
        return;
    }
    return;
}
