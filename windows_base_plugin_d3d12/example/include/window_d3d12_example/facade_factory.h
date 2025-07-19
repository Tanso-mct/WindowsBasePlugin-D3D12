#pragma once
#include "windows_base/windows_base.h"

namespace example
{
    class D3D12ExampleWindowFacadeFactory : public wb::IWindowFacadeFactory
    {
    public:
        D3D12ExampleWindowFacadeFactory() = default;
        ~D3D12ExampleWindowFacadeFactory() override = default;

        std::unique_ptr<wb::IWindowFacade> Create() const override;
    };

} // namespace example