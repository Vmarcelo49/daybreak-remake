// ============================================
// Address:  0x00659bf0
// Original: FUN_00659bf0
// Status:   unreviewed
// ============================================

/* WARNING: Function: __chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __fastcall FUN_00659bf0(int param_1)

{
    int iStack_80020;
    undefined1 auStack_8001c[524292];
    undefined2 local_18;
    undefined2 local_16;
    undefined4 local_14;
    undefined4 local_10;
    undefined2 local_c;
    undefined2 local_a;
    uint local_8;

    local_8 = 0x659bfd;
    _memset(auStack_8001c, 0, 0x80000);
    local_8  = local_8 & 0xffff0000;
    local_18 = 1;
    local_14 = 0xac44;
    local_a  = 0x10;
    local_16 = 1;
    local_c  = 2;
    local_10 = 0x15888;
    for (iStack_80020 = 0; iStack_80020 < 0x20; iStack_80020 = iStack_80020 + 1)
    {
        FUN_00667b00(auStack_8001c, 0x80000, &local_18);
        FUN_00667b00(auStack_8001c, 0x80000, &local_18);
    }
    *(undefined4 *)(param_1 + 0x3e0) = 0;
    *(undefined4 *)(param_1 + 0x3e4) = 0;
    *(undefined4 *)(param_1 + 1000)  = 10000;
    *(undefined4 *)(param_1 + 0x3ec) = 10000;
    return 1;
}
