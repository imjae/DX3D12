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

#include "DXSample.h"

// Note that while ComPtr is used to manage the lifetime of resources on the CPU,
// it has no understanding of the lifetime of resources on the GPU. Apps must account
// for the GPU lifetime of resources to avoid destroying objects that may still be
// referenced by the GPU.
//
// ComPtr는 CPU에서 리소스의 수명을 관리하지만 GPU에서의 리소스 수명은 추적하지 않는다.
// 앱은 GPU가 아직 참조할 수 있는 객체를 파괴하지 않도록 GPU에서의 리소스 수명도 관리해야 한다.
// An example of this can be found in the class method: OnDestroy(). | 이 클래스의 OnDestroy() 메서드에서 예를 볼 수 있다.
using Microsoft::WRL::ComPtr;

class D3D12HelloWindow : public DXSample
{
public:
    D3D12HelloWindow(UINT width, UINT height, std::wstring name);

    virtual void OnInit();
    virtual void OnUpdate();
    virtual void OnRender();
    virtual void OnDestroy();

private:
    static const UINT FrameCount = 2;

    // Pipeline objects. | 파이프라인 객체.
    ComPtr<IDXGISwapChain3> m_swapChain;
    ComPtr<ID3D12Device> m_device;
    ComPtr<ID3D12Resource> m_renderTargets[FrameCount];
    ComPtr<ID3D12CommandAllocator> m_commandAllocator;
    ComPtr<ID3D12CommandQueue> m_commandQueue;
    ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
    ComPtr<ID3D12PipelineState> m_pipelineState;
    ComPtr<ID3D12GraphicsCommandList> m_commandList;
    UINT m_rtvDescriptorSize;

    // Synchronization objects. | 동기화 객체.
    UINT m_frameIndex;
    HANDLE m_fenceEvent;
    ComPtr<ID3D12Fence> m_fence;
    UINT64 m_fenceValue;

    void LoadPipeline();
    void LoadAssets();
    void PopulateCommandList();
    void WaitForPreviousFrame();
};
