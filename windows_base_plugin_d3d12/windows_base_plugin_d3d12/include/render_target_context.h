#pragma once
#include "windows_base_plugin_d3d12/include/dll_config.h"

#include "windows_base_plugin_d3d12/include/interfaces/render_target_context.h"

namespace wbp_d3d12
{
    class WBP_D3D12_API RenderTargetContext : public wbp_d3d12::IRenderTargetContext
    {
    private:
        std::vector<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>> commandAllocators_;
        std::vector<Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>> commandLists_;

        const UINT renderTargetCount_;
        std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> renderTargets_;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap_ = nullptr;
        UINT rtvDescriptorSize_ = 0;

        const UINT depthStencilCount_;
        std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> depthStencils_;
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap_ = nullptr;
        UINT dsvDescriptorSize_ = 0;

        D3D12_VIEWPORT viewPort_;
        D3D12_RECT scissorRect_;

    public:
        RenderTargetContext(UINT renderTargetCount, UINT depthStencilCount);
        ~RenderTargetContext() override = default;

        /***************************************************************************************************************
         * IRenderTargetContext implementation
        /**************************************************************************************************************/

        std::vector<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>> &CommandAllocators() override { return commandAllocators_; }
        std::vector<Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>> &CommandLists() override { return commandLists_; }

        const UINT &RenderTargetCount() const override { return renderTargetCount_; }
        std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> &RenderTargets() override { return renderTargets_; }
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> &RtvDescriptorHeap() override { return rtvDescriptorHeap_; }
        UINT &RtvDescriptorSize() override { return rtvDescriptorSize_; }

        const UINT &DepthStencilCount() const override { return depthStencilCount_; }
        std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> &DepthStencils() override { return depthStencils_; }
        Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> &DsvDescriptorHeap() override { return dsvDescriptorHeap_; }
        UINT &DsvDescriptorSize() override { return dsvDescriptorSize_; }

        D3D12_VIEWPORT& ViewPort() override { return viewPort_; }
        D3D12_RECT& ScissorRect() override { return scissorRect_; }
    };

} // namespace wbp_d3d12