// ============================================
// Address:  0x006890c0
// Original: FUN_006890c0
// Status:   unreviewed
// ============================================


int __thiscall
FUN_006890c0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,void *param_6,undefined4 param_7)

{
  int iVar1;
  void *pvVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0069f57e;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0068dee0(param_2,0);
  local_8 = 0;
  FUN_0068d8d0();
  FUN_0068d8d0();
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = param_7;
  *(undefined4 *)(param_1 + 0x20) = param_4;
  *(undefined1 *)(param_1 + 0x24) = 0;
  *(undefined1 *)(param_1 + 0x25) = 0;
  *(undefined1 *)(param_1 + 0x26) = 0;
  *(undefined4 *)(param_1 + 0x28) = param_3;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  *(undefined4 *)(param_1 + 0x30) = 1;
  FUN_00686800();
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_0068d890();
  FUN_0068d8f0(0xffffffff,0x7fffffff);
  *(undefined8 *)(param_1 + 0x90) = 0x3ff0000000000000;
  if (param_6 != (void *)0x0) {
    iVar1 = FUN_006925d0(param_6);
    pvVar2 = operator_new((iVar1 + 1) * 2);
    *(void **)(param_1 + 0x14) = pvVar2;
    if (*(int *)(param_1 + 0x14) != 0) {
      _memcpy(*(void **)(param_1 + 0x14),param_6,(iVar1 + 1) * 2);
    }
  }
  ExceptionList = local_10;
  return param_1;
}

