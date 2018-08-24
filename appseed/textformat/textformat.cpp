#include "framework.h"


#ifndef CUBE

#ifdef METROWIN
[MTAThread]
#endif
WINBOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{

   return _001DefaultDllMain(hInstance, dwReason, lpReserved);

}


#endif