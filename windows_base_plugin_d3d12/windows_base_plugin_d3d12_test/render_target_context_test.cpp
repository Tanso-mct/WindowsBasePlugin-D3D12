#include "pch.h"

#include "windows_base_plugin_d3d12/include/render_target_context.h"
#pragma comment(lib, "windows_base_plugin_d3d12.lib")

TEST(RenderTargetContext, Get)
{
    const UINT RENDER_TARGET_COUNT = 2;
    const UINT DEPTH_STENCIL_COUNT = 1;
    std::unique_ptr<wbp_d3d12::IRenderTargetContext> renderTargetContext 
        = std::make_unique<wbp_d3d12::RenderTargetContext>();

    renderTargetContext->SetRenderTargetCount(RENDER_TARGET_COUNT);
    renderTargetContext->SetDepthStencilCount(DEPTH_STENCIL_COUNT); 
    renderTargetContext->Resize();

    EXPECT_NE(renderTargetContext, nullptr);
    EXPECT_EQ(renderTargetContext->GetCommandAllocators().size(), RENDER_TARGET_COUNT);
    EXPECT_EQ(renderTargetContext->GetCommandLists().size(), RENDER_TARGET_COUNT);

    EXPECT_EQ(renderTargetContext->GetRenderTargetCount(), RENDER_TARGET_COUNT);
    EXPECT_EQ(renderTargetContext->GetRenderTargets().size(), RENDER_TARGET_COUNT);
    EXPECT_TRUE(renderTargetContext->GetRtvDescriptorHeap() == nullptr);
    EXPECT_EQ(renderTargetContext->GetRtvDescriptorSize(), 0);

    EXPECT_EQ(renderTargetContext->GetDepthStencilCount(), DEPTH_STENCIL_COUNT);
    EXPECT_EQ(renderTargetContext->GetDepthStencils().size(), DEPTH_STENCIL_COUNT);
    EXPECT_TRUE(renderTargetContext->GetDsvDescriptorHeap() == nullptr);
    EXPECT_EQ(renderTargetContext->GetDsvDescriptorSize(), 0);

    D3D12_VIEWPORT &viewport = renderTargetContext->GetViewPort();
    D3D12_RECT &scissorRect = renderTargetContext->GetScissorRect();
}