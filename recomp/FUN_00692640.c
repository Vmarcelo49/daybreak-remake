// ============================================
// Address:  0x00692640
// Original: FUN_00692640
// Status:   unreviewed
// ============================================

undefined4 *FUN_00692640(undefined4 *param_1, undefined4 *param_2, uint param_3)

{
    uint uVar1;
    undefined1 *puVar2;
    undefined4 *puVar3;
    undefined1 *puVar4;

    if ((param_2 < param_1) && (param_1 < (undefined4 *)((int)param_2 + param_3)))
    {
        puVar2 = (undefined1 *)((int)param_2 + param_3);
        puVar4 = (undefined1 *)((int)param_1 + param_3);
        while (true)
        {
            puVar4 = puVar4 + -1;
            puVar2 = puVar2 + -1;
            if (param_3 == 0)
                break;
            param_3 = param_3 - 1;
            *puVar4 = *puVar2;
        }
    }
    else
    {
        uVar1  = param_3 & 3;
        puVar3 = param_1;
        for (param_3 = param_3 >> 2; param_3 != 0; param_3 = param_3 - 1)
        {
            *puVar3 = *param_2;
            param_2 = param_2 + 1;
            puVar3  = puVar3 + 1;
        }
        if (uVar1 != 0)
        {
            for (; uVar1 != 0; uVar1 = uVar1 - 1)
            {
                *(undefined1 *)puVar3 = *(undefined1 *)param_2;
                param_2               = (undefined4 *)((int)param_2 + 1);
                puVar3                = (undefined4 *)((int)puVar3 + 1);
            }
        }
    }
    return param_1;
}
