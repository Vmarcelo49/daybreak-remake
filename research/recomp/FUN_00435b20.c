// ============================================
// Address:  0x00435b20
// Original: FUN_00435b20
// Status:   unreviewed
// ============================================

void FUN_00435b20(void)

{
    char cVar1;
    undefined4 uVar2;
    undefined4 *puVar3;
    int iVar4;
    int *piVar5;
    undefined1 local_1c[4];
    undefined4 *local_18;
    undefined4 *local_14;
    undefined1 local_10[4];
    undefined1 local_c[4];
    undefined4 local_8;

    FUN_0065d670();
    FUN_00653d10(&local_8);
    while (true)
    {
        uVar2 = FUN_00654620(local_c);
        cVar1 = const_iterator__operator__(uVar2);
        if (cVar1 == '\0')
            break;
        FUN_00653d70();
        FUN_00435e20();
        puVar3 = (undefined4 *)FUN_00653d70();
        (**(code **)(*(int *)*puVar3 + 0x1c))();
        FUN_00653d70();
        iVar4 = FUN_00435e40();
        if (iVar4 == 0)
        {
            piVar5   = (int *)FUN_00653d70();
            local_18 = (undefined4 *)*piVar5;
            local_14 = local_18;
            if (local_18 != (undefined4 *)0x0)
            {
                (**(code **)*local_18)(1);
            }
            puVar3  = (undefined4 *)FUN_00425500(local_1c, local_8);
            local_8 = *puVar3;
        }
        else
        {
            FUN_0042fc40(local_10, 0);
        }
    }
    FUN_0065d6a0();
    return;
}
