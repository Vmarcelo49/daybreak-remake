// ============================================
// Address:  0x00658a50
// Original: FUN_00658a50
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_00658a50(undefined4 param_1, undefined4 *param_2)

{
    undefined4 *puVar1;
    undefined4 *puVar2;
    int iVar3;
    undefined4 uVar4;
    undefined1 local_6c[4];
    undefined1 local_68[4];
    undefined1 local_64[4];
    undefined1 local_60[4];
    undefined4 local_5c[21];
    undefined4 local_8;

    local_8 = DAT_006b77f4;
    puVar1  = local_5c;
    for (iVar3 = 0x14; iVar3 != 0; iVar3 = iVar3 + -1)
    {
        *puVar1 = *param_2;
        param_2 = param_2 + 1;
        puVar1  = puVar1 + 1;
    }
    puVar1 = (undefined4 *)FUN_00654670(local_60);
    uVar4  = *puVar1;
    puVar1 = (undefined4 *)FUN_00654620(local_64);
    FUN_00658da0(local_68, *puVar1, uVar4);
    puVar1 = local_5c;
    puVar2 = (undefined4 *)FUN_00654620(local_6c);
    FUN_00658d70(*puVar2, param_1, puVar1);
    return;
}
