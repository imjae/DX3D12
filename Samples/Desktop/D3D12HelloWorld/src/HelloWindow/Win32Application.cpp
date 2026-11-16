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

#include "stdafx.h"
#include "Win32Application.h"

HWND Win32Application::m_hwnd = nullptr;

int Win32Application::Run(DXSample* pSample, HINSTANCE hInstance, int nCmdShow)
{
    // Parse the command line parameters | 명령줄 인수를 파싱한다.
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    pSample->ParseCommandLineArgs(argv, argc);
    LocalFree(argv);

    // Initialize the window class. | 윈도우 클래스를 초기화한다.
    WNDCLASSEX windowClass = { 0 };
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName = L"DXSampleClass";
    RegisterClassEx(&windowClass);

    RECT windowRect = { 0, 0, static_cast<LONG>(pSample->GetWidth()), static_cast<LONG>(pSample->GetHeight()) };
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);

    // Create the window and store a handle to it. | 창을 생성하고 창 핸들을 저장한다.
    m_hwnd = CreateWindow(
        windowClass.lpszClassName,
        pSample->GetTitle(),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr,        // We have no parent window. | 부모 창이 없다.
        nullptr,        // We aren't using menus. | 메뉴를 사용하지 않는다.
        hInstance,
        pSample);

    // Initialize the sample. OnInit is defined in each child-implementation of DXSample. | 샘플을 초기화한다. OnInit은 DXSample을 상속한 각 클래스에서 정의한다.
    pSample->OnInit();

    ShowWindow(m_hwnd, nCmdShow);

    // Main sample loop. | 샘플의 메인 루프.
    MSG msg = {};
    while (msg.message != WM_QUIT)
    {
        // Process any messages in the queue. | 큐에 들어 있는 메시지를 처리한다.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    pSample->OnDestroy();

    // Return this part of the WM_QUIT message to Windows. | WM_QUIT 메시지의 이 부분(wParam)을 Windows에 반환한다.
    return static_cast<char>(msg.wParam);
}

// Main message handler for the sample. | 샘플의 기본 메시지 핸들러.
LRESULT CALLBACK Win32Application::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    DXSample* pSample = reinterpret_cast<DXSample*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch (message)
    {
    case WM_CREATE:
        {
            // Save the DXSample* passed in to CreateWindow. | CreateWindow에 전달한 DXSample* 포인터를 저장한다.
            LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
        }
        return 0;

    case WM_KEYDOWN:
        if (pSample)
        {
            pSample->OnKeyDown(static_cast<UINT8>(wParam));
        }
        return 0;

    case WM_KEYUP:
        if (pSample)
        {
            pSample->OnKeyUp(static_cast<UINT8>(wParam));
        }
        return 0;

    case WM_PAINT:
        if (pSample)
        {
            pSample->OnUpdate();
            pSample->OnRender();
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    // Handle any messages the switch statement didn't. | switch 문에서 처리하지 않은 메시지를 처리한다.
    return DefWindowProc(hWnd, message, wParam, lParam);
}
