// ============================================
// Address:  0x00402be0
// Original: FUN_00402be0
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_00402be0(int param_1)

{
    char cVar1;
    ushort uVar2;
    ushort uVar3;
    undefined4 uVar4;
    int iVar5;
    int iVar6;
    ushort local_3e;
    undefined2 local_22;
    int local_8;

    FUN_006584e0();
    FUN_006585f0();
    cVar1 = FUN_006586d0(0x1c);
    if ((cVar1 == '\0') || ((cVar1 = FUN_006586d0(0xb8),
                             cVar1 == '\0' && (cVar1 = FUN_006586d0(0x38), cVar1 == '\0'))))
    {
        cVar1 = FUN_006586d0(0xcb);
        if (cVar1 == '\0')
        {
            cVar1 = FUN_006586d0(0xcd);
            if (cVar1 == '\0')
            {
                *(undefined4 *)(param_1 + 0x3d4) = 0;
            }
            else
            {
                if (*(int *)(param_1 + 0x3d4) < 0)
                {
                    *(undefined4 *)(param_1 + 0x3d4) = 0;
                }
                *(int *)(param_1 + 0x3d4) = *(int *)(param_1 + 0x3d4) + 1;
            }
        }
        else
        {
            if (0 < *(int *)(param_1 + 0x3d4))
            {
                *(undefined4 *)(param_1 + 0x3d4) = 0;
            }
            *(int *)(param_1 + 0x3d4) = *(int *)(param_1 + 0x3d4) + -1;
        }
        cVar1 = FUN_006586d0(200);
        if (cVar1 == '\0')
        {
            cVar1 = FUN_006586d0(0xd0);
            if (cVar1 == '\0')
            {
                *(undefined4 *)(param_1 + 0x3d8) = 0;
            }
            else
            {
                if (*(int *)(param_1 + 0x3d8) < 0)
                {
                    *(undefined4 *)(param_1 + 0x3d8) = 0;
                }
                *(int *)(param_1 + 0x3d8) = *(int *)(param_1 + 0x3d8) + 1;
            }
        }
        else
        {
            if (0 < *(int *)(param_1 + 0x3d8))
            {
                *(undefined4 *)(param_1 + 0x3d8) = 0;
            }
            *(int *)(param_1 + 0x3d8) = *(int *)(param_1 + 0x3d8) + -1;
        }
        cVar1 = FUN_006586d0(0x1c);
        if ((((cVar1 == '\0') && (cVar1 = FUN_006586d0(0x39), cVar1 == '\0')) ||
             (cVar1 = FUN_006586d0(0xb8), cVar1 != '\0')) ||
            (cVar1 = FUN_006586d0(0x38), cVar1 != '\0'))
        {
            *(undefined4 *)(param_1 + 0x3dc) = 0;
        }
        else
        {
            *(int *)(param_1 + 0x3dc) = *(int *)(param_1 + 0x3dc) + 1;
        }
        cVar1 = FUN_006586d0(1);
        if (cVar1 == '\0')
        {
            *(undefined4 *)(param_1 + 0x3e0) = 0;
        }
        else
        {
            *(int *)(param_1 + 0x3e0) = *(int *)(param_1 + 0x3e0) + 1;
        }
        for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1)
        {
            FUN_00657390();
            iVar5 = FUN_0066b65c(*(undefined4 *)(param_1 + 0x3d4));
            iVar6 = FUN_00403aa0((&DAT_006cae94)[local_8 * 0x19]);
            if (iVar5 < iVar6)
            {
                *(undefined4 *)(param_1 + 0x3d4) = (&DAT_006cae94)[local_8 * 0x19];
            }
            iVar5 = FUN_0066b65c(*(undefined4 *)(param_1 + 0x3d8));
            iVar6 = FUN_00403aa0((&DAT_006cae98)[local_8 * 0x19]);
            if (iVar5 < iVar6)
            {
                *(undefined4 *)(param_1 + 0x3d8) = (&DAT_006cae98)[local_8 * 0x19];
            }
            if (*(uint *)(param_1 + 0x3dc) < (uint)(&DAT_006cae9c)[local_8 * 0x19])
            {
                *(undefined4 *)(param_1 + 0x3dc) = (&DAT_006cae9c)[local_8 * 0x19];
            }
            if (*(uint *)(param_1 + 0x3e0) < (uint)(&DAT_006caea0)[local_8 * 0x19])
            {
                *(undefined4 *)(param_1 + 0x3e0) = (&DAT_006caea0)[local_8 * 0x19];
            }
        }
        iVar5 = FUN_0066b65c(*(undefined4 *)(param_1 + 0x3d4));
        if ((iVar5 == 1) && (*(int *)(param_1 + 0x3d0) < 8))
        {
            FUN_0064aed0(0);
            switch (*(undefined4 *)(param_1 + 0x3d0))
            {
            case 0:
                DAT_006cfcec = '\x01' - (DAT_006cfcec != '\0');
                break;
            case 1:
                DAT_006cfcea = '\x01' - (DAT_006cfcea != '\0');
                break;
            case 2:
                DAT_006cfceb = '\x01' - (DAT_006cfceb != '\0');
                if (DAT_006cfceb == '\0')
                {
                    FUN_00687260(2);
                }
                else
                {
                    FUN_00687260(0);
                }
                break;
            case 3:
                DAT_006cfced               = '\x01' - (DAT_006cfced != '\0');
                *(char *)(param_1 + 0x3ee) = '\x01' - (*(char *)(param_1 + 0x3ee) != '\0');
                break;
            case 4:
                waveOutGetVolume((HWAVEOUT)0x0, (LPDWORD)(param_1 + 1000));
                if ((*(uint *)(param_1 + 1000) & 0xffff) < *(uint *)(param_1 + 1000) >> 0x10)
                {
                    local_22 = (undefined2)((uint) * (undefined4 *)(param_1 + 1000) >> 0x10);
                }
                else
                {
                    local_22 = (undefined2) * (undefined4 *)(param_1 + 1000);
                }
                *(undefined2 *)(param_1 + 0x3ec) = local_22;
                if (*(int *)(param_1 + 0x3d4) < 1)
                {
                    if (*(int *)(param_1 + 0x3d4) < 0)
                    {
                        if (*(ushort *)(param_1 + 0x3ec) < 0x800)
                        {
                            *(undefined2 *)(param_1 + 0x3ec) = 0;
                        }
                        else
                        {
                            *(short *)(param_1 + 0x3ec) = *(short *)(param_1 + 0x3ec) + -0x800;
                        }
                    }
                }
                else if (*(ushort *)(param_1 + 0x3ec) < 0xf800)
                {
                    *(short *)(param_1 + 0x3ec) = *(short *)(param_1 + 0x3ec) + 0x800;
                }
                else
                {
                    *(undefined2 *)(param_1 + 0x3ec) = 0xffff;
                }
                uVar2    = FUN_0066b668();
                uVar3    = FUN_0066b668();
                local_3e = uVar3;
                if (uVar3 < uVar2)
                {
                    local_3e = uVar2;
                }
                *(ushort *)(param_1 + 0x3ec) = local_3e;
                *(uint *)(param_1 + 1000)    = CONCAT22(uVar3, uVar2);
                waveOutSetVolume((HWAVEOUT)0x0, *(DWORD *)(param_1 + 1000));
                break;
            case 5:
                if (DAT_006cfcf4 < 1)
                {
                    DAT_006cfcf4 = 0x3c;
                }
                DAT_006cfcf4 = DAT_006cfcf4 + *(int *)(param_1 + 0x3d4) * 2;
                if (DAT_006cfcf4 < 0x3d)
                {
                    DAT_006cfcf4 = 0;
                }
                if (100 < DAT_006cfcf4)
                {
                    DAT_006cfcf4 = 100;
                }
                FUN_00403930();
                break;
            case 6:
                if (DAT_006cfcfc < 1)
                {
                    DAT_006cfcfc = 0x3c;
                }
                DAT_006cfcfc = DAT_006cfcfc + *(int *)(param_1 + 0x3d4) * 2;
                if (DAT_006cfcfc < 0x3d)
                {
                    DAT_006cfcfc = 0;
                }
                if (100 < DAT_006cfcfc)
                {
                    DAT_006cfcfc = 100;
                }
                FUN_00403930();
                break;
            case 7:
                if (DAT_006cfcf8 < 1)
                {
                    DAT_006cfcf8 = 0x3c;
                }
                DAT_006cfcf8 = DAT_006cfcf8 + *(int *)(param_1 + 0x3d4) * 2;
                if (DAT_006cfcf8 < 0x3d)
                {
                    DAT_006cfcf8 = 0;
                }
                if (100 < DAT_006cfcf8)
                {
                    DAT_006cfcf8 = 100;
                }
                FUN_00403930();
            }
            FUN_006488d0();
        }
        if ((*(int *)(param_1 + 0x3d0) == 8) && (*(int *)(param_1 + 0x3dc) == 1))
        {
            FUN_0064aed0(0);
            if (*(char *)(param_1 + 0x3ee) != '\0')
            {
                FUN_00403ac0();
            }
            uVar4 = 1;
        }
        else if (*(int *)(param_1 + 0x3e0) == 1)
        {
            FUN_0064aed0(1);
            if (*(char *)(param_1 + 0x3ee) != '\0')
            {
                FUN_00403ac0();
            }
            uVar4 = 1;
        }
        else
        {
            if (*(int *)(param_1 + 0x3d8) == 1)
            {
                *(int *)(param_1 + 0x3d0) = (*(int *)(param_1 + 0x3d0) + 1) % 9;
                FUN_0064aed0(2);
            }
            else if (*(int *)(param_1 + 0x3d8) == -1)
            {
                *(int *)(param_1 + 0x3d0) = (*(int *)(param_1 + 0x3d0) + 8) % 9;
                FUN_0064aed0(2);
            }
            uVar4 = 6;
        }
    }
    else
    {
        FUN_00403ac0();
        DAT_006cfced                     = '\x01' - (DAT_006cfced != '\0');
        *(undefined1 *)(param_1 + 0x3ee) = 0;
        uVar4                            = 6;
    }
    return uVar4;
}
