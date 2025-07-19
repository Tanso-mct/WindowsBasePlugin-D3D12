#pragma once
#include "windows_base/windows_base.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgi1_4.h>
#include <wrl/client.h>

namespace wbp_d3d12
{
    class IRenderTargetContext : public wb::IContext
    {
    public:
        virtual ~IRenderTargetContext() = default;

        virtual std::vector<Microsoft::WRL::ComPtr<ID3D12CommandAllocator>> &CommandAllocators() = 0;
        virtual std::vector<Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>> &CommandLists() = 0;

        virtual const UINT &RenderTargetCount() const = 0;
        virtual std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> &RenderTargets() = 0;
        virtual Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> &RtvDescriptorHeap() = 0;
        virtual UINT &RtvDescriptorSize() = 0;

        virtual const UINT &DepthStencilCount() const = 0;
        virtual std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> &DepthStencils() = 0;
        virtual Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> &DsvDescriptorHeap() = 0;
        virtual UINT &DsvDescriptorSize() = 0;

        virtual D3D12_VIEWPORT& ViewPort() = 0;
        virtual D3D12_RECT& ScissorRect() = 0;
    };

} // namespace wbp_d3d12