// Function: FUN_0068f9f0
// Address:  0x0068f9f0
// Source:   batch_decompile (mass dump)
// Hash:     4d1c0fdfc1c3eb4e


undefined4 __fastcall FUN_0068f9f0(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  uint local_14;
  int local_10;
  int local_8;
  
  if (((*(int *)(param_1 + 0x70) == 0) || (*(int *)(param_1 + 0x74) != 0)) ||
     (*(int *)(param_1 + 0xc0) != 0)) {
    uVar1 = 0;
  }
  else if (*(int *)(param_1 + 0x18) == 0) {
    uVar1 = FUN_0068fae0();
  }
  else {
    uVar4 = FUN_00697fc0();
    uVar2 = (uint)uVar4 + *(uint *)(param_1 + 0xb8);
    iVar3 = (int)((ulonglong)uVar4 >> 0x20) + *(int *)(param_1 + 0xbc) +
            (uint)CARRY4((uint)uVar4,*(uint *)(param_1 + 0xb8));
    (**(code **)(**(int **)(param_1 + 0x18) + 0xc))
              (*(undefined4 *)(param_1 + 0x18),&local_14,param_1,uVar2,iVar3);
    local_8 = __alldiv(uVar2 - local_14,(iVar3 - local_10) - (uint)(uVar2 < local_14),10000,0);
    if (local_8 < 0x32) {
      uVar1 = FUN_0068fae0();
    }
    else {
      uVar1 = FUN_006932a0(local_8,10,FUN_0068f950,param_1,0);
      *(undefined4 *)(param_1 + 0xc0) = uVar1;
      if (*(int *)(param_1 + 0xc0) == 0) {
        uVar1 = FUN_0068fae0();
      }
      else {
        uVar1 = 0;
      }
    }
  }
  return uVar1;
}

