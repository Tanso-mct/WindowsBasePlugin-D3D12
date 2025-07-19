#pragma once
#include "windows_base_plugin_d3d12/include/dll_config.h"

#include "windows_base_plugin_d3d12/include/interfaces/swap_chain_context.h"

namespace wbp_d3d12
{
    class SwapChainContext : public ISwapChainContext
    {
    private:
        Microsoft::WRL::ComPtr<IDXGISwapChain3> swapChain_ = nullptr;
        UINT frameCount_ = 0;
        UINT frameIndex_ = 0;

    public:
        SwapChainContext() = default;

        Microsoft::WRL::ComPtr<IDXGISwapChain3>& GetSwapChain() override { return swapChain_; }
        UINT& GetFrameCount() override { return frameCount_; }
        UINT& GetFrameIndex() override { return frameIndex_; }
    };
} // namespace wbp_d3d12