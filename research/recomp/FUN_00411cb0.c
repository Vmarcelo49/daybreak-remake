// ============================================
// Address:  0x00411cb0
// Original: FUN_00411cb0
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_00411cb0(int param_1)

{
    char cVar1;
    undefined4 uVar2;
    uint uVar3;

    if (*(char *)(param_1 + 0x5cd) == '\0')
    {
        uVar2 = 0;
    }
    else
    {
        cVar1 = FUN_00650f70();
        if (cVar1 != '\0')
        {
            (**(code **)(*DAT_006d16f8 + 0xe4))(DAT_006d16f8, 7, 0);
            FUN_00655f70(0, 0, 0x44480000, 0x43960000);
            FUN_00655f70(0, 0x43960000, 0x44480000, 0x44160000);
            if (DAT_006cfdb0 == '\0')
            {
                uVar3 = DAT_006cfb28 & 0x80000007;
                if ((int)uVar3 < 0)
                {
                    uVar3 = (uVar3 - 1 | 0xfffffff8) + 1;
                }
                FUN_00655830(0x43160000,
                             0x43480000,
                             (int)(DAT_006cfb28 + ((int)DAT_006cfb28 >> 0x1f & 7U)) >> 3,
                             uVar3);
                uVar3 = DAT_006cfb2c & 0x80000007;
                if ((int)uVar3 < 0)
                {
                    uVar3 = (uVar3 - 1 | 0xfffffff8) + 1;
                }
                FUN_00655830(0x43480000,
                             0x437a0000,
                             (int)(DAT_006cfb2c + ((int)DAT_006cfb2c >> 0x1f & 7U)) >> 3,
                             uVar3);
                uVar3 = DAT_006cfb30 & 0x80000007;
                if ((int)uVar3 < 0)
                {
                    uVar3 = (uVar3 - 1 | 0xfffffff8) + 1;
                }
                FUN_00655830(0x44160000,
                             0x43af0000,
                             (int)(DAT_006cfb30 + ((int)DAT_006cfb30 >> 0x1f & 7U)) >> 3,
                             uVar3);
                uVar3 = DAT_006cfb34 & 0x80000007;
                if ((int)uVar3 < 0)
                {
                    uVar3 = (uVar3 - 1 | 0xfffffff8) + 1;
                }
                FUN_00655830(0x44228000,
                             0x43c80000,
                             (int)(DAT_006cfb34 + ((int)DAT_006cfb34 >> 0x1f & 7U)) >> 3,
                             uVar3);
            }
            else
            {
                uVar3 = DAT_006cfb28 & 0x80000007;
                if ((int)uVar3 < 0)
                {
                    uVar3 = (uVar3 - 1 | 0xfffffff8) + 1;
                }
                FUN_00655830(0x43160000,
                             0x43200000,
                             (int)(DAT_006cfb28 + ((int)DAT_006cfb28 >> 0x1f & 7U)) >> 3,
                             uVar3);
                uVar3 = DAT_006cfb2c & 0x80000007;
                if ((int)uVar3 < 0)
                {
                    uVar3 = (uVar3 - 1 | 0xfffffff8) + 1;
                }
                FUN_00655830(0x43480000,
                             0x43700000,
                             (int)(DAT_006cfb2c + ((int)DAT_006cfb2c >> 0x1f & 7U)) >> 3,
                             uVar3);
                uVar3 = DAT_006cfb30 & 0x80000007;
                if ((int)uVar3 < 0)
                {
                    uVar3 = (uVar3 - 1 | 0xfffffff8) + 1;
                }
                FUN_00655830(0x44160000,
                             0x43af0000,
                             (int)(DAT_006cfb30 + ((int)DAT_006cfb30 >> 0x1f & 7U)) >> 3,
                             uVar3);
                uVar3 = DAT_006cfb34 & 0x80000007;
                if ((int)uVar3 < 0)
                {
                    uVar3 = (uVar3 - 1 | 0xfffffff8) + 1;
                }
                FUN_00655830(0x44228000,
                             0x43d70000,
                             (int)(DAT_006cfb34 + ((int)DAT_006cfb34 >> 0x1f & 7U)) >> 3,
                             uVar3);
                if (DAT_006cfaf8 < 4)
                {
                    FUN_00646bd0((&DAT_006cfb18)[DAT_006cfaf8], 0x42480000, 0x43340000, 1);
                }
                if (DAT_006cfafc < 4)
                {
                    FUN_00646bd0((&DAT_006cfb18)[DAT_006cfafc], 0x42c80000, 0x43820000, 1);
                }
                if (DAT_006cfb00 < 4)
                {
                    FUN_00646bd0((&DAT_006cfb18)[DAT_006cfb00], 0x43fa0000, 0x43b90000, 1);
                }
                if (DAT_006cfb04 < 4)
                {
                    FUN_00646bd0((&DAT_006cfb18)[DAT_006cfb04], 0x44098000, 0x43e10000, 1);
                }
            }
            FUN_00655d60(-*(float *)(param_1 + 0x5d0) + 500.0, 0x43938000);
            FUN_00655d60(-*(float *)(param_1 + 0x5d4) + 700.0, 0x43938000);
            FUN_00655d60(*(float *)(param_1 + 0x5dc) + 300.0, 0x44160000);
            FUN_00655d60(*(float *)(param_1 + 0x5d8) + 100.0, 0x44160000);
            if (0x5a < *(int *)(param_1 + 0x5c4))
            {
                FUN_00655d60(0x43c80000, 0x43960000);
            }
            FUN_00650fd0();
            if (*(char *)(param_1 + 0x5cc) != '\0')
            {
                *(undefined1 *)(param_1 + 0x5cd) = 0;
            }
        }
        uVar2 = 1;
    }
    return uVar2;
}
