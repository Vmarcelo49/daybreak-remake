// ============================================
// Address:  0x00669540
// Original: FUN_00669540
// Status:   unreviewed
// ============================================

undefined4 __thiscall FUN_00669540(int param_1, undefined4 param_2)

{
    char cVar1;
    undefined4 uVar2;
    void *pvVar3;

    cVar1 = FUN_00653540(param_2);
    if (cVar1 == '\0')
    {
        uVar2 = 0;
    }
    else
    {
        FUN_00653760(param_1, 0x12);
        FUN_00653760(param_1 + 0x18, 4);
        if (*(int *)(param_1 + 0x18) != 0)
        {
            if (*(int *)(param_1 + 0x14) != 0)
            {
                _free(*(void **)(param_1 + 0x14));
                *(undefined4 *)(param_1 + 0x14) = 0;
            }
            pvVar3                     = operator_new(*(uint *)(param_1 + 0x18));
            *(void **)(param_1 + 0x14) = pvVar3;
            FUN_00653760(*(undefined4 *)(param_1 + 0x14), *(undefined4 *)(param_1 + 0x18));
        }
        uVar2 = 1;
    }
    return uVar2;
}
