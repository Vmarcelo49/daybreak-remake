// ============================================
// Address:  0x0065f9e0
// Original: FUN_0065f9e0
// Status:   unreviewed
// ============================================


void __thiscall FUN_0065f9e0(undefined4 *param_1,undefined4 *param_2,undefined4 param_3)

{
  int iVar1;
  
  (**(code **)(*(int *)param_1[1] + 0x48))(param_1[1],L"port",&stack0x0000000c,4,2);
  iVar1 = FUN_0066cec4(param_3,1);
  (**(code **)(*(int *)param_1[1] + 0x48))(param_1[1],L"hostname",param_3,iVar1 * 2 + 2);
  _memset(param_1 + 2,0,0x48);
  param_1[2] = 0x48;
  param_1[3] = 1;
  param_1[8] = *param_2;
  param_1[9] = param_2[1];
  param_1[10] = param_2[2];
  param_1[0xb] = param_2[3];
  param_1[0xe] = L"Session";
  FUN_0065f780(0);
  param_1[0x21] = 0;
  (**(code **)(*(int *)*param_1 + 0x1c))
            (*param_1,param_1 + 2,param_1[1],0,0,0,0,0,0,param_1 + 0x21,0);
  return;
}

