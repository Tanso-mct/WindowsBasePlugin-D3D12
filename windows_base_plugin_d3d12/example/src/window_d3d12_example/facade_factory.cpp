#include "example/src/pch.h"
#include "example/include/window_d3d12_example/facade_factory.h"

#include "example/include/window_d3d12_example/monitor_keyboard.h"
#include "example/include/window_d3d12_example/monitor_mouse.h"

std::unique_ptr<wb::IWindowFacade> example::D3D12ExampleWindowFacadeFactory::Create() const
{
    std::unique_ptr<wb::IWindowFacade> facade = std::make_unique<wb::DefaultWindowFacade>();

    {
        std::unique_ptr<wb::IWindowContext> context = std::make_unique<wb::WindowContext>();
        context->Name() = L"D3D12Example Window";

        facade->SetContext(std::move(context));
    }

    facade->AddMonitorID(example::D3D12ExampleKeyboardMonitorID());
    facade->AddMonitorID(example::D3D12ExampleMouseMonitorID());

    return facade;
}