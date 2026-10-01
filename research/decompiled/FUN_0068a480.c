// Function: FUN_0068a480
// Address:  0x0068a480
// Source:   batch_decompile (mass dump)
// Hash:     ee6f45bb4b831ad2


int __thiscall
FUN_0068a480(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,undefined4 param_6)

{
  FUN_006890c0(param_2,param_3,param_4,param_5,param_6,0);
  FUN_0068d8d0();
  *(undefined4 *)(param_1 + 0x9c) = 0;
  *(undefined1 *)(param_1 + 0xa0) = 0;
  *(undefined1 *)(param_1 + 0xa1) = 0;
  _memset((void *)(param_1 + 0xa8),0,0x30);
  return param_1;
}

