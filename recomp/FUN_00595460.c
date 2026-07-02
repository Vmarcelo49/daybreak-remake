// ============================================
// Address:  0x00595460
// Original: FUN_00595460
// Status:   unreviewed
// ============================================

void __fastcall FUN_00595460(int *param_1)

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
    undefined4 uVar12;
    int local_34;
    int local_30;
    float local_2c;
    float local_8;

    if (param_1[0x28] != 0)
    {
        return;
    }
    FUN_00434a70(0, 0);
    FUN_00434a70(1, 1);
    FUN_00434bd0();
    iVar4 = param_1[0x2b7b];
    if (iVar4 < 0x156)
    {
        if (iVar4 == 0x155)
        {
            FUN_00434a70(0, 2);
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
            if (param_1[0x2b81] < 0x1e)
            {
                param_1[0x1a1] = 2;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00422900();
                FUN_00423000();
                param_1[0x18] = 0;
                FUN_0042c800(0);
                FUN_0042c840(1);
            }
            uVar3 = FUN_0042c7b0();
            if ((uVar3 & 2) != 0)
            {
                FUN_00421080(0x188);
                FUN_0042c800(0);
                return;
            }
            if (param_1[0x2b81] == 0x10)
            {
                FUN_0042c880(0x3d);
            }
            if ((param_1[0x2b81] < 0x10) && (param_1[0x3b] == 1))
            {
                FUN_0042db10(0, 0x41200000);
            }
            if (param_1[0x2b81] == 4)
            {
                param_1[0x15] = 0;
            }
            if (param_1[0x2b81] == 0xc)
            {
                param_1[0x15] = 0;
            }
            if ((param_1[0x2b81] < 0x11) || (0x13 < param_1[0x2b81]))
            {
                FUN_00434bd0();
            }
            else
            {
                FUN_00434b90(0);
            }
        }
        else if (iVar4 < 0x12d)
        {
            if (iVar4 == 300)
            {
                FUN_00434a70(0, 2);
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
                    param_1[0x15] = 0x41a00000;
                    fVar5         = (float10)FUN_0042d980();
                    if (fVar5 < (float10)640000.0)
                    {
                        param_1[0x3c] = 1;
                        param_1[0x15] = 0x41d80000;
                    }
                    FUN_0042db10(0, 0x43340000);
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
                    FUN_0042db10(0, 0x41a00000);
                }
                if (param_1[0x2b7d] == 1)
                {
                    FUN_0042db10(0, 0x40e00000);
                    fVar5 = (float10)FUN_0042d980();
                    if ((fVar5 < (float10)60000.0) || (param_1[0x3c] == 0))
                    {
                        FUN_00421100(2);
                        return;
                    }
                }
                if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 2))
                {
                    FUN_0042c880(0x3c);
                    fVar5 = (float10)FUN_0042d980();
                    if (((float10)60000.0 <= fVar5) ||
                        ((fVar5 = (float10)FUN_0042df90(param_1[0x19]),
                          (float10)30.0 <= fVar5 || (*(char *)((int)param_1 + 0xaec3) != '\x01'))))
                    {
                        fVar5 = (float10)FUN_0042d980();
                        if (((float10)60000.0 <= fVar5) ||
                            ((fVar5 = (float10)FUN_0042df90(param_1[0x19]),
                              (float10)30.0 <= fVar5 ||
                                  (*(char *)((int)param_1 + 0xaebe) != '\x01'))))
                        {
                            fVar5 = (float10)FUN_0042d980();
                            if (((float10)60000.0 <= fVar5) ||
                                ((fVar5 = (float10)FUN_0042df90(param_1[0x19]),
                                  (float10)30.0 <= fVar5 ||
                                      (*(char *)((int)param_1 + 0xaeb9) != '\x01'))))
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
                if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 8))
                {
                    param_1[0x15]  = 0;
                    param_1[0x21d] = 0;
                }
                if (((param_1[0x2b7d] == 2) && (2 < param_1[0x2b81])) && (param_1[0x2b81] < 0xb))
                {
                    FUN_00434b90(0);
                }
                else
                {
                    FUN_00434bd0();
                }
                if ((param_1[0x2b7d] == 2) && (0x28 < param_1[0x2b81]))
                {
                    if (((param_1[0x20c] == 3) &&
                         ((0 < param_1[0x20d] && (sVar2 = FUN_0042c7b0(), sVar2 == 0)))) &&
                        ((char)param_1[0x21] != '\0'))
                    {
                        FUN_00421080(0x18);
                        return;
                    }
                    if ((((param_1[0x20c] == 4) && (0 < param_1[0x20d])) &&
                         (sVar2 = FUN_0042c7b0(), sVar2 == 0)) &&
                        ((char)param_1[0x21] != '\0'))
                    {
                        FUN_00421080(0x17);
                        return;
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
                    goto switchD_005954f8_caseD_1;
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
                    param_1[0x15] = 0x40900000;
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
                        (param_1[0x20d] = param_1[0x20d] + -0xf, param_1[0x20d] < 0))
                    {
                        param_1[0x20d] = 0;
                    }
                    if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] % 0x16 == 6))
                    {
                        FUN_0042c8b0(5);
                    }
                    if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] % 0x16 == 0x11))
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
                        param_1[0x15] = 0x41b40000;
                        param_1[0x3a] = 0;
                    }
                    if (param_1[0x2b7d] == 1)
                    {
                        param_1[0x21d] = 0x40c00000;
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
                        param_1[0x15]  = (int)((float)param_1[0x15] - 1.0);
                        if ((float)param_1[0x15] < 0.0)
                        {
                            param_1[0x15] = 0;
                        }
                        if ((param_1[0x2b81] == 1) && (param_1[0x3a] < 10))
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
                        param_1[0x20d] = param_1[0x20d] + -0xe;
                        if (param_1[0x20d] < 0)
                        {
                            param_1[0x20d] = 0;
                        }
                    }
                    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                    {
                        param_1[0x19]   = 0;
                        param_1[0x18]   = -0x3d4c0000;
                        param_1[0x15]   = 0x41f00000;
                        param_1[0x2bd2] = param_1[0x2bd2] + 1;
                    }
                    if (param_1[0x2b7d] == 1)
                    {
                        param_1[0x18] = -0x3d4c0000;
                    }
                    if ((param_1[0x2b7d] < 2) && (param_1[0x15] = (int)((float)param_1[0x15] - 1.5),
                                                  (float)param_1[0x15] < 13.0))
                    {
                        param_1[0x15] = 0x41500000;
                    }
                    if (param_1[0x2b7d] == 2)
                    {
                        if ((char)param_1[0x21] == '\0')
                        {
                            param_1[0x16] = 0x3f000000;
                            FUN_00421080(0x2b);
                            return;
                        }
                        param_1[0x15] = (int)((float)param_1[0x15] - 1.0);
                        if ((float)param_1[0x15] < 0.0)
                        {
                            param_1[0x15] = 0;
                        }
                    }
                    uVar3 = param_1[0x2b81] & 0x80000007;
                    if ((int)uVar3 < 0)
                    {
                        uVar3 = (uVar3 - 1 | 0xfffffff8) + 1;
                    }
                    if (uVar3 == 0)
                    {
                        param_1[0x2b81] = param_1[0x2b81] + 1;
                        param_1[0x2b82] = param_1[0x2b82] + 1;
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
                        param_1[0x20d] = param_1[0x20d] + -0xe;
                        if (param_1[0x20d] < 0)
                        {
                            param_1[0x20d] = 0;
                        }
                    }
                    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                    {
                        param_1[0x19]   = 0;
                        param_1[0x18]   = 0x42b40000;
                        param_1[0x15]   = 0x41f00000;
                        param_1[0x2bd2] = param_1[0x2bd2] + 1;
                    }
                    if (param_1[0x2b7d] == 1)
                    {
                        param_1[0x18] = 0x42b40000;
                    }
                    if ((param_1[0x2b7d] < 2) && (param_1[0x15] = (int)((float)param_1[0x15] - 1.5),
                                                  (float)param_1[0x15] < 13.0))
                    {
                        param_1[0x15] = 0x41500000;
                    }
                    if ((param_1[0x2b7d] == 2) &&
                        (param_1[0x15] = (int)((float)param_1[0x15] - 1.0),
                         (float)param_1[0x15] < 0.0))
                    {
                        param_1[0x15] = 0;
                    }
                    uVar3 = param_1[0x2b81] & 0x80000007;
                    if ((int)uVar3 < 0)
                    {
                        uVar3 = (uVar3 - 1 | 0xfffffff8) + 1;
                    }
                    if (uVar3 == 0)
                    {
                        param_1[0x2b81] = param_1[0x2b81] + 1;
                        param_1[0x2b82] = param_1[0x2b82] + 1;
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
                        (param_1[0x20d] = param_1[0x20d] + -0xe, param_1[0x20d] < 0))
                    {
                        param_1[0x20d] = 0;
                    }
                    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                    {
                        param_1[0x19]   = 0;
                        param_1[0x18]   = 0x43340000;
                        param_1[0x15]   = 0x41940000;
                        param_1[0x2bd2] = param_1[0x2bd2] + 1;
                    }
                    if (param_1[0x2b7d] == 1)
                    {
                        param_1[0x21d] = 0;
                        param_1[0x15]  = 0x41940000;
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
                        param_1[0x20d] = param_1[0x20d] + -9;
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
                        param_1[0x15]  = 0x41580000;
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
                        param_1[0x15]  = 0x41580000;
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
                        param_1[0x10] = 0x41400000;
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
                        (param_1[0x20d] = param_1[0x20d] + -10, param_1[0x20d] < 0))
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
                FUN_00434a70(0, 2);
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
                if ((param_1[0x3b] != 0) && (param_1[0x1a1] = 2, param_1[0x2b81] < 8))
                {
                    FUN_0042db10(0, 0x41c80000);
                }
                if (param_1[0x2b81] == 0)
                {
                    param_1[0x15] = 0;
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
                if (param_1[0x2b81] == 9)
                {
                    FUN_0042c880(0x3d);
                    FUN_004223d0(2, 10, 0);
                }
                if (param_1[0x2b81] == 8)
                {
                    param_1[0x15]  = 0x41f00000;
                    param_1[0x21d] = 0;
                }
                if (param_1[0x2b81] == 0xe)
                {
                    param_1[0x15]  = 0;
                    param_1[0x21d] = 0;
                }
                if ((param_1[0x2b81] < 10) || (0x10 < param_1[0x2b81]))
                {
                    FUN_00434bd0();
                }
                else
                {
                    FUN_00434b90(0);
                }
                break;
            case 0x12e:
                FUN_00434a70(0, 2);
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
                    FUN_0042db10(0, 0x41700000);
                }
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    FUN_00422900();
                    FUN_00423000();
                }
                if (param_1[0x2b81] == 0)
                {
                    param_1[0x15] = 0;
                    param_1[0x18] = 0;
                    FUN_0042c800(0);
                    FUN_0042c840(1);
                }
                uVar3 = FUN_0042c7b0();
                if ((uVar3 & 2) != 0)
                {
                    FUN_00421080(0x188);
                    FUN_0042c800(0);
                    return;
                }
                if (param_1[0x2b81] == 10)
                {
                    FUN_0042c880(0x3e);
                    FUN_004223d0(3, 10, 0);
                }
                if (param_1[0x2b81] == 1)
                {
                    param_1[0x15]  = 0x41700000;
                    param_1[0x21d] = 0;
                }
                if (param_1[0x2b81] == 0xe)
                {
                    param_1[0x15]  = 0;
                    param_1[0x21d] = 0;
                }
                if ((param_1[0x2b81] < 10) || (0xd < param_1[0x2b81]))
                {
                    FUN_00434bd0();
                }
                else
                {
                    FUN_00434b90(0);
                }
                if (0x28 < param_1[0x2b81])
                {
                    if ((((param_1[0x20c] == 3) && (0 < param_1[0x20d])) &&
                         (sVar2 = FUN_0042c7b0(), sVar2 == 0)) &&
                        ((char)param_1[0x21] != '\0'))
                    {
                        FUN_00421080(0x18);
                        return;
                    }
                    if (((param_1[0x20c] == 4) && (0 < param_1[0x20d])) &&
                        ((sVar2 = FUN_0042c7b0(), sVar2 == 0 && ((char)param_1[0x21] != '\0'))))
                    {
                        FUN_00421080(0x17);
                        return;
                    }
                }
                break;
            default:
            switchD_005954f8_caseD_1:
                FUN_00428510();
                return;
            case 0x136:
                FUN_00434a70(0, 2);
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
                    param_1[0x15] = 0x41c80000;
                    param_1[0x3a] = 0;
                    FUN_0042db10(0, 0x43340000);
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
                if ((param_1[0x2b7d] == 1) &&
                    (fVar5 = (float10)FUN_0042d980(), fVar5 < (float10)40000.0))
                {
                    FUN_00421100(2);
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
                if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 2))
                {
                    FUN_0042c8b0(0x3e);
                    FUN_004223d0(3, 10, 0);
                }
                if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 0))
                {
                    param_1[0x15] = 0;
                }
                if (((param_1[0x2b7d] == 2) && (1 < param_1[0x2b81])) && (param_1[0x2b81] < 0xb))
                {
                    FUN_00434b90(0);
                }
                else
                {
                    FUN_00434bd0();
                }
                if (((param_1[0x2b7d] == 2) && (0xf < param_1[0x2b81])) &&
                    ((uVar3 = FUN_0042c7b0(), (uVar3 & 1) != 0 && (param_1[0xa0] != 0))))
                {
                    FUN_00421080(0x28);
                    return;
                }
                break;
            case 0x137:
                FUN_00434a70(0, 2);
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
                if (param_1[0x2b7d] == 0)
                {
                    if (param_1[0x2b81] < 0xf)
                    {
                        FUN_0042db10(0x41200000, 0x41700000);
                    }
                    if (param_1[0x2b81] == 0)
                    {
                        FUN_00422900();
                        FUN_00423000();
                        param_1[0x15] = 0;
                        param_1[0x18] = 0;
                        FUN_0042c800(0);
                        FUN_0042c840(1);
                    }
                    if (param_1[0x2b81] == 4)
                    {
                        param_1[0x15] = 0x41b40000;
                    }
                }
                if (param_1[0x2b7d] == 1)
                {
                    if (param_1[0x2b81] < 10)
                    {
                        FUN_0042db10(0x41200000, 0x41700000);
                    }
                    fVar5 = (float10)FUN_0042d980();
                    if ((fVar5 < (float10)40000.0) && (10 < param_1[0x2b81]))
                    {
                        FUN_00421100(2);
                        return;
                    }
                }
                if (param_1[0x2b7d] == 2)
                {
                    if (param_1[0x2b81] == 0)
                    {
                        param_1[0x15] = 0x41200000;
                    }
                    if (param_1[0x2b81] == 0xd)
                    {
                        FUN_0042c8b0(0x3e);
                        FUN_004223d0(2, 10, 0);
                    }
                    if (param_1[0x2b81] == 0x15)
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
                    if ((param_1[0x2b81] < 1) || (8 < param_1[0x2b81]))
                    {
                        FUN_00434bd0();
                    }
                    else
                    {
                        FUN_00434b90(0);
                    }
                    if ((0xf < param_1[0x2b81]) &&
                        (param_1[0x15] = (int)((float)param_1[0x15] - 0.65),
                         (float)param_1[0x15] < 0.0))
                    {
                        param_1[0x15] = 0;
                    }
                }
                break;
            case 0x140:
                FUN_00434a70(0, 2);
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
                    (0xf < param_1[0x2b81]))
                {
                    FUN_00421080(0x149);
                    param_1[0x15] = 0;
                    param_1[0x10] = 0;
                    param_1[0xb]  = 0;
                    return;
                }
                if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0))
                {
                    FUN_00422900();
                    FUN_00423000();
                    param_1[0x18] = 0;
                    FUN_0042c800(0);
                    FUN_0042c840(1);
                    param_1[0x3a] = 0;
                    param_1[0x3b] = 0;
                    param_1[0x3c] = 0;
                    param_1[0x15] = 0x41500000;
                    fVar5         = (float10)FUN_0042d980();
                    if (fVar5 < (float10)360000.0)
                    {
                        param_1[0x3c] = 0xaf;
                        FUN_0042db10(0, 0x43340000);
                    }
                    fVar5 = (float10)FUN_00423580(param_1[0x10], param_1[0x15]);
                    param_1[0xb] =
                        (int)(float)((fVar5 / (float10)3.1415927) * (float10)180.0 + (float10)15.0);
                    param_1[0xb6] = 0x428c0000;
                }
                param_1[0x3b] = param_1[0x3b] + 1;
                if ((param_1[0x2b7d] < 2) && (0 < param_1[0x3c]))
                {
                    fVar5   = (float10)FUN_00423580(param_1[0x10], param_1[0x15]);
                    local_8 = (float)((fVar5 / (float10)3.1415927) * (float10)180.0);
                    fVar5   = (float10)FUN_0042da80();
                    fVar10  = (float)(fVar5 + (float10)10.0);
                    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                    {
                        fVar5   = (float10)FUN_0042da80();
                        local_8 = (float)(fVar5 + (float10)10.0);
                    }
                    if ((fVar10 < local_8) && (local_8 = local_8 - 5.0, local_8 < fVar10))
                    {
                        local_8 = fVar10;
                    }
                    if ((local_8 < fVar10) && (local_8 = local_8 + 5.0, fVar10 < local_8))
                    {
                        local_8 = fVar10;
                    }
                    if (30.0 < local_8)
                    {
                        local_8 = 30.0;
                    }
                    if (local_8 < -40.0)
                    {
                        local_8 = -40.0;
                    }
                    iVar4         = param_1[0x3c];
                    fVar5         = (float10)FUN_0065d050(local_8);
                    param_1[0x15] = (int)(float)(fVar5 * (float10)((float)iVar4 * 0.1));
                    iVar4         = param_1[0x3c];
                    fVar5         = (float10)FUN_0065d010(local_8);
                    param_1[0x10] = (int)(float)(fVar5 * (float10)((float)iVar4 * 0.1));
                    fVar5         = (float10)FUN_00423580(param_1[0x10], param_1[0x15]);
                    param_1[0xb] =
                        (int)(float)((fVar5 / (float10)3.1415927) * (float10)180.0 + (float10)15.0);
                    param_1[0xb6] = 0x428c0000;
                    FUN_0042db10(0, 0x40a00000);
                    param_1[0x3c] = param_1[0x3c] + -3;
                    if (param_1[0x3c] < 0x82)
                    {
                        param_1[0x3c] = 0x82;
                    }
                }
                if ((param_1[0x2b7d] == 1) && (FUN_0042db10(0, 0x40000000), 5 < param_1[0x2b81]))
                {
                    fVar5 = (float10)FUN_0042d980();
                    fVar7 = (float10)FUN_0042da30();
                    fVar6 = (float10)FUN_0042da30();
                    if ((fVar6 * (float10)(float)fVar7 + (float10)(float)fVar5 <
                         (float10)70000.0) ||
                        ((0x19 < param_1[0x2b81] || (param_1[0x3c] == 0))))
                    {
                        FUN_00421100(2);
                        return;
                    }
                }
                if (param_1[0x2b7d] == 2)
                {
                    if ((param_1[0x2b81] < 0xb) && (param_1[0x3c] == 1))
                    {
                        FUN_0042db10(0, 0x40000000);
                    }
                    if (param_1[0x2b81] == 0xb)
                    {
                        FUN_0042c8b0(0x3e);
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
                    if (0x23 < param_1[0x2b81])
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
                if (((param_1[0x2b7d] == 2) && (param_1[0x2b81] < 0x12)) && (4 < param_1[0x2b81]))
                {
                    FUN_00434b90(0);
                }
                else
                {
                    FUN_00434bd0();
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
                FUN_00434a70(0, 2);
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
                if (param_1[0x2b7d] == 0)
                {
                    FUN_0042db10(0, 0x40a00000);
                }
                if (param_1[0x2b7d] == 1)
                {
                    FUN_0042db10(0, 0x40a00000);
                    param_1[0x15]  = 0x41dc0000;
                    param_1[0x21d] = 0;
                    if ((2 < param_1[0x2b81]) &&
                        ((fVar5 = (float10)FUN_0042d980(),
                          fVar5 < (float10)90000.0 || (param_1[0x2b81] == 0xc))))
                    {
                        FUN_00421100(2);
                        return;
                    }
                }
                if (param_1[0x2b7d] == 2)
                {
                    if (param_1[0x2b81] < 10)
                    {
                        FUN_0042db10(0, 0x40a00000);
                    }
                    if (param_1[0x2b81] == 10)
                    {
                        FUN_0042c8b0(0x3e);
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
                                    FUN_004223d0(3, 10, 0);
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
                    if (0x2d < param_1[0x2b81])
                    {
                        if ((((param_1[0x20c] == 3) && (0 < param_1[0x20d])) &&
                             (sVar2 = FUN_0042c7b0(), sVar2 == 0)) &&
                            ((char)param_1[0x21] != '\0'))
                        {
                            FUN_00421080(0x18);
                            return;
                        }
                        if (((param_1[0x20c] == 4) && (0 < param_1[0x20d])) &&
                            ((sVar2 = FUN_0042c7b0(), sVar2 == 0 && ((char)param_1[0x21] != '\0'))))
                        {
                            FUN_00421080(0x17);
                            return;
                        }
                    }
                }
                if (((param_1[0x2b7d] == 2) && (9 < param_1[0x2b81])) && (param_1[0x2b81] < 0x10))
                {
                    FUN_00434b90(0);
                }
                else
                {
                    FUN_00434bd0();
                }
                break;
            case 0x14b:
                FUN_00434a70(0, 2);
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
                    param_1[0x15] = 0x41a00000;
                    fVar5         = (float10)FUN_0042d980();
                    if (fVar5 < (float10)810000.0)
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
                if ((param_1[0x2b7d] == 0) && (param_1[0x3c] == 1))
                {
                    FUN_0042db10(0, 0x42480000);
                }
                if (((param_1[0x2b7d] == 1) && (2 < param_1[0x2b81])) &&
                    ((fVar5 = (float10)FUN_0042d980(),
                      fVar5 < (float10)90000.0 || (param_1[0x3c] == 0))))
                {
                    FUN_00421100(2);
                    return;
                }
                if (param_1[0x2b7d] == 2)
                {
                    if (param_1[0x2b81] == 2)
                    {
                        param_1[0x15] = 0x41a00000;
                    }
                    if (param_1[0x2b81] == 0xd)
                    {
                        FUN_0042c8b0(0x3e);
                        FUN_004223d0(3, 10, 0);
                    }
                    if (param_1[0x2b81] == 0x1a)
                    {
                        param_1[0x15] = 0;
                    }
                    if ((param_1[0x2b81] < 7) || (0x10 < param_1[0x2b81]))
                    {
                        FUN_00434bd0();
                    }
                    else
                    {
                        FUN_00434b90(0);
                    }
                    if ((0x2d < param_1[0x2b81]) && (sVar2 = FUN_0042c7b0(), sVar2 == 0))
                    {
                        if ((param_1[0x20c] == 3) &&
                            ((0 < param_1[0x20d] && ((char)param_1[0x21] != '\0'))))
                        {
                            FUN_00421080(0x18);
                            return;
                        }
                        if (((param_1[0x20c] == 4) && (0 < param_1[0x20d])) &&
                            ((char)param_1[0x21] != '\0'))
                        {
                            FUN_00421080(0x17);
                            return;
                        }
                    }
                }
                break;
            case 0x14c:
                FUN_00434a70(0, 2);
                cVar1 = FUN_004218c0();
                if (cVar1 != '\0')
                {
                    FUN_00421080(0x2b);
                    return;
                }
                if (((char)param_1[0x21] != '\0') && (1 < param_1[0x2b7d]))
                {
                    FUN_00421080(0x14d);
                    param_1[0x15] = 0;
                    param_1[0x10] = 0;
                    return;
                }
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    FUN_00422900();
                    FUN_00423000();
                }
                if (param_1[0x2b7d] == 0)
                {
                    FUN_0042db10(0, 0x40a00000);
                }
                if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0))
                {
                    param_1[0x3a] = 0;
                    param_1[0x15] = 0;
                    param_1[0x18] = 0;
                    param_1[0x10] = 0;
                    FUN_0042c800(0);
                    FUN_0042c840(1);
                }
                if (param_1[0x2b7d] == 1)
                {
                    param_1[0x3a] = param_1[0x3a] + 1;
                    param_1[0x15] = 0x41c80000;
                    fVar5         = (float10)FUN_0042da30();
                    fVar10        = (float)param_1[0x15];
                    fVar7         = (float10)FUN_0042d980();
                    fVar7         = (float10)FUN_0042de80((float)fVar7);
                    param_1[0x10] = (int)(float)((float10)(float)(fVar5 * (float10)fVar10) /
                                                 (fVar7 + (float10)1.0));
                    if ((float)param_1[0x10] <= -10.0)
                    {
                        local_2c = (float)param_1[0x10];
                    }
                    else
                    {
                        local_2c = -10.0;
                    }
                    if (-2.0 <= local_2c)
                    {
                        if ((float)param_1[0x10] <= -10.0)
                        {
                            local_34 = param_1[0x10];
                        }
                        else
                        {
                            local_34 = -0x3ee00000;
                        }
                        local_30 = local_34;
                    }
                    else
                    {
                        local_30 = -0x40000000;
                    }
                    param_1[0x10] = local_30;
                    param_1[0x3a] = param_1[0x3a] + 1;
                    sVar2         = FUN_0042c7b0();
                    if (sVar2 != 0)
                    {
                        param_1[0x10] = 0x41200000;
                        param_1[0x15] = -0x3f200000;
                        param_1[0x16] = 0x3eb33333;
                        FUN_00421080(0x14e);
                        FUN_0042c800(0);
                        FUN_0042c840(1);
                        return;
                    }
                    if (0x2d < param_1[0x3a])
                    {
                        param_1[0x3a] = 0;
                        FUN_00421100(2);
                        return;
                    }
                }
                if ((param_1[0x2b7d] == 2) &&
                    (param_1[0x3a] = param_1[0x3a] + 1, 0x14 < param_1[0x3a]))
                {
                    param_1[0x3a] = 0;
                    FUN_00421100(3);
                    param_1[0x15] = 0x41200000;
                    return;
                }
                if ((1 < param_1[0x2b7d]) &&
                    (param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]),
                     (float)param_1[0x15] < 0.0))
                {
                    param_1[0x15] = 0;
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
                if (((float)param_1[0x10] < 6.0) && (param_1[0x2b7d] == 0))
                {
                    FUN_00421100(1);
                    return;
                }
                if (((char)param_1[0x21] != '\0') &&
                    ((float)param_1[0x10] < 0.0 != ((float)param_1[0x10] == 0.0)))
                {
                    FUN_00421080(0x14d);
                    param_1[0x10] = 0;
                    return;
                }
                param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
                break;
            case 0x154:
                FUN_00434a70(0, 2);
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
                if (param_1[0x2b81] < 0x22)
                {
                    param_1[0x1a1] = 2;
                }
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    FUN_00422900();
                    FUN_00423000();
                    param_1[0x18] = 0;
                    FUN_0042c800(0);
                    FUN_0042c840(1);
                    param_1[0x3b] = 0;
                }
                sVar2 = FUN_0042c7b0();
                if ((sVar2 != 0) && (param_1[0x3b] == 0))
                {
                    param_1[0x3b] = 1;
                }
                uVar3 = FUN_0042c7b0();
                if ((uVar3 & 2) != 0)
                {
                    FUN_00421080(0x188);
                    FUN_0042c800(0);
                    return;
                }
                if (param_1[0x2b81] == 5)
                {
                    FUN_0042c880(0x3d);
                    FUN_004223d0(2, 10, 0);
                }
                if (param_1[0x2b81] < 0xc)
                {
                    FUN_0042db10(0, 0x41700000);
                }
                if (param_1[0x2b81] == 4)
                {
                    param_1[0x15] = 0x41a00000;
                }
                if (param_1[0x2b81] == 0xc)
                {
                    param_1[0x15] = 0;
                }
                if ((param_1[0x2b81] < 0x10) || (0x18 < param_1[0x2b81]))
                {
                    FUN_00434bd0();
                }
                else
                {
                    FUN_00434b90(0);
                }
            }
        }
    }
    else
    {
        switch (iVar4)
        {
        case 0x156:
            FUN_00434a70(0, 2);
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0);
                return;
            }
            if ((char)param_1[0x21] == '\0')
            {
                FUN_00421080(0x2b);
                return;
            }
            if (param_1[0x2b81] < 0x22)
            {
                param_1[0x1a1] = 2;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                param_1[0x15] = 0;
                FUN_00422900();
                FUN_00423000();
                param_1[0x18] = 0;
                FUN_0042c800(0);
                FUN_0042c840(1);
            }
            uVar3 = FUN_0042c7b0();
            if ((uVar3 & 2) != 0)
            {
                FUN_00421080(0x188);
                FUN_0042c800(0);
                return;
            }
            if (param_1[0x2b81] == 0xe)
            {
                param_1[0x15] = 0x41f00000;
            }
            if (param_1[0x2b81] == 0xf)
            {
                FUN_0042c880(0x3d);
                FUN_004223d0(3, 10, 0);
            }
            if (param_1[0x2b81] == 0x13)
            {
                param_1[0x15] = 0;
            }
            break;
        default:
            goto switchD_005954f8_caseD_1;
        case 0x15e:
            FUN_00434a70(0, 2);
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
            if (param_1[0x2b81] == 0)
            {
                FUN_00422900();
                param_1[0x18] = 0;
                FUN_00434bd0();
                param_1[0x15] = 0;
                FUN_004223d0(0x20, 0x14, 0);
                param_1[0x3a] = 0;
                param_1[0x3e] = 0;
            }
            if ((0x32 < param_1[0x2b81]) && (param_1[0x2b81] < 0x50))
            {
                if (param_1[0x3a] < 1)
                {
                    param_1[0x3a] = param_1[0x3a] + 1;
                    return;
                }
                param_1[0x3a] = 0;
            }
            if ((((param_1[0x2b81] == 0x11) || (param_1[0x2b81] == 0x16)) ||
                 (param_1[0x2b81] == 0x1a)) ||
                (((param_1[0x2b81] == 0x1e || (param_1[0x2b81] == 0x21)) ||
                  ((param_1[0x2b81] == 0x25 || (param_1[0x2b81] == 0x2a))))))
            {
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
                FUN_004230e0();
                FUN_00435000(0, 8, 0, (float)param_1[0x3c], 0);
                FUN_0042c880(0x40);
                FUN_0042c880(0x94);
            }
            if (param_1[0x2b81] < 0xc)
            {
                FUN_0042db10(0, 0x41500000);
            }
            if (param_1[0x2b81] < 0x2a)
            {
                FUN_0042db10(0, 0x3f800000);
            }
            if ((param_1[0x2b81] < 0x11) || (0x3c < param_1[0x2b81]))
            {
                FUN_00434bd0();
            }
            else
            {
                FUN_00434b90(0);
            }
            if ((param_1[0x2b81] == 0xc) && (param_1[0x3e] < 0xf))
            {
                param_1[0x3e] = param_1[0x3e] + 1;
                return;
            }
            break;
        case 0x168:
            FUN_00434a70(0, 2);
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                if ((char)param_1[0x21] == '\0')
                {
                    FUN_00421080(0x2b);
                    param_1[0x16] = 0x3f000000;
                    return;
                }
                FUN_00421080(0);
                return;
            }
            if ((char)param_1[0x21] != '\0')
            {
                param_1[0x15] = 0;
                param_1[0x10] = 0;
            }
            if (param_1[0x2b81] < 0xc)
            {
                FUN_0042dc20(0, 0x41500000);
            }
            if (param_1[0x2b81] < 0x2a)
            {
                FUN_0042dc20(0, 0x3f800000);
            }
            param_1[0x16] = 0x3dcccccd;
            param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
            if (param_1[0x2b7d] == 0)
            {
                if (param_1[0x2b81] == 0)
                {
                    FUN_00422900();
                    param_1[0x18] = 0;
                    FUN_00434bd0();
                    param_1[0x15] = 0;
                    FUN_004223d0(0x20, 0x14, 0);
                    param_1[0x3a] = 0;
                    param_1[0x3e] = 0;
                    if (3.0 < (float)param_1[0x10])
                    {
                        param_1[0x10] = 0x40400000;
                    }
                    if ((float)param_1[0x10] < -3.0)
                    {
                        param_1[0x10] = -0x3fc00000;
                    }
                }
                if ((0x32 < param_1[0x2b81]) && (param_1[0x2b81] < 0x50))
                {
                    if (param_1[0x3a] < 1)
                    {
                        param_1[0x3a] = param_1[0x3a] + 1;
                        return;
                    }
                    param_1[0x3a] = 0;
                }
                if (param_1[0x2b81] < 0x2a)
                {
                    FUN_0042db10(0, 0x41200000);
                    FUN_0042da80();
                    iVar4         = FUN_0066b668();
                    param_1[0x3c] = iVar4;
                    if (0x1e < param_1[0x3c])
                    {
                        param_1[0x3c] = 0x1e;
                    }
                    if (param_1[0x3c] < -0x1e)
                    {
                        param_1[0x3c] = -0x1e;
                    }
                    param_1[0xb]  = (int)(float)param_1[0x3c];
                    param_1[0xb6] = 0x428c0000;
                }
                if (((param_1[0x2b81] == 0x11) || (param_1[0x2b81] == 0x16)) ||
                    ((param_1[0x2b81] == 0x1a ||
                      ((((param_1[0x2b81] == 0x1e || (param_1[0x2b81] == 0x21)) ||
                         (param_1[0x2b81] == 0x25)) ||
                        (param_1[0x2b81] == 0x2a))))))
                {
                    FUN_004230e0();
                    FUN_00435000(0, 8, 0, (float)param_1[0x3c], 0);
                    FUN_0042c880(0x40);
                    FUN_0042c880(0x94);
                }
                if (0x50 < param_1[0x2b81])
                {
                    if ((0.0 < (float)param_1[0xb]) &&
                        (param_1[0xb] = (int)((float)param_1[0xb] - 2.0),
                         (float)param_1[0xb] < 0.0))
                    {
                        param_1[0xb] = 0;
                    }
                    if (((float)param_1[0xb] < 0.0) &&
                        (param_1[0xb] = (int)((float)param_1[0xb] + 2.0),
                         0.0 < (float)param_1[0xb]))
                    {
                        param_1[0xb] = 0;
                    }
                }
            }
            if ((param_1[0x2b81] < 0x11) || (0x3c < param_1[0x2b81]))
            {
                FUN_00434bd0();
            }
            else
            {
                FUN_00434b90(0);
            }
            if ((param_1[0x2b81] == 0xc) && (param_1[0x3e] < 0xf))
            {
                param_1[0x3e] = param_1[0x3e] + 1;
                return;
            }
            break;
        case 0x172:
            FUN_00434a70(0, 2);
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0);
                return;
            }
            if ((char)param_1[0x21] == '\0')
            {
                FUN_00421080(0x2b);
                param_1[0x15] = (int)((float)param_1[0x15] * 0.5);
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
                param_1[0x3e] = 0;
                param_1[0x15] = 0x41f00000;
                FUN_0042db10(0, 0x43340000);
                FUN_0042c8b0(0x95);
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 1))
            {
                uVar12 = 0;
                fVar11 = (float)param_1[0x17] + (float)param_1[0x19];
                fVar5 =
                    (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19], fVar11, 0);
                fVar10 = (float)(fVar5 * (float10)100.0 + (float10)(float)param_1[7]);
                fVar8  = (float)param_1[6] + 80.0;
                fVar5  = (float10)FUN_0065d050(
                    (float)param_1[0x17] + (float)param_1[0x19], fVar8, fVar10);
                FUN_00435450(9,
                             (float)(fVar5 * (float10)100.0 + (float10)(float)param_1[5]),
                             fVar8,
                             fVar10,
                             fVar11,
                             uVar12);
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
            if (param_1[0x2b7d] == 0)
            {
                FUN_0042db10(0, 0x40e00000);
            }
            if (((param_1[0x2b7d] == 1) && (FUN_0042db10(0, 0x40e00000), 0 < param_1[0x2b81])) &&
                (0 < param_1[0x2b81]))
            {
                FUN_00421100(2);
                return;
            }
            if (((param_1[0x2b7d] == 2) &&
                 (param_1[0x3e] = param_1[0x3e] + 1, 10 < param_1[0x2b81])) &&
                (param_1[0x15] = (int)((float)param_1[0x15] - 6.0), (float)param_1[0x15] < 0.0))
            {
                param_1[0x15] = 0;
            }
            if ((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 5))
            {
                FUN_0042c880(0x40);
                FUN_004223d0(3, 0x14, 0);
            }
            if (((param_1[0x2b7d] == 2) && (param_1[0x2b81] == 0x1a)) && (param_1[0x3e] < 10))
            {
                return;
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
                param_1[0x10] = 0;
                param_1[0x16] = 0x3dcccccd;
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
                FUN_00421080(0x18a);
                FUN_0042c8b0(0x33);
                FUN_0042c800(0);
                return;
            }
            if (param_1[0x2b7d] == 2)
            {
                param_1[0x16]  = 0x3f000000;
                param_1[0x21d] = 0;
                param_1[0x15]  = (int)((float)param_1[0x15] - 1.0);
                if ((float)param_1[0x15] < 0.0)
                {
                    param_1[0x15] = 0;
                }
            }
            param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
            break;
        case 0x18a:
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
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                param_1[0x18] = 0;
                param_1[0x15] = -0x3e900000;
                param_1[0x10] = 0x41200000;
                param_1[0x3a] = 0;
                param_1[0x16] = 0x3f000000;
            }
            if ((param_1[0x2b7d] < 2) && (uVar3 = FUN_0042c7b0(), (uVar3 & 2) != 0))
            {
                FUN_00421080(0x18a);
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
            if ((param_1[0x2b7d] == 1) && (param_1[0x3a] = param_1[0x3a] + 1, 0x14 < param_1[0x3a]))
            {
                FUN_00421100(2);
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
                if (-10.0 < (float)param_1[0x15])
                {
                    param_1[0x15] = -0x3ee00000;
                }
            }
            param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
            break;
        case 400:
            FUN_00434a70(0, 2);
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
            }
            if (param_1[0x2b81] < 6)
            {
                FUN_0042db10(0, 0x41f00000);
            }
            if ((param_1[0x2b7d] == 0) &&
                (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0))
            {
                param_1[0x15] = 0;
            }
            if (param_1[0x2b81] == 0xb)
            {
                FUN_0042c8b0(0x93);
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
                if (param_1[0x3c] < -0x1e)
                {
                    param_1[0x3c] = -0x1e;
                }
                if (0x1e < param_1[0x3c])
                {
                    param_1[0x3c] = 0x1e;
                }
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    fVar11 = (float)param_1[0x3c];
                    fVar8  = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar5  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar8, fVar11);
                    fVar10 = (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[7]);
                    fVar9  = (float)param_1[6] + 70.0;
                    fVar5  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar9, fVar10);
                    FUN_00435450(0,
                                 (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[5]),
                                 fVar9,
                                 fVar10,
                                 fVar8,
                                 fVar11);
                }
                else
                {
                    fVar11 = (float)param_1[0x3c];
                    fVar8  = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar5  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar8, fVar11);
                    fVar10 = (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[7]);
                    fVar9  = (float)param_1[6] + 70.0;
                    fVar5  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar9, fVar10);
                    FUN_00435450(2,
                                 (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[5]),
                                 fVar9,
                                 fVar10,
                                 fVar8,
                                 fVar11);
                }
            }
            if ((param_1[0x2b81] < 10) || (0x28 < param_1[0x2b81]))
            {
                FUN_00434bd0();
            }
            else
            {
                FUN_00434b90(0);
            }
            break;
        case 0x191:
            FUN_00434a70(0, 2);
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
            }
            if (param_1[0x2b7d] == 0)
            {
                param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
                if ((float)param_1[0x15] < 0.0)
                {
                    param_1[0x15] = 0;
                }
                FUN_0042dc20(0, 0x41700000);
            }
            if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] == 2))
            {
                FUN_0042c8b0(0x93);
                if (param_1[0x1b7] == 1)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1c, 10, 0);
                }
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0xf)
                {
                    param_1[0x3c] = -0xf;
                }
                if (0x37 < param_1[0x3c])
                {
                    param_1[0x3c] = 0x37;
                }
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    FUN_00435000(0, 1, 0, (float)param_1[0x3c], 0);
                }
                else
                {
                    FUN_00435000(0, 3, 0, (float)param_1[0x3c], 0);
                }
            }
            if (param_1[0x2b7d] == 1)
            {
                if ((param_1[0x2b81] < 3) || (0xe < param_1[0x2b81]))
                {
                    FUN_00434bd0();
                }
                else
                {
                    FUN_00434b90(0);
                }
            }
            break;
        case 0x192:
            FUN_00434a70(0, 2);
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0x2b);
                return;
            }
            if (((char)param_1[0x21] != '\0') && (0 < param_1[0x2b81]))
            {
                FUN_00421080(0x193);
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00422900();
            }
            if (param_1[0x2b81] < 6)
            {
                FUN_0042dc20(0, 0x41f00000);
            }
            if (param_1[0x2b81] == 0)
            {
                param_1[0x18] = 0;
            }
            if (param_1[0x2b81] == 0xb)
            {
                FUN_0042c8b0(0x93);
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
                if (param_1[0x3c] < -0x1e)
                {
                    param_1[0x3c] = -0x1e;
                }
                if (0x1e < param_1[0x3c])
                {
                    param_1[0x3c] = 0x1e;
                }
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    fVar11 = (float)param_1[0x3c];
                    fVar8  = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar5  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar8, fVar11);
                    fVar10 = (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[7]);
                    fVar9  = (float)param_1[6] + 70.0;
                    fVar5  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar9, fVar10);
                    FUN_00435450(0,
                                 (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[5]),
                                 fVar9,
                                 fVar10,
                                 fVar8,
                                 fVar11);
                }
                else
                {
                    fVar11 = (float)param_1[0x3c];
                    fVar8  = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar5  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar8, fVar11);
                    fVar10 = (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[7]);
                    fVar9  = (float)param_1[6] + 70.0;
                    fVar5  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar9, fVar10);
                    FUN_00435450(2,
                                 (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[5]),
                                 fVar9,
                                 fVar10,
                                 fVar8,
                                 fVar11);
                }
            }
            if ((float)param_1[0x16] == 0.0)
            {
                param_1[0x16] = 0x3f000000;
            }
            param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
            if ((param_1[0x2b81] < 10) || (0x28 < param_1[0x2b81]))
            {
                FUN_00434bd0();
            }
            else
            {
                FUN_00434b90(0);
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
            FUN_00434a70(0, 2);
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
            }
            if ((param_1[0x2b81] < 4) || (param_1[0x2b7d] == 0))
            {
                FUN_0042dc20(0, 0x41700000);
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
            if ((float)param_1[0x15] < 0.0)
            {
                param_1[0x15] = 0;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                param_1[0x18] = 0;
                param_1[0x15] = 0x41700000;
            }
            if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] == 4))
            {
                FUN_0042c8b0(0x93);
                if (param_1[0x1b7] == 1)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1c, 10, 0);
                }
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0xf)
                {
                    param_1[0x3c] = -0xf;
                }
                if (0x37 < param_1[0x3c])
                {
                    param_1[0x3c] = 0x37;
                }
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    FUN_00435000(0, 1, 0, (float)param_1[0x3c], 0);
                }
                else
                {
                    FUN_00435000(0, 3, 0, (float)param_1[0x3c], 0);
                }
            }
            if (param_1[0x2b7d] == 1)
            {
                if ((param_1[0x2b81] < 4) || (0x13 < param_1[0x2b81]))
                {
                    FUN_00434bd0();
                }
                else
                {
                    FUN_00434b90(0);
                }
            }
            break;
        case 0x195:
            FUN_00434a70(0, 2);
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
            }
            if (param_1[0x2b81] < 10)
            {
                FUN_0042db10(0, 0x41a00000);
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 0.25);
            if ((float)param_1[0x15] < 0.0)
            {
                param_1[0x15] = 0;
            }
            if (param_1[0x2b81] == 0)
            {
                param_1[0x18] = -0x3d4c0000;
                param_1[0x15] = 0x41700000;
            }
            if (param_1[0x2b81] == 10)
            {
                FUN_0042c8b0(0x93);
                if (param_1[0x1b7] == 1)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1c, 10, 0);
                }
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0x1e)
                {
                    param_1[0x3c] = -0x1e;
                }
                if (0x1e < param_1[0x3c])
                {
                    param_1[0x3c] = 0x1e;
                }
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    fVar11 = (float)param_1[0x3c];
                    fVar8  = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar5  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar8, fVar11);
                    fVar10 = (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[7]);
                    fVar9  = (float)param_1[6] + 70.0;
                    fVar5  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar9, fVar10);
                    FUN_00435450(0,
                                 (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[5]),
                                 fVar9,
                                 fVar10,
                                 fVar8,
                                 fVar11);
                }
                else
                {
                    fVar11 = (float)param_1[0x3c];
                    fVar8  = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar5  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar8, fVar11);
                    fVar10 = (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[7]);
                    fVar9  = (float)param_1[6] + 70.0;
                    fVar5  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar9, fVar10);
                    FUN_00435450(2,
                                 (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[5]),
                                 fVar9,
                                 fVar10,
                                 fVar8,
                                 fVar11);
                }
            }
            if ((param_1[0x2b81] < 7) || (0x19 < param_1[0x2b81]))
            {
                FUN_00434bd0();
            }
            else
            {
                FUN_00434b90(0);
            }
            break;
        case 0x196:
            FUN_00434a70(0, 2);
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
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00422900();
            }
            if (param_1[0x2b81] < 10)
            {
                FUN_0042db10(0, 0x41a00000);
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 0.25);
            if ((float)param_1[0x15] < 0.0)
            {
                param_1[0x15] = 0;
            }
            if (param_1[0x2b81] == 0)
            {
                param_1[0x18] = 0x42b40000;
                param_1[0x15] = 0x41700000;
            }
            if (param_1[0x2b81] == 10)
            {
                FUN_0042c8b0(0x93);
                if (param_1[0x1b7] == 1)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1c, 10, 0);
                }
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0x1e)
                {
                    param_1[0x3c] = -0x1e;
                }
                if (0x1e < param_1[0x3c])
                {
                    param_1[0x3c] = 0x1e;
                }
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    fVar11 = (float)param_1[0x3c];
                    fVar8  = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar5  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar8, fVar11);
                    fVar10 = (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[7]);
                    fVar9  = (float)param_1[6] + 70.0;
                    fVar5  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar9, fVar10);
                    FUN_00435450(0,
                                 (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[5]),
                                 fVar9,
                                 fVar10,
                                 fVar8,
                                 fVar11);
                }
                else
                {
                    fVar11 = (float)param_1[0x3c];
                    fVar8  = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar5  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar8, fVar11);
                    fVar10 = (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[7]);
                    fVar9  = (float)param_1[6] + 70.0;
                    fVar5  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar9, fVar10);
                    FUN_00435450(2,
                                 (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[5]),
                                 fVar9,
                                 fVar10,
                                 fVar8,
                                 fVar11);
                }
            }
            if ((param_1[0x2b81] < 7) || (0x19 < param_1[0x2b81]))
            {
                FUN_00434bd0();
            }
            else
            {
                FUN_00434b90(0);
            }
            break;
        case 0x197:
            FUN_00434a70(0, 2);
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
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 1.0);
            if ((float)param_1[0x15] < 0.0)
            {
                param_1[0x15] = 0;
            }
            if (param_1[0x2b81] < 0xb)
            {
                FUN_0042db10(0, 0x41a00000);
            }
            if (param_1[0x2b81] == 0)
            {
                param_1[0x18] = 0x43340000;
                param_1[0x15] = 0x41700000;
            }
            if (param_1[0x2b81] == 0xb)
            {
                FUN_0042c8b0(0x93);
                if (param_1[0x1b7] == 1)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1c, 10, 0);
                }
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0x1e)
                {
                    param_1[0x3c] = -0x1e;
                }
                if (0x1e < param_1[0x3c])
                {
                    param_1[0x3c] = 0x1e;
                }
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    fVar11 = (float)param_1[0x3c];
                    fVar8  = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar5  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar8, fVar11);
                    fVar10 = (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[7]);
                    fVar9  = (float)param_1[6] + 70.0;
                    fVar5  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar9, fVar10);
                    FUN_00435450(0,
                                 (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[5]),
                                 fVar9,
                                 fVar10,
                                 fVar8,
                                 fVar11);
                }
                else
                {
                    fVar11 = (float)param_1[0x3c];
                    fVar8  = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar5  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar8, fVar11);
                    fVar10 = (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[7]);
                    fVar9  = (float)param_1[6] + 70.0;
                    fVar5  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19], fVar9, fVar10);
                    FUN_00435450(2,
                                 (float)(fVar5 * (float10)20.0 + (float10)(float)param_1[5]),
                                 fVar9,
                                 fVar10,
                                 fVar8,
                                 fVar11);
                }
            }
            break;
        case 0x199:
            FUN_00434a70(0, 2);
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
        case 0x1c2:
            FUN_00434a70(0, 2);
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
            }
            if (param_1[0x2b81] < 10)
            {
                FUN_0042dc20(0, 0x41700000);
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
            if ((float)param_1[0x15] < 0.0)
            {
                param_1[0x15] = 0;
            }
            if (param_1[0x2b81] == 10)
            {
                if (param_1[0x1c8] < 3)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1d, 10, 0);
                }
                FUN_0042c8b0(0x93);
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0x28)
                {
                    param_1[0x3c] = -0x28;
                }
                if (0x28 < param_1[0x3c])
                {
                    param_1[0x3c] = 0x28;
                }
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    FUN_00435000(0, 4, 0x42200000, (float)param_1[0x3c], 0);
                }
                else
                {
                    FUN_00435000(0, 6, 0x42200000, (float)param_1[0x3c], 0);
                }
            }
            if (param_1[0x2b81] == 0x19)
            {
                FUN_0042c8b0(0x93);
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0x28)
                {
                    param_1[0x3c] = -0x28;
                }
                if (0x28 < param_1[0x3c])
                {
                    param_1[0x3c] = 0x28;
                }
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    FUN_00435000(0, 5, 0xc2200000, (float)param_1[0x3c], 0);
                }
                else
                {
                    FUN_00435000(0, 7, 0xc2200000, (float)param_1[0x3c], 0);
                }
            }
            if ((param_1[0x2b81] < 1) || (0x32 < param_1[0x2b81]))
            {
                FUN_00434bd0();
            }
            else
            {
                FUN_00434b90(0);
            }
            break;
        case 0x1c3:
            FUN_00434a70(0, 2);
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
            }
            if (param_1[0x2b81] < 10)
            {
                FUN_0042dc20(0, 0x41700000);
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 0.2);
            if ((float)param_1[0x15] < 0.0)
            {
                param_1[0x15] = 0;
            }
            if (param_1[0x2b81] == 10)
            {
                if (param_1[0x1c8] < 3)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1d, 10, 0);
                }
                FUN_0042c8b0(0x93);
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0x28)
                {
                    param_1[0x3c] = -0x28;
                }
                if (0x28 < param_1[0x3c])
                {
                    param_1[0x3c] = 0x28;
                }
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    FUN_00435000(0, 4, 0x42200000, (float)param_1[0x3c], 0);
                }
                else
                {
                    FUN_00435000(0, 6, 0x42200000, (float)param_1[0x3c], 0);
                }
            }
            if (param_1[0x2b81] == 0x19)
            {
                FUN_0042c8b0(0x93);
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0x28)
                {
                    param_1[0x3c] = -0x28;
                }
                if (0x28 < param_1[0x3c])
                {
                    param_1[0x3c] = 0x28;
                }
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    FUN_00435000(0, 5, 0xc2200000, (float)param_1[0x3c], 0);
                }
                else
                {
                    FUN_00435000(0, 7, 0xc2200000, (float)param_1[0x3c], 0);
                }
            }
            if ((param_1[0x2b81] < 1) || (0x32 < param_1[0x2b81]))
            {
                FUN_00434bd0();
            }
            else
            {
                FUN_00434b90(0);
            }
            break;
        case 0x1c4:
            FUN_00434a70(0, 2);
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
            }
            if (param_1[0x2b81] < 10)
            {
                FUN_0042dc20(0, 0x41700000);
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 0.2);
            if ((float)param_1[0x15] < 0.0)
            {
                param_1[0x15] = 0;
            }
            if ((param_1[0x2b81] == 10) || (param_1[0x2b81] == 0x19))
            {
                FUN_0042c8b0(0x93);
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0x28)
                {
                    param_1[0x3c] = -0x28;
                }
                if (0x28 < param_1[0x3c])
                {
                    param_1[0x3c] = 0x28;
                }
                FUN_004230e0();
                FUN_00435000(0, 4, 0, (float)param_1[0x3c], 0);
            }
            if ((param_1[0x2b81] < 1) || (0x32 < param_1[0x2b81]))
            {
                FUN_00434bd0();
            }
            else
            {
                FUN_00434b90(0);
            }
            break;
        case 0x1c5:
            FUN_00434a70(0, 2);
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
            }
            if (param_1[0x2b81] < 10)
            {
                FUN_0042dc20(0, 0x41700000);
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 0.2);
            if ((float)param_1[0x15] < 0.0)
            {
                param_1[0x15] = 0;
            }
            if ((param_1[0x2b81] == 10) || (param_1[0x2b81] == 0x19))
            {
                FUN_0042c8b0(0x93);
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0x28)
                {
                    param_1[0x3c] = -0x28;
                }
                if (0x28 < param_1[0x3c])
                {
                    param_1[0x3c] = 0x28;
                }
                FUN_004230e0();
                FUN_00435000(0, 4, 0, (float)param_1[0x3c], 0);
            }
            if ((param_1[0x2b81] < 1) || (0x32 < param_1[0x2b81]))
            {
                FUN_00434bd0();
            }
            else
            {
                FUN_00434b90(0);
            }
            break;
        case 0x1c6:
            FUN_00434a70(0, 2);
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
            }
            if (param_1[0x2b81] < 10)
            {
                FUN_0042dc20(0, 0x41700000);
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 0.2);
            if ((float)param_1[0x15] < 0.0)
            {
                param_1[0x15] = 0;
            }
            if ((param_1[0x2b81] == 10) || (param_1[0x2b81] == 0x19))
            {
                FUN_0042c8b0(0x93);
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0x28)
                {
                    param_1[0x3c] = -0x28;
                }
                if (0x28 < param_1[0x3c])
                {
                    param_1[0x3c] = 0x28;
                }
                FUN_004230e0();
                FUN_00435000(0, 4, 0, (float)param_1[0x3c], 0);
            }
            if ((param_1[0x2b81] < 1) || (0x32 < param_1[0x2b81]))
            {
                FUN_00434bd0();
            }
            else
            {
                FUN_00434b90(0);
            }
            break;
        case 0x1cc:
            FUN_00434a70(0, 2);
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0x2b);
                return;
            }
            if (((char)param_1[0x21] != '\0') && ((float)param_1[0x10] < 0.0))
            {
                FUN_00421080(0x1d5);
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00422900();
            }
            if (param_1[0x2b81] < 10)
            {
                FUN_0042dc20(0, 0x41900000);
            }
            if (param_1[0x2b81] == 0)
            {
                param_1[0x15] = (int)((float)param_1[0x15] * 0.5);
            }
            if (param_1[0x2b81] == 10)
            {
                if (param_1[0x1c8] < 3)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1d, 10, 0);
                }
                FUN_0042c8b0(0x93);
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0x28)
                {
                    param_1[0x3c] = -0x28;
                }
                if (0x28 < param_1[0x3c])
                {
                    param_1[0x3c] = 0x28;
                }
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    FUN_00435000(0, 4, 0x42200000, (float)param_1[0x3c], 0);
                }
                else
                {
                    FUN_00435000(0, 6, 0x42200000, (float)param_1[0x3c], 0);
                }
            }
            if (param_1[0x2b81] == 0x19)
            {
                FUN_0042c8b0(0x93);
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0x28)
                {
                    param_1[0x3c] = -0x28;
                }
                if (0x28 < param_1[0x3c])
                {
                    param_1[0x3c] = 0x28;
                }
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    FUN_00435000(0, 5, 0xc2200000, (float)param_1[0x3c], 0);
                }
                else
                {
                    FUN_00435000(0, 7, 0xc2200000, (float)param_1[0x3c], 0);
                }
            }
            if ((param_1[0x2b81] < 1) || (0x32 < param_1[0x2b81]))
            {
                FUN_00434bd0();
            }
            else
            {
                FUN_00434b90(0);
            }
            param_1[0x16] = 0x3f000000;
            param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
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
