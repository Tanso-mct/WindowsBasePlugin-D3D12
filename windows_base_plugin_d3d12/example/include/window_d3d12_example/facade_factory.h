#pragma once
#include "windows_base/windows_base.h"

namespace example
{
    constexpr UINT RENDER_TARGET_COUNT = 2;
    constexpr UINT DEPTH_STENCIL_COUNT = 1;

    class D3D12ExampleWindowFacadeFactory : public wb::IWindowFacadeFactory
    {
    public:
        D3D12ExampleWindowFacadeFactory() = default;
        ~D3D12ExampleWindowFacadeFactory() override = default;

        std::unique_ptr<wb::IWindowFacade> Create() const override;
    };

} // namespace example