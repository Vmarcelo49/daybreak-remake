// ============================================
// Address:  0x0066d47c
// Original: FUN_0066d47c
// Status:   unreviewed
// ============================================

void FUN_0066d47c(void)

{
    _ptiddata p_Var1;

    p_Var1 = __getptd();
    if (0 < (int)p_Var1->_purecall)
    {
        p_Var1            = __getptd();
        p_Var1->_purecall = (void *)((int)p_Var1->_purecall + -1);
    }
    return;
}
