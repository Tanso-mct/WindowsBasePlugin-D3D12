#include "windows_base_plugin_d3d12/src/pch.h"
#include "windows_base_plugin_d3d12/include/render_target_context.h"

wbp_d3d12::RenderTargetContext::RenderTargetContext(UINT renderTargetCount, UINT depthStencilCount) :
    renderTargetCount_(renderTargetCount),
    depthStencilCount_(depthStencilCount),
    rtvDescriptorSize_(0),
    dsvDescriptorSize_(0)
{
    // Resize vectors to hold the specified number of render targets and depth stencils
    renderTargets_.resize(renderTargetCount_);
    commandAllocators_.resize(renderTargetCount_);
    commandLists_.resize(renderTargetCount_);
    depthStencils_.resize(depthStencilCount_);
}   