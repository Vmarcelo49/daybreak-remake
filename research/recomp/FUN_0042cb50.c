// ============================================
// Address:  0x0042cb50
// Original: FUN_0042cb50
// Status:   unreviewed
// ============================================

void __thiscall FUN_0042cb50(int param_1, float *param_2)

{
    undefined4 uVar1;
    float10 fVar2;
    float *pfVar3;
    float local_10;
    undefined4 local_c;
    float local_8;

    fVar2 = (float10)FUN_0042df50(param_2);
    if ((float10)0.0 != fVar2)
    {
        *(undefined1 *)(param_1 + 0x85) = 0;
        DAT_006c78a4                    = 0x461c4000;
        pfVar3                          = param_2;
        uVar1                           = FUN_0064ecb0(param_2);
        FUN_0042d3b0(uVar1, pfVar3);
        *(undefined4 *)(param_1 + 0x80) = DAT_006c78a4;
        if (*(char *)(param_1 + 0x85) == '\0')
        {
            *(float *)(param_1 + 0x14) = *(float *)(param_1 + 0x14) + *param_2;
            *(float *)(param_1 + 0x1c) = *(float *)(param_1 + 0x1c) + param_2[2];
        }
        else
        {
            FUN_0042dec0(&DAT_006c78ac);
            local_10                        = DAT_006c78b8;
            local_c                         = DAT_006c78bc;
            local_8                         = DAT_006c78c0;
            *(undefined1 *)(param_1 + 0x85) = 0;
            DAT_006c78a4                    = 0x461c4000;
            pfVar3                          = &local_10;
            uVar1                           = FUN_0064ecb0(pfVar3);
            FUN_0042d3b0(uVar1, pfVar3);
            if (*(char *)(param_1 + 0x85) == '\0')
            {
                *(float *)(param_1 + 0x14) = local_10 + *(float *)(param_1 + 0x14);
                *(float *)(param_1 + 0x1c) = local_8 + *(float *)(param_1 + 0x1c);
            }
            else
            {
                FUN_0042dec0(&DAT_006c78ac);
            }
            *(undefined1 *)(param_1 + 0x85) = 1;
        }
    }
    return;
}
