// ============================================
// Address:  0x00405650
// Original: FUN_00405650
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_00405650(int param_1)

{
    char cVar1;
    undefined4 uVar2;
    int local_8;

    cVar1 = FUN_00405250();
    if (cVar1 == '\0')
    {
        if (*(int *)(param_1 + 4) < 10)
        {
            *(int *)(param_1 + 4) = *(int *)(param_1 + 4) + 1;
            if (*(int *)(param_1 + 4) != 10)
            {
                return 4;
            }
            FUN_0065b9b0();
            FUN_0065c950();
        }
        FUN_006584e0();
        FUN_006585f0();
        cVar1 = FUN_0065c9d0();
        if (cVar1 == '\0')
        {
            uVar2 = 5;
        }
        else
        {
            for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1)
            {
                FUN_00657390();
                if (((&DAT_006caeb8)[local_8 * 0x19] == 1) ||
                    (cVar1 = FUN_006586d0(1), cVar1 != '\0'))
                {
                    FUN_0065c990();
                    return 5;
                }
            }
            uVar2 = 4;
        }
    }
    else
    {
        uVar2 = 4;
    }
    return uVar2;
}
