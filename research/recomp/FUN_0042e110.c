// ============================================
// Address:  0x0042e110
// Original: FUN_0042e110
// Status:   unreviewed
// ============================================

int __fastcall FUN_0042e110(int param_1)

{
    int iVar1;
    uint uVar2;
    uint uVar3;
    uint uVar4;
    float10 fVar5;
    float fVar6;
    float fVar7;
    undefined4 uVar8;
    undefined4 uVar9;
    int local_10;
    float local_c;
    float local_8;

    if ((*(int *)(*(int *)(param_1 + 0x23c) + 0x1c) == 1) && (DAT_006cfdb0 != '\x02'))
    {
        FUN_00422560(*(undefined4 *)(param_1 + 8), 7, 0x1e, 0);
    }
    if (*(char *)(param_1 + 0xaec4) == '\x01')
    {
        FUN_00422730(*(undefined4 *)(param_1 + 8), 0x22, (int)*(char *)(param_1 + 0x310), 0x32, 0);
        *(undefined1 *)(param_1 + 0xaec4) = 0;
    }
    *(undefined1 *)(param_1 + 0xaec3) = 0;
    *(undefined1 *)(param_1 + 0xaeb9) = 0;
    *(undefined1 *)(param_1 + 0xaebe) = 0;
    iVar1                             = FUN_004236c0();
    if (((iVar1 == 0) || (*(int *)(*(int *)(param_1 + 0x308) + 0x7d8) == *(int *)(param_1 + 8))) ||
        (-1 < *(int *)(param_1 + 0x304)))
    {
        if ((*(int *)(*(int *)(param_1 + 0x308) + 0x308) == param_1) ||
            (-1 < *(int *)(param_1 + 0x304)))
        {
            if ((*(int *)(*(int *)(param_1 + 0x308) + 0x308) != param_1) &&
                (*(int *)(param_1 + 0x304) < 0))
            {
                local_c = (*(float *)(*(int *)(param_1 + 0x308) + 0x5c) +
                           *(float *)(*(int *)(param_1 + 0x308) + 100)) -
                          *(float *)(param_1 + 0x5c);
                if (local_c < -180.0)
                {
                    local_c = local_c + 360.0;
                }
                if (180.0 < local_c)
                {
                    local_c = local_c - 360.0;
                }
                fVar5 = (float10)FUN_0042df90(local_c);
                if (fVar5 < (float10)90.0)
                {
                    *(undefined1 *)(param_1 + 0xaeb9) = 1;
                }
            }
        }
        else
        {
            local_8 = (*(float *)(*(int *)(param_1 + 0x308) + 0x5c) +
                       *(float *)(*(int *)(param_1 + 0x308) + 100)) -
                      *(float *)(param_1 + 0x5c);
            if (local_8 < -180.0)
            {
                local_8 = local_8 + 360.0;
            }
            if (180.0 < local_8)
            {
                local_8 = local_8 - 360.0;
            }
            fVar5 = (float10)FUN_0042df90(local_8);
            if (fVar5 < (float10)90.0)
            {
                iVar1 = FUN_0042e950();
                if (iVar1 != 0)
                {
                    *(undefined1 *)(param_1 + 0xaebe) = 1;
                }
                *(undefined1 *)(param_1 + 0xaeb9) = 1;
            }
        }
    }
    else
    {
        *(undefined1 *)(param_1 + 0xaec3) = 1;
    }
    *(undefined4 *)(param_1 + 0x7d4) = 0xffffffff;
    if ((((*(int *)(param_1 + 0xadec) == 0x68) || (*(int *)(param_1 + 0xadec) == 0x69)) ||
         ((*(int *)(param_1 + 0xadec) == 0xcc || (*(int *)(param_1 + 0xadec) == 0xcd)))) &&
        ((*(int *)(param_1 + 0xadf4) == 0 && (*(int *)(param_1 + 0xadf4) == 0))))
    {
        *(undefined4 *)(param_1 + 0x7d4) = 2;
    }
    for (local_10 = 0; local_10 < 9; local_10 = local_10 + 1)
    {
        if (*(int *)(param_1 + 0x7dc + local_10 * 4) != 0)
        {
            *(int *)(param_1 + 0x7dc + local_10 * 4) =
                *(int *)(param_1 + 0x7dc + local_10 * 4) + -1;
        }
    }
    if ((((*(int *)(param_1 + 0xadec) == 0x6a) || (*(int *)(param_1 + 0xadec) == 0x6b)) ||
         (*(int *)(param_1 + 0xadec) == 0x6c)) ||
        (*(int *)(param_1 + 0xadec) == 0xce))
    {
        *(undefined4 *)(param_1 + 0x7d4) = 3;
        if (*(int *)(param_1 + 0xae04) % 7 == 0)
        {
            uVar9 = 0;
            uVar8 = 0;
            uVar2 = FUN_0065d150(0, 0);
            fVar7 = ((float)(uVar2 % 0x3c) + *(float *)(param_1 + 0x2d4)) - 30.0;
            uVar2 = FUN_0065d150(fVar7);
            fVar6 = *(float *)(param_1 + 0x2d0) - (float)(uVar2 % 0x50);
            uVar2 = FUN_0065d150(fVar6);
            FUN_0042c8e0(0x17c,
                         ((float)(uVar2 % 0x3c) + *(float *)(param_1 + 0x2cc)) - 30.0,
                         fVar6,
                         fVar7,
                         uVar8,
                         uVar9);
        }
        if (*(int *)(param_1 + 0xae04) % 0x3c == 0)
        {
            FUN_0042c8b0(0x24);
        }
    }
    if (((*(int *)(param_1 + 0x7dc) != 0) && (*(int *)(param_1 + 0xadec) != 0x6a)) &&
        ((*(int *)(param_1 + 0xadec) != 0x6b &&
          ((*(int *)(param_1 + 0xadec) != 0x6c && (*(int *)(param_1 + 0xadec) != 0xce))))))
    {
        *(undefined4 *)(param_1 + 0x7dc) = 0;
    }
    iVar1 = param_1;
    if (*(int *)(param_1 + 0x7ec) != 0)
    {
        if (*(int *)(param_1 + 0x7ec) % 0x3c == 0)
        {
            FUN_0042c8b0(0x22);
        }
        if (*(int *)(param_1 + 0x810) < *(int *)(param_1 + 0x7a4))
        {
            *(int *)(param_1 + 0x7a4) = *(int *)(param_1 + 0x7a4) - *(int *)(param_1 + 0x810);
        }
        uVar2 = FUN_0065d150();
        uVar3 = FUN_0065d150();
        uVar4 = FUN_0065d150();
        iVar1 = *(int *)(param_1 + 0x7ec) / 0xf;
        if (*(int *)(param_1 + 0x7ec) % 0xf == 0)
        {
            iVar1 =
                FUN_0042c8e0(0x3c,
                             ((float)(uVar2 % 100) + *(float *)(param_1 + 0x2c0)) - 50.0,
                             (*(float *)(param_1 + 0x2c4) + 50.0 + (float)(uVar4 % 0x3c)) - 50.0,
                             ((float)(uVar3 % 100) + *(float *)(param_1 + 0x2c8)) - 50.0,
                             0,
                             0);
        }
    }
    if (*(int *)(param_1 + 0x7f0) != 0)
    {
        if (*(int *)(param_1 + 0x7f0) % 0x3c == 0)
        {
            FUN_0042c8b0(0x25);
        }
        uVar2 = FUN_0065d150();
        uVar3 = FUN_0065d150();
        uVar4 = FUN_0065d150();
        iVar1 = *(int *)(param_1 + 0x7f0) / 10;
        if (*(int *)(param_1 + 0x7f0) % 10 == 0)
        {
            iVar1 =
                FUN_0042c8e0(0x5a,
                             ((float)(uVar2 % 100) + *(float *)(param_1 + 0x2c0)) - 50.0,
                             (*(float *)(param_1 + 0x2c4) + 50.0 + (float)(uVar4 % 0x3c)) - 50.0,
                             ((float)(uVar3 % 100) + *(float *)(param_1 + 0x2c8)) - 50.0,
                             0,
                             0);
        }
    }
    if (*(int *)(param_1 + 0x7f4) != 0)
    {
        if (*(int *)(param_1 + 0x7f4) % 0x3c == 0)
        {
            FUN_0042c8b0(0x23);
        }
        iVar1 = *(int *)(param_1 + 0x7f4) / 0xf;
        if (*(int *)(param_1 + 0x7f4) % 0xf == 0)
        {
            iVar1 = FUN_0042c8e0(0x50,
                                 *(undefined4 *)(param_1 + 0x2cc),
                                 *(float *)(param_1 + 0x2d0) + 50.0,
                                 *(undefined4 *)(param_1 + 0x2d4),
                                 0,
                                 0);
        }
    }
    if (*(int *)(param_1 + 0x7e0) != 0)
    {
        uVar2 = FUN_0065d150();
        uVar3 = FUN_0065d150();
        uVar4 = FUN_0065d150();
        iVar1 = *(int *)(param_1 + 0x7e0) / 0x1e;
        if (*(int *)(param_1 + 0x7e0) % 0x1e == 0)
        {
            iVar1 =
                FUN_0042c8e0(400,
                             ((float)(uVar2 % 100) + *(float *)(param_1 + 0x2c0)) - 50.0,
                             (*(float *)(param_1 + 0x2c4) + 50.0 + (float)(uVar4 % 0x3c)) - 50.0,
                             ((float)(uVar3 % 100) + *(float *)(param_1 + 0x2c8)) - 50.0,
                             0,
                             0);
        }
    }
    if (*(int *)(param_1 + 0x7e4) != 0)
    {
        uVar2 = FUN_0065d150();
        uVar3 = FUN_0065d150();
        uVar4 = FUN_0065d150();
        iVar1 = *(int *)(param_1 + 0x7e4) / 0x1e;
        if (*(int *)(param_1 + 0x7e4) % 0x1e == 0)
        {
            iVar1 =
                FUN_0042c8e0(0x186,
                             ((float)(uVar2 % 100) + *(float *)(param_1 + 0x2c0)) - 50.0,
                             (*(float *)(param_1 + 0x2c4) + 50.0 + (float)(uVar4 % 0x3c)) - 50.0,
                             ((float)(uVar3 % 100) + *(float *)(param_1 + 0x2c8)) - 50.0,
                             0,
                             0);
        }
    }
    return iVar1;
}
