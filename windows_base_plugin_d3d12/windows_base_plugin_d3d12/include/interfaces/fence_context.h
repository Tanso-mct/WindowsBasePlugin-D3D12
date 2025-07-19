#pragma once
#include "windows_base/windows_base.h"

#include <d3d12.h>
#include <wrl/client.h>

namespace wbp_d3d12
{
    class IFenceContext : public wb::IContext
    {
    public:
        virtual ~IFenceContext() = default;

        virtual Microsoft::WRL::ComPtr<ID3D12Fence> &Fence() = 0;
        virtual std::vector<UINT64> &FenceValues() = 0;
        virtual HANDLE &FenceEvent() = 0;
    };

} // namespace wbp_d3d12