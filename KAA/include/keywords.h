//
// File: keywords.h
// Description: C++11 keywords definition
// Created: April 13, 2013
// Author: Andrey A. Katentsev
//
// Copyright © Andrey A. Katentsev, 2013
//

#pragma once

#if((_MSC_VER <= 1500) && (_MANAGED != 1))
#define constexpr
#define final
#define noexcept throw()
#define nullptr 0
#define override
#define unique_ptr auto_ptr
#endif
