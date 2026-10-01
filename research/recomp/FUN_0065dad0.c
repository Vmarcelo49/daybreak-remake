// ============================================
// Address:  0x0065dad0
// Original: FUN_0065dad0
// Status:   unreviewed
// ============================================

void __thiscall
FUN_0065dad0(int param_1, char *param_2, void *param_3, int param_4, int param_5, byte param_6)

{
    byte bVar1;
    char cVar2;
    int iVar3;
    uint uVar4;
    int local_30;
    int local_2c;
    int local_24;
    size_t local_20;
    byte local_1a;
    byte local_19;
    int local_18;
    int local_14;
    int local_10;
    int local_c;
    byte local_5;

    local_2c = *(int *)(param_1 + 0x144);
    iVar3    = param_4 * param_5 * (uint)param_6;
    _memset(param_3, 0, (int)(iVar3 + (iVar3 >> 0x1f & 7U)) >> 3);
    local_1a = *(byte *)(param_1 + 0x20);
    local_5  = *(byte *)(param_1 + 0x21);
    local_19 = *(byte *)(param_1 + 0x22);
    local_10 = 1;
    local_c  = 1;
    local_24 = 0;
    local_20 = _strlen(param_2);
    FUN_0065d870();
    if (param_6 == 0x20)
    {
        while (local_24 < (int)local_20)
        {
            uVar4    = FUN_0065e3a0(param_2 + local_24, &local_18);
            uVar4    = uVar4 & 0xff;
            local_24 = local_24 + uVar4;
            if (local_18 == 0)
                break;
            if (local_18 == 0x5c)
            {
                bVar1 = FUN_0065e3a0(param_2 + local_24, &local_18);
                if (bVar1 < 2)
                {
                    if (local_18 == 99)
                    {
                        cVar2    = FUN_0065e450(param_2[local_24 + 1]);
                        local_1a = FUN_0065e450(param_2[local_24 + 2]);
                        local_1a = cVar2 << 4 | local_1a;
                        cVar2    = FUN_0065e450(param_2[local_24 + 3]);
                        local_5  = FUN_0065e450(param_2[local_24 + 4]);
                        local_5  = cVar2 << 4 | local_5;
                        cVar2    = FUN_0065e450(param_2[local_24 + 5]);
                        local_19 = FUN_0065e450(param_2[local_24 + 6]);
                        local_19 = cVar2 << 4 | local_19;
                        local_24 = local_24 + 7;
                    }
                    else if (local_18 == 0x65)
                    {
                        local_1a = *(byte *)(param_1 + 0x20);
                        local_5  = *(byte *)(param_1 + 0x21);
                        local_19 = *(byte *)(param_1 + 0x22);
                        local_24 = local_24 + 1;
                    }
                    else if (local_18 == 0x6e)
                    {
                        local_10 = 1;
                        local_c  = *(int *)(param_1 + 0x134) + *(int *)(param_1 + 0x138) + local_c;
                        local_2c = local_2c + -1;
                        if (local_2c < 1)
                        {
                            local_20 = 0;
                        }
                        else
                        {
                            local_24 = local_24 + 1;
                        }
                    }
                }
            }
            else if (local_18 == 0x20)
            {
                if (*(int *)(param_1 + 0x140) - local_10 <
                    (int)((*(int *)(param_1 + 0x134) / 2) * uVar4 + *(int *)(param_1 + 0x13c)))
                {
                    local_10 = 1;
                    if (param_5 - local_c < *(int *)(param_1 + 0x134) + *(int *)(param_1 + 0x138))
                        break;
                    local_c  = *(int *)(param_1 + 0x134) + *(int *)(param_1 + 0x138) + local_c;
                    local_2c = local_2c + -1;
                    if (local_2c < 1)
                        break;
                }
                local_10 =
                    (*(int *)(param_1 + 0x134) / 2) * uVar4 + *(int *)(param_1 + 0x13c) + local_10;
            }
            else if (local_18 == 0x8140)
            {
                if (*(int *)(param_1 + 0x140) - local_10 <
                    (int)((*(int *)(param_1 + 0x134) / 2) * uVar4 + *(int *)(param_1 + 0x13c)))
                {
                    local_10 = 1;
                    if (param_5 - local_c < *(int *)(param_1 + 0x134) + *(int *)(param_1 + 0x138))
                        break;
                    local_c  = *(int *)(param_1 + 0x134) + *(int *)(param_1 + 0x138) + local_c;
                    local_2c = local_2c + -1;
                    if (local_2c < 1)
                        break;
                }
                local_10 =
                    (*(int *)(param_1 + 0x134) / 2) * uVar4 + *(int *)(param_1 + 0x13c) + local_10;
            }
            else
            {
                FUN_0065d9a0(local_18);
                if (*(int *)(param_1 + 0x140) - local_10 <
                    (int)((*(int *)(param_1 + 0x134) / 2) * uVar4 + *(int *)(param_1 + 0x13c)))
                {
                    local_10 = 1;
                    if (param_5 - local_c < *(int *)(param_1 + 0x134) + *(int *)(param_1 + 0x138))
                        break;
                    local_c  = *(int *)(param_1 + 0x134) + *(int *)(param_1 + 0x138) + local_c;
                    local_2c = local_2c + -1;
                    if (local_2c < 1)
                        break;
                }
                if (((int)((*(int *)(param_1 + 0x134) / 2) * uVar4 + local_10 +
                           *(int *)(param_1 + 0x13c)) < param_4) &&
                    (local_c + *(int *)(param_1 + 0x134) < param_5))
                {
                    if (*(char *)(param_1 + 0x130) == '\0')
                    {
                        for (local_14 = 0; local_14 < *(int *)(param_1 + 0x18);
                             local_14 = local_14 + 1)
                        {
                            for (local_30 = 0; local_30 < *(int *)(param_1 + 0x14);
                                 local_30 = local_30 + 1)
                            {
                                if (*(char *)(*(int *)(param_1 + 0x10) +
                                              local_30 * *(int *)(param_1 + 0x1c) + local_14) !=
                                    '\0')
                                {
                                    *(uint *)((int)param_3 +
                                              (local_10 + *(int *)(param_1 + 0x28) + local_14 +
                                               (local_c + *(int *)(param_1 + 0x2c) + local_30) *
                                                   param_4) *
                                                  4) =
                                        (uint) *
                                            (byte *)(*(int *)(param_1 + 0x10) +
                                                     local_30 * *(int *)(param_1 + 0x1c) +
                                                     local_14) *
                                            0xe000000 |
                                        0x3000000 | (uint)local_1a << 0x10 | (uint)local_1a << 8 |
                                        (uint)local_19;
                                }
                            }
                        }
                    }
                    else
                    {
                        for (local_14 = 0; local_14 < *(int *)(param_1 + 0x18);
                             local_14 = local_14 + 1)
                        {
                            for (local_30 = 0; local_30 < *(int *)(param_1 + 0x14);
                                 local_30 = local_30 + 1)
                            {
                                if (*(char *)(*(int *)(param_1 + 0x10) +
                                              local_30 * *(int *)(param_1 + 0x1c) + local_14) !=
                                    '\0')
                                {
                                    *(uint *)((int)param_3 +
                                              (local_10 + *(int *)(param_1 + 0x28) + local_14 +
                                               (local_c + *(int *)(param_1 + 0x2c) + local_30) *
                                                   param_4) *
                                                  4) =
                                        (uint) *
                                            (byte *)(*(int *)(param_1 + 0x10) +
                                                     local_30 * *(int *)(param_1 + 0x1c) +
                                                     local_14) *
                                            0xe000000 |
                                        0x3000000 |
                                        (0xff - ((int)((*(int *)(param_1 + 0x2c) + local_30) *
                                                       (0xff - (uint)local_1a)) /
                                                     *(int *)(param_1 + 0x134) &
                                                 0xffU)) *
                                            0x10000 |
                                        (0xff - ((int)((*(int *)(param_1 + 0x2c) + local_30) *
                                                       (0xff - (uint)local_5)) /
                                                     *(int *)(param_1 + 0x134) &
                                                 0xffU)) *
                                            0x100 |
                                        0xff - ((int)((*(int *)(param_1 + 0x2c) + local_30) *
                                                      (0xff - (uint)local_19)) /
                                                    *(int *)(param_1 + 0x134) &
                                                0xffU);
                                }
                            }
                        }
                    }
                }
                local_10 =
                    (*(int *)(param_1 + 0x134) / 2) * uVar4 + *(int *)(param_1 + 0x13c) + local_10;
            }
        }
    }
    else if (param_6 == 0x10)
    {
        while (local_24 < (int)local_20)
        {
            uVar4    = FUN_0065e3a0(param_2 + local_24, &local_18);
            uVar4    = uVar4 & 0xff;
            local_24 = local_24 + uVar4;
            if (local_18 == 0x20)
            {
                local_10 =
                    (*(int *)(param_1 + 0x134) / 2) * uVar4 + *(int *)(param_1 + 0x13c) + local_10;
            }
            else if (local_18 == 0x8140)
            {
                local_10 =
                    (*(int *)(param_1 + 0x134) / 2) * uVar4 + *(int *)(param_1 + 0x13c) + local_10;
            }
            else
            {
                FUN_0065d9a0(local_18);
                if (param_4 - local_10 <
                    (int)((*(int *)(param_1 + 0x134) / 2) * uVar4 + *(int *)(param_1 + 0x13c)))
                {
                    local_10 = 0;
                    if (param_5 - local_c < *(int *)(param_1 + 0x134) + *(int *)(param_1 + 0x138))
                        break;
                    local_c = *(int *)(param_1 + 0x134) + *(int *)(param_1 + 0x138) + local_c;
                }
                for (local_14 = 0; local_14 < *(int *)(param_1 + 0x18); local_14 = local_14 + 1)
                {
                    for (local_30 = 0; local_30 < *(int *)(param_1 + 0x14); local_30 = local_30 + 1)
                    {
                        if (*(char *)(*(int *)(param_1 + 0x10) +
                                      local_30 * *(int *)(param_1 + 0x1c) + local_14) != '\0')
                        {
                            *(ushort *)((int)param_3 +
                                        (local_10 + *(int *)(param_1 + 0x28) + local_14 +
                                         (local_c + *(int *)(param_1 + 0x2c) + local_30) *
                                             param_4) *
                                            2) =
                                ((ushort) *
                                     (byte *)(*(int *)(param_1 + 0x10) +
                                              local_30 * *(int *)(param_1 + 0x1c) + local_14) *
                                     2 +
                                 -1) *
                                    0x421 |
                                0x8000;
                        }
                    }
                }
                local_10 =
                    (*(int *)(param_1 + 0x134) / 2) * uVar4 + *(int *)(param_1 + 0x13c) + local_10;
            }
        }
    }
    FUN_0065d910();
    return;
}
