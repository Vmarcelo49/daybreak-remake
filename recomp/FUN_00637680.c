// ============================================
// Address:  0x00637680
// Original: FUN_00637680
// Status:   unreviewed
// ============================================

void __fastcall FUN_00637680(int param_1)

{
    char cVar1;
    int *piVar2;
    undefined4 *puVar3;
    int iVar4;
    undefined4 uVar5;
    undefined4 uVar6;
    undefined1 local_3c[4];
    undefined1 local_38[4];
    undefined4 *local_34;
    undefined4 *local_30;
    undefined1 local_2c[4];
    undefined1 local_28[4];
    int local_24;
    undefined1 local_20[4];
    undefined1 local_1c[4];
    int local_18;
    int local_14;
    undefined4 local_10;
    undefined4 local_c;
    int local_8;

    for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1)
    {
        FUN_0065d670();
        FUN_00653d10(&local_c);
        FUN_00654620(&local_10);
        while (cVar1 = const_iterator__operator__(&local_10), cVar1 != '\0')
        {
            FUN_00653d70();
            FUN_00435e20();
            for (local_14 = 0; local_14 < 4; local_14 = local_14 + 1)
            {
                piVar2 = (int *)FUN_00653d70();
                uVar6  = *(undefined4 *)(param_1 + 0x129c + *(int *)(*piVar2 + 8) * 4);
                uVar5  = *(undefined4 *)(param_1 + 0x129c + local_14 * 4);
                puVar3 = (undefined4 *)FUN_00653d70(uVar5, uVar6);
                FUN_00637950(*puVar3, uVar5, uVar6);
            }
            piVar2 = (int *)FUN_00653d70();
            if ((*(uint *)(*(int *)(*piVar2 + 0x10) + 0x28) & 0x10000) != 0)
            {
                for (local_18 = 0; local_18 < 4; local_18 = local_18 + 1)
                {
                    if (local_18 != local_8)
                    {
                        FUN_00653d10(local_20);
                        FUN_00654620(local_1c);
                        while (cVar1 = const_iterator__operator__(local_1c), cVar1 != '\0')
                        {
                            puVar3 = (undefined4 *)FUN_00653d70();
                            uVar6  = *puVar3;
                            puVar3 = (undefined4 *)FUN_00653d70(uVar6);
                            FUN_00638fd0(*puVar3, uVar6);
                            FUN_0042fc40(local_28, 0);
                        }
                    }
                }
            }
            FUN_00653d70();
            iVar4 = FUN_00435e40();
            if (iVar4 == 0)
            {
                piVar2   = (int *)FUN_00653d70();
                local_34 = (undefined4 *)*piVar2;
                local_30 = local_34;
                if (local_34 != (undefined4 *)0x0)
                {
                    (**(code **)*local_34)(1);
                }
                puVar3   = (undefined4 *)FUN_00425500(local_38, local_c);
                local_c  = *puVar3;
                puVar3   = (undefined4 *)FUN_00654620(local_3c);
                local_10 = *puVar3;
            }
            else
            {
                FUN_0042fc40(local_2c, 0);
            }
        }
        FUN_0065d6a0();
        for (local_24 = 0; local_24 < 4; local_24 = local_24 + 1)
        {
            if (local_24 != local_8)
            {
                FUN_00637950(*(undefined4 *)(param_1 + 0x129c + local_8 * 4),
                             *(undefined4 *)(param_1 + 0x129c + local_24 * 4),
                             *(undefined4 *)(param_1 + 0x129c + local_8 * 4));
            }
        }
    }
    return;
}
