#include "windows_base_plugin_d3d12/src/pch.h"
#include "windows_base_plugin_d3d12/include/window_d3d12_facade.h"

#include "windows_base_plugin_d3d12/include/d3d12_helpers.h"
#include "windows_base_plugin_d3d12/include/gpu_context.h"
#include "windows_base_plugin_d3d12/include/swap_chain_context.h"
#include "windows_base_plugin_d3d12/include/render_target_context.h"
#include "windows_base_plugin_d3d12/include/fence_context.h"

#pragma comment(lib, "windows_base.lib")

wbp_d3d12::WindowD3D12Facade::WindowD3D12Facade(UINT renderTargetCount, UINT depthStencilCount) :
    RENDER_TARGET_COUNT(renderTargetCount),
    DEPTH_STENCIL_COUNT(depthStencilCount)
{
    if (renderTargetCount == 0)
    {
        std::string err = wb::CreateErrorMessage
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"Render target count must be greater than 0."}
        );

        wb::ConsoleLogErr(err);
        wb::ErrorNotify("WINDOWS_BASE_PLUGIN_D3D12", err);
        wb::ThrowRuntimeError(err);
    }

    if (depthStencilCount == 0)
    {
        std::string err = wb::CreateErrorMessage
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"Depth stencil count must be greater than 0."}
        );

        wb::ConsoleLogErr(err);
        wb::ErrorNotify("WINDOWS_BASE_PLUGIN_D3D12", err);
        wb::ThrowRuntimeError(err);
    }
}

bool wbp_d3d12::WindowD3D12Facade::CheckIsReady() const
{
    if (context_ == nullptr)
    {
        std::string err = wb::CreateErrorMessage
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"Context is not set for this window facade."}
        );

        wb::ConsoleLogWrn(err);
        return false;
    }

    if (swapChainContext_ == nullptr)
    {
        std::string err = wb::CreateErrorMessage
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"Swap chain context is not set for this window facade."}
        );

        wb::ConsoleLogWrn(err);
        return false;
    }

    if (renderTargetContext_ == nullptr)
    {
        std::string err = wb::CreateErrorMessage
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"Render target context is not set for this window facade."}
        );

        wb::ConsoleLogWrn(err);
        return false;
    }

    if (fenceContext_ == nullptr)
    {
        std::string err = wb::CreateErrorMessage
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"Fence context is not set for this window facade."}
        );

        wb::ConsoleLogWrn(err);
        return false;
    }

    return true;
}

void wbp_d3d12::WindowD3D12Facade::Create(WNDCLASSEX &wc)
{
    if (!CheckIsReady())
    {
        std::string err = wb::CreateErrorMessage
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"Window facade is not ready."}
        );

        wb::ConsoleLogErr(err);
        wb::ErrorNotify("WINDOWS_BASE_PLUGIN_D3D12", err);
        wb::ThrowRuntimeError(err);
    }

    /*******************************************************************************************************************
     * Create window
    /******************************************************************************************************************/

    wb::CreateWindowWB
    (
        context_->Handle(), context_->Style(), context_->Name().c_str(),
        context_->PosX(), context_->PosY(), context_->Width(), context_->Height(),
        context_->ParentHandle(), wc
    );

    // Keep the window's instance
    context_->Instance() = wc.hInstance;

    /*******************************************************************************************************************
     * Get the window's client area size
    /******************************************************************************************************************/

    {
        RECT clientRect;
        if (!GetClientRect(context_->Handle(), &clientRect))
        {
            std::string err = wb::CreateErrorMessage
            (
                __FILE__, __LINE__, __FUNCTION__,
                {"Failed to get client rectangle for the window."}
            );

            wb::ConsoleLogErr(err);
            wb::ErrorNotify("WINDOWS_BASE", err);
            wb::ThrowRuntimeError(err);
        }

        context_->ClientWidth() = clientRect.right - clientRect.left;
        context_->ClientHeight() = clientRect.bottom - clientRect.top;

        POINT clientPos = {clientRect.left, clientRect.top};
        if (!ClientToScreen(context_->Handle(), &clientPos))
        {
            std::string err = wb::CreateErrorMessage
            (
                __FILE__, __LINE__, __FUNCTION__,
                {"Failed to convert client position to screen coordinates."}
            );

            wb::ConsoleLogErr(err);
            wb::ErrorNotify("WINDOWS_BASE", err);
            wb::ThrowRuntimeError(err);
        }

        context_->PosX() = clientPos.x;
        context_->PosY() = clientPos.y;
    }

    /*******************************************************************************************************************
     * Enable raw input for the window
    /******************************************************************************************************************/

    {
        RAWINPUTDEVICE rawInputDevice[2];

        // Mouse
        rawInputDevice[0].usUsagePage = 0x01; // Generic Desktop Controls
        rawInputDevice[0].usUsage = 0x02; // Mouse
        rawInputDevice[0].dwFlags = 0;
        rawInputDevice[0].hwndTarget = context_->Handle();

        // Keyboard
        rawInputDevice[1].usUsagePage = 0x01; // Generic Desktop
        rawInputDevice[1].usUsage = 0x06; // Keyboard
        rawInputDevice[1].dwFlags = 0;
        rawInputDevice[1].hwndTarget = context_->Handle();

        if (!RegisterRawInputDevices(rawInputDevice, 2, sizeof(RAWINPUTDEVICE)))
        {
            std::string err = wb::CreateErrorMessage
            (
                __FILE__, __LINE__, __FUNCTION__,
                {"Failed to register raw input devices for the window."}
            );

            wb::ConsoleLogErr(err);
            wb::ErrorNotify("WINDOWS_BASE", err);
            wb::ThrowRuntimeError(err);
        }
    }

    /*******************************************************************************************************************
     * Check if the GPU context is created
    /******************************************************************************************************************/

    wbp_d3d12::GPUContext &gpuContext = wbp_d3d12::GPUContext::GetInstance();
    if (!gpuContext.IsCreated())
    {
        std::string err = wb::CreateErrorMessage
        (
            __FILE__, __LINE__, __FUNCTION__,
            {"GPU context is not created. Cannot create window."}
        );

        wb::ConsoleLogErr(err);
        wb::ErrorNotify("WINDOWS_BASE_PLUGIN_D3D12", err);
        wb::ThrowRuntimeError(err);
    }

    /*******************************************************************************************************************
     * Create swap chain
    /******************************************************************************************************************/

    swapChainContext_->GetFrameCount() = RENDER_TARGET_COUNT;

    wbp_d3d12::CreateSwapChain
    (
        gpuContext.GetFactory(), gpuContext.GetCommandQueue(),
        swapChainContext_->GetFrameCount(), swapChainContext_->GetFrameIndex(),
        context_->Handle(), context_->ClientWidth(), context_->ClientHeight(),
        swapChainContext_->GetSwapChain()
    );

    /*******************************************************************************************************************
     * Get render targets from the swap chain
    /******************************************************************************************************************/

    renderTargetContext_->SetRenderTargetCount(RENDER_TARGET_COUNT);
    renderTargetContext_->SetDepthStencilCount(DEPTH_STENCIL_COUNT);
    renderTargetContext_->Resize();

    wbp_d3d12::GetBuffersFromSwapChain
    (
        swapChainContext_->GetSwapChain(), swapChainContext_->GetFrameCount(),
        renderTargetContext_->GetRenderTargets()
    );

    for (UINT i = 0; i < renderTargetContext_->GetRenderTargetCount(); ++i)
    {
        wbp_d3d12::SetName
        (
            renderTargetContext_->GetRenderTargets()[i],
            L"SwapChain_RenderTarget" + std::to_wstring(i)
        );
    }

    /*******************************************************************************************************************
     * Create RTV
    /******************************************************************************************************************/

    wbp_d3d12::CreateRenderTargetViewHeap
    (
        gpuContext.GetDevice(), renderTargetContext_->GetRenderTargetCount(),
        renderTargetContext_->GetRtvDescriptorHeap(), renderTargetContext_->GetRtvDescriptorSize()
    );
}