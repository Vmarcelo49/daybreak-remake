// ============================================
// Address:  0x005f5bf0
// Original: FUN_005f5bf0
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_005f5bf0(int *param_1)

{
    int iVar1;
    int *piVar2;
    float10 fVar3;
    undefined4 uVar4;

    param_1[2]    = *(int *)(*(int *)(param_1[0x47] + 0x2c) + 8);
    param_1[0x58] = DAT_006b7630;
    param_1[0x15] = 0;
    param_1[0x55] = 0;
    param_1[0x56] = 0;
    param_1[0x57] = 0;
    param_1[0x1e] = 0x3f800000;
    param_1[0x1d] = 0x3f800000;
    param_1[0x1c] = 0x3f800000;
    uVar4         = 0;
    FUN_004244e0(0);
    iVar1      = FUN_00424370(uVar4);
    param_1[4] = iVar1;
    FUN_0042c800(0);
    FUN_0042c840(0);
    FUN_0042dd90();
    fVar3 = (float10)FUN_00423580(param_1[0x11], param_1[0xf]);
    param_1[0x19] =
        (int)(float)((fVar3 / (float10)3.1415927) * (float10)180.0 - (float10)(float)param_1[0x17]);
    if (180.0 < (float)param_1[0x19])
    {
        param_1[0x19] = (int)((float)param_1[0x19] - 360.0);
    }
    if ((float)param_1[0x19] < -180.0)
    {
        param_1[0x19] = (int)((float)param_1[0x19] + 360.0);
    }
    fVar3                           = (float10)FUN_004365f0(param_1[0x10]);
    param_1[0x1b]                   = (int)(float)((fVar3 / (float10)3.1415927) * (float10)180.0);
    piVar2                          = (int *)FUN_00423750(0, 0, 0);
    param_1[0x4c]                   = *piVar2;
    param_1[0x4d]                   = piVar2[1];
    param_1[0x4e]                   = piVar2[2];
    *(undefined1 *)(param_1 + 0x52) = 1;
    *(undefined1 *)((int)param_1 + 0x149) = 0;
    *(undefined1 *)((int)param_1 + 0x85)  = 0;
    param_1[0xd]                          = 0;
    param_1[0xc]                          = 0;
    param_1[0xb]                          = 0;
    param_1[0x4f]                         = 0;
    param_1[0x50]                         = 0;
    *(undefined1 *)((int)param_1 + 0x147) = 0xff;
    *(undefined1 *)((int)param_1 + 0x146) = 0xff;
    *(undefined1 *)((int)param_1 + 0x145) = 0xff;
    *(undefined1 *)(param_1 + 0x51)       = 0xff;
    (**(code **)(*param_1 + 0x24))();
    return 1;
}
