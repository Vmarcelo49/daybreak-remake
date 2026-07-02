// ============================================
// Address:  0x0067c190
// Original: FUN_0067c190
// Status:   unreviewed
// ============================================

void FUN_0067c190(undefined4 *param_1)

{
    int iVar1;
    int iVar2;

    if (param_1 != (undefined4 *)0x0)
    {
        if ((void *)param_1[4] != (void *)0x0)
        {
            _free((void *)param_1[4]);
        }
        if ((void *)param_1[5] != (void *)0x0)
        {
            _free((void *)param_1[5]);
        }
        if ((void *)param_1[6] != (void *)0x0)
        {
            _free((void *)param_1[6]);
        }
        if (param_1[2] != 0)
        {
            iVar1 = 0;
            do
            {
                iVar2 = 0;
                do
                {
                    _free(*(void **)(*(int *)(param_1[2] + iVar1) + iVar2));
                    iVar2 = iVar2 + 4;
                } while (iVar2 < 0x20);
                _free(*(void **)(param_1[2] + iVar1));
                iVar1 = iVar1 + 4;
            } while (iVar1 < 0x44);
            _free((void *)param_1[2]);
        }
        if (param_1[3] != 0)
        {
            iVar1 = 0;
            do
            {
                _free(*(void **)(param_1[3] + iVar1));
                iVar1 = iVar1 + 4;
            } while (iVar1 < 0xc);
            _free((void *)param_1[3]);
        }
        for (iVar1 = 0xc; iVar1 != 0; iVar1 = iVar1 + -1)
        {
            *param_1 = 0;
            param_1  = param_1 + 1;
        }
    }
    return;
}
