// Function: _Allocate<char>
// Address:  0x00410d00
// Reason:   keyword:char


/* Library Function - Single Match
    char * __cdecl std::_Allocate<char>(unsigned int,char *)
   
   Library: Visual Studio 2003 Debug */

char * __cdecl std::_Allocate<char>(uint param_1,char *param_2)

{
  char *pcVar1;
  
  pcVar1 = operator_new(param_1);
  return pcVar1;
}

