#include "pch.h"

#include "windows_base_plugin_d3d12/include/swap_chain_context.h"
#pragma comment(lib, "windows_base_plugin_d3d12.lib")

TEST(SwapChainContext, Get)
{
    const UINT frameCount = 2;
    std::unique_ptr<wbp_d3d12::ISwapChainContext> swapChainContext 
        = std::make_unique<wbp_d3d12::SwapChainContext>(frameCount);

    EXPECT_NE(swapChainContext, nullptr);
    EXPECT_EQ(swapChainContext->FrameCount(), frameCount);
    EXPECT_EQ(swapChainContext->FrameIndex(), 0);
    EXPECT_EQ(swapChainContext->SwapChain().Get(), nullptr);
}