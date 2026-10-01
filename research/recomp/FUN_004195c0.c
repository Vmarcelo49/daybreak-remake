// ============================================
// Address:  0x004195c0
// Original: FUN_004195c0
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_004195c0(int param_1, int param_2, undefined4 param_3)

{
    int iVar1;
    int local_208;
    undefined1 local_204[8];
    undefined4 auStack_1fc[4];
    undefined4 auStack_1ec[4];
    undefined4 auStack_1dc[4];
    int aiStack_1cc[4];
    int aiStack_1bc[8];
    undefined4 local_19c;
    undefined4 local_198;
    undefined4 local_194;
    undefined4 local_190;
    undefined4 local_18c;
    undefined4 local_188;
    undefined4 local_17c;
    int local_178;
    int local_174;
    int local_170;
    undefined1 local_16c[8];
    undefined4 auStack_164[4];
    undefined4 auStack_154[4];
    undefined4 auStack_144[4];
    int aiStack_134[4];
    int aiStack_124[4];
    int aiStack_114[4];
    undefined4 local_104;
    undefined4 local_100;
    undefined4 local_fc;
    undefined4 local_f8;
    undefined4 local_f4;
    undefined4 local_f0;
    undefined1 local_ec[8];
    undefined1 auStack_e4[8];
    undefined1 auStack_dc[72];
    undefined1 auStack_94[8];
    undefined1 auStack_8c[4];
    undefined1 local_88;
    undefined1 local_87;
    undefined1 local_86;
    undefined1 local_85;
    undefined1 local_84;
    undefined1 local_83;
    undefined1 local_7c[8];
    char local_74;
    undefined1 local_73;
    undefined1 local_72[94];
    undefined1 local_14[12];
    undefined4 local_8;

    local_8 = DAT_006b77f4;
    iVar1   = FUN_004165e0(param_3);
    if (iVar1 == 1)
    {
        FUN_00416410();
        FUN_0041d7e0(param_3);
        switch (local_17c)
        {
        case 0xd:
        case 0xf:
            FUN_004177a0();
            for (local_208 = 0; local_208 < 4; local_208 = local_208 + 1)
            {
                auStack_1ec[local_208] = (&DAT_006cfb28)[local_208];
                auStack_1fc[local_208] = (&DAT_006cfaf8)[local_208];
                auStack_1dc[local_208] = *(undefined4 *)(&DAT_006cfb38 + local_208 * 4);
                aiStack_1cc[local_208] = (int)(char)(&DAT_006cfb48)[local_208];
                aiStack_1bc[local_208] = (int)(char)(&DAT_006cfb4c)[local_208];
            }
            local_19c = DAT_006cfaf4;
            local_198 = DAT_006cf3c0;
            local_194 = DAT_006cf3b8;
            local_190 = DAT_006cf3bc;
            local_18c = DAT_006cf3b0;
            local_188 = DAT_006cf3b4;
            FUN_00415d30(param_2, local_204, 0, 8);
            break;
        case 0x11:
            *(undefined4 *)(param_1 + 0x140 + param_2 * 4) = 1;
            break;
        case 0x13:
            *(undefined4 *)(param_1 + 0x120 + param_2 * 4) = 1;
        }
    }
    else if (iVar1 == 5)
    {
        *(undefined4 *)(param_1 + 0x120 + param_2 * 4) = 1;
    }
    else if (iVar1 == 0xf)
    {
        FUN_00416600();
        FUN_00416560(param_3);
        FUN_00415ea0();
        local_84 = 0;
        local_83 = 0;
        local_88 = DAT_006cfdd0;
        local_87 = DAT_006cfdf9;
        local_86 = DAT_006cfe1c;
        local_85 = DAT_006cfe1e;
        _memcpy(&DAT_006cfb58 + param_2 * 9, local_14, 9);
        FUN_00645dc0(param_2, &DAT_006cfb58 + param_2 * 9);
        for (local_170 = 0; local_170 < 8; local_170 = local_170 + 1)
        {
            _memcpy(auStack_dc + local_170 * 9, &DAT_006cfb58 + local_170 * 9, 9);
            auStack_e4[local_170] = (&DAT_006cfdd1)[local_170];
            auStack_94[local_170] = (&DAT_006cfde1)[local_170];
        }
        for (local_174 = 0; local_174 < 4; local_174 = local_174 + 1)
        {
            auStack_8c[local_174] = *(undefined1 *)(&DAT_006cfb18 + local_174);
        }
        FUN_00415d30(0, local_ec, 0, 8);
        FUN_004177a0();
        for (local_178 = 0; local_178 < 4; local_178 = local_178 + 1)
        {
            auStack_154[local_178] = (&DAT_006cfb28)[local_178];
            auStack_164[local_178] = (&DAT_006cfaf8)[local_178];
            auStack_144[local_178] = *(undefined4 *)(&DAT_006cfb38 + local_178 * 4);
            aiStack_134[local_178] = (int)(char)(&DAT_006cfb48)[local_178];
            aiStack_124[local_178] = (int)(char)(&DAT_006cfb4c)[local_178];
            aiStack_114[local_178] = (int)(char)(&DAT_006cfb54)[local_178];
        }
        local_104 = DAT_006cfaf4;
        local_100 = DAT_006cf3c0;
        local_fc  = DAT_006cf3b8;
        local_f8  = DAT_006cf3bc;
        local_f4  = DAT_006cf3b0;
        local_f0  = DAT_006cf3b4;
        FUN_00415d30(param_2, local_16c, 0, 8);
        FUN_00416670();
        local_74 = (char)param_2;
        local_73 = 2;
        FUN_0066b860(local_72, &DAT_006a1fb8);
        FUN_00415d30(0, local_7c, 0, 8);
        FUN_00646110((int)local_74, local_72, local_73);
    }
    return;
}
