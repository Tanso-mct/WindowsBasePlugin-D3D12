#pragma once
#include "windows_base/windows_base.h"

namespace example
{
    class D3D12ExampleWindowEventFactory : public wb::IWindowEventFactory
    {
    public:
        D3D12ExampleWindowEventFactory() = default;
        ~D3D12ExampleWindowEventFactory() override = default;

        std::unique_ptr<wb::IWindowEvent> Create() const override;
    };

} // namespace example

