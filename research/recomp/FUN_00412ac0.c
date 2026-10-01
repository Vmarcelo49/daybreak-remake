// ============================================
// Address:  0x00412ac0
// Original: FUN_00412ac0
// Status:   unreviewed
// ============================================

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

undefined4 __fastcall FUN_00412ac0(int param_1)

{
    char cVar1;
    uint uVar2;
    int iVar3;
    wchar_t local_42c[262];
    char *local_220;
    char local_21c[268];
    uint local_110;
    wchar_t local_10c[100];
    int local_44;
    int local_40;
    int local_3c;
    int local_38;
    uint local_34;
    char acStack_30[4];
    int local_2c;
    int local_28;
    int local_24;
    int local_20;
    char acStack_1c[8];
    undefined4 local_14;
    uint local_10;
    int local_c;
    int local_8;

    local_14 = DAT_006b77f4;
    FUN_006584e0();
    FUN_006585f0();
    cVar1 = FUN_006586d0(0x1c);
    if ((cVar1 != '\0') && ((cVar1 = FUN_006586d0(0xb8),
                             cVar1 != '\0' || (cVar1 = FUN_006586d0(0x38), cVar1 != '\0'))))
    {
        FUN_0064ad70();
    }
    FUN_00657390();
    local_c = DAT_006cae94;
    local_8 = DAT_006cae98;
    switch (*(undefined4 *)(param_1 + 0x1088))
    {
    case 0:
        if (DAT_006cae98 == 1)
        {
            *(int *)(param_1 + 0x1070) = (*(int *)(param_1 + 0x1070) + 1) % 6;
            FUN_0064aed0(2);
        }
        if (local_8 == -1)
        {
            *(int *)(param_1 + 0x1070) = (*(int *)(param_1 + 0x1070) + 5) % 6;
            FUN_0064aed0(2);
        }
        if (DAT_006cae9c == 1)
        {
            FUN_0064aed0(0);
            switch (*(undefined4 *)(param_1 + 0x1070))
            {
            case 0:
                FUN_00645840();
                FUN_0065ff30();
                FUN_006601d0(&DAT_006a1c84, DAT_006cfdc6);
                DAT_006cfdb0 = 1;
                return 0xc;
            case 1:
                *(undefined4 *)(param_1 + 0x1088) = 1;
                *(undefined4 *)(param_1 + 0x1074) = 0;
                break;
            case 2:
                *(undefined4 *)(param_1 + 0x1074) = 7;
                while (0 < *(int *)(param_1 + 0x1074))
                {
                    if ((&DAT_006cfdb8)[*(int *)(param_1 + 0x1074)] != '\0')
                    {
                        *(int *)(param_1 + 0x1074) = *(int *)(param_1 + 0x1074) + 1;
                        if (7 < *(int *)(param_1 + 0x1074))
                        {
                            *(undefined4 *)(param_1 + 0x1074) = 7;
                        }
                        break;
                    }
                    *(int *)(param_1 + 0x1074) = *(int *)(param_1 + 0x1074) + -1;
                }
                *(undefined4 *)(param_1 + 0x107c) = 0;
                *(undefined4 *)(param_1 + 0x1080) = 0;
                *(undefined4 *)(param_1 + 0x1084) = 0;
                *(undefined4 *)(param_1 + 0x1088) = 2;
                break;
            case 3:
                *(undefined4 *)(param_1 + 0x1088) = 3;
                break;
            case 4:
                *(undefined4 *)(param_1 + 0x1088) = 4;
                *(undefined4 *)(param_1 + 0x1074) = 0;
                break;
            case 5:
                *(undefined4 *)(param_1 + 0x1088) = 9;
                *(undefined4 *)(param_1 + 0x1074) = 0;
            }
        }
        else if (DAT_006caea0 == 1)
        {
            FUN_0064aed0(1);
            return 1;
        }
        break;
    case 1:
        if (DAT_006cae98 == 1)
        {
            uVar2 = *(int *)(param_1 + 0x1074) + 1U & 0x80000001;
            if ((int)uVar2 < 0)
            {
                uVar2 = (uVar2 - 1 | 0xfffffffe) + 1;
            }
            *(uint *)(param_1 + 0x1074) = uVar2;
            FUN_0064aed0(2);
        }
        if (local_8 == -1)
        {
            uVar2 = *(int *)(param_1 + 0x1074) + 1U & 0x80000001;
            if ((int)uVar2 < 0)
            {
                uVar2 = (uVar2 - 1 | 0xfffffffe) + 1;
            }
            *(uint *)(param_1 + 0x1074) = uVar2;
            FUN_0064aed0(2);
        }
        if (*(char *)(param_1 + 0x18b4) == '\0')
        {
            *(undefined4 *)(param_1 + 0x1074) = 0;
        }
        if (DAT_006cae9c == 1)
        {
            FUN_0064aed0(0);
            if (*(int *)(param_1 + 0x1074) == 0)
            {
                *(undefined4 *)(param_1 + 0x1088) = 5;
            }
            else
            {
                *(undefined4 *)(param_1 + 0x1088) = 6;
            }
            *(undefined4 *)(param_1 + 0x1078) = 0;
        }
        if (DAT_006caea0 == 1)
        {
            FUN_0064aed0(1);
            *(undefined4 *)(param_1 + 0x1088) = 0;
        }
        break;
    case 2:
        if ((DAT_006cae94 == 1) || ((0xf < DAT_006cae94 && (DAT_006cae94 % 6 == 1))))
        {
            *(int *)(param_1 + 0x107c) = (*(int *)(param_1 + 0x107c) + 1) % 0x11;
            if ((4 < *(int *)(param_1 + 0x1080)) && (*(int *)(param_1 + 0x107c) == 0x10))
            {
                *(undefined4 *)(param_1 + 0x107c) = 0;
            }
            FUN_0064aed0(2);
        }
        if ((local_c == -1) || ((local_c < -0xf && (-local_c % 6 == 1))))
        {
            *(int *)(param_1 + 0x107c) = (*(int *)(param_1 + 0x107c) + 0x10) % 0x11;
            if ((4 < *(int *)(param_1 + 0x1080)) && (*(int *)(param_1 + 0x107c) == 0x10))
            {
                *(undefined4 *)(param_1 + 0x107c) = 0xf;
            }
            FUN_0064aed0(2);
        }
        if (*(int *)(param_1 + 0x107c) == 0x10)
        {
            if ((local_8 == 1) || ((0xf < local_8 && (local_8 % 6 == 1))))
            {
                *(int *)(param_1 + 0x1080) = (*(int *)(param_1 + 0x1080) + 1) % 5;
                FUN_0064aed0(2);
            }
            if ((local_8 == -1) || ((local_8 < -0xf && (-local_8 % 6 == 1))))
            {
                *(int *)(param_1 + 0x1080) = (*(int *)(param_1 + 0x1080) + 4) % 5;
                FUN_0064aed0(2);
            }
            if (DAT_006cae9c == 1)
            {
                FUN_0064aed0(0);
                switch (*(undefined4 *)(param_1 + 0x1080))
                {
                case 0:
                    uVar2 = *(int *)(param_1 + 0x1084) + 1U & 0x80000001;
                    if ((int)uVar2 < 0)
                    {
                        uVar2 = (uVar2 - 1 | 0xfffffffe) + 1;
                    }
                    *(uint *)(param_1 + 0x1084) = uVar2;
                    break;
                case 1:
                    if (*(int *)(param_1 + 0x1074) < 7)
                    {
                        *(int *)(param_1 + 0x1074) = *(int *)(param_1 + 0x1074) + 1;
                    }
                    break;
                case 2:
                    if (0 < *(int *)(param_1 + 0x1074))
                    {
                        *(int *)(param_1 + 0x1074) = *(int *)(param_1 + 0x1074) + -1;
                    }
                    break;
                case 3:
                    *(undefined4 *)(param_1 + 0x1088) = 0;
                    FUN_006486c0();
                    break;
                case 4:
                    *(undefined4 *)(param_1 + 0x1088) = 0;
                    FUN_006488d0();
                }
            }
        }
        else
        {
            if ((local_8 == 1) || ((0x14 < local_8 && (local_8 % 6 == 1))))
            {
                uVar2 = *(int *)(param_1 + 0x1080) + 1U & 0x8000000f;
                if ((int)uVar2 < 0)
                {
                    uVar2 = (uVar2 - 1 | 0xfffffff0) + 1;
                }
                *(uint *)(param_1 + 0x1080) = uVar2;
                FUN_0064aed0(2);
            }
            if ((local_8 == -1) || ((local_8 < -0x14 && (-local_8 % 6 == 1))))
            {
                uVar2 = *(int *)(param_1 + 0x1080) + 0xfU & 0x8000000f;
                if ((int)uVar2 < 0)
                {
                    uVar2 = (uVar2 - 1 | 0xfffffff0) + 1;
                }
                *(uint *)(param_1 + 0x1080) = uVar2;
                FUN_0064aed0(2);
            }
            if (DAT_006cae9c == 1)
            {
                (&DAT_006cfdb8)[*(int *)(param_1 + 0x1074)] =
                    (char)(*(int *)(param_1 + 0x1080) << 4) +
                    (char)*(undefined4 *)(param_1 + 0x107c);
                if (*(int *)(param_1 + 0x1084) == 1)
                {
                    DAT_006cfdc0 = DAT_006cfdc0 |
                                   (byte)(1 << ((byte) * (undefined4 *)(param_1 + 0x1074) & 0x1f));
                }
                else
                {
                    DAT_006cfdc0 = DAT_006cfdc0 &
                                   ~(byte)(1 << ((byte) * (undefined4 *)(param_1 + 0x1074) & 0x1f));
                }
                FUN_0064aed0(0);
                if (*(int *)(param_1 + 0x1074) < 7)
                {
                    *(int *)(param_1 + 0x1074) = *(int *)(param_1 + 0x1074) + 1;
                }
            }
            else if (DAT_006caea0 == 1)
            {
                (&DAT_006cfdb8)[*(int *)(param_1 + 0x1074)] = 0;
                DAT_006cfdc0 =
                    DAT_006cfdc0 & ~(byte)(1 << ((byte) * (undefined4 *)(param_1 + 0x1074) & 0x1f));
                FUN_0064aed0(1);
                *(int *)(param_1 + 0x1074) = *(int *)(param_1 + 0x1074) + -1;
                if (*(int *)(param_1 + 0x1074) < 0)
                {
                    *(undefined4 *)(param_1 + 0x1074) = 0;
                }
            }
        }
        break;
    case 3:
        iVar3 = FUN_0066b65c(DAT_006cae98);
        if (iVar3 == 1)
        {
            DAT_006cfdc5 = DAT_006cfdc5 - (char)local_8;
            if (DAT_006cfdc5 == 0)
            {
                DAT_006cfdc5 = 9;
            }
            if (9 < DAT_006cfdc5)
            {
                DAT_006cfdc5 = 1;
            }
            FUN_0064aed0(2);
        }
        if ((DAT_006cae9c == 1) || (DAT_006caea0 == 1))
        {
            FUN_0064aed0(0);
            *(undefined4 *)(param_1 + 0x1088) = 0;
            FUN_006488d0();
        }
        break;
    case 4:
        iVar3 = FUN_0066b65c(DAT_006cae94);
        if (iVar3 == 1)
        {
            FUN_0064aed0(2);
            *(int *)(param_1 + 0x1074) = (*(int *)(param_1 + 0x1074) + 5 + local_c) % 5;
        }
        else
        {
            iVar3 = FUN_0066b65c(local_8);
            if (iVar3 == 1)
            {
                FUN_0064aed0(2);
                local_10 = (uint)DAT_006cfdc6;
                for (local_20 = 0; local_20 < 5; local_20 = local_20 + 1)
                {
                    acStack_1c[4 - local_20] = (char)((ulonglong)local_10 % 10);
                    local_10                 = local_10 / 10;
                }
                acStack_1c[*(int *)(param_1 + 0x1074)] =
                    (char)(((acStack_1c[*(int *)(param_1 + 0x1074)] - local_8) + 10) % 10);
                for (local_24 = 0; local_24 < 5; local_24 = local_24 + 1)
                {
                    local_10 = local_10 * 10;
                    local_10 = (int)acStack_1c[local_24] + local_10;
                }
                if (0xffff < local_10)
                {
                    acStack_1c[*(int *)(param_1 + 0x1074)] = '\0';
                    local_10                               = 0;
                    for (local_28 = 0; local_28 < 5; local_28 = local_28 + 1)
                    {
                        local_10 = local_10 * 10;
                        local_10 = (int)acStack_1c[local_28] + local_10;
                    }
                }
                DAT_006cfdc6 = (ushort)local_10;
            }
        }
        if ((DAT_006cae9c == 1) || (DAT_006caea0 == 1))
        {
            FUN_0064aed0(0);
            *(undefined4 *)(param_1 + 0x1088) = 0;
            FUN_006488d0();
        }
        break;
    case 5:
        if (DAT_006cae94 == 1)
        {
            *(int *)(param_1 + 0x1078) = (*(int *)(param_1 + 0x1078) + 1) % 0xc;
            FUN_0064aed0(2);
        }
        else if (DAT_006cae94 == -1)
        {
            *(int *)(param_1 + 0x1078) = (*(int *)(param_1 + 0x1078) + 0xb) % 0xc;
            FUN_0064aed0(2);
        }
        else
        {
            iVar3 = FUN_0066b65c(DAT_006cae98);
            if (iVar3 == 1)
            {
                FUN_0064aed0(2);
                local_38 = *(int *)(param_1 + 0x1078) / 3;
                local_2c = *(int *)(param_1 + 0x1078) % 3;
                local_34 = (uint)(&DAT_006cfdc1)[local_38];
                for (local_3c = 0; local_3c < 3; local_3c = local_3c + 1)
                {
                    acStack_30[2 - local_3c] = (char)((ulonglong)local_34 % 10);
                    local_34                 = local_34 / 10;
                }
                acStack_30[local_2c] = (char)(((acStack_30[local_2c] - local_8) + 10) % 10);
                for (local_40 = 0; local_40 < 3; local_40 = local_40 + 1)
                {
                    local_34 = (int)acStack_30[local_40] + local_34 * 10;
                }
                if (0xff < local_34)
                {
                    acStack_30[local_2c] = '\0';
                    local_34             = 0;
                    for (local_44 = 0; local_44 < 3; local_44 = local_44 + 1)
                    {
                        local_34 = (int)acStack_30[local_44] + local_34 * 10;
                    }
                }
                (&DAT_006cfdc1)[local_38] = (undefined1)local_34;
            }
        }
        if (DAT_006cae9c == 1)
        {
            FUN_0064aed0(0);
            FUN_006488d0();
            _swprintf(local_10c,
                      L"%d.%d.%d.%d",
                      (uint)DAT_006cfdc1,
                      (uint)DAT_006cfdc2,
                      (uint)DAT_006cfdc3,
                      (uint)DAT_006cfdc4);
            FUN_0065f7c0();
            *(undefined4 *)(param_1 + 0x1088) = 7;
            *(undefined4 *)(param_1 + 0x18b8) = 0;
            FUN_0065f9e0(&DAT_006a1c84, local_10c, DAT_006cfdc6);
        }
        else if (DAT_006caea0 == 1)
        {
            *(undefined4 *)(param_1 + 0x1088) = 1;
            FUN_006488d0();
        }
        break;
    case 6:
        iVar3 = FUN_0066b65c(DAT_006cae98);
        if (iVar3 == 1)
        {
            *(char *)(param_1 + 0x18b5) =
                (char)((*(char *)(param_1 + 0x18b5) + local_8 + (int)*(char *)(param_1 + 0x18b4)) %
                       (int)*(char *)(param_1 + 0x18b4));
            FUN_0064aed0(2);
        }
        else if (DAT_006cae9c == 1)
        {
            FUN_0064aed0(0);
            FUN_006488d0();
            FUN_0066b860(local_21c, param_1 + 0x1094 + *(char *)(param_1 + 0x18b5) * 0x104);
            local_220 = _strchr(local_21c, 0x3a);
            if (local_220 == (char *)0x0)
            {
                _swprintf(local_42c, L"%S", param_1 + 0x1094 + *(char *)(param_1 + 0x18b5) * 0x104);
                local_110 = (uint)DAT_006cfdc6;
            }
            else
            {
                *local_220 = '\0';
                _swprintf(local_42c, L"%S", local_21c);
                local_220 = local_220 + 1;
                local_110 = _atol(local_220);
            }
            FUN_0065f7c0();
            *(undefined4 *)(param_1 + 0x1088) = 7;
            *(undefined4 *)(param_1 + 0x18b8) = 0;
            FUN_0065f9e0(&DAT_006a1c84, local_42c, local_110);
            return 0xb;
        }
        if (DAT_006caea0 == 1)
        {
            *(undefined4 *)(param_1 + 0x1088) = 1;
            FUN_006488d0();
        }
        break;
    case 7:
        cVar1 = FUN_004146e0();
        if (cVar1 != '\0')
        {
            FUN_00645840();
            DAT_006cfdb0 = 2;
            return 0xd;
        }
        if ((DAT_006caea0 == 1) || (0x708 < *(int *)(param_1 + 0x18b8)))
        {
            FUN_0065fae0();
            FUN_0065f8b0();
            *(undefined4 *)(param_1 + 0x1088) = 1;
        }
        *(int *)(param_1 + 0x18b8) = *(int *)(param_1 + 0x18b8) + 1;
        break;
    case 8:
        if (DAT_006cae9c == 1)
        {
            *(undefined4 *)(param_1 + 0x1088) = 1;
        }
        break;
    case 9:
        iVar3 = FUN_0066b65c(DAT_006cae94);
        if ((iVar3 == 1) || (iVar3 = FUN_0066b65c(local_8), iVar3 == 1))
        {
            DAT_006cfdc8 = '\x01' - (DAT_006cfdc8 != '\0');
            FUN_0064aed0(2);
        }
        if ((DAT_006cae9c == 1) || (DAT_006caea0 == 1))
        {
            FUN_0064aed0(0);
            *(undefined4 *)(param_1 + 0x1088) = 0;
            FUN_006488d0();
        }
    }
    return 0xb;
}
