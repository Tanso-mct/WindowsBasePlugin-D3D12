#include "pch.h"

#include "windows_base_plugin_d3d12/include/render_target_context.h"
#pragma comment(lib, "windows_base_plugin_d3d12.lib")

TEST(RenderTargetContext, Get)
{
    const UINT RENDER_TARGET_COUNT = 2;
    const UINT DEPTH_STENCIL_COUNT = 1;
    std::unique_ptr<wbp_d3d12::IRenderTargetContext> renderTargetContext 
        = std::make_unique<wbp_d3d12::RenderTargetContext>(RENDER_TARGET_COUNT, DEPTH_STENCIL_COUNT);

    EXPECT_NE(renderTargetContext, nullptr);
    EXPECT_EQ(renderTargetContext->CommandAllocators().size(), RENDER_TARGET_COUNT);
    EXPECT_EQ(renderTargetContext->CommandLists().size(), RENDER_TARGET_COUNT);

    EXPECT_EQ(renderTargetContext->RenderTargetCount(), RENDER_TARGET_COUNT);
    EXPECT_EQ(renderTargetContext->RenderTargets().size(), RENDER_TARGET_COUNT);
    EXPECT_TRUE(renderTargetContext->RtvDescriptorHeap() == nullptr);
    EXPECT_EQ(renderTargetContext->RtvDescriptorSize(), 0);

    EXPECT_EQ(renderTargetContext->DepthStencilCount(), DEPTH_STENCIL_COUNT);
    EXPECT_EQ(renderTargetContext->DepthStencils().size(), DEPTH_STENCIL_COUNT);
    EXPECT_TRUE(renderTargetContext->DsvDescriptorHeap() == nullptr);
    EXPECT_EQ(renderTargetContext->DsvDescriptorSize(), 0);

    D3D12_VIEWPORT &viewport = renderTargetContext->ViewPort();
    D3D12_RECT &scissorRect = renderTargetContext->ScissorRect();
}