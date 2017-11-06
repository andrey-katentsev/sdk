//
// FILE: hsModule.cpp
// DESCRIPTION: module image helper.
// CREATED: 21/05/2012
// AUTHOR: Andrey A. Katentsev
//
// COPYRIGHT © 2012, Hyperlink Software.
//

#include "hsModule.h"

// SUMMARY
//  NAME: hsGetModuleHandle
//  AUTHOR:  Andrew A. Katentsev
//  PARAMS: this function has no parameters.
//  RETURNS: retrieves a module handle for the caller module.
//  CREATED: 21/05/2012
//  PURPOSE: used to get DLL instance.
//  NOTES: no error processing.
HINSTANCE hsGetModuleHandle(void)
{
	MEMORY_BASIC_INFORMATION mbi = {0};
	VirtualQuery(hsGetModuleHandle, &mbi, sizeof(mbi));
	return reinterpret_cast<HINSTANCE>(mbi.AllocationBase);
}