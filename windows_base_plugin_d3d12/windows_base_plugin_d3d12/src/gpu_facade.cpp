#include "windows_base_plugin_d3d12/src/pch.h"
#include "windows_base_plugin_d3d12/include/gpu_facade.h"

#pragma comment(lib, "windows_base.lib")

#include "windows_base_plugin_d3d12/include/d3d12_helpers.h"

WBP_D3D12_API const size_t &wbp_d3d12::GPUFacadeID()
{
    static size_t id = wb::IDFactory::CreateSharedFacadeID();
    return id;
}

wbp_d3d12::GPUFacade::GPUFacade()
{
    wbp_d3d12::GPUContext &gpuContext = wbp_d3d12::GPUContext::GetInstance();
    if (!gpuContext.IsCreated())
    {
        wbp_d3d12::CreateDX12Factory(gpuContext.GetFactory());
        wbp_d3d12::CreateDX12Device(gpuContext.GetDevice(), gpuContext.GetFeatureLevel(), gpuContext.GetFactory());
        wbp_d3d12::CreateDX12CommandQueue(gpuContext.GetDevice(), gpuContext.GetCommandQueue());

        gpuContext.IsCreated() = true;
    }
    else
    {
        std::string err = wb::CreateErrorMessage
        (
            __FILE__, __LINE__, __FUNCTION__,
            { "GPUContext is already created. No need to create it again." }
        );
        wb::ConsoleLogErr(err);
        wb::ErrorNotify("WindowsBasePlugin-D3D12", err);
        wb::ThrowRuntimeError(err);
    }
}

void wbp_d3d12::GPUFacade::SetContext(std::unique_ptr<wb::IContext> context)
{
    // GPUContext is a singleton, so not necessary to set context here
}

bool wbp_d3d12::GPUFacade::CheckIsReady() const
{
    return true;
}

namespace wbp_d3d12
{
    WB_REGISTER_SHARED_FACADE(GPUFacadeID, GPUFacade);

} // namespace wbp_d3d12