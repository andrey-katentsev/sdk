//
// File: hsTSTD.h
// Description: Generic-Text Mappings for Standart Template Library (STL) and Standard C++ Library (STD).
// Created: 4/8/2012
// Author: Andrey A. Katentsev
//
// Copyright (c) 2012, Hyperlink Software.
//

#pragma once

#ifdef __cplusplus

#ifdef _UNICODE
#define tstring wstring
#else
#define tstring string
#endif

#endif // C++