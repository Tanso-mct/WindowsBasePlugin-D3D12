#include "pch.h"

#include "windows_base_plugin_d3d12/include/fence_context.h"
#pragma comment(lib, "windows_base_plugin_d3d12.lib")

TEST(FenceContext, Get)
{
    const UINT frameCount = 2;
    std::unique_ptr<wbp_d3d12::IFenceContext> fenceContext = std::make_unique<wbp_d3d12::FenceContext>();

    fenceContext->SetFenceCount(frameCount);
    fenceContext->Resize();

    EXPECT_NE(fenceContext, nullptr);
    EXPECT_EQ(fenceContext->GetFenceValues().size(), frameCount);
    EXPECT_EQ(fenceContext->GetFenceValues()[0], wbp_d3d12::INITIAL_FENCE_VALUE);
    EXPECT_EQ(fenceContext->GetFenceValues()[1], wbp_d3d12::INITIAL_FENCE_VALUE);
    
    EXPECT_TRUE(fenceContext->GetFence().Get() == nullptr);
    EXPECT_TRUE(fenceContext->GetFenceEvent() == nullptr);
}