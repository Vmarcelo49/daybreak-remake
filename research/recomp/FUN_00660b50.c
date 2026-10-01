// ============================================
// Address:  0x00660b50
// Original: FUN_00660b50
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __fastcall FUN_00660b50(undefined4 *param_1)

{
    int iVar1;
    size_t sVar2;
    size_t local_420;
    size_t local_41c;
    char local_414[1028];
    undefined4 local_10;
    LONG local_c;
    size_t local_8;

    local_10 = DAT_006b77f4;
    local_c  = ImmGetCompositionStringA((HIMC)*param_1, 0x800, param_1 + 0x202, 0xff);
    *(undefined1 *)((int)param_1 + local_c + 0x808) = 0;
    FUN_0066b860(local_414, (int)param_1 + param_1[0x284] + 8);
    iVar1 = param_1[0x284];
    sVar2 = _strlen((char *)(param_1 + 0x202));
    if (0x400 - iVar1 < (int)sVar2)
    {
        local_41c = 0x400 - param_1[0x284];
    }
    else
    {
        local_41c = _strlen((char *)(param_1 + 0x202));
    }
    local_8 = local_41c;
    _strncpy((char *)((int)param_1 + param_1[0x284] + 8), (char *)(param_1 + 0x202), local_41c);
    param_1[0x284] = param_1[0x284] + local_c;
    iVar1          = param_1[0x284];
    sVar2          = _strlen(local_414);
    if (0x400 - iVar1 < (int)sVar2)
    {
        local_420 = 0x400 - param_1[0x284];
    }
    else
    {
        local_420 = _strlen(local_414);
    }
    local_8 = local_420;
    _strncpy((char *)((int)param_1 + param_1[0x284] + 8), local_414, local_420);
    if ((int)param_1[0x282] < (int)param_1[0x284])
    {
        param_1[0x284] = param_1[0x282];
    }
    *(undefined1 *)((int)param_1 + param_1[0x282] + 8) = 0;
    _memset(param_1 + 0x202, 0, 0x100);
    *(undefined1 *)((int)param_1 + 0xa0d) = 1;
    return;
}
