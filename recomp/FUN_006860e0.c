// ============================================
// Address:  0x006860e0
// Original: FUN_006860e0
// Status:   unreviewed
// ============================================

void FUN_006860e0(undefined4 *param_1)

{
    void *_Memory;
    int iVar1;
    undefined4 *puVar2;

    if (param_1 != (undefined4 *)0x0)
    {
        if ((undefined4 *)param_1[2] != (undefined4 *)0x0)
        {
            _Memory = *(void **)param_1[2];
            if (_Memory != (void *)0x0)
            {
                _free(_Memory);
            }
            if (*(void **)(param_1[2] + 4) != (void *)0x0)
            {
                _free(*(void **)(param_1[2] + 4));
            }
            _free((void *)param_1[2]);
        }
        puVar2 = param_1;
        for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1)
        {
            *puVar2 = 0;
            puVar2  = puVar2 + 1;
        }
        _free(param_1);
    }
    return;
}
