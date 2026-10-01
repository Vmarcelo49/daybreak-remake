// ============================================
// Address:  0x005f5ec0
// Original: FUN_005f5ec0
// Status:   unreviewed
// ============================================

void __fastcall FUN_005f5ec0(int *param_1)

{
    undefined4 uVar1;
    float10 fVar2;
    float10 fVar3;
    undefined1 local_1c[24];

    if (*(char *)((int)param_1 + 0x149) == '\0')
    {
        if ((char)param_1[0x52] == '\0')
        {
            FUN_0042dec0(param_1 + 0xf);
            fVar2         = (float10)FUN_0042df50(param_1 + 0xf);
            param_1[0x20] = (int)(float)((float10)(float)param_1[0x20] - fVar2);
        }
        else
        {
            fVar2         = (float10)FUN_0065d010(param_1[0x1b]);
            param_1[0x10] = (int)(float)fVar2;
            fVar2         = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19]);
            fVar3         = (float10)FUN_0065d050(param_1[0x1b]);
            param_1[0xf]  = (int)(float)(fVar3 * (float10)(float)fVar2);
            fVar2         = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19]);
            fVar3         = (float10)FUN_0065d050(param_1[0x1b]);
            param_1[0x11] = (int)(float)(fVar3 * (float10)(float)fVar2);
            uVar1         = FUN_004241d0(local_1c, param_1[0x15]);
            FUN_0042dec0(uVar1);
            param_1[0x20] = (int)((float)param_1[0x20] - (float)param_1[0x15]);
        }
    }
    else
    {
        fVar2         = (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19]);
        param_1[0xf]  = (int)(float)(fVar2 * (float10)(float)param_1[0x15]);
        param_1[0x12] = param_1[0xf];
        param_1[0x13] = param_1[0x10];
        fVar2         = (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19]);
        param_1[0x11] = (int)(float)(fVar2 * (float10)(float)param_1[0x15]);
        param_1[0x14] = param_1[0x11];
        uVar1         = FUN_00423750(param_1[0x12], 0, param_1[0x14]);
        FUN_0042cb50(uVar1);
        FUN_0042c970(param_1 + 0x13);
    }
    FUN_0042dd90();
    (**(code **)(*param_1 + 0x24))();
    if (param_1[0x4f] != 0)
    {
        FUN_004369c0();
    }
    return;
}
