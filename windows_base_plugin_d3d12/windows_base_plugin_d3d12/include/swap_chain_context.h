#pragma once
#include "windows_base_plugin_d3d12/include/dll_config.h"

#include "windows_base_plugin_d3d12/include/interfaces/swap_chain_context.h"

namespace wbp_d3d12
{
    class WBP_D3D12_API SwapChainContext : public ISwapChainContext
    {
    private:
        Microsoft::WRL::ComPtr<IDXGISwapChain3> swapChain_ = nullptr;
        const UINT frameCount_;
        UINT frameIndex_ = 0;

    public:
        SwapChainContext(UINT frameCount);

        Microsoft::WRL::ComPtr<IDXGISwapChain3>& SwapChain() override { return swapChain_; }
        const UINT& FrameCount() const override { return frameCount_; }
        UINT& FrameIndex() override { return frameIndex_; }
    };
} // namespace wbp_d3d12