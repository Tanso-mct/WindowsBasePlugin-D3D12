#pragma once
#include "windows_base_plugin_d3d12/include/dll_config.h"

#include "windows_base_plugin_d3d12/include/interfaces/fence_context.h"

namespace wbp_d3d12
{
    constexpr UINT64 INITIAL_FENCE_VALUE = 0;

    class WBP_D3D12_API FenceContext : public wbp_d3d12::IFenceContext
    {
    private:
        Microsoft::WRL::ComPtr<ID3D12Fence> fence_ = nullptr;
        std::vector<UINT64> fenceValues_;
        HANDLE fenceEvent_ = nullptr;

    public:
        FenceContext(UINT frameCount);
        ~FenceContext() override;

        /***************************************************************************************************************
         * IFenceContext implementation
        /**************************************************************************************************************/

        Microsoft::WRL::ComPtr<ID3D12Fence> &Fence() override { return fence_; }
        std::vector<UINT64> &FenceValues() override { return fenceValues_; }
        HANDLE &FenceEvent() override { return fenceEvent_; }
    };

} // namespace wbp_d3d12