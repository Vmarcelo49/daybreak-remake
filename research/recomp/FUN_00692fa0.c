// ============================================
// Address:  0x00692fa0
// Original: FUN_00692fa0
// Status:   unreviewed
// ============================================

undefined4 FUN_00692fa0(void *param_1, int *param_2)

{
    SIZE_T cb;
    undefined4 uVar1;
    int iVar2;
    LPVOID pvVar3;

    if (param_2 == (int *)0x0)
    {
        uVar1 = 0x80004003;
    }
    else
    {
        iVar2    = FUN_006925d0(param_1);
        cb       = iVar2 * 2 + 2;
        pvVar3   = CoTaskMemAlloc(cb);
        *param_2 = (int)pvVar3;
        if (*param_2 == 0)
        {
            uVar1 = 0x8007000e;
        }
        else
        {
            _memcpy((void *)*param_2, param_1, cb);
            uVar1 = 0;
        }
    }
    return uVar1;
}
