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

#pragma once

#include "DXSampleHelper.h"
#include "Win32Application.h"

class DXSample
{
public:
    DXSample(UINT width, UINT height, std::wstring name);
    virtual ~DXSample();

    virtual void OnInit() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnRender() = 0;
    virtual void OnDestroy() = 0;

    // Samples override the event handlers to handle specific messages. | 각 샘플은 특정 메시지를 처리하기 위해 이벤트 핸들러를 재정의한다.
    virtual void OnKeyDown(UINT8 /*key*/ /* 키 */)   {}
    virtual void OnKeyUp(UINT8 /*key*/ /* 키 */)     {}

    // Accessors. | 접근자.
    UINT GetWidth() const           { return m_width; }
    UINT GetHeight() const          { return m_height; }
    const WCHAR* GetTitle() const   { return m_title.c_str(); }

    void ParseCommandLineArgs(_In_reads_(argc) WCHAR* argv[], int argc);

protected:
    std::wstring GetAssetFullPath(LPCWSTR assetName);

    void GetHardwareAdapter(
        _In_ IDXGIFactory1* pFactory,
        _Outptr_result_maybenull_ IDXGIAdapter1** ppAdapter,
        bool requestHighPerformanceAdapter = false);

    void SetCustomWindowText(LPCWSTR text);

    // Viewport dimensions. | 뷰포트 크기.
    UINT m_width;
    UINT m_height;
    float m_aspectRatio;

    // Adapter info. | 어댑터 정보.
    bool m_useWarpDevice;

private:
    // Root assets path. | 에셋 루트 경로.
    std::wstring m_assetsPath;

    // Window title. | 창 제목.
    std::wstring m_title;
};
