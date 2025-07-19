#include "pch.h"

#pragma comment(lib, "windows_base.lib")

#include "windows_base_plugin_d3d12/include/gpu_facade.h"
#pragma comment(lib, "windows_base_plugin_d3d12.lib")

TEST(GPUFacade, Create)
{
    // Get the gpu facade factory from registry
    wb::ISharedFacadeFactory &factory = wb::gSharedFacadeRegistry.GetFactory(wbp_d3d12::GPUFacadeID());

    // Create GPUFacade instance
    std::unique_ptr<wb::ISharedFacade> gpuFacade = factory.Create();

    EXPECT_NE(gpuFacade, nullptr);
    EXPECT_TRUE(gpuFacade->CheckIsReady());

    // Check if the GPUContext is created
    wbp_d3d12::GPUContext &gpuContext = wbp_d3d12::GPUContext::GetInstance();
    EXPECT_TRUE(gpuContext.IsCreated());
}