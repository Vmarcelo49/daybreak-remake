// Function: FUN_00648f30
// Address:  0x00648f30
// Source:   batch_decompile (mass dump)
// Hash:     d3700dea03df7f7c


/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall FUN_00648f30(int param_1,undefined1 param_2)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  int local_130;
  int local_120;
  CHAR local_11c [268];
  char local_10 [8];
  undefined4 local_8;
  
  local_8 = DAT_006b77f4;
  *(undefined1 *)(param_1 + 0x53a6) = param_2;
  wsprintfA(local_11c,"data/scenario/team%02d.dat",(int)*(char *)(param_1 + 0x53a6));
  FUN_00653540(local_11c);
  uVar3 = FUN_00653860();
  *(undefined4 *)(param_1 + 0x5308) = uVar3;
  uVar3 = FUN_00653860();
  *(undefined4 *)(param_1 + 0x530c) = uVar3;
  local_10[0] = '\0';
  local_10[1] = 1;
  local_10[2] = 2;
  local_10[3] = 3;
  local_10[4] = 4;
  local_10[5] = 5;
  if (((*(char *)(param_1 + 0x53a6) != '\x01') && (*(char *)(param_1 + 0x53a6) != '\x05')) &&
     (*(char *)(param_1 + 0x53a6) != '\x06')) {
    for (local_120 = 0; local_120 < 0x10; local_120 = local_120 + 1) {
      uVar4 = FUN_0065d150();
      uVar5 = FUN_0065d150();
      cVar1 = local_10[uVar4 % 3 + 1];
      local_10[uVar4 % 3 + 1] = local_10[uVar5 % 3 + 1];
      local_10[uVar5 % 3 + 1] = cVar1;
    }
  }
  for (local_130 = 0; local_130 < 6; local_130 = local_130 + 1) {
    uVar2 = FUN_00653860();
    *(undefined1 *)(param_1 + 0x53ad + local_10[local_130] * 2) = uVar2;
    uVar2 = FUN_00653860();
    *(undefined1 *)(param_1 + 0x53ae + local_10[local_130] * 2) = uVar2;
    uVar2 = FUN_00653860();
    *(undefined1 *)(param_1 + 0x53b9 + (int)local_10[local_130]) = uVar2;
    uVar2 = FUN_00653860();
    *(undefined1 *)(param_1 + 0x53bf + (int)local_10[local_130]) = uVar2;
    uVar2 = FUN_00653860();
    *(undefined1 *)(param_1 + 0x53a7 + (int)local_10[local_130]) = uVar2;
  }
  FUN_00653760(param_1 + 0x53c5,0x104);
  if (*(char *)(param_1 + 0x53a6) < '\a') {
    FUN_0065c050(*(undefined4 *)(param_1 + 0x10));
  }
  else {
    FUN_0065c050(*(undefined4 *)(param_1 + 0x14));
  }
  *(undefined4 *)(param_1 + 0x52e0) = 4;
  *(undefined4 *)(param_1 + 0x52e4) = 4;
  *(undefined4 *)(param_1 + 0x538c) = 2;
  *(undefined4 *)(param_1 + 0x5390) = 3;
  *(undefined1 *)(param_1 + 0x5330) = 0;
  *(undefined1 *)(param_1 + 0x5331) = 0;
  *(undefined1 *)(param_1 + 0x5332) = 0;
  *(undefined1 *)(param_1 + 0x5333) = 0;
  *(undefined1 *)(param_1 + 0x5334) = 0;
  *(undefined1 *)(param_1 + 0x5335) = 0;
  *(undefined1 *)(param_1 + 0x53a4) = 0;
  *(undefined1 *)(param_1 + 0x53a5) = 0;
  FUN_0064ab30(0);
  FUN_0064ab30(1);
  *(undefined4 *)(param_1 + 0x4ba0) = 0;
  *(undefined4 *)(param_1 + 0x4b94) = 100;
  *(undefined4 *)(param_1 + 0x4b90) = 100;
  *(undefined4 *)(param_1 + 0x4b98) = 100;
  *(undefined4 *)(param_1 + 0x4b9c) = 100;
  return;
}

