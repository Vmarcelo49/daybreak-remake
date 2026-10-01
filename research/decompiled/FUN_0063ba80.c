// Function: FUN_0063ba80
// Address:  0x0063ba80
// Source:   batch_decompile (mass dump)
// Hash:     052fc0fc82e9534c


undefined4 __thiscall FUN_0063ba80(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 0x84) == '\0') {
    uVar1 = 199;
  }
  else if ((*(uint *)(*(int *)(param_1 + 0x10) + 0x28) & 0x800) == 0) {
    switch(param_2) {
    case 100:
    case 0x65:
    case 200:
    case 0xc9:
      uVar1 = 0xc5;
      break;
    case 0x66:
    case 0xca:
      uVar1 = 0xc0;
      break;
    default:
      uVar1 = 0xc6;
      break;
    case 0x82:
    case 0x83:
    case 0xe6:
    case 0xe7:
      uVar1 = 0xc1;
    }
  }
  else {
    uVar1 = 0xbf;
  }
  return uVar1;
}

