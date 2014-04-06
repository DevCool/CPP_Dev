#include <Windows.h>

#define WIN32_LEAN_AND_MEAN

BOOL APIENTRY DllMain( HMODULE hModule,
					   DWORD ul_reason_for_call,
					   LPVOID lpReaserve )
{
	switch( ul_reason_for_call )
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_DETACH:
		break;
	}

	return TRUE;
}
