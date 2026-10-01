// ============================================
// Address:  0x0042c970
// Original: FUN_0042c970
// Status:   unreviewed
// ============================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall FUN_0042c970(int param_1, float *param_2)

{
    undefined4 uVar1;
    float10 fVar2;
    float fVar3;

    *(undefined4 *)(param_1 + 0x7c) = 0x461c4000;
    _DAT_006c789c                   = 0.0;
    _DAT_006c78ac                   = 0;
    _DAT_006c78b0                   = 0;
    _DAT_006c78b4                   = 0;
    DAT_006c7898                    = 0;
    DAT_006c78a8                    = 0;
    fVar3                           = *param_2;
    uVar1                           = FUN_0064ecb0(fVar3);
    FUN_0042cd50(uVar1, fVar3);
    if (*(char *)(param_1 + 0x84) == '\0')
    {
        fVar3 = *(float *)(param_1 + 0x7c) + *param_2;
        if ((fVar3 < 0.0 != (fVar3 == 0.0)) && (*param_2 < 0.0 != (*param_2 == 0.0)))
        {
            if ((0.0 < _DAT_006c789c) && (-(*(float *)(param_1 + 0x7c) + *param_2) < _DAT_006c789c))
            {
                _DAT_006c789c = -*(float *)(param_1 + 0x7c) + *param_2;
            }
            *(undefined1 *)(param_1 + 0x84) = 1;
        }
        fVar2 = (float10)FUN_0042de80(_DAT_006c7894 * _DAT_006c7894);
        FUN_0042df10((float)(((float10)_DAT_006c7894 / ((float10)1.0 - fVar2) + (float10)1.0) *
                             (float10)_DAT_006c789c));
    }
    else if ((0.0 < *param_2) || (20.0 < *(float *)(param_1 + 0x7c) + *param_2))
    {
        *(undefined1 *)(param_1 + 0x84) = 0;
    }
    if (*(char *)(param_1 + 0x84) == '\0')
    {
        if (0.0 <= *(float *)(param_1 + 0x7c) + *param_2)
        {
            *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x18) + *param_2;
        }
        else
        {
            *(float *)(param_1 + 0x18) =
                *(float *)(param_1 + 0x18) - (*(float *)(param_1 + 0x7c) + *param_2);
        }
    }
    else
    {
        *(float *)(param_1 + 0x18) = *(float *)(param_1 + 0x18) - *(float *)(param_1 + 0x7c);
    }
    FUN_0042dec0(&DAT_006c78ac);
    return;
}
