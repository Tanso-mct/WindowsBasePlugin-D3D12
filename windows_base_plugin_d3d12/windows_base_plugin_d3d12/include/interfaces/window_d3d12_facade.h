#pragma once

#include <d3d12.h>

#include "windows_base_plugin_d3d12/include/interfaces/swap_chain_context.h"
#include "windows_base_plugin_d3d12/include/interfaces/render_target_context.h"
#include "windows_base_plugin_d3d12/include/interfaces/fence_context.h"

namespace wbp_d3d12
{
    class ID3D12WindowFacade
    {
    public:
        virtual ~ID3D12WindowFacade() = default;

        virtual void SetSwapChainContext(std::unique_ptr<ISwapChainContext> swapChainContext) = 0;
        virtual void SetRenderTargetContext(std::unique_ptr<IRenderTargetContext> renderTargetContext) = 0;
        virtual void SetFenceContext(std::unique_ptr<IFenceContext> fenceContext) = 0;

        virtual void ResetCommand(ID3D12PipelineState *pipelineState) = 0;
        virtual void CloseCommand() = 0;

        virtual void SetBarrierToRenderTarget() = 0;
        virtual void SetBarrierToPresent() = 0;
        virtual void SetRenderTarget() = 0;

        virtual ID3D12CommandAllocator *GetCommandAllocator() = 0;
        virtual ID3D12GraphicsCommandList *GetCommandList() = 0;

        virtual void ClearViews(const float (&clearColor)[4]) = 0;
        virtual void Present() = 0;

        virtual void WaitForGPU() = 0;
        virtual void WaitThisFrameForGPU() = 0;

    };

} // namespace wbp_d3d12