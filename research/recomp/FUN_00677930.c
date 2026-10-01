// ============================================
// Address:  0x00677930
// Original: FUN_00677930
// Status:   unreviewed
// ============================================

int FUN_00677930(int param_1,
                 int *param_2,
                 undefined4 *param_3,
                 uint param_4,
                 int param_5,
                 code *param_6,
                 int param_7,
                 int param_8)

{
    undefined4 *puVar1;
    void *pvVar2;
    int iVar3;
    int iVar4;
    uint uVar5;
    int *piVar6;

    iVar3 = param_1;
    if (param_1 == 0)
    {
        param_1 = -1;
    }
    else
    {
        param_1 = (*param_6)(param_1, 0, 0, 1);
    }
    piVar6 = param_2;
    for (iVar4 = 0xb4; iVar4 != 0; iVar4 = iVar4 + -1)
    {
        *piVar6 = 0;
        piVar6  = piVar6 + 1;
    }
    *param_2      = iVar3;
    param_2[0xb0] = param_5;
    param_2[0xb1] = (int)param_6;
    piVar6        = param_2 + 6;
    param_2[0xb2] = param_7;
    param_2[0xb3] = param_8;
    FUN_0069cd50(piVar6);
    if (param_3 != (undefined4 *)0x0)
    {
        puVar1 = (undefined4 *)FUN_0069cda0(piVar6, param_4);
        for (uVar5 = param_4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1)
        {
            *puVar1 = *param_3;
            param_3 = param_3 + 1;
            puVar1  = puVar1 + 1;
        }
        for (uVar5 = param_4 & 3; uVar5 != 0; uVar5 = uVar5 - 1)
        {
            *(undefined1 *)puVar1 = *(undefined1 *)param_3;
            param_3               = (undefined4 *)((int)param_3 + 1);
            puVar1                = (undefined4 *)((int)puVar1 + 1);
        }
        FUN_0069ce20(piVar6, param_4);
    }
    if (param_1 != -1)
    {
        param_2[1] = 1;
    }
    param_2[0xd]  = 1;
    pvVar2        = _calloc(1, 0x20);
    param_2[0x12] = (int)pvVar2;
    pvVar2        = _calloc(param_2[0xd], 0x10);
    param_2[0x13] = (int)pvVar2;
    FUN_0069cb60(param_2 + 0x1e, 0xffffffff);
    iVar3 = FUN_00677a50(param_2, param_2[0x12], param_2[0x13], param_2 + 0x17, 0);
    if (iVar3 < 0)
    {
        *param_2 = 0;
        FUN_006777e0(param_2);
        return iVar3;
    }
    param_2[0x16] = 1;
    return iVar3;
}
