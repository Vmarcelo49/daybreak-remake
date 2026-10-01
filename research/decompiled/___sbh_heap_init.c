// Function: ___sbh_heap_init
// Address:  0x00672f92
// Reason:   keyword:Init


/* Library Function - Single Match
    ___sbh_heap_init
   
   Library: Visual Studio 2003 Release */

undefined4 ___sbh_heap_init(undefined4 param_1)

{
  DAT_006d896c = HeapAlloc(DAT_006d8bc0,0,0x140);
  if (DAT_006d896c == (LPVOID)0x0) {
    return 0;
  }
  DAT_006d8964 = 0;
  DAT_006d8968 = 0;
  DAT_006d8974 = DAT_006d896c;
  DAT_006d8970 = param_1;
  DAT_006d8978 = 0x10;
  return 1;
}

