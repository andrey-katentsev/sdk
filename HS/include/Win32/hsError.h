//
// File: hsError.h
// Description: definition of error codes.
// Created: 4/27/2012
// Author: Andrey A. Katentsev
//
// Copyright (c) 2012, Hyperlink Software.
//

#pragma once
#include <stddef.h>

#define ZERO 0

#define HS_MSG_PROCESSED ZERO

#define HS_DLG_OK 1
#define HS_DLG_CANCEL 2
#define HS_DLG_CLOSE 4
#define HS_DLG_ERROR 6

#define HS_DLG_SUCCESS HS_DLG_OK

#define HS_PARAMETER_NOT_USED NULL