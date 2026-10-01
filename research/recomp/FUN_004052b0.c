// ============================================
// Address:  0x004052b0
// Original: FUN_004052b0
// Status:   unreviewed
// ============================================

undefined4 *__fastcall FUN_004052b0(undefined4 *param_1)

{
    undefined4 *puVar1;
    undefined4 uVar2;
    undefined4 uVar3;
    undefined4 uVar4;
    undefined4 uVar5;
    undefined1 local_14[4];
    void *local_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069db18;
    local_10      = ExceptionList;
    ExceptionList = &local_10;
    FUN_00403a50();
    local_8  = 0;
    *param_1 = &PTR_FUN_006a14fc;
    FUN_00403a70();
    param_1[1] = 0;
    FUN_0065b9b0();
    FUN_0065c080(&DAT_006cfbe5);
    uVar5  = 0x1e0;
    uVar4  = 0x280;
    uVar3  = 0;
    uVar2  = 0;
    puVar1 = (undefined4 *)FUN_00405200(local_14);
    FUN_00655af0(*puVar1, uVar2, uVar3, uVar4, uVar5);
    FUN_00408250(0x3fa00000);
    ExceptionList = local_10;
    return param_1;
}
