#include "framework.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		{
			output_debug_string("devedge DLL_PROCESS_ATTACH");
		}
		break;
	case DLL_THREAD_ATTACH:
		{
         output_debug_string("devedge DLL_THREAD_ATTACH");
		}
		break;
	case DLL_THREAD_DETACH:
		{
         output_debug_string("devedge DLL_THREAD_DETACH");
		}
		break;
	case DLL_PROCESS_DETACH:
		{
         output_debug_string("devedge DLL_PROCESS_DETACH");
		}
		break;
	}
	return TRUE;
}
