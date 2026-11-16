//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// 저작권 (c) Microsoft. 모든 권리는 Microsoft에 있다.
// 이 코드는 MIT 라이선스(MIT)에 따라 제공된다.
// 이 코드는 *있는 그대로* 제공되며, 특정 목적에의 적합성, 상품성 또는 비침해에 대한
// 묵시적 보증을 포함하여 어떠한 명시적 또는 묵시적 보증도 제공하지 않는다.
//
//*********************************************************

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently.
//
// stdafx.h는 표준 시스템 헤더와 자주 사용하지만 변경 빈도가 낮은 프로젝트 전용 헤더를 포함한다.

#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers. | Windows 헤더에서 거의 사용하지 않는 항목을 제외한다.
#endif

#include <windows.h>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "include/d3dx12/d3dx12.h"

#include <string>
#include <wrl.h>
#include <shellapi.h>
