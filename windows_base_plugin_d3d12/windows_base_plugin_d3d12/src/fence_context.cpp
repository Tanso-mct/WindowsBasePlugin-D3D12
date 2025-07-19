#include "windows_base_plugin_d3d12/src/pch.h"
#include "windows_base_plugin_d3d12/include/fence_context.h"

#include "windows_base_plugin_d3d12/include/d3d12_helpers.h"

wbp_d3d12::FenceContext::FenceContext(UINT frameCount)
{
    fenceValues_.resize(frameCount, INITIAL_FENCE_VALUE);
}

wbp_d3d12::FenceContext::~FenceContext()
{
    wbp_d3d12::CloseFenceEvent(fenceEvent_);
}