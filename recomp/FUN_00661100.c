// ============================================
// Address:  0x00661100
// Original: FUN_00661100
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __fastcall FUN_00661100(int param_1)

{
    int iVar1;
    char cVar2;
    size_t sVar3;
    size_t local_414;
    char local_40c[1024];
    undefined4 local_c;
    size_t local_8;

    local_c = DAT_006b77f4;
    if (*(char *)(param_1 + 8 + *(int *)(param_1 + 0xa10)) != '\0')
    {
        cVar2 = FUN_00661620(*(undefined1 *)(param_1 + 8 + *(int *)(param_1 + 0xa10)));
        if (cVar2 == '\0')
        {
            FUN_0066b860(local_40c, param_1 + 9 + *(int *)(param_1 + 0xa10));
        }
        else
        {
            FUN_0066b860(local_40c, param_1 + 10 + *(int *)(param_1 + 0xa10));
        }
        *(undefined1 *)(param_1 + 8 + *(int *)(param_1 + 0xa10)) = 0;
        iVar1                                                    = *(int *)(param_1 + 0xa10);
        sVar3                                                    = _strlen(local_40c);
        if (0x3ff - iVar1 < (int)(sVar3 + 2))
        {
            local_414 = 0x3ff - *(int *)(param_1 + 0xa10);
        }
        else
        {
            local_414 = _strlen(local_40c);
            local_414 = local_414 + 2;
        }
        local_8 = local_414;
        _strncpy((char *)(param_1 + 8 + *(int *)(param_1 + 0xa10)), local_40c, local_414);
        *(undefined1 *)(param_1 + 8 + *(int *)(param_1 + 0xa08)) = 0;
        *(undefined1 *)(param_1 + 0xa0d)                         = 1;
    }
    return;
}
