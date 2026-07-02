// ============================================
// Address:  0x0057f600
// Original: FUN_0057f600
// Status:   unreviewed
// ============================================

void __fastcall FUN_0057f600(int *param_1)

{
    char cVar1;
    short sVar2;
    uint uVar3;
    int iVar4;
    undefined4 *puVar5;
    float10 fVar6;
    float10 fVar7;
    float10 fVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    int local_20;
    int local_1c;
    float local_18;
    float local_8;

    if (param_1[0x28] != 0)
    {
        return;
    }
    FUN_00434a70(0, 0);
    FUN_00434a70(1, 1);
    FUN_00434bd0();
    iVar4 = param_1[0x2b7b];
    if (iVar4 < 0x15f)
    {
        if (iVar4 == 0x15e)
        {
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0);
                FUN_00434a70(0, 0);
                FUN_00434a70(1, 1);
                return;
            }
            if ((char)param_1[0x21] == '\0')
            {
                FUN_00421080(0x2b);
                param_1[0x16] = 0x3f000000;
                FUN_00434a70(0, 0);
                FUN_00434a70(1, 1);
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00422900();
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                param_1[0x15] = 0;
                param_1[0x3a] = 0;
                param_1[0x3b] = 0;
                param_1[0x3c] = 0;
                FUN_004223d0(0x21, 0x14, 0);
            }
            if (param_1[0x3a] < 0x1e)
            {
                param_1[0x3a] = param_1[0x3a] + 1;
                FUN_0042db10(0, 0x41200000);
                param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
                if ((float)param_1[0x15] < 0.0)
                {
                    param_1[0x15] = 0;
                }
            }
            else
            {
                param_1[0x15] = 0;
            }
            if (param_1[0x2b81] < 0x28)
            {
                FUN_0042dc20(0, 0x40400000);
            }
            if (param_1[0x3b] < 5)
            {
                FUN_00434a70(0, 2);
                FUN_00434a70(1, 3);
            }
            if (param_1[0x2b81] == 0x1e)
            {
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3d] = iVar4;
                if (param_1[0x3d] < -0x1e)
                {
                    param_1[0x3d] = -0x1e;
                }
                if (0x1e < param_1[0x3d])
                {
                    param_1[0x3d] = 0x1e;
                }
                FUN_0042c8b0(0x92);
                param_1[0x3b] = param_1[0x3b] + 1;
                param_1[0x3b] = 0;
                while (param_1[0x3b] < 5)
                {
                    FUN_004230e0();
                    FUN_004230e0();
                    fVar12 = (float)param_1[0x3b] * 5.0 + 5.0;
                    fVar10 = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar6  = (float10)FUN_0065d010(param_1[0x17], fVar10, fVar12);
                    fVar11 = (float)param_1[7];
                    fVar8  = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
                    fVar11 = (float)((float10)(float)(fVar6 * (float10)50.0 + (float10)fVar11) -
                                     fVar8 * (float10)50.0);
                    fVar9  = (float)param_1[6] + 50.0;
                    fVar6  = (float10)FUN_0065d050(param_1[0x17], fVar9, fVar11);
                    fVar13 = (float)param_1[5];
                    fVar8  = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
                    FUN_00435450(10,
                                 (float)((float10)(float)(fVar6 * (float10)50.0 + (float10)fVar13) -
                                         fVar8 * (float10)50.0),
                                 fVar9,
                                 fVar11,
                                 fVar10,
                                 fVar12);
                    fVar12 = (float)param_1[0x3b] * 5.0 + 5.0;
                    fVar10 = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar6  = (float10)FUN_0065d010(param_1[0x17], fVar10, fVar12);
                    fVar11 = (float)param_1[7];
                    fVar8  = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
                    fVar11 = (float)(fVar8 * (float10)50.0 +
                                     (float10)(float)(fVar6 * (float10)50.0 + (float10)fVar11));
                    fVar9  = (float)param_1[6] + 50.0;
                    fVar6  = (float10)FUN_0065d050(param_1[0x17], fVar9, fVar11);
                    fVar13 = (float)param_1[5];
                    fVar8  = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
                    FUN_00435450(10,
                                 (float)(fVar8 * (float10)50.0 +
                                         (float10)(float)(fVar6 * (float10)50.0 + (float10)fVar13)),
                                 fVar9,
                                 fVar11,
                                 fVar10,
                                 fVar12);
                    param_1[0x3b] = param_1[0x3b] + 1;
                }
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
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    FUN_00422900();
                    FUN_00423000();
                }
                if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0))
                {
                    param_1[0x18] = 0;
                    FUN_0042c800(0);
                    FUN_0042c840(1);
                    param_1[0x3a] = 0;
                    param_1[0x3b] = 0;
                    param_1[0x3c] = 1;
                    param_1[0x15] = 0x41880000;
                    FUN_0042db10(0, 0x43340000);
                    fVar6 = (float10)FUN_0042d980();
                    if (fVar6 < (float10)360000.0)
                    {
                        param_1[0x3c] = 1;
                        param_1[0x15] = 0x41a00000;
                    }
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
                if ((param_1[0x2b7d] == 0) && (param_1[0x3c] == 1))
                {
                    FUN_0042db10(0, 0x40e00000);
                }
                if (param_1[0x2b7d] == 1)
                {
                    if (param_1[0x3c] == 1)
                    {
                        FUN_0042db10(0, 0x40e00000);
                    }
                    fVar6 = (float10)FUN_0042d980();
                    if ((fVar6 < (float10)60000.0) || (param_1[0x3c] == 0))
                    {
                        FUN_00421100(2);
                        return;
                    }
                }
                if (param_1[0x2b7d] == 2)
                {
                    if (param_1[0x2b81] == 3)
                    {
                        FUN_0042c880(0x3c);
                        fVar6 = (float10)FUN_0042d980();
                        if ((((float10)60000.0 <= fVar6) ||
                             (fVar6 = (float10)FUN_0042df90(param_1[0x19]),
                              (float10)30.0 <= fVar6)) ||
                            (*(char *)((int)param_1 + 0xaec3) != '\x01'))
                        {
                            fVar6 = (float10)FUN_0042d980();
                            if ((((float10)60000.0 <= fVar6) ||
                                 (fVar6 = (float10)FUN_0042df90(param_1[0x19]),
                                  (float10)30.0 <= fVar6)) ||
                                (*(char *)((int)param_1 + 0xaebe) != '\x01'))
                            {
                                fVar6 = (float10)FUN_0042d980();
                                if ((((float10)60000.0 <= fVar6) ||
                                     (fVar6 = (float10)FUN_0042df90(param_1[0x19]),
                                      (float10)30.0 <= fVar6)) ||
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
                    if ((3 < param_1[0x2b81]) && (param_1[0x15] = (int)((float)param_1[0x15] - 1.5),
                                                  (float)param_1[0x15] < 0.0))
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
                    goto switchD_0057f698_caseD_1;
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
                    param_1[0x15] = 0x40d00000;
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
                        (param_1[0x20d] = param_1[0x20d] + -9, param_1[0x20d] < 0))
                    {
                        param_1[0x20d] = 0;
                    }
                    if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] % 0x24 == 0xc))
                    {
                        FUN_0042c8b0(5);
                    }
                    if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] % 0x24 == 0x1e))
                    {
                        FUN_0042c8b0(6);
                    }
                    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                    {
                        param_1[0x18] = 0;
                        param_1[0x19] = 0;
                        fVar6         = (float10)FUN_0042df90(param_1[0x19]);
                        if ((float10)12.0 <= fVar6)
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
                        param_1[0x15] = 0x41500000;
                        param_1[0x3a] = 0;
                    }
                    if (param_1[0x2b7d] == 1)
                    {
                        param_1[0x21d] = 0x40800000;
                        param_1[0x15]  = 0x41500000;
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
                        if ((param_1[0x2b81] == 2) && (param_1[0x3a] < 0xf))
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
                        param_1[0x20d] = param_1[0x20d] + -8;
                        if (param_1[0x20d] < 0)
                        {
                            param_1[0x20d] = 0;
                        }
                    }
                    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                    {
                        param_1[0x19]   = 0;
                        param_1[0x18]   = -0x3d4c0000;
                        param_1[0x15]   = 0x418c0000;
                        param_1[0x2bd2] = param_1[0x2bd2] + 1;
                    }
                    if (param_1[0x2b7d] == 1)
                    {
                        param_1[0x18] = -0x3d4c0000;
                    }
                    if ((param_1[0x2b7d] < 2) && (param_1[0x15] = (int)((float)param_1[0x15] - 0.5),
                                                  (float)param_1[0x15] < 12.0))
                    {
                        param_1[0x15] = 0x41400000;
                    }
                    if (param_1[0x2b7d] == 2)
                    {
                        if ((char)param_1[0x21] == '\0')
                        {
                            param_1[0x16] = 0x3f000000;
                            FUN_00421080(0x2b);
                            return;
                        }
                        param_1[0x15] = (int)((float)param_1[0x15] - 0.7);
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
                        param_1[0x20d] = param_1[0x20d] + -8;
                        if (param_1[0x20d] < 0)
                        {
                            param_1[0x20d] = 0;
                        }
                    }
                    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                    {
                        param_1[0x19]   = 0;
                        param_1[0x18]   = 0x42b40000;
                        param_1[0x15]   = 0x418c0000;
                        param_1[0x2bd2] = param_1[0x2bd2] + 1;
                    }
                    if (param_1[0x2b7d] == 1)
                    {
                        param_1[0x18] = 0x42b40000;
                    }
                    if ((param_1[0x2b7d] < 2) && (param_1[0x15] = (int)((float)param_1[0x15] - 0.5),
                                                  (float)param_1[0x15] < 12.0))
                    {
                        param_1[0x15] = 0x41400000;
                    }
                    if ((param_1[0x2b7d] == 2) &&
                        (param_1[0x15] = (int)((float)param_1[0x15] - 0.7),
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
                        (param_1[0x20d] = param_1[0x20d] + -8, param_1[0x20d] < 0))
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
                        param_1[0x15]  = 0x41600000;
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
                        param_1[0x15]  = 0x41600000;
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
                if ((param_1[0x3b] != 0) && (param_1[0x1a1] = 2, param_1[0x2b81] < 0xc))
                {
                    FUN_0042db10(0, 0x41700000);
                }
                if (param_1[0x2b81] == 0)
                {
                    FUN_00422900();
                    FUN_00423000();
                    param_1[0x18] = 0;
                    param_1[0x15] = 0x41700000;
                    FUN_0042c800(0);
                    FUN_0042c840(1);
                }
                if (param_1[0x2b81] == 0xb)
                {
                    FUN_0042c880(0x3d);
                    FUN_004223d0(2, 10, 0);
                }
                if (param_1[0x2b81] == 0xe)
                {
                    param_1[0x15]  = 0;
                    param_1[0x21d] = 0;
                }
                uVar3 = FUN_0042c7b0();
                if ((uVar3 & 2) != 0)
                {
                    FUN_00421080(0x188);
                    FUN_0042c800(0);
                    return;
                }
                if ((param_1[0x2b81] < 0xe) &&
                    (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 0.0))
                {
                    param_1[0x15] = 0;
                }
                break;
            default:
            switchD_0057f698_caseD_1:
                FUN_00428510();
                return;
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
                    FUN_0042db10(0, 0x43340000);
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
                    FUN_0042db10(0, 0x41200000);
                }
                if (param_1[0x2b7d] == 1)
                {
                    param_1[0x15] = 0x41c80000;
                    fVar6         = (float10)FUN_0042d980();
                    if ((fVar6 < (float10)90000.0) || (param_1[0x2b81] == 2))
                    {
                        FUN_00421100(2);
                    }
                }
                if ((param_1[0x2b7d] == 1) || ((param_1[0x2b7d] == 2 && (param_1[0x2b81] < 8))))
                {
                    FUN_0042db10(0, 0x40400000);
                }
                if (param_1[0x2b7d] == 2)
                {
                    if (param_1[0x2b81] == 10)
                    {
                        FUN_0042c880(0x3e);
                        FUN_004223d0(2, 10, 0);
                    }
                    if (param_1[0x2b81] == 0x11)
                    {
                        param_1[0x15] = 0;
                    }
                }
                if (((0 < param_1[0x2b7d]) && (param_1[0x2b81] < 0x11)) &&
                    (param_1[0x15] = (int)((float)param_1[0x15] - 1.5), (float)param_1[0x15] < 5.0))
                {
                    param_1[0x15] = 0x40a00000;
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
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    FUN_00422900();
                    FUN_00423000();
                }
                if (param_1[0x2b81] < 0x19)
                {
                    FUN_0042db10(0, 0x41200000);
                }
                if (param_1[0x2b81] == 0)
                {
                    FUN_0042db10(0, 0x43340000);
                    param_1[0x15] = 0;
                    param_1[0x18] = 0;
                    FUN_0042c800(0);
                    FUN_0042c840(1);
                }
                if (param_1[0x2b81] == 0xd)
                {
                    param_1[0x15] = 0x41940000;
                    FUN_004223d0(2, 10, 0);
                    FUN_0042c8b0(0x3f);
                }
                if ((0x14 < param_1[0x2b81]) && (param_1[0x15] = (int)((float)param_1[0x15] - 0.75),
                                                 (float)param_1[0x15] < 0.0))
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
                if ((param_1[0x2b7d] == 2) && (0xd < param_1[0x2b81]))
                {
                    param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
                }
                if ((((char)param_1[0x21] != '\0') && (param_1[0x2b7d] == 2)) &&
                    (0x14 < param_1[0x2b81]))
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
                        local_18 = (float)param_1[0x10];
                    }
                    else
                    {
                        local_18 = 3.0;
                    }
                    if (-3.0 <= local_18)
                    {
                        if ((float)param_1[0x10] <= 3.0)
                        {
                            local_20 = param_1[0x10];
                        }
                        else
                        {
                            local_20 = 0x40400000;
                        }
                        local_1c = local_20;
                    }
                    else
                    {
                        local_1c = -0x3fc00000;
                    }
                    param_1[0x10] = local_1c;
                    param_1[0x15] = 0x41380000;
                    if ((param_1[0x2b81] == 0) &&
                        (fVar6 = (float10)FUN_0042d980(), fVar6 < (float10)360000.0))
                    {
                        FUN_0042db10(0, 0x43340000);
                        param_1[0x3c] = 0xbe;
                    }
                    fVar6 = (float10)FUN_00423580(param_1[0x10], param_1[0x15]);
                    param_1[0xb] =
                        (int)(float)((fVar6 / (float10)3.1415927) * (float10)180.0 + (float10)15.0);
                    param_1[0xb6] = 0x428c0000;
                }
                param_1[0x3b] = param_1[0x3b] + 1;
                if ((param_1[0x2b7d] < 2) && (0 < param_1[0x3c]))
                {
                    fVar6   = (float10)FUN_00423580(param_1[0x10], param_1[0x15]);
                    local_8 = (float)((fVar6 / (float10)3.1415927) * (float10)180.0);
                    fVar6   = (float10)FUN_0042da80();
                    fVar11  = (float)(fVar6 + (float10)10.0);
                    if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                    {
                        fVar6   = (float10)FUN_0042da80();
                        local_8 = (float)(fVar6 + (float10)10.0);
                    }
                    if ((fVar11 < local_8) && (local_8 = local_8 - 5.0, local_8 < fVar11))
                    {
                        local_8 = fVar11;
                    }
                    if ((local_8 < fVar11) && (local_8 = local_8 + 5.0, fVar11 < local_8))
                    {
                        local_8 = fVar11;
                    }
                    if (35.0 < local_8)
                    {
                        local_8 = 35.0;
                    }
                    if (local_8 < -25.0)
                    {
                        local_8 = -25.0;
                    }
                    iVar4         = param_1[0x3c];
                    fVar6         = (float10)FUN_0065d050(local_8);
                    param_1[0x15] = (int)(float)(fVar6 * (float10)((float)iVar4 * 0.1));
                    iVar4         = param_1[0x3c];
                    fVar6         = (float10)FUN_0065d010(local_8);
                    param_1[0x10] = (int)(float)(fVar6 * (float10)((float)iVar4 * 0.1));
                    fVar6         = (float10)FUN_00423580(param_1[0x10], param_1[0x15]);
                    param_1[0xb] =
                        (int)(float)((fVar6 / (float10)3.1415927) * (float10)180.0 + (float10)15.0);
                    param_1[0xb6] = 0x428c0000;
                    FUN_0042db10(0, 0x40a00000);
                    param_1[0x3c] = param_1[0x3c] + -4;
                    if (param_1[0x3c] < 0x6e)
                    {
                        param_1[0x3c] = 0x6e;
                    }
                }
                if ((param_1[0x2b7d] == 1) && (FUN_0042db10(0, 0x40400000), 10 < param_1[0x2b81]))
                {
                    fVar6 = (float10)FUN_0042d980();
                    fVar8 = (float10)FUN_0042da30();
                    fVar7 = (float10)FUN_0042da30();
                    if ((fVar7 * (float10)(float)fVar8 + (float10)(float)fVar6 <
                         (float10)60000.0) ||
                        ((0x19 < param_1[0x2b81] || (param_1[0x3c] == 0))))
                    {
                        FUN_00421100(2);
                        return;
                    }
                }
                if (param_1[0x2b7d] == 2)
                {
                    if (param_1[0x2b81] < 5)
                    {
                        FUN_0042db10(0, 0x40400000);
                    }
                    if (param_1[0x2b81] == 7)
                    {
                        FUN_0042c880(0x3e);
                        fVar6 = (float10)FUN_0042d980();
                        if ((((float10)40000.0 <= fVar6) ||
                             (fVar6 = (float10)FUN_0042df90(param_1[0x19]),
                              (float10)30.0 <= fVar6)) ||
                            (*(char *)((int)param_1 + 0xaec3) != '\x01'))
                        {
                            fVar6 = (float10)FUN_0042d980();
                            if ((((float10)40000.0 <= fVar6) ||
                                 (fVar6 = (float10)FUN_0042df90(param_1[0x19]),
                                  (float10)30.0 <= fVar6)) ||
                                (*(char *)((int)param_1 + 0xaebe) != '\x01'))
                            {
                                fVar6 = (float10)FUN_0042d980();
                                if ((((float10)40000.0 <= fVar6) ||
                                     (fVar6 = (float10)FUN_0042df90(param_1[0x19]),
                                      (float10)30.0 <= fVar6)) ||
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
                    FUN_00422900();
                    FUN_00423000();
                }
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
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
                if (param_1[0x2b7d] == 0)
                {
                    FUN_0042db10(0, 0x41700000);
                }
                if (param_1[0x2b7d] == 1)
                {
                    FUN_0042db10(0, 0x40800000);
                    param_1[0x15] = 0x41f00000;
                    fVar6         = (float10)FUN_0042d980();
                    if ((fVar6 < (float10)160000.0) || (2 < param_1[0x2b81]))
                    {
                        fVar6 = (float10)FUN_0042d980();
                        if (((float10)40000.0 <= fVar6) ||
                            ((fVar6 = (float10)FUN_0042df90(param_1[0x19]),
                              (float10)30.0 <= fVar6 ||
                                  (*(char *)((int)param_1 + 0xaec3) != '\x01'))))
                        {
                            fVar6 = (float10)FUN_0042d980();
                            if (((float10)40000.0 <= fVar6) ||
                                ((fVar6 = (float10)FUN_0042df90(param_1[0x19]),
                                  (float10)30.0 <= fVar6 ||
                                      (*(char *)((int)param_1 + 0xaebe) != '\x01'))))
                            {
                                fVar6 = (float10)FUN_0042d980();
                                if (((float10)40000.0 <= fVar6) ||
                                    ((fVar6 = (float10)FUN_0042df90(param_1[0x19]),
                                      (float10)30.0 <= fVar6 ||
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
                        FUN_00421100(2);
                        return;
                    }
                }
                if (param_1[0x2b7d] == 2)
                {
                    if (param_1[0x2b81] == 10)
                    {
                        FUN_0042c880(0x3e);
                        FUN_004223d0(2, 10, 0);
                    }
                    if (param_1[0x2b81] == 0x11)
                    {
                        param_1[0x15] = 0;
                    }
                }
                if (((0 < param_1[0x2b7d]) && (param_1[0x2b81] < 0x11)) &&
                    (param_1[0x15] = (int)((float)param_1[0x15] - 1.5), (float)param_1[0x15] < 5.0))
                {
                    param_1[0x15] = 0x40a00000;
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
                    param_1[0x3b] = 0;
                    param_1[0x3c] = 0;
                    param_1[0x15] = 0x41940000;
                    fVar6         = (float10)FUN_0042d980();
                    if (fVar6 < (float10)490000.0)
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
                    ((fVar6 = (float10)FUN_0042d980(),
                      fVar6 < (float10)60000.0 ||
                          ((0x14 < param_1[0x2b81] || (param_1[0x3c] == 0))))))
                {
                    FUN_00421100(2);
                    return;
                }
                if (param_1[0x2b7d] == 2)
                {
                    if (param_1[0x3b] == 1)
                    {
                        FUN_0042db10(0, 0x40e00000);
                    }
                    if (param_1[0x2b81] == 8)
                    {
                        FUN_0042c8b0(0x3f);
                        FUN_004223d0(2, 10, 0);
                    }
                    if (param_1[0x2b81] == 0x10)
                    {
                        param_1[0x15] = 0;
                    }
                }
                if ((1 < param_1[0x2b7d]) && (param_1[0x15] = (int)((float)param_1[0x15] - 0.35),
                                              (float)param_1[0x15] < 0.0))
                {
                    param_1[0x15] = 0;
                }
                break;
            case 0x14c:
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
                    param_1[0x10] = -0x3f000000;
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
                    if (0x1e < param_1[0x3a])
                    {
                        FUN_00421100(2);
                        param_1[0x15] = 0x41200000;
                        return;
                    }
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
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    param_1[0x18] = 0;
                    FUN_0042c800(0);
                    param_1[0x15] = 0x41700000;
                    FUN_0042c840(1);
                }
                uVar3 = FUN_0042c7b0();
                if ((uVar3 & 2) != 0)
                {
                    FUN_00421080(0x188);
                    FUN_0042c800(0);
                    return;
                }
                if (param_1[0x2b81] == 8)
                {
                    FUN_0042c880(0x3d);
                    FUN_004223d0(2, 10, 0);
                }
                if (param_1[0x2b81] < 8)
                {
                    FUN_0042db10(0, 0x41a00000);
                }
                if ((param_1[0x2b7d] == 0) &&
                    (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 0.0))
                {
                    param_1[0x15] = 0;
                }
                break;
            case 0x155:
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
                if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
                {
                    param_1[0x18] = 0;
                    FUN_0042c800(0);
                    param_1[0x15] = 0x41700000;
                    FUN_0042c840(1);
                }
                uVar3 = FUN_0042c7b0();
                if ((uVar3 & 2) != 0)
                {
                    FUN_00421080(0x188);
                    FUN_0042c800(0);
                    return;
                }
                if (param_1[0x2b81] == 8)
                {
                    FUN_0042c880(0x3d);
                    FUN_004223d0(3, 10, 0);
                }
                if (param_1[0x2b81] < 8)
                {
                    FUN_0042db10(0, 0x41c80000);
                }
                if ((param_1[0x2b7d] == 0) &&
                    (param_1[0x15] = (int)((float)param_1[0x15] - 1.0), (float)param_1[0x15] < 0.0))
                {
                    param_1[0x15] = 0;
                }
            }
        }
    }
    else
    {
        switch (iVar4)
        {
        case 0x168:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0x2b);
                param_1[0x16] = 0x3f000000;
                return;
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                param_1[0x3a] = 0;
                param_1[0x3b] = 0;
                param_1[0x3c] = 0;
                FUN_004223d0(0x21, 0x14, 0);
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00422900();
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                param_1[0x16] = 0x3f000000;
                param_1[0x15] = 0;
                param_1[0x10] = 0;
                param_1[0x3a] = 0;
                param_1[0x3b] = 0;
                param_1[0x3c] = 0;
            }
            if (param_1[0x3b] < 5)
            {
                FUN_00434a70(0, 2);
                FUN_00434a70(1, 3);
            }
            if (param_1[0x2b81] < 0x1e)
            {
                FUN_0042dc20(0, 0x41200000);
                param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
                if ((float)param_1[0x15] < 0.0)
                {
                    param_1[0x15] = 0;
                }
            }
            else
            {
                param_1[0x15] = (int)((float)param_1[0x15] + 0.5);
                if (-3.0 < (float)param_1[0x15])
                {
                    param_1[0x15] = -0x3fc00000;
                }
            }
            if (param_1[0x2b81] < 0x28)
            {
                FUN_0042dc20(0, 0x40400000);
            }
            if (0x1d < param_1[0x2b81])
            {
                param_1[0x10] = (int)((float)param_1[0x10] - 0.5);
            }
            param_1[0x16] = 0x3f000000;
            if (param_1[0x2b81] == 0x1e)
            {
                param_1[0x18] = 0;
                FUN_0042c8b0(0x92);
                param_1[0x3b] = param_1[0x3b] + 1;
                param_1[0x15] = -0x3ee00000;
                param_1[0x10] = 0x40a00000;
                FUN_0042c8b0(0x92);
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (0x14 < param_1[0x3c])
                {
                    param_1[0x3c] = 0x14;
                }
                if (param_1[0x3c] < -0x28)
                {
                    param_1[0x3c] = -0x28;
                }
                param_1[0x3b] = 0;
                while (param_1[0x3b] < 5)
                {
                    FUN_004230e0();
                    FUN_004230e0();
                    fVar12 = (float)param_1[0x3b] * 5.0 + (float)param_1[0x3c];
                    fVar10 = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar6  = (float10)FUN_0065d010(param_1[0x17], fVar10, fVar12);
                    fVar11 = (float)param_1[7];
                    fVar8  = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
                    fVar11 = (float)((float10)(float)(fVar6 * (float10)50.0 + (float10)fVar11) -
                                     fVar8 * (float10)50.0);
                    fVar9  = (float)param_1[6] + 50.0;
                    fVar6  = (float10)FUN_0065d050(param_1[0x17], fVar9, fVar11);
                    fVar13 = (float)param_1[5];
                    fVar8  = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
                    FUN_00435450(10,
                                 (float)((float10)(float)(fVar6 * (float10)50.0 + (float10)fVar13) -
                                         fVar8 * (float10)50.0),
                                 fVar9,
                                 fVar11,
                                 fVar10,
                                 fVar12);
                    fVar12 = (float)param_1[0x3b] * 5.0 + (float)param_1[0x3c];
                    fVar10 = (float)param_1[0x17] + (float)param_1[0x19];
                    fVar6  = (float10)FUN_0065d010(param_1[0x17], fVar10, fVar12);
                    fVar11 = (float)param_1[7];
                    fVar8  = (float10)FUN_0065d010((float)param_1[0x17] + 90.0);
                    fVar11 = (float)(fVar8 * (float10)50.0 +
                                     (float10)(float)(fVar6 * (float10)50.0 + (float10)fVar11));
                    fVar9  = (float)param_1[6] + 50.0;
                    fVar6  = (float10)FUN_0065d050(param_1[0x17], fVar9, fVar11);
                    fVar13 = (float)param_1[5];
                    fVar8  = (float10)FUN_0065d050((float)param_1[0x17] + 90.0);
                    FUN_00435450(10,
                                 (float)(fVar8 * (float10)50.0 +
                                         (float10)(float)(fVar6 * (float10)50.0 + (float10)fVar13)),
                                 fVar9,
                                 fVar11,
                                 fVar10,
                                 fVar12);
                    param_1[0x3b] = param_1[0x3b] + 1;
                }
            }
            break;
        case 0x169:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0);
                return;
            }
            FUN_00434a70(0, 0);
            FUN_00434a70(1, 1);
            param_1[0x16]  = 0;
            param_1[0x10]  = 0;
            param_1[0x18]  = 0;
            param_1[0x21d] = 0;
            if ((0.0 < (float)param_1[0x15]) &&
                (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0))
            {
                param_1[0x15] = 0;
            }
            if (((float)param_1[0x15] < 0.0) &&
                (param_1[0x15] = (int)((float)param_1[0x15] + 0.5), 0.0 < (float)param_1[0x15]))
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
            break;
        default:
            goto switchD_0057f698_caseD_1;
        case 0x172:
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
                FUN_004223d0(0x27, 0x14, 1);
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
            if ((float)param_1[0x15] < 0.0)
            {
                param_1[0x15] = 0;
            }
            if ((param_1[0x2b7d] == 1) && (param_1[0x2b81] == 0xf))
            {
                FUN_0042c8b0(0xa1);
                FUN_00435450(0xc,
                             param_1[5],
                             param_1[6],
                             param_1[7],
                             (float)param_1[0x17] + (float)param_1[0x19],
                             0);
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
            if (param_1[0x2b81] < 0xc)
            {
                FUN_0042db10(0, 0x41a00000);
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 0.5);
            if ((float)param_1[0x15] < 0.0)
            {
                param_1[0x15] = 0;
            }
            if (param_1[0x2b81] == 0xc)
            {
                if (param_1[0x1b7] < 4)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1b, 10, 0);
                }
                FUN_0042c8b0(0x80);
                param_1[0x15] = -0x3ee00000;
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
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar10, fVar11);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar10, fVar11);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                }
                else
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar10, fVar11);
                    FUN_00435450(3,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar10, fVar11);
                    FUN_00435450(2,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 4.0;
                    fVar6 =
                        (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19] + 4.0);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6 =
                        (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19] + 4.0);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0;
                    fVar6 =
                        (float10)FUN_0065d010(((float)param_1[0x17] + (float)param_1[0x19]) - 4.0);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6 =
                        (float10)FUN_0065d050(((float)param_1[0x17] + (float)param_1[0x19]) - 4.0);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
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
            if (param_1[0x2b81] < 0xf)
            {
                FUN_0042db10(0, 0x41a00000);
            }
            if (param_1[0x2b81] == 0)
            {
                param_1[0x18] = 0x43340000;
                param_1[0x15] = 0x40a00000;
            }
            if (param_1[0x2b81] == 0xf)
            {
                FUN_004223d0(0x1b, 10, 0);
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3a] = iVar4;
                if (param_1[0x3a] < -0x28)
                {
                    param_1[0x3a] = -0x28;
                }
                if (0x28 < param_1[0x3a])
                {
                    param_1[0x3a] = 0x28;
                }
                FUN_0042c8b0(0x48);
                FUN_00435000(0, 0, 0, (float)param_1[0x3a], 0);
                FUN_00435000(1, 0, 0, (float)param_1[0x3a], 0);
            }
            if ((((0x1d < param_1[0x2b81]) && (1 < param_1[0x1b7])) && (0 < param_1[0xae])) &&
                (param_1[0xae] < 10))
            {
                if (0 < param_1[0x9e])
                {
                    FUN_00421080(0x19b);
                    return;
                }
                if (param_1[0x9e] < 0)
                {
                    FUN_00421080(0x19c);
                    return;
                }
                if (param_1[0x9f] < 0)
                {
                    FUN_00421080(0x19a);
                    return;
                }
                if (0 < param_1[0x9f])
                {
                    FUN_00421080(0x191);
                    return;
                }
            }
            break;
        case 0x192:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                FUN_00421080(0x2b);
                return;
            }
            if ((char)param_1[0x21] != '\0')
            {
                FUN_00421080(0x193);
                return;
            }
            if ((param_1[0x2b81] == 0) && (param_1[0x2b7d] == 0))
            {
                FUN_00422900();
            }
            if (param_1[0x2b81] < 0xc)
            {
                FUN_0042dc20(0, 0x41a00000);
            }
            if (param_1[0x2b81] == 0xc)
            {
                if (param_1[0x1b7] < 4)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1b, 10, 0);
                }
                FUN_0042c8b0(0x80);
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
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar10, fVar11);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar10, fVar11);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                }
                else
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar10, fVar11);
                    FUN_00435450(3,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar10, fVar11);
                    FUN_00435450(2,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 4.0;
                    fVar6 =
                        (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19] + 4.0);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6 =
                        (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19] + 4.0);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0;
                    fVar6 =
                        (float10)FUN_0065d010(((float)param_1[0x17] + (float)param_1[0x19]) - 4.0);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6 =
                        (float10)FUN_0065d050(((float)param_1[0x17] + (float)param_1[0x19]) - 4.0);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                }
            }
            if ((float)param_1[0x16] == 0.0)
            {
                param_1[0x16] = 0x3f000000;
            }
            param_1[0x10] = (int)((float)param_1[0x10] - (float)param_1[0x16]);
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
            if (param_1[0x2b81] < 0x16)
            {
                FUN_0042db10(0, 0x40a00000);
            }
            else if (param_1[0x2b81] < 0x20)
            {
                FUN_0042db10(0, 0x40000000);
            }
            if ((0x20 < param_1[0x2b81]) &&
                (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0))
            {
                param_1[0x15] = 0;
            }
            if (param_1[0x2b81] == 0)
            {
                param_1[0x18] = 0;
                param_1[0x15] = 0x41200000;
                param_1[0x3b] = 0;
            }
            if (param_1[0x2b81] == 0xc)
            {
                if (param_1[0x1b7] < 4)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1c, 10, 0);
                }
                FUN_0042c8b0(0x80);
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
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar10, fVar11);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar10, fVar11);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                }
                else
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar10, fVar11);
                    FUN_00435450(3,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar10, fVar11);
                    FUN_00435450(2,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 4.0;
                    fVar6 =
                        (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19] + 4.0);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6 =
                        (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19] + 4.0);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0;
                    fVar6 =
                        (float10)FUN_0065d010(((float)param_1[0x17] + (float)param_1[0x19]) - 4.0);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6 =
                        (float10)FUN_0065d050(((float)param_1[0x17] + (float)param_1[0x19]) - 4.0);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                }
            }
            break;
        case 0x195:
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
            if (param_1[0x2b81] < 0xc)
            {
                FUN_0042db10(0, 0x41200000);
            }
            else if (param_1[0x2b81] < 0x1a)
            {
                FUN_0042db10(0, 0x40c00000);
            }
            if ((0x18 < param_1[0x2b81]) &&
                (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0))
            {
                param_1[0x15] = 0;
            }
            if (param_1[0x2b81] == 0)
            {
                param_1[0x18] = -0x3d4c0000;
                param_1[0x15] = 0x41200000;
                param_1[0x3b] = 0;
            }
            if (param_1[0x2b81] == 0xc)
            {
                if (param_1[0x1b7] < 4)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1c, 10, 0);
                }
                FUN_0042c8b0(0x80);
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
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar10, fVar11);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar10, fVar11);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                }
                else
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar10, fVar11);
                    FUN_00435450(3,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar10, fVar11);
                    FUN_00435450(2,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 4.0;
                    fVar6 =
                        (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19] + 4.0);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6 =
                        (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19] + 4.0);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0;
                    fVar6 =
                        (float10)FUN_0065d010(((float)param_1[0x17] + (float)param_1[0x19]) - 4.0);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6 =
                        (float10)FUN_0065d050(((float)param_1[0x17] + (float)param_1[0x19]) - 4.0);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                }
            }
            break;
        case 0x196:
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
            if (param_1[0x2b81] < 0xc)
            {
                FUN_0042db10(0, 0x41200000);
            }
            else if (param_1[0x2b81] < 0x1a)
            {
                FUN_0042db10(0, 0x40c00000);
            }
            if ((0x18 < param_1[0x2b81]) &&
                (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0))
            {
                param_1[0x15] = 0;
            }
            if (param_1[0x2b81] == 0)
            {
                param_1[0x18] = 0x42b40000;
                param_1[0x15] = 0x41200000;
                param_1[0x3b] = 0;
            }
            if (param_1[0x2b81] == 0xc)
            {
                if (param_1[0x1b7] < 4)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1c, 10, 0);
                }
                FUN_0042c8b0(0x80);
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
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar10, fVar11);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar10, fVar11);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                }
                else
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar10, fVar11);
                    FUN_00435450(3,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar10, fVar11);
                    FUN_00435450(2,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19] + 4.0, fVar10, fVar11);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0;
                    fVar6  = (float10)FUN_0065d010(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 4.0, fVar10, fVar11);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                }
            }
            break;
        case 0x197:
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
            if (param_1[0x2b81] < 0xc)
            {
                FUN_0042db10(0, 0x41200000);
            }
            if ((0x1a < param_1[0x2b81]) &&
                (param_1[0x15] = (int)((float)param_1[0x15] - 0.5), (float)param_1[0x15] < 0.0))
            {
                param_1[0x15] = 0;
            }
            if (param_1[0x2b81] == 0)
            {
                param_1[0x18] = 0x43340000;
                param_1[0x15] = 0x41200000;
                param_1[0x3b] = 0;
            }
            if (param_1[0x2b81] == 0xc)
            {
                if (param_1[0x1b7] < 4)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1c, 10, 0);
                }
                FUN_0042c8b0(0x80);
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3c] = iVar4;
                if (param_1[0x3c] < -0x2d)
                {
                    param_1[0x3c] = -0x2d;
                }
                if (0x2d < param_1[0x3c])
                {
                    param_1[0x3c] = 0x2d;
                }
                FUN_004230e0();
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 15.0;
                    fVar6  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19] + 15.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19] + 15.0, fVar10, fVar11);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 15.0;
                    fVar6  = (float10)FUN_0065d010(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 15.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 15.0, fVar10, fVar11);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                }
                else
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 15.0;
                    fVar6  = (float10)FUN_0065d010(
                        (float)param_1[0x17] + (float)param_1[0x19] + 15.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        (float)param_1[0x17] + (float)param_1[0x19] + 15.0, fVar10, fVar11);
                    FUN_00435450(3,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 15.0;
                    fVar6  = (float10)FUN_0065d010(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 15.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6  = (float10)FUN_0065d050(
                        ((float)param_1[0x17] + (float)param_1[0x19]) - 15.0, fVar10, fVar11);
                    FUN_00435450(2,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x17] + (float)param_1[0x19] + 15.0;
                    fVar6 =
                        (float10)FUN_0065d010((float)param_1[0x17] + (float)param_1[0x19] + 15.0);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6 =
                        (float10)FUN_0065d050((float)param_1[0x17] + (float)param_1[0x19] + 15.0);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = ((float)param_1[0x17] + (float)param_1[0x19]) - 15.0;
                    fVar6 =
                        (float10)FUN_0065d010(((float)param_1[0x17] + (float)param_1[0x19]) - 15.0);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 100.0;
                    fVar6 =
                        (float10)FUN_0065d050(((float)param_1[0x17] + (float)param_1[0x19]) - 15.0);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                }
            }
            break;
        case 0x199:
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
        case 0x19a:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                if ((param_1[0x9f] == 0) && (param_1[0x9e] == 0))
                {
                    FUN_00421080(0);
                    return;
                }
                FUN_004211f0(10);
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
                param_1[0x3e]  = 0;
                param_1[0x21d] = 0;
            }
            if ((param_1[0x3e] == 0) && (0x14 < param_1[0x2b81]))
            {
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
                    if (param_1[0x9e] == 0)
                    {
                        param_1[0x3e]   = 1;
                        param_1[0x2b7c] = 0;
                        param_1[0x2b7e] = 0;
                        param_1[0x2b82] = 0;
                        FUN_00421410(0, 0);
                        param_1[0x3a]  = 0;
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
            }
            if (((0x14 < param_1[0x2b81]) && (param_1[0x3e] == 1)) &&
                ((param_1[0x9f] != 0 || (param_1[0x9e] != 0))))
            {
                param_1[0x3e]   = 0;
                param_1[0x2b7c] = 10;
                param_1[0x2b7e] = 0;
                param_1[0x2b82] = 0;
                puVar5          = (undefined4 *)FUN_004244e0(param_1[0x2b7e]);
                FUN_00421410(0, *puVar5);
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
            }
            if (param_1[0x3e] == 0)
            {
                param_1[0x15] = 0x40b00000;
            }
            if (param_1[0x3e] == 1)
            {
                param_1[0x15] = 0;
            }
            if (0xc < param_1[0x2b81])
            {
                param_1[0x21d] = (int)((float)param_1[0x21d] - 1.0);
                if ((float)param_1[0x21d] < 1.0)
                {
                    param_1[0x21d] = 0x3f800000;
                }
                FUN_00421780();
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00422900();
                param_1[0x18] = 0;
            }
            if (param_1[0x2b81] == 0xc)
            {
                if (param_1[0x1b7] < 4)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1b, 10, 0);
                }
                FUN_0042c8b0(0x80);
                iVar4         = FUN_0066b668();
                param_1[0x3b] = iVar4;
                iVar4         = FUN_0066b668();
                param_1[0x3b] = iVar4;
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
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] + 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] + 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] + 25.0, fVar10, fVar11);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] - 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] - 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] - 25.0, fVar10, fVar11);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                }
                else
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] + 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] + 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] + 25.0, fVar10, fVar11);
                    FUN_00435450(3,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] - 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] - 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] - 25.0, fVar10, fVar11);
                    FUN_00435450(2,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] + 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] + 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] + 25.0, fVar10, fVar11);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] - 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] - 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] - 25.0, fVar10, fVar11);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                }
            }
            break;
        case 0x19b:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                if ((param_1[0x9f] == 0) && (param_1[0x9e] == 0))
                {
                    FUN_00421080(0);
                    return;
                }
                FUN_004211f0(10);
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
                param_1[0x3e]  = 0;
                param_1[0x21d] = 0;
            }
            if ((param_1[0x3e] == 0) && (0x14 < param_1[0x2b81]))
            {
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
                    if (param_1[0x9e] == 0)
                    {
                        param_1[0x3e]   = 1;
                        param_1[0x2b7c] = 0;
                        param_1[0x2b7e] = 0;
                        param_1[0x2b82] = 0;
                        FUN_00421410(0, 0);
                        param_1[0x3a]  = 0;
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
            }
            if (((0x14 < param_1[0x2b81]) && (param_1[0x3e] == 1)) &&
                ((param_1[0x9f] != 0 || (param_1[0x9e] != 0))))
            {
                param_1[0x3e]   = 0;
                param_1[0x2b7c] = 10;
                param_1[0x2b7e] = 0;
                param_1[0x2b82] = 0;
                puVar5          = (undefined4 *)FUN_004244e0(param_1[0x2b7e]);
                FUN_00421410(0, *puVar5);
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
            }
            if (param_1[0x3e] == 0)
            {
                param_1[0x15] = 0x40b00000;
            }
            if (param_1[0x3e] == 1)
            {
                param_1[0x15] = 0;
            }
            if (0xc < param_1[0x2b81])
            {
                param_1[0x21d] = (int)((float)param_1[0x21d] - 1.0);
                if ((float)param_1[0x21d] < 1.0)
                {
                    param_1[0x21d] = 0x3f800000;
                }
                FUN_00421780();
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00422900();
                param_1[0x18] = 0;
            }
            if (param_1[0x2b81] == 0xc)
            {
                if (param_1[0x1b7] < 4)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1b, 10, 0);
                }
                FUN_0042c8b0(0x80);
                iVar4         = FUN_0066b668();
                param_1[0x3b] = iVar4;
                iVar4         = FUN_0066b668();
                param_1[0x3b] = iVar4;
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
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] + 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] + 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] + 25.0, fVar10, fVar11);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] - 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] - 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] - 25.0, fVar10, fVar11);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                }
                else
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] + 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] + 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] + 25.0, fVar10, fVar11);
                    FUN_00435450(3,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] - 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] - 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] - 25.0, fVar10, fVar11);
                    FUN_00435450(2,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] + 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] + 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] + 25.0, fVar10, fVar11);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] - 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] - 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] - 25.0, fVar10, fVar11);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                }
            }
            break;
        case 0x19c:
            cVar1 = FUN_004218c0();
            if (cVar1 != '\0')
            {
                if ((param_1[0x9f] == 0) && (param_1[0x9e] == 0))
                {
                    FUN_00421080(0);
                    return;
                }
                FUN_004211f0(10);
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
                param_1[0x3e]  = 0;
                param_1[0x21d] = 0;
            }
            if ((param_1[0x3e] == 0) && (0x14 < param_1[0x2b81]))
            {
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
                    if (param_1[0x9e] == 0)
                    {
                        param_1[0x3e]   = 1;
                        param_1[0x2b7c] = 0;
                        param_1[0x2b7e] = 0;
                        param_1[0x2b82] = 0;
                        FUN_00421410(0, 0);
                        param_1[0x3a]  = 0;
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
            }
            if (((0x14 < param_1[0x2b81]) && (param_1[0x3e] == 1)) &&
                ((param_1[0x9f] != 0 || (param_1[0x9e] != 0))))
            {
                param_1[0x3e]   = 0;
                param_1[0x2b7c] = 10;
                param_1[0x2b7e] = 0;
                param_1[0x2b82] = 0;
                puVar5          = (undefined4 *)FUN_004244e0(param_1[0x2b7e]);
                FUN_00421410(0, *puVar5);
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
            }
            if (param_1[0x3e] == 0)
            {
                param_1[0x15] = 0x40b00000;
            }
            if (param_1[0x3e] == 1)
            {
                param_1[0x15] = 0;
            }
            if (0xc < param_1[0x2b81])
            {
                param_1[0x21d] = (int)((float)param_1[0x21d] - 1.0);
                if ((float)param_1[0x21d] < 1.0)
                {
                    param_1[0x21d] = 0x3f800000;
                }
                FUN_00421780();
            }
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00422900();
                param_1[0x18] = 0;
            }
            if (param_1[0x2b81] == 0xc)
            {
                if (param_1[0x1b7] < 4)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1b, 10, 0);
                }
                FUN_0042c8b0(0x80);
                iVar4         = FUN_0066b668();
                param_1[0x3b] = iVar4;
                iVar4         = FUN_0066b668();
                param_1[0x3b] = iVar4;
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
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] + 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] + 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] + 25.0, fVar10, fVar11);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] - 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] - 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] - 25.0, fVar10, fVar11);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                }
                else
                {
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] + 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] + 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] + 25.0, fVar10, fVar11);
                    FUN_00435450(3,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] - 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] - 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] - 25.0, fVar10, fVar11);
                    FUN_00435450(2,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] + 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] + 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] + 25.0, fVar10, fVar11);
                    FUN_00435450(1,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
                    fVar13 = (float)param_1[0x3c];
                    fVar12 = (float)param_1[0x3b] - 25.0;
                    fVar6  = (float10)FUN_0065d010((float)param_1[0x3b] - 25.0, fVar12, fVar13);
                    fVar11 = (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[7]);
                    fVar10 = (float)param_1[6] + 125.0;
                    fVar6  = (float10)FUN_0065d050((float)param_1[0x3b] - 25.0, fVar10, fVar11);
                    FUN_00435450(0,
                                 (float)(fVar6 * (float10)100.0 + (float10)(float)param_1[5]),
                                 fVar10,
                                 fVar11,
                                 fVar12,
                                 fVar13);
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
            if ((param_1[0x2b7d] == 0) && (param_1[0x2b81] == 0))
            {
                FUN_00422900();
            }
            if (param_1[0x2b81] < 0x16)
            {
                FUN_00434a70(0, 2);
                FUN_00434a70(1, 0xffffffff);
            }
            if (param_1[0x2b81] < 0x14)
            {
                FUN_0042dc20(0, 0x41200000);
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 0.25);
            if ((float)param_1[0x15] < 0.0)
            {
                param_1[0x15] = 0;
            }
            if (param_1[0x2b81] == 0x16)
            {
                FUN_0042c8b0(0x81);
                FUN_004230e0();
                if (param_1[0x1c8] == 1)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1d, 10, 0);
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
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    FUN_00434fd0(4, 0, (float)param_1[0x3c], 0);
                }
                else
                {
                    FUN_00434fd0(5, 0, (float)param_1[0x3c], 0);
                }
            }
            break;
        case 0x1c3:
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
            if (param_1[0x2b81] < 0x11)
            {
                FUN_0042dc20(0, 0x41200000);
            }
            else if (param_1[0x2b81] < 0x1a)
            {
                FUN_0042db10(0, 0x40800000);
            }
            if (param_1[0x2b81] < 0x11)
            {
                FUN_00434a70(0, 2);
                FUN_00434a70(1, 0xffffffff);
            }
            param_1[0x15] = (int)((float)param_1[0x15] - 0.25);
            if ((float)param_1[0x15] < 0.0)
            {
                param_1[0x15] = 0;
            }
            if (param_1[0x2b81] == 0x11)
            {
                if (param_1[0x1c8] == 1)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1d, 10, 0);
                }
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3a] = iVar4;
                if (param_1[0x3a] < -0x28)
                {
                    param_1[0x3a] = -0x28;
                }
                if (0x28 < param_1[0x3a])
                {
                    param_1[0x3a] = 0x28;
                }
                FUN_004230e0();
                FUN_0042c8b0(0x81);
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    FUN_00434fd0(4, 0, (float)param_1[0x3a], 0);
                }
                else
                {
                    FUN_00434fd0(5, 0, (float)param_1[0x3a], 0);
                }
            }
            break;
        case 0x1cc:
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
            if (param_1[0x2b81] < 0xf)
            {
                FUN_0042dc20(0, 0x41700000);
            }
            if (param_1[0x2b81] < 0x11)
            {
                FUN_00434a70(0, 2);
                FUN_00434a70(1, 0xffffffff);
            }
            if (param_1[0x2b81] == 0x11)
            {
                if (param_1[0x1c8] == 1)
                {
                    FUN_004223d0(0x1e, 10, 0);
                }
                else
                {
                    FUN_004223d0(0x1d, 10, 0);
                }
                param_1[0x18] = 0;
                param_1[0x15] = -0x3ee00000;
                param_1[0x10] = 0x40a00000;
                FUN_0042da80();
                iVar4         = FUN_0066b668();
                param_1[0x3a] = iVar4;
                if (param_1[0x3a] < -0x28)
                {
                    param_1[0x3a] = -0x28;
                }
                if (0x28 < param_1[0x3a])
                {
                    param_1[0x3a] = 0x28;
                }
                FUN_0042c8b0(0x81);
                FUN_004230e0();
                if ((*(char *)((int)param_1 + 0x845) == '\0') || (param_1[0x212] == 0))
                {
                    FUN_00434fd0(4, 0, (float)param_1[0x3a], 0);
                }
                else
                {
                    FUN_00434fd0(5, 0, (float)param_1[0x3a], 0);
                }
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
