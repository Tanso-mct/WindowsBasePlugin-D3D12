#include "pch.h"

#include "windows_base_plugin_d3d12/include/swap_chain_context.h"
#pragma comment(lib, "windows_base_plugin_d3d12.lib")

TEST(SwapChainContext, Get)
{
    std::unique_ptr<wbp_d3d12::ISwapChainContext> swapChainContext = std::make_unique<wbp_d3d12::SwapChainContext>();

    EXPECT_NE(swapChainContext, nullptr);
    EXPECT_EQ(swapChainContext->GetFrameCount(), 0);
    EXPECT_EQ(swapChainContext->GetFrameIndex(), 0);
    EXPECT_EQ(swapChainContext->GetSwapChain().Get(), nullptr);
    EXPECT_EQ(swapChainContext->GetSyncInterval(), wbp_d3d12::DEFAULT_SYNC_INTERVAL);
}