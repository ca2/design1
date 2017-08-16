#include "framework.h"

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   UNREFERENCED_PARAMETER(hInstance);
   UNREFERENCED_PARAMETER(lpReserved);

   if (dwReason == DLL_PROCESS_ATTACH)
   {
      ::output_debug_string("::ca2:: refactor.dll :: initializing!\n");
      

   }
   else if (dwReason == DLL_PROCESS_DETACH)
   {
      ::output_debug_string("::ca2:: refactor.dll :: terminating!\n");
   }
   return 1;   // ok
}


