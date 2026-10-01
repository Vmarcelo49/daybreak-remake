// ============================================
// Address:  0x00637950
// Original: FUN_00637950
// Status:   unreviewed
// ============================================

void __thiscall FUN_00637950(int param_1, int param_2, int param_3, int param_4)

{
    undefined4 uVar1;
    undefined4 *puVar2;
    undefined4 uVar3;
    undefined4 uVar4;
    allocator<char> *paVar5;
    uint uVar6;
    int iVar7;
    float10 fVar8;
    undefined4 uVar9;
    undefined4 uVar10;
    undefined1 *puVar11;
    float fVar12;
    undefined4 uVar13;
    undefined4 local_194;
    undefined4 local_190;
    undefined1 local_188[40];
    undefined1 local_160[28];
    undefined1 local_144[16];
    undefined1 local_134[136];
    undefined1 local_ac[8];
    undefined1 local_a4;
    undefined1 local_a3;
    undefined1 local_a0[8];
    undefined1 local_98;
    undefined1 local_97;
    int local_94;
    int local_90;
    int local_8c;
    undefined1 local_88[8];
    undefined1 local_80;
    undefined2 local_7e;
    short local_7c;
    undefined4 local_78;
    undefined4 local_74;
    undefined4 local_70;
    undefined4 local_6c;
    undefined4 local_68;
    undefined4 local_64;
    char local_5d;
    int local_5c;
    float local_58;
    char local_51;
    undefined4 local_50;
    undefined4 local_4c;
    undefined4 local_48;
    short local_40;
    undefined1 local_3a;
    char local_39;
    int local_38;
    float local_34;
    char local_2d;
    int local_2c;
    float local_28;
    int local_24;
    char local_1d;
    float local_1c;
    int local_18;
    undefined4 local_14;
    undefined4 local_10;
    undefined4 local_c;
    undefined4 local_8;

    if (((((((*(int *)(param_2 + 8) != *(int *)(param_3 + 8)) ||
             ((*(uint *)(*(int *)(param_2 + 0x10) + 0x2c) & 0x10000) != 0)) &&
            (*(int *)(param_3 + 0x7ac) < 1)) &&
           (((*(char *)(param_3 + 0xaecc) == '\0' &&
              (*(short *)(param_2 + 0x88 + *(int *)(param_3 + 8) * 2) == 0)) &&
             ((0 < *(int *)(param_2 + 0x90 + *(int *)(param_3 + 8) * 4) &&
               (*(int *)(*(int *)(param_2 + 0x10) + 0x24) != 0)))))) &&
          ((**(int **)(param_3 + 0xc) != **(int **)(param_4 + 0xc) ||
            (*(int *)(*(int *)(param_2 + 0x10) + 0x3c) != 0)))) &&
         ((*(int *)(*(int *)(param_2 + 0x10) + 0x4c) != 0 || (0 < *(int *)(param_3 + 0x7a4))))) &&
        (((*(int *)(param_2 + 0x38) == param_3 ||
           ((*(uint *)(*(int *)(param_2 + 0x10) + 0x2c) & 0x20000) == 0)) &&
          (((*(uint *)(*(int *)(param_2 + 0x10) + 0x2c) & 0x8000) == 0 ||
            (((*(int *)(*(int *)(param_3 + 0x308) + 8) == *(int *)(param_2 + 8) &&
               (*(float *)(param_3 + 100) < 90.0)) &&
              (*(float *)(param_3 + 100) < -90.0 == (*(float *)(param_3 + 100) == -90.0)))))))))
    {
        local_1d = 0;
        local_5d = 0;
        if (*(int *)(*(int *)(param_2 + 0x10) + 8) == 0)
        {
            fVar12   = (float)*(int *)(*(int *)(param_2 + 0x10) + 0x24);
            uVar1    = std::allocator<char>::allocator<char>((allocator<char> *)(param_2 + 0xc4));
            uVar1    = FUN_004237f0(uVar1);
            uVar10   = 0x41f00000;
            uVar13   = std::allocator<char>::allocator<char>((allocator<char> *)(param_3 + 0xa4));
            uVar13   = FUN_004237f0(uVar13);
            local_1d = FUN_0063b470(uVar13, uVar10, uVar1, fVar12);
            fVar12   = (float)*(int *)(*(int *)(param_2 + 0x10) + 0x24);
            uVar1    = std::allocator<char>::allocator<char>((allocator<char> *)(param_2 + 0xc4));
            uVar1    = FUN_004237f0(uVar1);
            uVar10   = 0x41f00000;
            uVar13   = std::allocator<char>::allocator<char>((allocator<char> *)(param_3 + 0xb4));
            uVar13   = FUN_004237f0(uVar13);
            local_5d = FUN_0063b470(uVar13, uVar10, uVar1, fVar12);
        }
        else
        {
            fVar12   = (float)*(int *)(*(int *)(param_2 + 0x10) + 0x24);
            uVar1    = std::allocator<char>::allocator<char>((allocator<char> *)(param_2 + 0xd4));
            puVar2   = (undefined4 *)FUN_004237f0(uVar1);
            uVar1    = *puVar2;
            uVar13   = puVar2[1];
            uVar10   = puVar2[2];
            uVar3    = std::allocator<char>::allocator<char>((allocator<char> *)(param_2 + 0xc4));
            uVar3    = FUN_004237f0(uVar3);
            uVar9    = 0x41f00000;
            uVar4    = std::allocator<char>::allocator<char>((allocator<char> *)(param_3 + 0xa4));
            uVar4    = FUN_004237f0(uVar4);
            local_1d = FUN_0063b4d0(uVar4, uVar9, uVar3, uVar1, uVar13, uVar10, fVar12);
            fVar12   = (float)*(int *)(*(int *)(param_2 + 0x10) + 0x24);
            uVar1    = std::allocator<char>::allocator<char>((allocator<char> *)(param_2 + 0xd4));
            puVar2   = (undefined4 *)FUN_004237f0(uVar1);
            uVar1    = *puVar2;
            uVar13   = puVar2[1];
            uVar10   = puVar2[2];
            uVar3    = std::allocator<char>::allocator<char>((allocator<char> *)(param_2 + 0xc4));
            uVar3    = FUN_004237f0(uVar3);
            uVar9    = 0x41f00000;
            uVar4    = std::allocator<char>::allocator<char>((allocator<char> *)(param_3 + 0xb4));
            uVar4    = FUN_004237f0(uVar4);
            local_5d = FUN_0063b4d0(uVar4, uVar9, uVar3, uVar1, uVar13, uVar10, fVar12);
        }
        if ((local_1d != '\0') || (local_5d != '\0'))
        {
            if ((**(int **)(param_3 + 0xc) == **(int **)(param_4 + 0xc)) &&
                ((*(uint *)(*(int *)(param_2 + 0x10) + 0x2c) & 0x4180) != 0))
            {
                *(undefined2 *)(param_2 + 0x88 + *(int *)(param_3 + 8) * 2) = 0x80;
                *(int *)(param_2 + 0x90 + *(int *)(param_3 + 8) * 4) =
                    *(int *)(param_2 + 0x90 + *(int *)(param_3 + 8) * 4) + -1;
                if ((*(uint *)(*(int *)(param_2 + 0x10) + 0x2c) & 0x4000) != 0)
                {
                    if (*(int *)(param_3 + 0x7a4) < 1)
                    {
                        return;
                    }
                    *(int *)(param_3 + 0x7a4) =
                        *(int *)(param_3 + 0x7a4) + *(int *)(*(int *)(param_2 + 0x10) + 0x3c);
                    *(int *)(param_4 + 0xaefc) =
                        *(int *)(param_4 + 0xaefc) + *(int *)(*(int *)(param_2 + 0x10) + 0x3c);
                    if (9999 < *(int *)(param_3 + 0x7a4))
                    {
                        *(undefined4 *)(param_3 + 0x7a4) = 10000;
                    }
                }
                if ((*(uint *)(*(int *)(param_2 + 0x10) + 0x2c) & 0x80) != 0)
                {
                    if (*(int *)(*(int *)(param_2 + 0x10) + 0x38) < *(int *)(param_3 + 0x7e4))
                    {
                        local_190 = *(undefined4 *)(param_3 + 0x7e4);
                    }
                    else
                    {
                        local_190 = *(undefined4 *)(*(int *)(param_2 + 0x10) + 0x38);
                    }
                    *(undefined4 *)(param_3 + 0x7e0) = local_190;
                }
                if ((*(uint *)(*(int *)(param_2 + 0x10) + 0x2c) & 0x100) != 0)
                {
                    if (*(int *)(*(int *)(param_2 + 0x10) + 0x38) < *(int *)(param_3 + 0x7e4))
                    {
                        local_194 = *(undefined4 *)(param_3 + 0x7e4);
                    }
                    else
                    {
                        local_194 = *(undefined4 *)(*(int *)(param_2 + 0x10) + 0x38);
                    }
                    *(undefined4 *)(param_3 + 0x7e4) = local_194;
                }
            }
            else
            {
                if ((*(uint *)(*(int *)(param_2 + 0x10) + 0x2c) & 0x10) == 0)
                {
                    fVar8 = (float10)FUN_00423580(
                        *(float *)(param_2 + 0x1c) - *(float *)(param_3 + 0x1c),
                        *(float *)(param_2 + 0x14) - *(float *)(param_3 + 0x14));
                    fVar8 = (fVar8 / (float10)3.1415927) * (float10)180.0;
                }
                else
                {
                    fVar8 = (float10)FUN_00423580(-*(float *)(param_2 + 0x44),
                                                  -*(float *)(param_2 + 0x3c));
                    fVar8 = (fVar8 / (float10)3.1415927) * (float10)180.0;
                }
                local_58 = (float)fVar8;
                local_34 = local_58;
                for (local_1c = local_58 - (*(float *)(param_3 + 0x5c) + *(float *)(param_3 + 100));
                     180.0 < local_1c;
                     local_1c = local_1c - 360.0)
                {
                }
                for (; local_1c < -180.0; local_1c = local_1c + 360.0)
                {
                }
                *(undefined4 *)(param_3 + 0x684) = 0xffffffff;
                *(undefined4 *)(param_3 + 0x7d8) = *(undefined4 *)(param_2 + 8);
                fVar8                            = (float10)FUN_0042df90(local_1c);
                if (((fVar8 < (float10)45.0 == (fVar8 == (float10)45.0)) &&
                     ((*(uint *)(*(int *)(param_3 + 0x10) + 0x28) & 0x2000) == 0)) ||
                    (((*(uint *)(*(int *)(param_3 + 0x10) + 0x28) & 0x400) == 0 ||
                      ((*(uint *)(*(int *)(param_2 + 0x10) + 0x2c) & 8) != 0))))
                {
                    FUN_00430750(0, 0, 0, 0x3f800000);
                    std::allocator<char>::allocator<char>((allocator<char> *)&local_14);
                    local_28 = 0.0;
                    if (local_1d != '\0')
                    {
                        FUN_0063b960(param_3 + 0xa4);
                        local_28 = local_28 + 1.0;
                    }
                    if (local_5d != '\0')
                    {
                        FUN_0063b960(param_3 + 0xb4);
                        local_28 = local_28 + 1.0;
                    }
                    if (*(int *)(*(int *)(param_2 + 0x10) + 8) == 0)
                    {
                        local_14 = *(undefined4 *)(param_2 + 0xc4);
                        local_10 = *(undefined4 *)(param_2 + 200);
                        local_c  = *(undefined4 *)(param_2 + 0xcc);
                        local_8  = *(undefined4 *)(param_2 + 0xd0);
                    }
                    else
                    {
                        uVar1   = 0x40000000;
                        puVar11 = local_144;
                        FUN_004306f0(local_134, param_2 + 0xd4);
                        puVar2   = (undefined4 *)FUN_0063ba20(puVar11, uVar1);
                        local_14 = *puVar2;
                        local_10 = puVar2[1];
                        local_c  = puVar2[2];
                        local_8  = puVar2[3];
                    }
                    FUN_004307e0(local_28);
                    if (0 < *(int *)(*(int *)(param_2 + 0x10) + 0x70))
                    {
                        iVar7  = param_3;
                        paVar5 = (allocator<char> *)FUN_0063b9c0(local_160, &local_14);
                        uVar1  = std::allocator<char>::allocator<char>(paVar5);
                        uVar1  = FUN_004237f0(uVar1);
                        FUN_00435990(*(undefined4 *)(*(int *)(param_2 + 0x10) + 0x70),
                                     local_50,
                                     local_4c,
                                     local_48,
                                     uVar1,
                                     iVar7);
                    }
                    *(undefined2 *)(param_2 + 0x88 + *(int *)(param_3 + 8) * 2) = 1;
                    *(int *)(param_2 + 0x90 + *(int *)(param_3 + 8) * 4) =
                        *(int *)(param_2 + 0x90 + *(int *)(param_3 + 8) * 4) + -1;
                    switch (*(undefined4 *)(*(int *)(param_2 + 0x10) + 0x6c))
                    {
                    case 0:
                        local_40 = 0;
                        break;
                    default:
                        local_40 = *(short *)(*(int *)(param_2 + 0x10) + 0x6c);
                        break;
                    case 10:
                    case 0x14:
                    case 0x1e:
                        iVar7 = *(int *)(param_2 + 0x10);
                        uVar6 = FUN_0065d150();
                        local_40 =
                            (short)((ulonglong)uVar6 % 3) + (short)*(undefined4 *)(iVar7 + 0x6c);
                    }
                    if (0 < local_40)
                    {
                        uVar13 = 1;
                        uVar1 = std::allocator<char>::allocator<char>((allocator<char> *)&local_50);
                        uVar1 = FUN_004237f0(uVar1);
                        FUN_0064ae70((int)local_40, uVar1, uVar13);
                        if (DAT_006cfdb0 == '\x01')
                        {
                            FUN_0063bba0();
                            local_80 = *(undefined1 *)(param_3 + 8);
                            local_7e = *(undefined2 *)(*(int *)(param_2 + 0x10) + 0x70);
                            local_7c = local_40;
                            local_78 = local_50;
                            local_74 = local_4c;
                            local_70 = local_48;
                            paVar5   = (allocator<char> *)FUN_0063b9c0(local_188, &local_14);
                            uVar1    = std::allocator<char>::allocator<char>(paVar5);
                            puVar2   = (undefined4 *)FUN_004237f0(uVar1);
                            local_6c = *puVar2;
                            local_68 = puVar2[1];
                            local_64 = puVar2[2];
                            FUN_00415d30(0, local_88, 0, 8);
                        }
                    }
                    local_18 = 100;
                    if (**(int **)(param_3 + 0xc) == **(int **)(param_4 + 0xc))
                    {
                        if (*(int *)(param_3 + 8) != *(int *)(param_4 + 8))
                        {
                            *(int *)(param_4 + 0xaf24)        = *(int *)(param_4 + 0xaf24) + 1;
                            *(undefined1 *)(param_3 + 0xaebf) = 1;
                        }
                        local_18 = *(int *)(*(int *)(param_2 + 0x10) + 0x3c);
                    }
                    if (*(char *)(param_3 + 0x318) == '\0')
                    {
                        if (((*(char *)(param_3 + 0x844) == '\0') &&
                             (*(int *)(param_3 + 0x838) < *(int *)(param_3 + 0x324))) &&
                            (*(int *)(param_3 + 0x838) =
                                 (((((*(int *)(*(int *)(param_2 + 0x10) + 0x44) *
                                      *(int *)(param_1 + 0x43d0)) /
                                     0x85) *
                                    *(int *)(param_3 + 0x7cc)) /
                                   100) *
                                  local_18) /
                                     100 +
                                 *(int *)(param_3 + 0x838),
                             *(int *)(param_3 + 0x324) <= *(int *)(param_3 + 0x838)))
                        {
                            FUN_0064af20(*(undefined4 *)(param_3 + 8), 5);
                            *(undefined4 *)(param_3 + 0x838) = *(undefined4 *)(param_3 + 0x324);
                        }
                    }
                    else if ((((*(char *)(param_3 + 0x318) == '\x02') &&
                               (*(char *)(param_3 + 0x846) == '\0')) &&
                              (*(int *)(param_3 + 0x840) < *(int *)(param_3 + 0x324))) &&
                             (*(int *)(param_3 + 0x840) =
                                  (((((*(int *)(*(int *)(param_2 + 0x10) + 0x44) *
                                       *(int *)(param_1 + 0x43d0)) /
                                      0xe1) *
                                     *(int *)(param_3 + 0x7cc)) /
                                    100) *
                                   local_18) /
                                      100 +
                                  *(int *)(param_3 + 0x840),
                              *(int *)(param_3 + 0x324) <= *(int *)(param_3 + 0x840)))
                    {
                        *(undefined4 *)(param_3 + 0x840) = *(undefined4 *)(param_3 + 0x324);
                    }
                    if (((*(char *)(param_4 + 0x318) == '\x01') &&
                         (*(char *)(param_4 + 0x845) == '\0')) &&
                        ((*(int *)(param_4 + 0x83c) < *(int *)(param_4 + 0x32c) &&
                          (*(int *)(param_4 + 0x83c) = (*(int *)(*(int *)(param_2 + 0x10) + 0x48) *
                                                        *(int *)(param_1 + 0x43d0)) /
                                                           0x5a +
                                                       *(int *)(param_4 + 0x83c),
                           *(int *)(param_4 + 0x32c) <= *(int *)(param_4 + 0x83c)))))
                    {
                        FUN_0064af20(*(undefined4 *)(param_4 + 8), 6);
                        *(undefined1 *)(param_4 + 0xaec2) = 1;
                        *(undefined4 *)(param_4 + 0x83c)  = *(undefined4 *)(param_4 + 0x32c);
                    }
                    *(undefined4 *)(param_2 + 0xa0) =
                        *(undefined4 *)(*(int *)(param_2 + 0x10) + 0x54);
                    *(undefined4 *)(param_3 + 0xa0) =
                        *(undefined4 *)(*(int *)(param_2 + 0x10) + 0x58);
                    if (*(int *)(param_3 + 0xa0) < 0x3c)
                    {
                        *(undefined4 *)(param_3 + 0x82c) = 0;
                    }
                    else
                    {
                        *(undefined4 *)(param_3 + 0x82c) = *(undefined4 *)(param_3 + 0xa0);
                    }
                    iVar7 = *(int *)(param_3 + 0x7b0);
                    if (iVar7 == 0)
                    {
                        local_2c = 100;
                    }
                    else if (iVar7 == 1)
                    {
                        local_2c = 0x46;
                    }
                    else if (iVar7 == 2)
                    {
                        local_2c = 0x32;
                    }
                    else
                    {
                        local_2c = 0x21;
                    }
                    local_2c = (((local_2c * 100) / *(int *)(param_1 + 0x43cc)) * local_18) / 100;
                    local_38 = *(int *)(param_3 + 0xadec);
                    local_51 = '\0';
                    local_2d = '\0';
                    local_3a = 0;
                    if (0 < *(int *)(*(int *)(param_2 + 0x10) + 0x4c))
                    {
                        *(int *)(param_3 + 0x7b8) =
                            (*(int *)(*(int *)(param_2 + 0x10) + 0x4c) * *(int *)(param_3 + 2000)) /
                                100 +
                            *(int *)(param_3 + 0x7b8);
                        *(undefined4 *)(param_3 + 0x7bc) = 0x78;
                        if (99 < *(int *)(param_3 + 0x7b8))
                        {
                            *(float *)(param_3 + 0x87c) =
                                (float)*(int *)(*(int *)(param_2 + 0x10) + 0x74);
                            *(float *)(param_3 + 0x878) =
                                (float)*(int *)(*(int *)(param_2 + 0x10) + 0x78);
                            *(int *)(param_3 + 0x7b0)        = *(int *)(param_3 + 0x7b0) + 1;
                            *(int *)(param_3 + 0x7b4)        = *(int *)(param_3 + 0x7b4) + 1;
                            local_2d                         = '\x01';
                            *(undefined4 *)(param_3 + 0x7b8) = 0;
                            *(int *)(param_3 + 0x7c0) = *(int *)(param_3 + 0x7c0) +
                                                        *(int *)(*(int *)(param_2 + 0x10) + 0x50);
                            *(undefined4 *)(param_3 + 0x7c4) = 0x78;
                            if ((*(uint *)(*(int *)(param_3 + 0x10) + 0x28) & 0x800) == 0)
                            {
                                if ((*(char *)(param_3 + 0x84) == '\0') ||
                                    (99 < *(int *)(param_3 + 0x7c0)))
                                {
                                    local_38 = *(int *)(*(int *)(param_2 + 0x10) + 0x68);
                                }
                                else
                                {
                                    local_38 = *(int *)(*(int *)(param_2 + 0x10) + 100);
                                }
                            }
                            else
                            {
                                local_38 = 0x79;
                                local_2c = (local_2c * 7) / 10;
                            }
                            fVar8 = (float10)FUN_0042df90(local_1c);
                            if ((float10)90.0 < fVar8)
                            {
                                iVar7 = FUN_004236c0();
                                if ((iVar7 == 0) && (*(int *)(*(int *)(param_4 + 0x308) + 8) !=
                                                     *(int *)(param_3 + 8)))
                                {
                                    *(undefined1 *)(param_3 + 0xaeba) = 1;
                                }
                                local_38 = local_38 + 100;
                                local_58 = local_58 + 180.0;
                            }
                            if (99 < *(int *)(param_3 + 0x7c0))
                            {
                                *(undefined4 *)(param_3 + 0x7ac) = 0x1e;
                            }
                            *(float *)(param_3 + 100) = -(*(float *)(param_3 + 0x5c) - local_58);
                            while (180.0 < *(float *)(param_3 + 100))
                            {
                                *(float *)(param_3 + 100) = *(float *)(param_3 + 100) - 360.0;
                            }
                            while (*(float *)(param_3 + 100) < -180.0)
                            {
                                *(float *)(param_3 + 100) = *(float *)(param_3 + 100) + 360.0;
                            }
                            local_51 = '\x01';
                        }
                    }
                    for (local_8c = 0; local_8c < 8; local_8c = local_8c + 1)
                    {
                        if ((((0x40 << ((byte)local_8c & 0x1f) &
                               *(uint *)(*(int *)(param_2 + 0x10) + 0x2c)) != 0) &&
                             (local_8c != 2)) &&
                            (local_8c != 1))
                        {
                            if ((*(int *)(param_3 + 0x7dc + local_8c * 4) == 0) && (local_8c != 0))
                            {
                                *(undefined1 *)(param_3 + 0xaec0) = 1;
                            }
                            if (local_8c == 4)
                            {
                                if (*(int *)(param_3 + 0x7ec) == 0)
                                {
                                    *(undefined4 *)(param_3 + 0x7ec) =
                                        *(undefined4 *)(*(int *)(param_2 + 0x10) + 0x38);
                                    *(int *)(param_3 + 0x810) =
                                        (*(int *)(*(int *)(param_2 + 0x10) + 0x34) *
                                         *(int *)(param_4 + 0x7c8)) /
                                        100;
                                }
                                else if ((*(int *)(param_3 + 0x810) <=
                                          (*(int *)(*(int *)(param_2 + 0x10) + 0x34) *
                                           *(int *)(param_4 + 0x7c8)) /
                                              100) &&
                                         (*(int *)(param_3 + 0x7ec) <
                                          *(int *)(*(int *)(param_2 + 0x10) + 0x38)))
                                {
                                    *(undefined4 *)(param_3 + 0x7ec) =
                                        *(undefined4 *)(*(int *)(param_2 + 0x10) + 0x38);
                                    *(int *)(param_3 + 0x810) =
                                        (*(int *)(*(int *)(param_2 + 0x10) + 0x34) *
                                         *(int *)(param_4 + 0x7c8)) /
                                        100;
                                }
                            }
                            else if (*(int *)(param_3 + 0x7dc + local_8c * 4) == 0)
                            {
                                *(undefined4 *)(param_3 + 0x7dc + local_8c * 4) =
                                    *(undefined4 *)(*(int *)(param_2 + 0x10) + 0x38);
                                *(undefined4 *)(param_3 + 0x800 + local_8c * 4) =
                                    *(undefined4 *)(*(int *)(param_2 + 0x10) + 0x34);
                            }
                            else if ((*(int *)(param_3 + 0x800 + local_8c * 4) <=
                                      *(int *)(*(int *)(param_2 + 0x10) + 0x34)) &&
                                     (*(int *)(param_3 + 0x7dc + local_8c * 4) <
                                      *(int *)(*(int *)(param_2 + 0x10) + 0x38)))
                            {
                                *(undefined4 *)(param_3 + 0x7dc + local_8c * 4) =
                                    *(undefined4 *)(*(int *)(param_2 + 0x10) + 0x38);
                                *(undefined4 *)(param_3 + 0x800 + local_8c * 4) =
                                    *(undefined4 *)(*(int *)(param_2 + 0x10) + 0x34);
                            }
                        }
                    }
                    local_39 = 0 < *(int *)(param_3 + 0x7a4);
                    local_5c = (((((*(int *)(*(int *)(param_2 + 0x10) + 0x30) * local_2c) / 100) *
                                  *(int *)(param_4 + 0x7c8)) /
                                 100) *
                                *(int *)(param_3 + 0x7cc)) /
                               100;
                    if ((9999 < *(int *)(*(int *)(param_2 + 0x10) + 0x30)) && (local_5d != '\0'))
                    {
                        local_5c = local_5c / 3;
                    }
                    *(int *)(param_3 + 0x7a4) = *(int *)(param_3 + 0x7a4) - local_5c;
                    local_24                  = 0;
                    if (*(int *)(param_3 + 0x7a4) < 0)
                    {
                        local_24 = -*(int *)(param_3 + 0x7a4);
                    }
                    if (param_3 == *(int *)(param_2 + 0x38))
                    {
                        *(int *)(param_3 + 0xaef4) =
                            (local_5c - local_24) + *(int *)(param_3 + 0xaef4);
                        *(int *)(param_4 + 0xaeec) =
                            (local_5c - local_24) + *(int *)(param_4 + 0xaeec);
                        if (0 < *(int *)(*(int *)(param_2 + 0x10) + 0x4c))
                        {
                            *(int *)(param_3 + 0xaf28) = *(int *)(param_3 + 0xaf28) + 1;
                            *(int *)(param_4 + 0xaf1c) = *(int *)(param_4 + 0xaf1c) + 1;
                        }
                    }
                    else
                    {
                        *(int *)(param_3 + 0xaef8) =
                            (local_5c - local_24) + *(int *)(param_3 + 0xaef8);
                        *(int *)(param_4 + 0xaef0) =
                            (local_5c - local_24) + *(int *)(param_4 + 0xaef0);
                        if (0 < *(int *)(*(int *)(param_2 + 0x10) + 0x4c))
                        {
                            *(int *)(param_3 + 0xaf2c) = *(int *)(param_3 + 0xaf2c) + 1;
                            *(int *)(param_4 + 0xaf20) = *(int *)(param_4 + 0xaf20) + 1;
                        }
                    }
                    if ((((*(char *)(param_3 + 0x318) == '\x02') &&
                          (*(char *)(param_3 + 0x846) == '\0')) &&
                         (*(int *)(param_3 + 0x7a4) < 1)) &&
                        (((bool)local_39 &&
                          (*(int *)(param_3 + 0x324) <= *(int *)(param_3 + 0x840)))))
                    {
                        *(undefined4 *)(param_3 + 0x7a4) = 1;
                        if (*(char *)(param_3 + 0x84) == '\0')
                        {
                            local_38 = 0x1f7;
                        }
                        else
                        {
                            local_38 = 0x1f6;
                        }
                        local_51 = '\x01';
                    }
                    if (*(int *)(param_3 + 0x7a4) < 1)
                    {
                        local_38 = FUN_0063ba80(*(undefined4 *)(*(int *)(param_2 + 0x10) + 100));
                        local_90 = 0;
                        if (((*(int *)(param_3 + 0xadec) != 0xc6) &&
                             (*(int *)(param_3 + 0xadec) != 199)) &&
                            ((*(int *)(param_3 + 0xadec) != 0xc4 &&
                              (((local_38 == 0xc6 || (local_38 == 199)) &&
                                (*(int *)(param_3 + 0x84c) == 0))))))
                        {
                            *(undefined4 *)(param_3 + 0x84c) = 1;
                            local_90                         = 1;
                        }
                        if (local_39 == '\0')
                        {
                            if (local_2d != '\0')
                            {
                                FUN_00639650(**(undefined4 **)(param_3 + 0xc), local_90 + 1);
                                *(int *)(param_4 + 0xaf38) =
                                    local_90 + 1 + *(int *)(param_4 + 0xaf38);
                                iVar7 = FUN_00421930();
                                if ((iVar7 < 1) &&
                                    (FUN_00421960(), *(int *)(param_1 + 0x4a3c) == 2))
                                {
                                    *(undefined1 *)(param_4 + 0xaec9) = 1;
                                    *(undefined1 *)(param_4 + 0xaeb8) = 1;
                                    *(undefined4 *)(param_1 + 0x4428) =
                                        *(undefined4 *)(param_4 + 8);
                                    if (DAT_006cfdb0 == '\x01')
                                    {
                                        FUN_0063be00();
                                        local_a4 = *(undefined1 *)(param_4 + 8);
                                        local_a3 = *(undefined1 *)(param_3 + 8);
                                        FUN_00415d30(0, local_ac, 0, 8);
                                    }
                                }
                                FUN_0064aed0(10);
                            }
                        }
                        else
                        {
                            local_94 = -*(int *)(param_3 + 0x7a4) / 500;
                            if (5 < local_94)
                            {
                                local_94 = 5;
                            }
                            if (*(int *)(param_3 + 0x7a4) < -0xdac)
                            {
                                local_94 = local_94 + 1;
                            }
                            if (*(int *)(param_3 + 0x7a4) < -0x1194)
                            {
                                local_94 = local_94 + 1;
                            }
                            FUN_00639650(**(undefined4 **)(param_3 + 0xc),
                                         local_94 + 0x14 + local_90);
                            FUN_0064aed0(9);
                            FUN_00421960();
                            if (*(int *)(param_1 + 0x4a3c) == 2)
                            {
                                *(undefined1 *)(param_4 + 0xaec9) = 1;
                                *(undefined1 *)(param_4 + 0xaeb8) = 1;
                                *(undefined4 *)(param_1 + 0x4428) = *(undefined4 *)(param_4 + 8);
                                *(int *)(param_4 + 0xaf34)        = *(int *)(param_4 + 0xaf34) + 1;
                                *(int *)(param_3 + 0xaf3c)        = *(int *)(param_3 + 0xaf3c) + 1;
                                if (DAT_006cfdb0 == '\x01')
                                {
                                    FUN_0063be00();
                                    local_98 = *(undefined1 *)(param_4 + 8);
                                    local_97 = *(undefined1 *)(param_3 + 8);
                                    FUN_00415d30(0, local_a0, 0, 8);
                                }
                            }
                            *(undefined4 *)(param_3 + 0x7b8) = 0;
                        }
                        if (*(int *)(param_1 + 0x4a3c) == 2)
                        {
                            *(undefined4 *)(param_3 + 0x7a4) = 0;
                        }
                        else
                        {
                            *(undefined4 *)(param_3 + 0x7a4) = 1;
                        }
                        local_51                  = '\x01';
                        *(float *)(param_3 + 100) = -(*(float *)(param_3 + 0x5c) - local_34);
                        while (180.0 < *(float *)(param_3 + 100))
                        {
                            *(float *)(param_3 + 100) = *(float *)(param_3 + 100) - 360.0;
                        }
                        while (*(float *)(param_3 + 100) < -180.0)
                        {
                            *(float *)(param_3 + 100) = *(float *)(param_3 + 100) + 360.0;
                        }
                    }
                    if (local_51 != '\0')
                    {
                        FUN_00421080(local_38);
                    }
                }
                else
                {
                    *(undefined2 *)(param_2 + 0x88 + *(int *)(param_3 + 8) * 2) = 2;
                    if ((*(uint *)(*(int *)(param_3 + 0x10) + 0x28) & 0x8000) != 0)
                    {
                        *(ushort *)(param_2 + 0x88 + *(int *)(param_3 + 8) * 2) =
                            *(ushort *)(param_2 + 0x88 + *(int *)(param_3 + 8) * 2) | 0x100;
                    }
                    *(int *)(param_2 + 0x90 + *(int *)(param_3 + 8) * 4) =
                        *(int *)(param_2 + 0x90 + *(int *)(param_3 + 8) * 4) + -1;
                    FUN_0042c800(2);
                    *(int *)(param_3 + 0xaf30) = *(int *)(param_3 + 0xaf30) + 1;
                }
            }
        }
    }
    return;
}
