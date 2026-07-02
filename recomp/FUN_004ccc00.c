// ============================================
// Address:  0x004ccc00
// Original: FUN_004ccc00
// Status:   unreviewed
// ============================================

void __fastcall FUN_004ccc00(int *param_1)

{
    char cVar1;
    short sVar2;
    uint uVar3;
    int iVar4;
    float10 fVar5;
    float10 fVar6;
    float10 fVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    undefined4 uVar13;
    int local_84;
    int local_80;
    float local_7c;
    int local_68;
    int local_64;
    float local_60;
    int local_54;
    int local_50;
    float local_4c;
    int local_38;
    int local_34;
    float local_30;
    float local_20;
    float local_18;
    float local_10;
    float local_8;

    if (param_1[0x28] != 0)
    {
        return;
    }
    FUN_00434a70(0, 0);
    FUN_00434a70(1, 1);
    FUN_00434bd0();
    iVar4 = param_1[0x2b7b];
    if (iVar4 < 0x150)
    {
        if (iVar4 == 0x14f)
        {
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0);
                return;
            }
            if ((char)param_1[0x21] == '\0')
            {
                FUN_00421080(0x2b);
                param_1[0x16] = 0x3f000000;
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00422900();
                FUN_00423000();
            }
            if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0))
            {
                param_1[0x19] = param_1[0x18];
                param_1[0x18] = 0;
                FUN_0042c800(0);
                FUN_0042c840(1);
                param_1[0x3a] = 0;
                param_1[0x3c] = 0;
                param_1[0x15] = 0x418c0000;
                fVar5         = (float10)FUN_0042d980();
                if (fVar5 < (float10)490000.0)
                {
                    param_1[0x3c] = 1;
                }
            }
            uVar3 = FUN_0042c7b0();
            if ((uVar3 & 2) != 0)
            {
                FUN_00421080(0x188);
                FUN_0042c800(0);
                return;
            }
            if ((param_1[0x2b7d] < 2) && (param_1[0x3c] == 1))
            {
                FUN_0042db10(0, 0x41a00000);
            }
            if (((param_1[0x2b7d] == 1) && (2 < param_1[0x2b81])) &&
                ((fVar5 = (float10)FUN_0042d980(),
                  fVar5 < (float10)60000.0 || ((0x14 < param_1[0x2b81] || (param_1[0x3c] == 0))))))
            {
                FUN_00421100(2);
                return;
            }
            if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 9))
            {
                FUN_004223d0(3, 10, 0);
            }
            if ((1 < param_1[0x2b7d]) &&
                (param_1[0x15] = (int)((float)param_1[0x15] - 0.3), (float)param_1[0x15] < 0.0))
            {
                param_1[0x15] = 0;
            }
        }
        else if (iVar4 < 0x12d)
        {
            if (iVar4 == 300)
            {
                cVar1 = FUN_004218c0();
                if (cVar1 != '\0')
                {
                    FUN_00421080(0);
                    return;
                }
                if ((char)param_1[0x21] == '\0')
                {
                    FUN_00421080(0x2b);
                    param_1[0x16] = 0x3f000000;
                    return;
                }
                if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0))
                {
                    param_1[0x18] = 0;
                    FUN_0042c800(0);
                    FUN_0042c840(1);
                    param_1[0x3a] = 0;
                    param_1[0x3b] = 0;
                    param_1[0x3c] = 1;
                    param_1[0x15] = 0x41600000;
                    FUN_0042db10(0, 0x43340000);
                    fVar5 = (float10)FUN_0042d980();
                    if (fVar5 < (float10)640000.0)
                    {
                        param_1[0x3c] = 1;
                        param_1[0x15] = 0x41a00000;
                    }
                }
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    FUN_00422900();
                    FUN_00423000();
                }
                uVar3 = FUN_0042c7b0();
                if ((uVar3 & 2) != 0)
                {
                    FUN_00421080(0x188);
                    FUN_0042c800(0);
                    return;
                }
                sVar2 = FUN_0042c7b0();
                if ((sVar2 != 0) && (param_1[0x3b] == 0))
                {
                    param_1[0x3b] = 1;
                }
                if ((param_1[0x2b7d] == 0) && (param_1[0x3c] == 1))
                {
                    FUN_0042db10(0, 0x41700000);
                }
                if (param_1[0x2b7d] == 1)
                {
                    if (param_1[0x3c] == 1)
                    {
                        FUN_0042db10(0, 0x41700000);
                    }
                    fVar5 = (float10)FUN_0042d980();
                    if ((fVar5 < (float10)90000.0) || (param_1[0x3c] == 0))
                    {
                        FUN_00421100(2);
                        return;
                    }
                }
                if (param_1[0x2b7d] == 2)
                {
                    if ((param_1[0x2b81] < 9) && (param_1[0x3c] == 1))
                    {
                        FUN_0042db10(0, 0x41200000);
                    }
                    if (param_1[0x2b81] == 9)
                    {
                        FUN_0042c880(0x3d);
                        fVar5 = (float10)FUN_0042d980();
                        if ((((float10)90000.0 <= fVar5) ||
                             (fVar5 = (float10)FUN_0042df90(param_1[0x19]),
                              (float10)30.0 <= fVar5)) ||
                            (*(char *)((int)param_1 + 0xaec3) != '\x01'))
                        {
                            fVar5 = (float10)FUN_0042d980();
                            if ((((float10)90000.0 <= fVar5) ||
                                 (fVar5 = (float10)FUN_0042df90(param_1[0x19]),
                                  (float10)30.0 <= fVar5)) ||
                                (*(char *)((int)param_1 + 0xaebe) != '\x01'))
                            {
                                fVar5 = (float10)FUN_0042d980();
                                if ((((float10)90000.0 <= fVar5) ||
                                     (fVar5 = (float10)FUN_0042df90(param_1[0x19]),
                                      (float10)30.0 <= fVar5)) ||
                                    (*(char *)((int)param_1 + 0xaeb9) != '\x01'))
                                {
                                    FUN_004223d0(1, 10, 0);
                                }
                                else
                                {
                                    FUN_004223d0(5, 0xc, 0);
                                }
                            }
                            else
                            {
                                FUN_004223d0(0xf, 0xc, 0);
                            }
                        }
                        else
                        {
                            FUN_004223d0(0, 0xc, 0);
                        }
                    }
                    if (param_1[0x2b81] == 10)
                    {
                        param_1[0x15] = 0;
                    }
                }
            }
            else
            {
                switch (iVar4)
                {
                case 0:
                    param_1[0x15] = 0;
                    param_1[0x10] = 0;
                    if (param_1[0x1fd] < 1)
                    {
                        param_1[0x20d] = param_1[0x20d] + 0x28;
                    }
                    else
                    {
                        param_1[0x20d] = param_1[0x20d] + 5;
                    }
                    param_1[0x21d] = 0;
                    if (1000 < param_1[0x20d])
                    {
                        param_1[0x20d] = 1000;
                    }
                    param_1[0x3a] = 10;
                    if ((char)param_1[0x21] == '\0')
                    {
                        param_1[0x16] = 0x3f000000;
                        FUN_00421080(0x2b);
                        return;
                    }
                    if ((param_1[0x9e] != 0) || (param_1[0x9f] != 0))
                    {
                        FUN_00421080(10);
                        return;
                    }
                    break;
                default:
                    goto switchD_004ccc9b_caseD_1;
                case 10:
                    param_1[0x10] = 0;
                    if ((char)param_1[0x21] == '\0')
                    {
                        param_1[0x16] = 0x3f000000;
                        FUN_00421080(0x2b);
                        return;
                    }
                    if ((param_1[0x9e] == 0) && (param_1[0x9f] == 0))
                    {
                        FUN_00421080(0);
                        return;
                    }
                    if (param_1[0x9f] < 0)
                    {
                        if ((0 < param_1[0x9e]) && (param_1[0x3a] != 1))
                        {
                            param_1[0x3a]  = 1;
                            param_1[0x21d] = 0x41a00000;
                        }
                        if ((param_1[0x9e] == 0) && (param_1[0x3a] != 0))
                        {
                            param_1[0x3a]  = 0;
                            param_1[0x21d] = 0x41a00000;
                        }
                        if ((param_1[0x9e] < 0) && (param_1[0x3a] != 2))
                        {
                            param_1[0x3a]  = 2;
                            param_1[0x21d] = 0x41a00000;
                        }
                    }
                    if (param_1[0x9f] == 0)
                    {
                        if ((0 < param_1[0x9e]) && (param_1[0x3a] != 3))
                        {
                            param_1[0x3a]  = 3;
                            param_1[0x21d] = 0x41a00000;
                        }
                        if ((param_1[0x9e] == 0) && (param_1[0x3a] != 10))
                        {
                            param_1[0x3a]  = 10;
                            param_1[0x21d] = 0x41a00000;
                        }
                        if ((param_1[0x9e] < 0) && (param_1[0x3a] != 4))
                        {
                            param_1[0x3a]  = 4;
                            param_1[0x21d] = 0x41a00000;
                        }
                    }
                    if (0 < param_1[0x9f])
                    {
                        if ((0 < param_1[0x9e]) && (param_1[0x3a] != 5))
                        {
                            param_1[0x3a]  = 5;
                            param_1[0x21d] = 0x41a00000;
                        }
                        if ((param_1[0x9e] == 0) && (param_1[0x3a] != 6))
                        {
                            param_1[0x3a]  = 6;
                            param_1[0x21d] = 0x41a00000;
                        }
                        if ((param_1[0x9e] < 0) && (param_1[0x3a] != 7))
                        {
                            param_1[0x3a]  = 7;
                            param_1[0x21d] = 0x41a00000;
                        }
                    }
                    param_1[0x21d] = (int)((float)param_1[0x21d] - 1.0);
                    if ((float)param_1[0x21d] < 1.0)
                    {
                        param_1[0x21d] = 0x3f800000;
                    }
                    param_1[0x15] = 0x40c80000;
                    if (param_1[0x1fd] < 1)
                    {
                        param_1[0x20d] = param_1[0x20d] + 0x28;
                    }
                    else
                    {
                        param_1[0x20d] = param_1[0x20d] + 5;
                    }
                    if (1000 < param_1[0x20d])
                    {
                        param_1[0x20d] = 1000;
                    }
                    param_1[0x18] = 0;
                    FUN_00421780();
                    break;
                case 0x14:
                    cVar1 = FUN_004218c0();
                    if (cVar1 != '\0')
                    {
                        if ((char)param_1[0x21] == '\0')
                        {
                            param_1[0x16] = 0x3f000000;
                            FUN_00421080(0x2b);
                            return;
                        }
                        FUN_00421080(0);
                        return;
                    }
                    if ((char)param_1[0x21] == '\0')
                    {
                        FUN_00421080(0x1e);
                        return;
                    }
                    if ((param_1[0x2b7d] < 2) &&
                        (param_1[0x20d] = param_1[0x20d] + -0xb, param_1[0x20d] < 0))
                    {
                        param_1[0x20d] = 0;
                    }
                    if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] % 0x24 == 0xd))
                    {
                        FUN_0042c8b0(5);
                    }
                    if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] % 0x24 == 0x1f))
                    {
                        FUN_0042c8b0(6);
                    }
                    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                    {
                        param_1[0x18] = 0;
                        param_1[0x19] = 0;
                        fVar5         = (float10)FUN_0042df90(param_1[0x19]);
                        if ((float10)12.0 <= fVar5)
                        {
                            if (0.0 <= (float)param_1[0x19])
                            {
                                if (0.0 < (float)param_1[0x19])
                                {
                                    param_1[0x19] = (int)((float)param_1[0x19] - 10.0);
                                }
                            }
                            else
                            {
                                param_1[0x19] = (int)((float)param_1[0x19] + 10.0);
                            }
                        }
                        else
                        {
                            param_1[0x19] = 0;
                        }
                        param_1[0x15] = 0x41380000;
                        param_1[0x3a] = 0;
                    }
                    if (param_1[0x2b7d] == 1)
                    {
                        param_1[0x21d] = 0x40800000;
                        param_1[0x15]  = 0x41380000;
                        FUN_00421780();
                        if (((param_1[0x9f] == 0) && (param_1[0x9e] == 0)) || (param_1[0x20d] < 1))
                        {
                            FUN_00421100(2);
                            return;
                        }
                    }
                    if (param_1[0x2b7d] == 2)
                    {
                        param_1[0x21d] = 0;
                        param_1[0x15]  = (int)((float)param_1[0x15] - 0.5);
                        if ((float)param_1[0x15] < 0.0)
                        {
                            param_1[0x15] = 0;
                        }
                        if ((param_1[0x2b81] == 5) && (param_1[0x3a] < 0xf))
                        {
                            param_1[0x3a] = param_1[0x3a] + 1;
                            return;
                        }
                    }
                    break;
                case 0x17:
                    cVar1 = FUN_004218c0();
                    if (cVar1 != '\0')
                    {
                        FUN_00421080(0);
                        return;
                    }
                    if ((char)param_1[0x21] == '\0')
                    {
                        param_1[0x16] = 0x3f000000;
                        FUN_00421080(0x2b);
                        return;
                    }
                    if (param_1[0x2b7d] < 2)
                    {
                        FUN_0042db10(0, 0x41a00000);
                        param_1[0x20d] = param_1[0x20d] + -0xc;
                        if (param_1[0x20d] < 0)
                        {
                            param_1[0x20d] = 0;
                        }
                    }
                    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                    {
                        param_1[0x19]   = 0;
                        param_1[0x18]   = -0x3d4c0000;
                        param_1[0x15]   = 0x41700000;
                        param_1[0x2bd2] = param_1[0x2bd2] + 1;
                    }
                    if (param_1[0x2b7d] == 1)
                    {
                        param_1[0x18] = -0x3d4c0000;
                    }
                    if ((param_1[0x2b7d] < 2) && (param_1[0x15] = (int)((float)param_1[0x15] - 0.5),
                                                  (float)param_1[0x15] < 11.0))
                    {
                        param_1[0x15] = 0x41300000;
                    }
                    if (param_1[0x2b7d] == 2)
                    {
                        if ((char)param_1[0x21] == '\0')
                        {
                            param_1[0x16] = 0x3f000000;
                            FUN_00421080(0x2b);
                            return;
                        }
                        param_1[0x15] = (int)((float)param_1[0x15] - 0.35);
                        if ((float)param_1[0x15] < 0.0)
                        {
                            param_1[0x15] = 0;
                        }
                    }
                    break;
                case 0x18:
                    cVar1 = FUN_004218c0();
                    if (cVar1 != '\0')
                    {
                        if (10.0 < (float)param_1[0x1f])
                        {
                            param_1[0x16] = 0x3f000000;
                            FUN_00421080(0x2b);
                            return;
                        }
                        FUN_00421080(0);
                        return;
                    }
                    if ((char)param_1[0x21] == '\0')
                    {
                        param_1[0x16] = 0x3f000000;
                        FUN_00421080(0x2b);
                        return;
                    }
                    if (param_1[0x2b7d] < 2)
                    {
                        FUN_0042db10(0, 0x41a00000);
                        param_1[0x20d] = param_1[0x20d] + -0xc;
                        if (param_1[0x20d] < 0)
                        {
                            param_1[0x20d] = 0;
                        }
                    }
                    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                    {
                        param_1[0x19]   = 0;
                        param_1[0x18]   = 0x42b40000;
                        param_1[0x15]   = 0x41700000;
                        param_1[0x2bd2] = param_1[0x2bd2] + 1;
                    }
                    if (param_1[0x2b7d] == 1)
                    {
                        param_1[0x18] = 0x42b40000;
                    }
                    if ((param_1[0x2b7d] < 2) && (param_1[0x15] = (int)((float)param_1[0x15] - 0.5),
                                                  (float)param_1[0x15] < 11.0))
                    {
                        param_1[0x15] = 0x41300000;
                    }
                    if ((param_1[0x2b7d] == 2) &&
                        (param_1[0x15] = (int)((float)param_1[0x15] - 0.35),
                         (float)param_1[0x15] < 0.0))
                    {
                        param_1[0x15] = 0;
                    }
                    break;
                case 0x1b:
                case 0x1c:
                    cVar1 = FUN_004218c0();
                    if (cVar1 != '\0')
                    {
                        if (10.0 < (float)param_1[0x1f])
                        {
                            param_1[0x16] = 0x3f000000;
                            FUN_00421080(0x2b);
                            return;
                        }
                        FUN_00421080(0);
                        return;
                    }
                    if ((char)param_1[0x21] == '\0')
                    {
                        param_1[0x16] = 0x3f000000;
                        FUN_00421080(0x2b);
                        return;
                    }
                    if ((param_1[0x2b7d] < 2) &&
                        (param_1[0x20d] = param_1[0x20d] + -0xc, param_1[0x20d] < 0))
                    {
                        param_1[0x20d] = 0;
                    }
                    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                    {
                        param_1[0x19]   = 0;
                        param_1[0x18]   = 0x43340000;
                        param_1[0x15]   = 0x41580000;
                        param_1[0x2bd2] = param_1[0x2bd2] + 1;
                    }
                    if (param_1[0x2b7d] == 1)
                    {
                        param_1[0x21d] = 0;
                        param_1[0x15]  = 0x41580000;
                        param_1[0x18]  = 0x43340000;
                    }
                    if ((param_1[0x2b7d] == 2) &&
                        (param_1[0x15] = (int)((float)param_1[0x15] - 1.0),
                         (float)param_1[0x15] < 0.0))
                    {
                        param_1[0x15] = 0;
                    }
                    break;
                case 0x1e:
                    cVar1 = FUN_004218c0();
                    if (cVar1 != '\0')
                    {
                        param_1[0x16] = 0x3f000000;
                        FUN_00421080(0x2b);
                        return;
                    }
                    if (param_1[0x2b7d] < 3)
                    {
                        param_1[0x20d] = param_1[0x20d] + -10;
                        if (param_1[0x2b7d] < 2)
                        {
                            if (param_1[0xa0] == 0)
                            {
                                param_1[0x10] = (int)((float)param_1[0x10] - 0.5);
                                if ((float)param_1[0x10] < 0.0)
                                {
                                    param_1[0x10] = 0;
                                }
                            }
                            else
                            {
                                param_1[0x10] = (int)((float)param_1[0x10] + 0.5);
                                if (8.0 < (float)param_1[0x10])
                                {
                                    param_1[0x10] = 0x41000000;
                                }
                                param_1[0x20d] = param_1[0x20d] + -3;
                            }
                        }
                        if (param_1[0x20d] < 0)
                        {
                            param_1[0x20d] = 0;
                        }
                    }
                    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                    {
                        param_1[0x15]  = 0x414c0000;
                        param_1[0x10]  = 0;
                        param_1[0x21d] = 0x42700000;
                        param_1[0x18]  = 0;
                        param_1[0x3a]  = 0;
                    }
                    if (((param_1[0x2b7d] == 1) && (param_1[0x2b81] == 0)) && (param_1[0x3a] == 0))
                    {
                        FUN_0042c880(2);
                    }
                    if (param_1[0x2b7d] == 1)
                    {
                        param_1[0x21d] = 0x40000000;
                        param_1[0x15]  = 0x414c0000;
                        param_1[0x3a]  = param_1[0x3a] + 1;
                        if ((5 < param_1[0x3a]) && (((param_1[0x9f] == 0 && (param_1[0x9e] == 0)) ||
                                                     (param_1[0x20d] < 1))))
                        {
                            FUN_00421100(2);
                            return;
                        }
                    }
                    if (param_1[0x2b7d] == 2)
                    {
                        param_1[0x16] = 0x3f000000;
                        param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
                        if ((char)param_1[0x21] != '\0')
                        {
                            FUN_00421080(0x2c);
                            param_1[0x10] = 0;
                            return;
                        }
                    }
                    FUN_00421780();
                    break;
                case 0x28:
                    cVar1 = FUN_004218c0();
                    if (cVar1 != '\0')
                    {
                        FUN_00421080(0x29);
                        return;
                    }
                    param_1[0x18] = 0;
                    if (param_1[0x1fd] < 1)
                    {
                        param_1[0x20d] = param_1[0x20d] + 0x28;
                    }
                    else
                    {
                        param_1[0x20d] = param_1[0x20d] + 5;
                    }
                    if (1000 < param_1[0x20d])
                    {
                        param_1[0x20d] = 1000;
                    }
                    param_1[0x16]  = 0;
                    param_1[0x15]  = 0;
                    param_1[0x21d] = 0x41900000;
                    param_1[0x18]  = 0;
                    FUN_00421780();
                    break;
                case 0x29:
                    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                    {
                        param_1[0x10] = 0x41280000;
                        param_1[0x3a] = 0;
                        if ((param_1[0x9f] != 0) || (param_1[0x9e] != 0))
                        {
                            param_1[0x15] = 0x40c00000;
                        }
                    }
                    if (((float)param_1[0x10] < 6.0) && (param_1[0x2b7d] == 1))
                    {
                        FUN_00421080(0x2a);
                        return;
                    }
                    if (((char)param_1[0x21] != '\0') &&
                        ((float)param_1[0x10] < 0.0 != ((float)param_1[0x10] == 0.0)))
                    {
                        FUN_00421080(0x2c);
                        param_1[0x10] = 0;
                        return;
                    }
                    param_1[0x21d] = 0x3f800000;
                    param_1[0x10]  = (int)((float)param_1[0x10] - (float)param_1[0x16]);
                    param_1[0x3a]  = param_1[0x3a] + 1;
                    if (((float)param_1[0x16] == 0.0) &&
                        (param_1[0x20d] = param_1[0x20d] + -0xc, param_1[0x20d] < 0))
                    {
                        param_1[0x20d] = 0;
                    }
                    if (param_1[0xa0] == 0)
                    {
                        param_1[0x3a] = 0;
                    }
                    if (((param_1[0x3a] == 0) || (99 < param_1[0x3a])) || (param_1[0x20d] < 1))
                    {
                        param_1[0x16] = 0x3f000000;
                    }
                    if ((param_1[0x9f] == 0) && (param_1[0x9e] == 0))
                    {
                        param_1[0x15] = (int)((float)param_1[0x15] - 0.2);
                        if ((float)param_1[0x15] < 0.0)
                        {
                            param_1[0x15] = 0;
                        }
                    }
                    else
                    {
                        param_1[0x15] = (int)((float)param_1[0x15] + 0.2);
                        if (6.0 < (float)param_1[0x15])
                        {
                            param_1[0x15] = 0x40c00000;
                        }
                    }
                    FUN_00421780();
                    break;
                case 0x2a:
                    if (((char)param_1[0x21] != '\0') &&
                        ((float)param_1[0x10] < 0.0 != ((float)param_1[0x10] == 0.0)))
                    {
                        FUN_00421080(0x2c);
                        param_1[0x10] = 0;
                        return;
                    }
                    param_1[0x21d] = 0x3f800000;
                    param_1[0x10]  = (int)((float)param_1[0x10] - (float)param_1[0x16]);
                    if ((param_1[0xa0] == 0) || (0x3b < (uint)param_1[0xa0]))
                    {
                        param_1[0x16] = 0x3f000000;
                    }
                    if ((param_1[0x9f] == 0) && (param_1[0x9e] == 0))
                    {
                        param_1[0x15] = (int)((float)param_1[0x15] - 0.2);
                        if ((float)param_1[0x15] < 0.0)
                        {
                            param_1[0x15] = 0;
                        }
                    }
                    else
                    {
                        param_1[0x15] = (int)((float)param_1[0x15] + 0.2);
                        if (6.0 < (float)param_1[0x15])
                        {
                            param_1[0x15] = 0x40c00000;
                        }
                    }
                    FUN_00421780();
                    break;
                case 0x2b:
                    if (((char)param_1[0x21] != '\0') &&
                        ((float)param_1[0x10] < 0.0 != ((float)param_1[0x10] == 0.0)))
                    {
                        FUN_00421080(0x2c);
                        param_1[0x10] = 0;
                        return;
                    }
                    param_1[0x21d] = 0x3f800000;
                    if ((float)param_1[0x16] == 0.0)
                    {
                        param_1[0x16] = 0x3f000000;
                    }
                    param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
                    if ((param_1[0xa0] == 0) || (0x3b < (uint)param_1[0xa0]))
                    {
                        param_1[0x16] = 0x3f000000;
                    }
                    FUN_00421780();
                    break;
                case 0x2c:
                    cVar1 = FUN_004218c0();
                    if (cVar1 != '\0')
                    {
                        FUN_00421080(0);
                        return;
                    }
                    param_1[0x16]  = 0;
                    param_1[0x10]  = 0;
                    param_1[0x18]  = 0;
                    param_1[0x21d] = 0;
                    if ((0.0 < (float)param_1[0x15]) &&
                        (param_1[0x15] = (int)((float)param_1[0x15] - 0.5),
                         (float)param_1[0x15] < 0.0))
                    {
                        param_1[0x15] = 0;
                    }
                    if (((float)param_1[0x15] < 0.0) &&
                        (param_1[0x15] = (int)((float)param_1[0x15] + 0.5),
                         0.0 < (float)param_1[0x15]))
                    {
                        param_1[0x15] = 0;
                    }
                    param_1[0x15] = 0;
                    if (param_1[0x1fd] < 1)
                    {
                        param_1[0x20d] = param_1[0x20d] + 0x28;
                    }
                    else
                    {
                        param_1[0x20d] = param_1[0x20d] + 5;
                    }
                    if (1000 < param_1[0x20d])
                    {
                        param_1[0x20d] = 1000;
                    }
                }
            }
        }
        else
        {
            switch (iVar4)
            {
            case 0x12d:
                cVar1 = FUN_004218c0();
                if (cVar1 != '\0')
                {
                    FUN_00421080(0);
                    return;
                }
                if ((char)param_1[0x21] == '\0')
                {
                    FUN_00421080(0x2b);
                    param_1[0x16] = 0x3f000000;
                    return;
                }
                if ((param_1[0x3b] != 0) && (param_1[0x1a1] = 2, param_1[0x2b81] < 10))
                {
                    FUN_0042db10(0, 0x41a00000);
                }
                if (param_1[0x2b81] == 0)
                {
                    param_1[0x18] = 0;
                    FUN_0042c800(0);
                    FUN_0042c840(1);
                }
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    FUN_00422900();
                    FUN_00423000();
                }
                uVar3 = FUN_0042c7b0();
                if ((uVar3 & 2) != 0)
                {
                    FUN_00421080(0x188);
                    FUN_0042c800(0);
                    return;
                }
                if (param_1[0x2b81] == 0x12)
                {
                    FUN_0042c880(0x3e);
                    FUN_004223d0(3, 10, 0);
                }
                if (param_1[0x2b81] == 0xc)
                {
                    param_1[0x15]  = 0x41c80000;
                    param_1[0x21d] = 0;
                }
                if (param_1[0x2b81] == 0x18)
                {
                    param_1[0x15]  = 0;
                    param_1[0x21d] = 0;
                }
                break;
            default:
            switchD_004ccc9b_caseD_1:
                FUN_00428510();
                return;
            case 0x131:
                cVar1 = FUN_004218c0();
                if (cVar1 != '\0')
                {
                    FUN_00421080(0);
                    return;
                }
                if ((char)param_1[0x21] == '\0')
                {
                    FUN_00421080(0x2b);
                    param_1[0x16] = 0x3f000000;
                    return;
                }
                if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0))
                {
                    param_1[0x18] = 0;
                    FUN_0042c800(0);
                    FUN_0042c840(1);
                    param_1[0x3a] = 0;
                    param_1[0x3b] = 0;
                    param_1[0x3c] = 1;
                    param_1[0x15] = 0x41600000;
                    FUN_0042db10(0, 0x43340000);
                    fVar5 = (float10)FUN_0042d980();
                    if (fVar5 < (float10)640000.0)
                    {
                        param_1[0x3c] = 1;
                        param_1[0x15] = 0x41a00000;
                    }
                }
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    FUN_00422900();
                    FUN_00423000();
                }
                uVar3 = FUN_0042c7b0();
                if ((uVar3 & 2) != 0)
                {
                    FUN_00421080(0x188);
                    FUN_0042c800(0);
                    return;
                }
                sVar2 = FUN_0042c7b0();
                if ((sVar2 != 0) && (param_1[0x3b] == 0))
                {
                    param_1[0x3b] = 1;
                }
                if ((param_1[0x2b7d] == 0) && (param_1[0x3c] == 1))
                {
                    FUN_0042db10(0, 0x41700000);
                }
                if (param_1[0x2b7d] == 1)
                {
                    if (param_1[0x3c] == 1)
                    {
                        FUN_0042db10(0, 0x41700000);
                    }
                    fVar5 = (float10)FUN_0042d980();
                    if ((fVar5 < (float10)90000.0) || (param_1[0x3c] == 0))
                    {
                        FUN_00421100(2);
                        return;
                    }
                }
                if (param_1[0x2b7d] == 2)
                {
                    if ((param_1[0x2b81] < 9) && (param_1[0x3c] == 1))
                    {
                        FUN_0042db10(0, 0x41200000);
                    }
                    if (param_1[0x2b81] == 9)
                    {
                        FUN_0042c880(0x3d);
                        fVar5 = (float10)FUN_0042d980();
                        if ((((float10)90000.0 <= fVar5) ||
                             (fVar5 = (float10)FUN_0042df90(param_1[0x19]),
                              (float10)30.0 <= fVar5)) ||
                            (*(char *)((int)param_1 + 0xaec3) != '\x01'))
                        {
                            fVar5 = (float10)FUN_0042d980();
                            if ((((float10)90000.0 <= fVar5) ||
                                 (fVar5 = (float10)FUN_0042df90(param_1[0x19]),
                                  (float10)30.0 <= fVar5)) ||
                                (*(char *)((int)param_1 + 0xaebe) != '\x01'))
                            {
                                fVar5 = (float10)FUN_0042d980();
                                if ((((float10)90000.0 <= fVar5) ||
                                     (fVar5 = (float10)FUN_0042df90(param_1[0x19]),
                                      (float10)30.0 <= fVar5)) ||
                                    (*(char *)((int)param_1 + 0xaeb9) != '\x01'))
                                {
                                    FUN_004223d0(1, 10, 0);
                                }
                                else
                                {
                                    FUN_004223d0(5, 0xc, 0);
                                }
                            }
                            else
                            {
                                FUN_004223d0(0xf, 0xc, 0);
                            }
                        }
                        else
                        {
                            FUN_004223d0(0, 0xc, 0);
                        }
                    }
                    if (param_1[0x2b81] == 10)
                    {
                        param_1[0x15] = 0;
                    }
                }
                break;
            case 0x136:
                cVar1 = FUN_004218c0();
                if (cVar1 != '\0')
                {
                    FUN_00421080(0);
                    return;
                }
                if ((char)param_1[0x21] == '\0')
                {
                    FUN_00421080(0x2b);
                    param_1[0x16] = 0x3f000000;
                    return;
                }
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    param_1[0x18] = 0;
                    FUN_0042c800(0);
                    FUN_0042c840(1);
                    param_1[0x15] = 0x41b40000;
                    param_1[0x3a] = 0;
                    FUN_0042db10(0, 0x43340000);
                }
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    FUN_00422900();
                    FUN_00423000();
                }
                if ((param_1[0x2b7d] == 1) &&
                    (fVar5 = (float10)FUN_0042d980(), fVar5 < (float10)75000.0))
                {
                    FUN_00421100(2);
                }
                if (param_1[0x2b7d] == 0)
                {
                    FUN_0042db10(0, 0x41000000);
                }
                if (param_1[0x2b7d] == 1)
                {
                    FUN_0042db10(0, 0x41200000);
                }
                if (param_1[0x2b7d] == 2)
                {
                    param_1[0x15] = (int)((float)param_1[0x15] - 1.0);
                    if (param_1[0x2b81] < 10)
                    {
                        FUN_0042db10(0, 0x40c00000);
                    }
                    if ((float)param_1[0x15] < 0.0)
                    {
                        param_1[0x15] = 0;
                    }
                    if (param_1[0x2b81] == 4)
                    {
                        FUN_0042c880(0x3e);
                        FUN_004223d0(2, 10, 0);
                    }
                }
                break;
            case 0x137:
                cVar1 = FUN_004218c0();
                if (cVar1 != '\0')
                {
                    FUN_00421080(0);
                    return;
                }
                if ((char)param_1[0x21] == '\0')
                {
                    FUN_00421080(0x2b);
                    param_1[0x16] = 0x3f000000;
                    return;
                }
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] < 0xd))
                {
                    FUN_0042db10(0, 0x41700000);
                }
                if (param_1[0x2b81] == 0)
                {
                    param_1[0x15] = 0x41940000;
                    param_1[0x18] = 0;
                    FUN_0042c800(0);
                    FUN_0042c840(1);
                    FUN_0042db10(0, 0x43340000);
                }
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    FUN_00422900();
                    FUN_00423000();
                }
                if (param_1[0x2b81] == 0xd)
                {
                    FUN_0042c880(0x3e);
                    FUN_004223d0(3, 10, 0);
                }
                if (param_1[0x2b81] == 0x19)
                {
                    param_1[0x15] = 0;
                }
                uVar3 = FUN_0042c7b0();
                if ((uVar3 & 2) != 0)
                {
                    FUN_00421080(0x188);
                    FUN_0042c800(0);
                    return;
                }
                break;
            case 0x140:
                cVar1 = FUN_004218c0();
                if (cVar1 != '\0')
                {
                    FUN_00421080(0x2b);
                    param_1[0xb] = 0;
                    return;
                }
                if ((float)param_1[0x16] == 0.0)
                {
                    param_1[0x16] = 0x3f000000;
                }
                if ((param_1[0x2b7d] == 2) && (10 < param_1[0x2b81]))
                {
                    param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
                }
                if ((((char)param_1[0x21] != '\0') && (param_1[0x2b7d] == 2)) &&
                    (10 < param_1[0x2b81]))
                {
                    FUN_00421080(0x149);
                    param_1[0x15] = 0;
                    param_1[0x10] = 0;
                    param_1[0xb]  = 0;
                    return;
                }
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    param_1[0x18] = 0;
                    FUN_0042c800(0);
                    FUN_0042c840(1);
                    param_1[0x3a] = 0;
                    param_1[0x3b] = 0;
                    param_1[0x3c] = 0;
                    FUN_00422900();
                    FUN_00423000();
                    if ((float)param_1[0x10] <= 3.0)
                    {
                        local_30 = (float)param_1[0x10];
                    }
                    else
                    {
                        local_30 = 3.0;
                    }
                    if (-3.0 <= local_30)
                    {
                        if ((float)param_1[0x10] <= 3.0)
                        {
                            local_38 = param_1[0x10];
                        }
                        else
                        {
                            local_38 = 0x40400000;
                        }
                        local_34 = local_38;
                    }
                    else
                    {
                        local_34 = -0x3fc00000;
                    }
                    param_1[0x10] = local_34;
                    param_1[0x15] = 0x41200000;
                    if ((param_1[0x2b81] == 0) &&
                        (fVar5 = (float10)FUN_0042d980(), fVar5 < (float10)640000.0))
                    {
                        param_1[0x3c] = 0xb4;
                        FUN_0042db10(0, 0x43340000);
                    }
                    fVar5 = (float10)FUN_00423580(param_1[0x10], param_1[0x15]);
                    param_1[0xb] =
                        (int)(float)((fVar5 / (float10)3.1415927) * (float10)180.0 + (float10)20.0);
                    param_1[0xb6] = 0x428c0000;
                }
                param_1[0x3b] = param_1[0x3b] + 1;
                if ((param_1[0x2b7d] < 2) && (0 < param_1[0x3c]))
                {
                    fVar5   = (float10)FUN_00423580(param_1[0x10], param_1[0x15]);
                    local_8 = (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                    fVar5   = (float10)FUN_0042da80();
                    fVar11  = (float)(fVar5 + (float10)10.0);
                    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                    {
                        fVar5   = (float10)FUN_0042da80();
                        local_8 = (float)(fVar5 + (float10)10.0);
                    }
                    if ((fVar11 < local_8) && (local_8 = local_8 - 5.0, local_8 < fVar11))
                    {
                        local_8 = fVar11;
                    }
                    if ((local_8 < fVar11) && (local_8 = local_8 + 5.0, fVar11 < local_8))
                    {
                        local_8 = fVar11;
                    }
                    if (40.0 < local_8)
                    {
                        local_8 = 40.0;
                    }
                    if (local_8 < -35.0)
                    {
                        local_8 = -35.0;
                    }
                    iVar4         = param_1[0x3c];
                    fVar5         = (float10)FUN_0065d050(local_8);
                    param_1[0x15] = (int)(float)(fVar5 * (float10)((float)iVar4 * 0.1));
                    iVar4         = param_1[0x3c];
                    fVar5         = (float10)FUN_0065d010(local_8);
                    param_1[0x10] = (int)(float)(fVar5 * (float10)((float)iVar4 * 0.1));
                    fVar5         = (float10)FUN_00423580(param_1[0x10], param_1[0x15]);
                    param_1[0xb] =
                        (int)(float)((fVar5 / (float10)3.1415927) * (float10)180.0 + (float10)20.0);
                    param_1[0xb6] = 0x428c0000;
                    FUN_0042db10(0, 0x41200000);
                    param_1[0x3c] = param_1[0x3c] + -4;
                    if (param_1[0x3c] < 100)
                    {
                        param_1[0x3c] = 100;
                    }
                }
                if ((param_1[0x2b7d] == 1) && (FUN_0042db10(0, 0x40000000), 7 < param_1[0x2b81]))
                {
                    fVar5 = (float10)FUN_0042d980();
                    fVar6 = (float10)FUN_0042da30();
                    fVar7 = (float10)FUN_0042da30();
                    if ((fVar7 * (float10)(float)fVar6 + (float10)(float)fVar5 <
                         (float10)50000.0) ||
                        ((0x19 < param_1[0x2b81] || (param_1[0x3c] == 0))))
                    {
                        FUN_00421100(2);
                        return;
                    }
                }
                if (param_1[0x2b7d] == 2)
                {
                    if (param_1[0x2b81] == 0)
                    {
                        FUN_0042c880(0x3e);
                        fVar5 = (float10)FUN_0042d980();
                        if ((((float10)40000.0 <= fVar5) ||
                             (fVar5 = (float10)FUN_0042df90(param_1[0x19]),
                              (float10)30.0 <= fVar5)) ||
                            (*(char *)((int)param_1 + 0xaec3) != '\x01'))
                        {
                            fVar5 = (float10)FUN_0042d980();
                            if ((((float10)40000.0 <= fVar5) ||
                                 (fVar5 = (float10)FUN_0042df90(param_1[0x19]),
                                  (float10)30.0 <= fVar5)) ||
                                (*(char *)((int)param_1 + 0xaebe) != '\x01'))
                            {
                                fVar5 = (float10)FUN_0042d980();
                                if ((((float10)40000.0 <= fVar5) ||
                                     (fVar5 = (float10)FUN_0042df90(param_1[0x19]),
                                      (float10)30.0 <= fVar5)) ||
                                    (*(char *)((int)param_1 + 0xaeb9) != '\x01'))
                                {
                                    FUN_004223d0(1, 10, 0);
                                }
                                else
                                {
                                    FUN_004223d0(5, 0xc, 0);
                                }
                            }
                            else
                            {
                                FUN_004223d0(0xf, 0xc, 0);
                            }
                        }
                        else
                        {
                            FUN_004223d0(0, 0xc, 0);
                        }
                    }
                    if (0x19 < param_1[0x2b81])
                    {
                        if ((0.0 < (float)param_1[0xb]) &&
                            (param_1[0xb] = (int)((float)param_1[0xb] - 5.0),
                             (float)param_1[0xb] < 0.0))
                        {
                            param_1[0xb] = 0;
                        }
                        if (((float)param_1[0xb] < 0.0) &&
                            (param_1[0xb] = (int)((float)param_1[0xb] + 5.0),
                             0.0 < (float)param_1[0xb]))
                        {
                            param_1[0xb] = 0;
                        }
                    }
                }
                break;
            case 0x149:
                cVar1 = FUN_004218c0();
                if (cVar1 != '\0')
                {
                    FUN_00421080(0);
                    return;
                }
                param_1[0x16]  = 0;
                param_1[0x10]  = 0;
                param_1[0x18]  = 0;
                param_1[0x21d] = 0;
                param_1[0x15]  = 0;
                if (param_1[0x1fd] < 1)
                {
                    param_1[0x20d] = param_1[0x20d] + 0x28;
                }
                else
                {
                    param_1[0x20d] = param_1[0x20d] + 5;
                }
                if (1000 < param_1[0x20d])
                {
                    param_1[0x20d] = 1000;
                }
                break;
            case 0x14a:
                cVar1 = FUN_004218c0();
                if (cVar1 != '\0')
                {
                    FUN_00421080(0);
                    return;
                }
                if ((char)param_1[0x21] == '\0')
                {
                    FUN_00421080(0x2b);
                    param_1[0x16] = 0x3f000000;
                    return;
                }
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    param_1[0x18] = 0;
                    FUN_0042c800(0);
                    FUN_0042c840(1);
                    param_1[0x3a] = 0;
                    param_1[0x15] = 0x41840000;
                    FUN_00422900();
                    FUN_00423000();
                }
                uVar3 = FUN_0042c7b0();
                if ((uVar3 & 2) != 0)
                {
                    FUN_00421080(0x188);
                    FUN_0042c800(0);
                    return;
                }
                if (param_1[0x2b7d] == 0)
                {
                    FUN_0042db10(0, 0x41a00000);
                }
                if (param_1[0x2b7d] == 1)
                {
                    FUN_0042db10(0, 0x40a00000);
                    fVar5 = (float10)FUN_0042d980();
                    if ((fVar5 < (float10)90000.0) && (2 < param_1[0x2b81]))
                    {
                        FUN_00421100(2);
                        return;
                    }
                }
                if (param_1[0x2b7d] == 2)
                {
                    if (param_1[0x2b81] == 0)
                    {
                        param_1[0x15] = 0x41b40000;
                    }
                    if (10 < param_1[0x2b81])
                    {
                        param_1[0x15] = (int)((float)param_1[0x15] - 1.5);
                    }
                    if ((float)param_1[0x15] < 0.0)
                    {
                        param_1[0x15] = 0;
                    }
                    if (param_1[0x2b81] == 4)
                    {
                        fVar5 = (float10)FUN_0042d980();
                        if ((((float10)40000.0 <= fVar5) ||
                             (fVar5 = (float10)FUN_0042df90(param_1[0x19]),
                              (float10)30.0 <= fVar5)) ||
                            (*(char *)((int)param_1 + 0xaec3) != '\x01'))
                        {
                            fVar5 = (float10)FUN_0042d980();
                            if ((((float10)40000.0 <= fVar5) ||
                                 (fVar5 = (float10)FUN_0042df90(param_1[0x19]),
                                  (float10)30.0 <= fVar5)) ||
                                (*(char *)((int)param_1 + 0xaebe) != '\x01'))
                            {
                                fVar5 = (float10)FUN_0042d980();
                                if ((((float10)40000.0 <= fVar5) ||
                                     (fVar5 = (float10)FUN_0042df90(param_1[0x19]),
                                      (float10)30.0 <= fVar5)) ||
                                    (*(char *)((int)param_1 + 0xaeb9) != '\x01'))
                                {
                                    FUN_004223d0(1, 10, 0);
                                }
                                else
                                {
                                    FUN_004223d0(5, 0xc, 0);
                                }
                            }
                            else
                            {
                                FUN_004223d0(0xf, 0xc, 0);
                            }
                        }
                        else
                        {
                            FUN_004223d0(0, 0xc, 0);
                        }
                    }
                }
                break;
            case 0x14b:
                cVar1 = FUN_004218c0();
                if (cVar1 != '\0')
                {
                    FUN_00421080(0);
                    return;
                }
                if ((char)param_1[0x21] == '\0')
                {
                    FUN_00421080(0x2b);
                    param_1[0x16] = 0x3f000000;
                    return;
                }
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    FUN_00422900();
                    FUN_00423000();
                }
                if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0))
                {
                    param_1[0x19] = param_1[0x18];
                    param_1[0x18] = 0;
                    FUN_0042c800(0);
                    FUN_0042c840(1);
                    param_1[0x3a] = 0;
                    param_1[0x3c] = 0;
                    param_1[0x15] = 0x418c0000;
                    fVar5         = (float10)FUN_0042d980();
                    if (fVar5 < (float10)490000.0)
                    {
                        param_1[0x3c] = 1;
                    }
                }
                uVar3 = FUN_0042c7b0();
                if ((uVar3 & 2) != 0)
                {
                    FUN_00421080(0x188);
                    FUN_0042c800(0);
                    return;
                }
                if ((param_1[0x2b7d] < 2) && (param_1[0x3c] == 1))
                {
                    FUN_0042db10(0, 0x41a00000);
                }
                if (((param_1[0x2b7d] == 1) && (2 < param_1[0x2b81])) &&
                    ((fVar5 = (float10)FUN_0042d980(),
                      fVar5 < (float10)60000.0 ||
                          ((0x14 < param_1[0x2b81] || (param_1[0x3c] == 0))))))
                {
                    FUN_00421100(2);
                    return;
                }
                if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 9))
                {
                    FUN_004223d0(3, 10, 0);
                }
                if ((1 < param_1[0x2b7d]) &&
                    (param_1[0x15] = (int)((float)param_1[0x15] - 0.3), (float)param_1[0x15] < 0.0))
                {
                    param_1[0x15] = 0;
                }
                break;
            case 0x14c:
                cVar1 = FUN_004218c0();
                if (cVar1 != '\0')
                {
                    FUN_00421080(0);
                    return;
                }
                if (((char)param_1[0x21] != '\0') && (param_1[0x2b7d] < 2))
                {
                    if (param_1[0x2b7d] == 0)
                    {
                        FUN_00421080(0x14e);
                    }
                    if (param_1[0x2b7d] == 1)
                    {
                        FUN_00421100(2);
                        FUN_0042c8b0(0x28);
                    }
                    param_1[0x10] = 0;
                    param_1[0x16] = 0;
                    return;
                }
                if (param_1[0x2b7d] == 0)
                {
                    FUN_0042db10(0, 0x41a00000);
                }
                if (param_1[0x2b7d] == 1)
                {
                    FUN_0042db10(0, 0x40000000);
                }
                if (param_1[0x2b7d] < 2)
                {
                    param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
                }
                if (param_1[0x2b7d] == 2)
                {
                    param_1[0x15] = (int)((float)param_1[0x15] - 1.0);
                    if ((float)param_1[0x15] < 0.0)
                    {
                        param_1[0x15] = 0;
                    }
                    if ((char)param_1[0x21] == '\0')
                    {
                        FUN_00421080(0x2b);
                        param_1[0x16] = 0x3f000000;
                        return;
                    }
                }
                if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0))
                {
                    FUN_00422900();
                    FUN_00423000();
                    param_1[0x15] = 0x418c0000;
                    param_1[0x10] = 0x41700000;
                    param_1[0x18] = 0;
                    param_1[0x16] = 0x3f800000;
                    FUN_0042c800(0);
                    FUN_0042c840(1);
                }
                break;
            case 0x14d:
                cVar1 = FUN_004218c0();
                if (cVar1 != '\0')
                {
                    FUN_00421080(0);
                    return;
                }
                param_1[0x16]  = 0;
                param_1[0x10]  = 0;
                param_1[0x18]  = 0;
                param_1[0x21d] = 0;
                param_1[0x15]  = 0;
                if (param_1[0x1fd] < 1)
                {
                    param_1[0x20d] = param_1[0x20d] + 0x28;
                }
                else
                {
                    param_1[0x20d] = param_1[0x20d] + 5;
                }
                if (1000 < param_1[0x20d])
                {
                    param_1[0x20d] = 1000;
                }
                break;
            case 0x14e:
                cVar1 = FUN_004218c0();
                if (cVar1 != '\0')
                {
                    FUN_00421080(0);
                    return;
                }
                param_1[0x16]  = 0;
                param_1[0x10]  = 0;
                param_1[0x18]  = 0;
                param_1[0x21d] = 0;
                param_1[0x15]  = 0;
                if (param_1[0x1fd] < 1)
                {
                    param_1[0x20d] = param_1[0x20d] + 0x28;
                }
                else
                {
                    param_1[0x20d] = param_1[0x20d] + 5;
                }
                if (1000 < param_1[0x20d])
                {
                    param_1[0x20d] = 1000;
                }
            }
        }
    }
    else
    {
        switch (iVar4)
        {
        case 0x154:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0);
                return;
            }
            if ((char)param_1[0x21] == '\0')
            {
                FUN_00421080(0x2b);
                param_1[0x16] = 0x3f000000;
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00422900();
                FUN_00423000();
            }
            param_1[0x1a1] = 2;
            if (param_1[0x2b81] == 0)
            {
                param_1[0x18] = 0;
                FUN_0042c800(0);
                FUN_0042c840(1);
            }
            if (param_1[0x2b81] == 0xf)
            {
                FUN_0042c880(0x3d);
                FUN_004223d0(2, 10, 0);
            }
            if (param_1[0x2b81] < 10)
            {
                FUN_0042db10(0, 0x41700000);
            }
            if (param_1[0x2b81] == 0)
            {
                param_1[0x15] = 0x41a00000;
            }
            if (param_1[0x2b81] == 0x11)
            {
                param_1[0x15]  = 0;
                param_1[0x21d] = 0;
            }
            break;
        case 0x155:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0);
                return;
            }
            if ((param_1[0x2b7d] == 2) && ((char)param_1[0x21] == '\0'))
            {
                FUN_00421080(0x2b);
                param_1[0x16] = 0x3f000000;
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00422900();
                param_1[0x18] = 0;
                FUN_0042c800(0);
                FUN_0042c840(1);
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 10))
            {
                FUN_004223d0(3, 10, 0);
                param_1[0x15]  = 0x41c80000;
                param_1[0x10]  = 0x41080000;
                param_1[0x16]  = 0x3f19999a;
                param_1[0x21d] = 0;
            }
            if ((param_1[0x2b7d] == 0) &&
                (fVar5 = (float10)FUN_0042d980(), fVar5 < (float10)250000.0))
            {
                FUN_0042db10(0, 0x41900000);
            }
            if (param_1[0x2b7d] == 1)
            {
                param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
                FUN_0042db10(0, 0x3f800000);
                if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0))
                {
                    param_1[0x10] = 0;
                    FUN_00421100(2);
                    return;
                }
            }
            if ((param_1[0x2b7d] == 2) &&
                (param_1[0x15] = (int)((float)param_1[0x15] - 1.5), (float)param_1[0x15] < 0.0))
            {
                param_1[0x15] = 0;
            }
            break;
        default:
            goto switchD_004ccc9b_caseD_1;
        case 0x15e:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0);
                return;
            }
            if ((char)param_1[0x21] == '\0')
            {
                FUN_00421080(0x2b);
                param_1[0x16] = 0x3f000000;
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_0042db10(0, 0x43340000);
                FUN_00422900();
                FUN_00423000();
                FUN_0042c800(0);
                FUN_0042c840(1);
                param_1[0x18] = 0;
                param_1[0x3d] = 0;
                param_1[0x3e] = 0;
                param_1[0x3a] = 0;
                param_1[0x15] = 0x418c0000;
            }
            if (param_1[0x2b7d] == 1)
            {
                FUN_0042db10(0, 0x40a00000);
                fVar5 = (float10)FUN_0042d980();
                if ((fVar5 < (float10)20000.0) || (0x19 < param_1[0x2b81]))
                {
                    FUN_00421100(2);
                    return;
                }
            }
            if (param_1[0x2b7d] == 2)
            {
                if (param_1[0x2b81] == 6)
                {
                    param_1[0x15] = 0;
                    FUN_004223d0(1, 10, 0);
                }
                uVar3 = FUN_0042c7b0();
                if (((uVar3 & 1) != 0) && (cVar1 = FUN_00422950(0xbe, 1, 0), cVar1 != '\0'))
                {
                    FUN_00421080(0x15f);
                    param_1[0x1eb] = 0x3c;
                }
            }
            break;
        case 0x15f:
            if (param_1[0x1eb] < 0x1c)
            {
                param_1[0x1eb] = 0x1e;
            }
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0);
                return;
            }
            if (((char)param_1[0x21] == '\0') && (1 < param_1[0x2b7d]))
            {
                FUN_00421080(0x2b);
                param_1[0x10] = 0;
                param_1[0x16] = 0x3f000000;
                return;
            }
            if (param_1[0x2b7d] == 0)
            {
                if (param_1[0x2b81] == 1)
                {
                    FUN_004223d0(0x20, 0x14, 0);
                }
                FUN_0042c840(1);
                FUN_0042c800(0);
                FUN_0042db10(0x43340000, 0x40a00000);
                if (param_1[0x2b81] == 0x12)
                {
                    param_1[0x18] = 0x43340000;
                    param_1[0x10] = 0x42960000;
                    param_1[0x15] = 0x41200000;
                }
                if (0x12 < param_1[0x2b81])
                {
                    param_1[0x10] = (int)((float)param_1[0x10] - 2.0);
                }
                if ((param_1[0x2b81] == 0x13) && (4.0 < (float)param_1[0x10]))
                {
                    return;
                }
            }
            if (param_1[0x2b7d] == 1)
            {
                param_1[0x10] = (int)((float)param_1[0x10] - 2.0);
                param_1[0xc]  = (int)((float)param_1[0xc] + 10.0);
                if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0))
                {
                    param_1[0xc] = 0;
                    FUN_0042c8b0(0x85);
                    FUN_00434fd0(3, 0, 0, 0);
                    (**(code **)(*param_1 + 0xc))(
                        300, param_1[5], param_1[6], param_1[7], param_1[0x17], 0);
                    (**(code **)(*param_1 + 0xc))(
                        0x136, param_1[5], param_1[6], param_1[7], param_1[0x17], 0);
                    FUN_00421100(2);
                    FUN_00422bd0(0x79, 0xc4, 5000, 1, 0, 0, 0);
                    param_1[0x2bd8] = 0;
                    param_1[0x10]   = 0;
                    return;
                }
            }
            if ((0 < param_1[0x2b7d]) &&
                (param_1[0x15] = (int)((float)param_1[0x15] + 0.5), 0.0 < (float)param_1[0x15]))
            {
                param_1[0x15] = 0;
            }
            break;
        case 0x168:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0x2b);
                param_1[0xb] = 0;
                return;
            }
            if ((float)param_1[0x16] == 0.0)
            {
                param_1[0x16] = 0x3f000000;
            }
            if ((param_1[0x2b7d] == 2) && (10 < param_1[0x2b81]))
            {
                param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
            }
            if ((((char)param_1[0x21] != '\0') && (param_1[0x2b7d] == 2)) && (10 < param_1[0x2b81]))
            {
                FUN_00421080(0x1d5);
                param_1[0x15] = 0;
                param_1[0x10] = 0;
                param_1[0x16] = 0;
                param_1[0xb]  = 0;
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                param_1[0x18] = 0;
                FUN_0042c800(0);
                FUN_0042c840(1);
                param_1[0x3a] = 0;
                param_1[0x3b] = 0;
                param_1[0x3c] = 0;
                FUN_00422900();
                FUN_00423000();
                if ((float)param_1[0x10] <= 3.0)
                {
                    local_4c = (float)param_1[0x10];
                }
                else
                {
                    local_4c = 3.0;
                }
                if (-3.0 <= local_4c)
                {
                    if ((float)param_1[0x10] <= 3.0)
                    {
                        local_54 = param_1[0x10];
                    }
                    else
                    {
                        local_54 = 0x40400000;
                    }
                    local_50 = local_54;
                }
                else
                {
                    local_50 = -0x3fc00000;
                }
                param_1[0x10] = local_50;
                param_1[0x3c] = 1;
                FUN_0042db10(0, 0x43340000);
                fVar5    = (float10)FUN_00423580(param_1[0x10], param_1[0x15]);
                local_10 = (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                fVar5    = (float10)FUN_0042da80();
                fVar11   = (float)(fVar5 + (float10)10.0);
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    fVar5    = (float10)FUN_0042da80();
                    local_10 = (float)(fVar5 + (float10)10.0);
                }
                if ((fVar11 < local_10) && (local_10 = local_10 - 5.0, local_10 < fVar11))
                {
                    local_10 = fVar11;
                }
                if ((local_10 < fVar11) && (local_10 = local_10 + 5.0, fVar11 < local_10))
                {
                    local_10 = fVar11;
                }
                if (40.0 < local_10)
                {
                    local_10 = 40.0;
                }
                if (local_10 < -35.0)
                {
                    local_10 = -35.0;
                }
                fVar5         = (float10)FUN_0065d050(local_10);
                param_1[0x15] = (int)(float)(fVar5 * (float10)15.5);
                fVar5         = (float10)FUN_0065d010(local_10);
                param_1[0x10] = (int)(float)(fVar5 * (float10)15.5);
                fVar5         = (float10)FUN_00423580(param_1[0x10], param_1[0x15]);
                param_1[0xb] =
                    (int)(float)((fVar5 / (float10)3.1415927) * (float10)180.0 + (float10)20.0);
                param_1[0xb6] = 0x428c0000;
            }
            param_1[0x3b] = param_1[0x3b] + 1;
            if ((param_1[0x2b7d] < 2) && (param_1[0x3c] == 1))
            {
                FUN_0042db10(0, 0x40000000);
            }
            if ((param_1[0x2b7d] == 1) && (7 < param_1[0x2b81]))
            {
                fVar5 = (float10)FUN_0042d980();
                fVar6 = (float10)FUN_0042da30();
                fVar7 = (float10)FUN_0042da30();
                if ((fVar7 * (float10)(float)fVar6 + (float10)(float)fVar5 < (float10)50000.0) ||
                    (0xf < param_1[0x2b81]))
                {
                    FUN_00421100(2);
                    return;
                }
            }
            if (param_1[0x2b7d] == 2)
            {
                uVar3 = FUN_0042c7b0();
                if (((uVar3 & 1) != 0) && (cVar1 = FUN_00422950(0xbe, 1, 0), cVar1 != '\0'))
                {
                    param_1[0x1eb] = 0x1e;
                    FUN_00421080(0x169);
                    return;
                }
                if (0x14 < param_1[0x2b81])
                {
                    if ((0.0 < (float)param_1[0xb]) &&
                        (param_1[0xb] = (int)((float)param_1[0xb] - 5.0),
                         (float)param_1[0xb] < 0.0))
                    {
                        param_1[0xb] = 0;
                    }
                    if (((float)param_1[0xb] < 0.0) &&
                        (param_1[0xb] = (int)((float)param_1[0xb] + 5.0),
                         0.0 < (float)param_1[0xb]))
                    {
                        param_1[0xb] = 0;
                    }
                }
            }
            break;
        case 0x169:
            if (param_1[0x1eb] < 0x1c)
            {
                param_1[0x1eb] = 0x1e;
            }
            FUN_004218c0();
            if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0))
            {
                param_1[0x10] = 0;
                param_1[0x15] = 0;
                FUN_00421080(0x15f);
                return;
            }
            param_1[0x10] = (int)((float)param_1[0x10] - 0.5);
            break;
        case 0x16a:
            param_1[0x1eb] = 0x1e;
            cVar1          = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0x15f);
                return;
            }
            param_1[0x16]  = 0;
            param_1[0x10]  = 0;
            param_1[0x18]  = 0;
            param_1[0x21d] = 0;
            param_1[0x15]  = 0;
            break;
        case 0x172:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0);
                return;
            }
            if ((((char)param_1[0x21] != '\0') && (param_1[0x2b7d] < 2)) &&
                ((float)param_1[0x10] < 0.0))
            {
                FUN_0042c8b0(0x85);
                FUN_00421100(2);
                FUN_004230e0();
                FUN_00435450(6,
                             param_1[5],
                             param_1[6],
                             param_1[7],
                             (float)param_1[0x17] + (float)param_1[0x19],
                             0);
                FUN_0042c8b0(0x28);
                param_1[0x10] = 0;
                param_1[0x16] = 0;
                return;
            }
            if (param_1[0x2b7d] < 2)
            {
                param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
            }
            if (param_1[0x2b7d] == 2)
            {
                param_1[0x15] = (int)((float)param_1[0x15] - 1.0);
                if ((float)param_1[0x15] < 0.0)
                {
                    param_1[0x15] = 0;
                }
                if ((char)param_1[0x21] == '\0')
                {
                    FUN_00421080(0x2b);
                    param_1[0x16] = 0x3f000000;
                    return;
                }
                if ((param_1[0x2b81] == 0x1c) && (param_1[0x3e] < 0x1e))
                {
                    param_1[0x3e] = param_1[0x3e] + 1;
                    return;
                }
            }
            if ((param_1[0x2b7d] == 0) && (FUN_0042db10(0, 0x3f800000), param_1[0x2b81] == 5))
            {
                if ((0.0 <= (float)param_1[0x10]) || (iVar4 = FUN_0066b668(), iVar4 % 0x168 != 0))
                {
                    param_1[0xb6] = 0x428c0000;
                    param_1[0xb]  = (int)((float)param_1[0xb] - 20.0);
                    return;
                }
                param_1[0xb] = 0;
            }
            if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0))
            {
                FUN_0042c8b0(0x84);
                FUN_00422490(0x27, 0, 0x14, 0);
                FUN_00422900();
                FUN_00423000();
                param_1[0x15] = 0x40a00000;
                param_1[0x3e] = 0;
                param_1[0x10] = 0x42480000;
                param_1[0x18] = 0;
                param_1[0x16] = 0x3f4ccccd;
                FUN_0042c800(0);
                FUN_0042c840(1);
            }
            break;
        case 0x186:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                if ((char)param_1[0x21] == '\0')
                {
                    param_1[0x16] = 0x3f000000;
                    FUN_00421080(0x2b);
                    return;
                }
                FUN_00421080(0);
                return;
            }
            if ((char)param_1[0x21] == '\0')
            {
                param_1[0x16] = 0x3f000000;
                FUN_00421080(0x2b);
                return;
            }
            if ((param_1[0x2b7d] == 1) &&
                (param_1[0x20d] = param_1[0x20d] + -10, param_1[0x20d] < 0))
            {
                param_1[0x20d] = 0;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_0042c8b0(4);
                param_1[0x18] = 0;
                param_1[0x15] = 0;
                FUN_0042c800(0);
            }
            if (param_1[0x2b7d] == 0)
            {
                FUN_0042db10(0, 0x41a00000);
            }
            if ((param_1[0x2b7d] == 1) &&
                (((param_1[0x20d] == 0 || (param_1[0xa0] == 0)) || (param_1[0xa1] == 0))))
            {
                FUN_00421100(2);
                return;
            }
            uVar3 = FUN_0042c7b0();
            if (((uVar3 & 2) != 0) && (0 < param_1[0x20d]))
            {
                (**(code **)(*param_1 + 0xc))(0x46,
                                              param_1[5],
                                              (float)param_1[6] + 100.0,
                                              param_1[7],
                                              (float)param_1[0x17] + (float)param_1[0x19],
                                              0);
                FUN_00421080(0x187);
                FUN_0042c8b0(0x33);
                FUN_0042c800(0);
                return;
            }
            if (param_1[0x2b7d] == 2)
            {
                param_1[0x21d] = 0;
                param_1[0x15]  = (int)((float)param_1[0x15] - 1.0);
                if ((float)param_1[0x15] < 0.0)
                {
                    param_1[0x15] = 0;
                }
            }
            break;
        case 0x187:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_004223d0(0xc, 0x14, 0);
                if ((char)param_1[0x21] == '\0')
                {
                    param_1[0x16] = 0x3f000000;
                    FUN_00421080(0x2b);
                    return;
                }
                FUN_00421080(0);
                return;
            }
            if ((char)param_1[0x21] == '\0')
            {
                param_1[0x16] = 0x3f000000;
                FUN_00421080(0x67);
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                param_1[0x18] = 0;
                param_1[0x15] = -0x3e900000;
                param_1[0x3a] = 0;
            }
            if ((param_1[0x2b7d] < 2) && (uVar3 = FUN_0042c7b0(), (uVar3 & 2) != 0))
            {
                FUN_00421080(0x187);
                (**(code **)(*param_1 + 0xc))(0x46,
                                              param_1[5],
                                              (float)param_1[6] + 100.0,
                                              param_1[7],
                                              (float)param_1[0x17] + (float)param_1[0x19],
                                              0);
                FUN_0042c880(0x33);
                FUN_0042c800(0);
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x3a] = param_1[0x3a] + 1, 0x14 < param_1[0x3a]))
            {
                FUN_00421100(1);
                return;
            }
            if (param_1[0x2b7d] == 2)
            {
                param_1[0x1eb] = 0x2d;
            }
            if (param_1[0x2b7d] < 3)
            {
                param_1[0x21d] = 0;
                param_1[0x15]  = (int)((float)param_1[0x15] + 1.0);
                if (0.0 < (float)param_1[0x15])
                {
                    param_1[0x15] = 0;
                }
            }
            break;
        case 0x188:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                if ((char)param_1[0x21] == '\0')
                {
                    param_1[0x16] = 0x3f000000;
                    FUN_00421080(0x2b);
                    return;
                }
                FUN_00421080(0);
                return;
            }
            if ((char)param_1[0x21] == '\0')
            {
                param_1[0x16] = 0x3f000000;
                FUN_00421080(0x2b);
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                param_1[0x18] = 0;
                param_1[0x15] = -0x3e900000;
                param_1[0x3a] = 0;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x3a] = param_1[0x3a] + 1, 0x14 < param_1[0x3a]))
            {
                FUN_00421100(1);
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_004223d0(0xd, 10, 0);
            }
            if (param_1[0x2b7d] < 2)
            {
                param_1[0x21d] = 0;
                param_1[0x15]  = (int)((float)param_1[0x15] + 1.0);
                if (0.0 < (float)param_1[0x15])
                {
                    param_1[0x15] = 0;
                }
            }
            break;
        case 0x189:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                if ((char)param_1[0x21] == '\0')
                {
                    param_1[0x16] = 0x3f000000;
                    FUN_00421080(0x2b);
                    return;
                }
                FUN_00421080(0);
                return;
            }
            if ((char)param_1[0x21] == '\0')
            {
                param_1[0x16] = 0x3f000000;
                FUN_00421080(0x2b);
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                param_1[0x18] = 0;
                param_1[0x15] = -0x3e900000;
                param_1[0x3a] = 0;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x3a] = param_1[0x3a] + 1, 10 < param_1[0x3a]))
            {
                FUN_00421100(1);
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_004223d0(8, 10, 0);
            }
            if (param_1[0x2b7d] < 2)
            {
                param_1[0x21d] = 0;
                param_1[0x15]  = (int)((float)param_1[0x15] + 1.0);
                if (0.0 < (float)param_1[0x15])
                {
                    param_1[0x15] = 0;
                }
            }
            break;
        case 0x18a:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                if ((char)param_1[0x21] == '\0')
                {
                    param_1[0x16] = 0x3f000000;
                    FUN_00421080(0x2b);
                    return;
                }
                FUN_00421080(0);
                param_1[0x10] = 0;
                return;
            }
            if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0))
            {
                param_1[0x16] = 0;
                param_1[0x10] = 0;
                FUN_00421080(0x2c);
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                param_1[0x18] = 0;
                param_1[0x15] = -0x3e900000;
                param_1[0x10] = 0x40a00000;
                param_1[0x16] = 0x3f000000;
                param_1[0x3a] = 0;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x3a] = param_1[0x3a] + 1, 10 < param_1[0x3a]))
            {
                FUN_00421100(1);
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_004223d0(8, 10, 0);
            }
            if (param_1[0x2b7d] < 2)
            {
                param_1[0x21d] = 0;
                param_1[0x15]  = (int)((float)param_1[0x15] + 1.0);
                if (0.0 < (float)param_1[0x15])
                {
                    param_1[0x15] = 0;
                }
            }
            param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
            break;
        case 400:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0);
                return;
            }
            if ((char)param_1[0x21] == '\0')
            {
                FUN_00421080(0x2b);
                param_1[0x16] = 0x3f000000;
                return;
            }
            if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0))
            {
                FUN_00434fd0(0, 0, 0, 0);
                param_1[0x18] = 0;
                FUN_0042c800(0);
                FUN_0042c840(1);
                param_1[0x3a] = 0;
                param_1[0x3b] = 0;
                param_1[0x3c] = 1;
                param_1[0x3d] = 0;
                FUN_0042db10(0, 0x43340000);
                param_1[0x15] = 0x41600000;
                if ((*(char *)((int)param_1 + 0x845) != '\0') && (param_1[0x212] != 0))
                {
                    param_1[0x15] = 0x41a00000;
                    uVar13        = 0;
                    fVar10        = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar5         = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar10, 0);
                    fVar11 = (float)(fVar5 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar9  = (float)param_1[6] + 80.0;
                    fVar5  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar9, fVar11);
                    FUN_00435450(2,
                                 (float)(fVar5 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar9,
                                 fVar11,
                                 fVar10,
                                 uVar13);
                }
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00422900();
                FUN_00423000();
            }
            sVar2 = FUN_0042c7b0();
            if ((sVar2 != 0) && (param_1[0x3b] == 0))
            {
                param_1[0x3b] = 1;
            }
            if (param_1[0x2b7d] == 0)
            {
                FUN_0042db10(0, 0x41700000);
            }
            if (((param_1[0x2b7d] == 1) && (FUN_0042db10(0, 0x40a00000), 2 < param_1[0x2b81])) &&
                ((fVar5 = (float10)FUN_0042d980(),
                  fVar5 < (float10)50000.0 || (0x14 < param_1[0x2b81]))))
            {
                FUN_00421100(2);
                return;
            }
            if (param_1[0x2b7d] == 2)
            {
                param_1[0x15] = (int)((float)param_1[0x15] - 1.0);
                if ((float)param_1[0x15] < 0.0)
                {
                    param_1[0x15] = 0;
                }
                if (param_1[0x2b81] < 7)
                {
                    FUN_0042db10(0, 0x40a00000);
                }
                uVar3 = FUN_0042c7b0();
                if ((uVar3 & 1) != 0)
                {
                    FUN_0042c840(0);
                    if (-1 < param_1[0xc1])
                    {
                        param_1[0x3d] = 1;
                    }
                    cVar1 = FUN_00422950(0xbb, 1, 0);
                    if (cVar1 != '\0')
                    {
                        param_1[0x2bd8] = 1;
                        param_1[0x2bd9] = 0xf0;
                    }
                }
                if (param_1[0x2b81] == 10)
                {
                    param_1[0x15] = 0;
                }
            }
            break;
        case 0x191:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0);
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00423000();
                FUN_00422900();
                param_1[0x3a] = 0;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] < 0x14))
            {
                FUN_0042db10(0, 0x41700000);
            }
            if (param_1[0x1eb] < 0x1c)
            {
                param_1[0x1eb] = 0x1e;
            }
            param_1[0x15] = 0;
            param_1[0x10] = 0;
            if (param_1[0x2b81] == 0x11)
            {
                FUN_0042c8b0(0x41);
                if (param_1[0x1b7] == 1)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1b, 10, 0);
                }
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0x14)
                {
                    param_1[0x3c] = -0x14;
                }
                if (0x14 < param_1[0x3c])
                {
                    param_1[0x3c] = 0x14;
                }
                if (param_1[0x3d] == 1)
                {
                    fVar5  = (float10)FUN_0065d010((float)param_1[0x3c]);
                    fVar11 = (float)(fVar5 * (float10)4000.0);
                    fVar5  = (float10)FUN_0065d050((float)param_1[0x3c], fVar11);
                    FUN_00422bd0(
                        0x85, 0xc6, 0x271, 1, 0x43340000, (float)(fVar5 * (float10)4000.0), fVar11);
                }
                else
                {
                    fVar5  = (float10)FUN_0065d010((float)param_1[0x3c]);
                    fVar11 = (float)(fVar5 * (float10)4000.0);
                    fVar5  = (float10)FUN_0065d050((float)param_1[0x3c], fVar11);
                    FUN_00422bd0(
                        0x85, 0xc6, 0x9c4, 1, 0x43340000, (float)(fVar5 * (float10)4000.0), fVar11);
                }
                param_1[0x2bd8] = 0;
            }
            break;
        case 0x192:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0x2b);
                param_1[0xb] = 0;
                return;
            }
            if ((float)param_1[0x16] == 0.0)
            {
                param_1[0x16] = 0x3f000000;
            }
            if ((param_1[0x2b7d] == 2) && (10 < param_1[0x2b81]))
            {
                param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
            }
            if ((((char)param_1[0x21] != '\0') && (param_1[0x2b7d] == 2)) && (10 < param_1[0x2b81]))
            {
                FUN_00421080(0x193);
                param_1[0x15] = 0;
                param_1[0x10] = 0;
                param_1[0xb]  = 0;
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00434fd0(0, 0, 0, 0);
                param_1[0x18] = 0;
                FUN_0042c800(0);
                FUN_0042c840(1);
                param_1[0x3a] = 0;
                param_1[0x3b] = 0;
                param_1[0x3c] = 0;
                param_1[0x3d] = 0;
                FUN_00422900();
                FUN_00423000();
                if ((float)param_1[0x10] <= 3.0)
                {
                    local_60 = (float)param_1[0x10];
                }
                else
                {
                    local_60 = 3.0;
                }
                if (-3.0 <= local_60)
                {
                    if ((float)param_1[0x10] <= 3.0)
                    {
                        local_68 = param_1[0x10];
                    }
                    else
                    {
                        local_68 = 0x40400000;
                    }
                    local_64 = local_68;
                }
                else
                {
                    local_64 = -0x3fc00000;
                }
                param_1[0x10] = local_64;
                param_1[0x15] = 0x41280000;
                if ((*(char *)((int)param_1 + 0x845) != '\0') && (param_1[0x212] != 0))
                {
                    param_1[0x3c] = 0x78;
                }
                if ((param_1[0x2b81] == 0) &&
                    (fVar5 = (float10)FUN_0042d980(), fVar5 < (float10)640000.0))
                {
                    if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                    {
                        param_1[0x3c] = 0x78;
                    }
                    else
                    {
                        param_1[0x3c] = 0xa5;
                    }
                    FUN_0042db10(0, 0x43340000);
                }
                fVar5 = (float10)FUN_00423580(param_1[0x10], param_1[0x15]);
                param_1[0xb] =
                    (int)(float)((fVar5 / (float10)3.1415927) * (float10)180.0 + (float10)20.0);
                param_1[0xb6] = 0x428c0000;
            }
            param_1[0x3b] = param_1[0x3b] + 1;
            if ((param_1[0x2b7d] < 2) && (0 < param_1[0x3c]))
            {
                fVar5    = (float10)FUN_00423580(param_1[0x10], param_1[0x15]);
                local_18 = (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                fVar5    = (float10)FUN_0042da80();
                fVar11   = (float)(fVar5 + (float10)10.0);
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    fVar5    = (float10)FUN_0042da80();
                    local_18 = (float)(fVar5 + (float10)10.0);
                }
                if ((((*(char *)((int)param_1 + 0x845) != '\0') && (param_1[0x212] != 0)) &&
                     (param_1[0x2b7d] == 0)) &&
                    (param_1[0x2b81] == 0))
                {
                    param_1[0x3c] = 0xe6;
                    fVar9         = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar12        = fVar11;
                    fVar5         = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar9, fVar11);
                    fVar10 = (float)(fVar5 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar8  = (float)param_1[6] + 80.0;
                    fVar5  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar8, fVar10);
                    FUN_00435450(2,
                                 (float)(fVar5 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar8,
                                 fVar10,
                                 fVar9,
                                 fVar12);
                }
                if ((fVar11 < local_18) && (local_18 = local_18 - 5.0, local_18 < fVar11))
                {
                    local_18 = fVar11;
                }
                if ((local_18 < fVar11) && (local_18 = local_18 + 5.0, fVar11 < local_18))
                {
                    local_18 = fVar11;
                }
                if (40.0 < local_18)
                {
                    local_18 = 40.0;
                }
                if (local_18 < -35.0)
                {
                    local_18 = -35.0;
                }
                iVar4         = param_1[0x3c];
                fVar5         = (float10)FUN_0065d050(local_18);
                param_1[0x15] = (int)(float)(fVar5 * (float10)((float)iVar4 * 0.1));
                iVar4         = param_1[0x3c];
                fVar5         = (float10)FUN_0065d010(local_18);
                param_1[0x10] = (int)(float)(fVar5 * (float10)((float)iVar4 * 0.1));
                fVar5         = (float10)FUN_00423580(param_1[0x10], param_1[0x15]);
                param_1[0xb] =
                    (int)(float)((fVar5 / (float10)3.1415927) * (float10)180.0 + (float10)20.0);
                param_1[0xb6] = 0x428c0000;
                FUN_0042db10(0, 0x40c00000);
            }
            if ((param_1[0x2b7d] == 1) && (FUN_0042db10(0, 0x40000000), 7 < param_1[0x2b81]))
            {
                fVar5 = (float10)FUN_0042d980();
                fVar6 = (float10)FUN_0042da30();
                fVar7 = (float10)FUN_0042da30();
                if ((fVar7 * (float10)(float)fVar6 + (float10)(float)fVar5 < (float10)50000.0) ||
                    ((0x19 < param_1[0x2b81] || (param_1[0x3c] == 0))))
                {
                    FUN_00421100(2);
                    return;
                }
            }
            if (param_1[0x2b7d] == 2)
            {
                uVar3 = FUN_0042c7b0();
                if ((uVar3 & 1) != 0)
                {
                    if (-1 < param_1[0xc1])
                    {
                        param_1[0x3d] = 1;
                    }
                    cVar1 = FUN_00422950(0xbb, 1, 0);
                    if (cVar1 != '\0')
                    {
                        FUN_0042c840(0);
                        param_1[0x2bd8] = 1;
                        param_1[0x2bd9] = 0xf0;
                    }
                }
                if (0x19 < param_1[0x2b81])
                {
                    if ((0.0 < (float)param_1[0xb]) &&
                        (param_1[0xb] = (int)((float)param_1[0xb] - 5.0),
                         (float)param_1[0xb] < 0.0))
                    {
                        param_1[0xb] = 0;
                    }
                    if (((float)param_1[0xb] < 0.0) &&
                        (param_1[0xb] = (int)((float)param_1[0xb] + 5.0),
                         0.0 < (float)param_1[0xb]))
                    {
                        param_1[0xb] = 0;
                    }
                }
            }
            break;
        case 0x193:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0);
                return;
            }
            param_1[0x16]  = 0;
            param_1[0x10]  = 0;
            param_1[0x18]  = 0;
            param_1[0x21d] = 0;
            param_1[0x15]  = 0;
            if (param_1[0x1fd] < 1)
            {
                param_1[0x20d] = param_1[0x20d] + 0x28;
            }
            else
            {
                param_1[0x20d] = param_1[0x20d] + 5;
            }
            if (1000 < param_1[0x20d])
            {
                param_1[0x20d] = 1000;
            }
            break;
        case 0x194:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0x2b);
                return;
            }
            if (param_1[0x1eb] < 0x1c)
            {
                param_1[0x1eb] = 0x1e;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00422900();
                param_1[0x3a] = 0;
                param_1[0x15] = 0;
                param_1[0x10] = 0;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] < 0x14))
            {
                FUN_0042db10(0, 0x41700000);
            }
            param_1[0x15] = 0;
            param_1[0x10] = 0;
            if (param_1[0x2b81] == 0x11)
            {
                FUN_0042c8b0(0x41);
                if (param_1[0x1b7] == 1)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1b, 10, 0);
                }
                param_1[0x2bd8] = 0;
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0x28)
                {
                    param_1[0x3c] = -0x28;
                }
                if (10 < param_1[0x3c])
                {
                    param_1[0x3c] = 10;
                }
                if (param_1[0x3d] == 1)
                {
                    fVar5  = (float10)FUN_0065d010((float)param_1[0x3c]);
                    fVar11 = (float)(fVar5 * (float10)4000.0);
                    fVar5  = (float10)FUN_0065d050((float)param_1[0x3c], fVar11);
                    FUN_00422bd0(
                        0x85, 0xc6, 0x271, 1, 0x43340000, (float)(fVar5 * (float10)4000.0), fVar11);
                }
                else
                {
                    fVar5  = (float10)FUN_0065d010((float)param_1[0x3c]);
                    fVar11 = (float)(fVar5 * (float10)4000.0);
                    fVar5  = (float10)FUN_0065d050((float)param_1[0x3c], fVar11);
                    FUN_00422bd0(
                        0x85, 0xc6, 0x9c4, 1, 0x43340000, (float)(fVar5 * (float10)4000.0), fVar11);
                }
            }
            break;
        case 0x1c2:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0);
                return;
            }
            if ((char)param_1[0x21] == '\0')
            {
                FUN_00421080(0x2b);
                param_1[0x16] = 0x3f000000;
                return;
            }
            if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0))
            {
                FUN_00434fd0(1, 0, 0, 0);
                param_1[0x18] = 0;
                FUN_0042c800(0);
                FUN_0042c840(1);
                param_1[0x3a] = 0;
                param_1[0x3b] = 0;
                param_1[0x3c] = 1;
                FUN_0042db10(0, 0x43340000);
                param_1[0x15] = 0x41a00000;
                if ((*(char *)((int)param_1 + 0x845) != '\0') && (param_1[0x212] != 0))
                {
                    param_1[0x15] = 0x41f00000;
                    uVar13        = 0;
                    fVar10        = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar5         = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar10, 0);
                    fVar11 = (float)(fVar5 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar9  = (float)param_1[6] + 80.0;
                    fVar5  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar9, fVar11);
                    FUN_00435450(2,
                                 (float)(fVar5 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar9,
                                 fVar11,
                                 fVar10,
                                 uVar13);
                }
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00422900();
                FUN_00423000();
            }
            sVar2 = FUN_0042c7b0();
            if ((sVar2 != 0) && (param_1[0x3b] == 0))
            {
                param_1[0x3b] = 1;
            }
            if (param_1[0x2b7d] == 0)
            {
                FUN_0042db10(0, 0x41700000);
            }
            if (((param_1[0x2b7d] == 1) && (FUN_0042db10(0, 0x40a00000), 2 < param_1[0x2b81])) &&
                ((fVar5 = (float10)FUN_0042d980(),
                  fVar5 < (float10)60000.0 || (0x1e < param_1[0x2b81]))))
            {
                FUN_00421100(2);
                return;
            }
            if (param_1[0x2b7d] == 2)
            {
                if (param_1[0x2b81] < 10)
                {
                    FUN_0042db10(0, 0x40a00000);
                }
                uVar3 = FUN_0042c7b0();
                if (((uVar3 & 1) != 0) && (cVar1 = FUN_00422950(0xbe, 0, 0), cVar1 != '\0'))
                {
                    param_1[0x1eb] = 0x1e;
                    FUN_00421080(0x1c3);
                    return;
                }
                if (param_1[0x2b81] == 10)
                {
                    param_1[0x15] = 0;
                }
            }
            break;
        case 0x1c3:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0);
                if ((char)param_1[0x21] != '\0')
                {
                    return;
                }
                FUN_00421080(0x2b);
                param_1[0x16] = 0x3f000000;
                return;
            }
            if ((char)param_1[0x21] == '\0')
            {
                param_1[0x10] = (int)((float)param_1[0x10] - 0.1);
            }
            if ((char)param_1[0x21] != '\0')
            {
                param_1[0x10] = 0;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                param_1[0x15] = 0;
                param_1[0x10] = 0;
                FUN_00422900();
                param_1[0x3a] = 0;
                param_1[0x3b] = 0;
                param_1[0x3e] = 0;
                FUN_0042c840(1);
                FUN_0042c800(0);
                if (param_1[0x2b81] == 0)
                {
                    FUN_0042c8b0(0x84);
                }
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 6))
            {
                FUN_00422950(0xbd, 0, 0);
            }
            if (param_1[0x1eb] < 0x1c)
            {
                param_1[0x1eb] = 0x1e;
            }
            if (param_1[0x2b7d] == 1)
            {
                if (param_1[0x2b81] == 0x4c)
                {
                    FUN_00421100(2);
                    return;
                }
                param_1[0x3b] = param_1[0x3b] + 1;
                param_1[0xc]  = (int)((float)param_1[0x3b] * 0.15 + (float)param_1[0xc]);
                if ((param_1[0x9f] == 0) && (param_1[0x9e] == 0))
                {
                    param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
                    if ((float)param_1[0x15] < 0.0)
                    {
                        param_1[0x15] = 0;
                    }
                }
                else
                {
                    param_1[0x15] = (int)((float)param_1[0x15] + 0.5);
                    if (10.0 < (float)param_1[0x15])
                    {
                        param_1[0x15] = 0x41200000;
                    }
                }
                if (param_1[0x9f] < 0)
                {
                    if ((0 < param_1[0x9e]) && (param_1[0x3a] != 1))
                    {
                        param_1[0x3a]  = 1;
                        param_1[0x21d] = 0x40a00000;
                    }
                    if ((param_1[0x9e] == 0) && (param_1[0x3a] != 0))
                    {
                        param_1[0x3a]  = 0;
                        param_1[0x21d] = 0x40a00000;
                    }
                    if ((param_1[0x9e] < 0) && (param_1[0x3a] != 2))
                    {
                        param_1[0x3a]  = 2;
                        param_1[0x21d] = 0x40a00000;
                    }
                }
                if (param_1[0x9f] == 0)
                {
                    if ((0 < param_1[0x9e]) && (param_1[0x3a] != 3))
                    {
                        param_1[0x3a]  = 3;
                        param_1[0x21d] = 0x40a00000;
                    }
                    if ((param_1[0x9e] == 0) && (param_1[0x3a] != 10))
                    {
                        param_1[0x3a]  = 10;
                        param_1[0x21d] = 0x40a00000;
                    }
                    if ((param_1[0x9e] < 0) && (param_1[0x3a] != 4))
                    {
                        param_1[0x3a]  = 4;
                        param_1[0x21d] = 0x40a00000;
                    }
                }
                if (0 < param_1[0x9f])
                {
                    if ((0 < param_1[0x9e]) && (param_1[0x3a] != 5))
                    {
                        param_1[0x3a]  = 5;
                        param_1[0x21d] = 0x40a00000;
                    }
                    if ((param_1[0x9e] == 0) && (param_1[0x3a] != 6))
                    {
                        param_1[0x3a]  = 6;
                        param_1[0x21d] = 0x40a00000;
                    }
                    if ((param_1[0x9e] < 0) && (param_1[0x3a] != 7))
                    {
                        param_1[0x3a]  = 7;
                        param_1[0x21d] = 0x40a00000;
                    }
                }
                param_1[0x18] = 0;
                FUN_00421780();
            }
            if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 0))
            {
                FUN_0042db10(0, 0x43340000);
                param_1[0x15] = 0;
            }
            if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 3))
            {
                param_1[0xc] = 0;
                FUN_00422490(0x21, 0, 0x14, 0);
                FUN_00422bd0(0x85, 0xc6, 0xdac, 1, 0x43340000, 0x455ac000, 0x43fa0000);
                param_1[0x2bd8] = 0;
            }
            break;
        case 0x1cc:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0x2b);
                param_1[0xb] = 0;
                return;
            }
            if ((float)param_1[0x16] == 0.0)
            {
                param_1[0x16] = 0x3f000000;
            }
            if ((param_1[0x2b7d] == 2) && (10 < param_1[0x2b81]))
            {
                param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
            }
            if ((((char)param_1[0x21] != '\0') && (param_1[0x2b7d] == 2)) && (10 < param_1[0x2b81]))
            {
                FUN_00421080(0x1d5);
                param_1[0x15] = 0;
                param_1[0x10] = 0;
                param_1[0xb]  = 0;
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00434fd0(1, 0, 0, 0);
                param_1[0x18] = 0;
                FUN_0042c800(0);
                FUN_0042c840(1);
                param_1[0x3a] = 0;
                param_1[0x3b] = 0;
                param_1[0x3c] = 0;
                FUN_00422900();
                FUN_00423000();
                if ((float)param_1[0x10] <= 3.0)
                {
                    local_7c = (float)param_1[0x10];
                }
                else
                {
                    local_7c = 3.0;
                }
                if (-3.0 <= local_7c)
                {
                    if ((float)param_1[0x10] <= 3.0)
                    {
                        local_84 = param_1[0x10];
                    }
                    else
                    {
                        local_84 = 0x40400000;
                    }
                    local_80 = local_84;
                }
                else
                {
                    local_80 = -0x3fc00000;
                }
                param_1[0x10] = local_80;
                param_1[0x3c] = 1;
                FUN_0042db10(0, 0x43340000);
                fVar5    = (float10)FUN_00423580(param_1[0x10], param_1[0x15]);
                local_20 = (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                fVar5    = (float10)FUN_0042da80();
                fVar11   = (float)(fVar5 + (float10)10.0);
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    fVar5    = (float10)FUN_0042da80();
                    local_20 = (float)(fVar5 + (float10)10.0);
                }
                if ((fVar11 < local_20) && (local_20 = local_20 - 5.0, local_20 < fVar11))
                {
                    local_20 = fVar11;
                }
                if ((local_20 < fVar11) && (local_20 = local_20 + 5.0, fVar11 < local_20))
                {
                    local_20 = fVar11;
                }
                if (20.0 < local_20)
                {
                    local_20 = 20.0;
                }
                if (local_20 < -40.0)
                {
                    local_20 = -40.0;
                }
                fVar5         = (float10)FUN_0065d050(local_20);
                param_1[0x15] = (int)(float)(fVar5 * (float10)15.5);
                fVar5         = (float10)FUN_0065d010(local_20);
                param_1[0x10] = (int)(float)(fVar5 * (float10)15.5);
                fVar5         = (float10)FUN_00423580(param_1[0x10], param_1[0x15]);
                param_1[0xb] =
                    (int)(float)((fVar5 / (float10)3.1415927) * (float10)180.0 + (float10)20.0);
                param_1[0xb6] = 0x428c0000;
                if ((*(char *)((int)param_1 + 0x845) != '\0') && (param_1[0x212] != 0))
                {
                    fVar5         = (float10)FUN_0065d050(local_20);
                    param_1[0x15] = (int)(float)(fVar5 * (float10)22.0);
                    fVar5         = (float10)FUN_0065d010(local_20);
                    param_1[0x10] = (int)(float)(fVar5 * (float10)22.0);
                    iVar4         = param_1[0xb];
                    fVar10        = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar5         = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar10, iVar4);
                    fVar11 = (float)(fVar5 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar9  = (float)param_1[6] + 80.0;
                    fVar5  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar9, fVar11);
                    FUN_00435450(2,
                                 (float)(fVar5 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar9,
                                 fVar11,
                                 fVar10,
                                 iVar4);
                }
            }
            param_1[0x3b] = param_1[0x3b] + 1;
            if ((param_1[0x2b7d] < 2) && (param_1[0x3c] == 1))
            {
                FUN_0042db10(0, 0x40000000);
            }
            if ((param_1[0x2b7d] == 1) && (7 < param_1[0x2b81]))
            {
                fVar5 = (float10)FUN_0042d980();
                fVar6 = (float10)FUN_0042da30();
                fVar7 = (float10)FUN_0042da30();
                if ((fVar7 * (float10)(float)fVar6 + (float10)(float)fVar5 < (float10)50000.0) ||
                    (0xf < param_1[0x2b81]))
                {
                    FUN_00421100(2);
                    return;
                }
            }
            if (param_1[0x2b7d] == 2)
            {
                uVar3 = FUN_0042c7b0();
                if (((uVar3 & 1) != 0) && (cVar1 = FUN_00422950(0xbe, 0, 0), cVar1 != '\0'))
                {
                    param_1[0x1eb] = 0x1e;
                    FUN_00421080(0x1cd);
                    return;
                }
                if (0x14 < param_1[0x2b81])
                {
                    if ((0.0 < (float)param_1[0xb]) &&
                        (param_1[0xb] = (int)((float)param_1[0xb] - 5.0),
                         (float)param_1[0xb] < 0.0))
                    {
                        param_1[0xb] = 0;
                    }
                    if (((float)param_1[0xb] < 0.0) &&
                        (param_1[0xb] = (int)((float)param_1[0xb] + 5.0),
                         0.0 < (float)param_1[0xb]))
                    {
                        param_1[0xb] = 0;
                    }
                }
            }
            break;
        case 0x1cd:
            if (param_1[0x1eb] < 0x1c)
            {
                param_1[0x1eb] = 0x1e;
            }
            FUN_004218c0();
            if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0))
            {
                param_1[0x10] = 0;
                param_1[0x15] = 0;
                FUN_00421080(0x1c3);
                return;
            }
            param_1[0x10] = (int)((float)param_1[0x10] - 0.5);
            break;
        case 0x1ce:
            param_1[0x1eb] = 0x1e;
            cVar1          = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0x1c3);
                return;
            }
            param_1[0x16]  = 0;
            param_1[0x10]  = 0;
            param_1[0x18]  = 0;
            param_1[0x21d] = 0;
            param_1[0x15]  = 0;
            break;
        case 0x1d5:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0);
                return;
            }
            param_1[0x16]  = 0;
            param_1[0x10]  = 0;
            param_1[0x18]  = 0;
            param_1[0x21d] = 0;
            param_1[0x15]  = 0;
            if (param_1[0x1fd] < 1)
            {
                param_1[0x20d] = param_1[0x20d] + 0x28;
            }
            else
            {
                param_1[0x20d] = param_1[0x20d] + 5;
            }
            if (1000 < param_1[0x20d])
            {
                param_1[0x20d] = 1000;
            }
        }
    }
    param_1[0x2b81] = param_1[0x2b81] + 1;
    param_1[0x2b82] = param_1[0x2b82] + 1;
    FUN_004212f0();
    if ((*(int *)param_1[0x2b79] < param_1[0x2b81]) && (*(int *)(param_1[0x2b79] + 0x20) == 0))
    {
        FUN_00421100(param_1[0x2b7d] + 1);
    }
    return;
}
