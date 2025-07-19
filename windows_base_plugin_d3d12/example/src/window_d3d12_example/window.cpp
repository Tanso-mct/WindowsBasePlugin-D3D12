#include "example/src/pch.h"
#include "example/include/window_d3d12_example/window.h"

#include "example/include/window_d3d12_example/facade_factory.h"
#include "example/include/window_d3d12_example/event_factory.h"

const size_t &example::D3D12ExampleWindowID()
{
    static size_t id = wb::IDFactory::CreateWindowID();
    return id;
}

namespace example
{
    WB_REGISTER_WINDOW(D3D12ExampleWindowID, D3D12ExampleWindowFacadeFactory, D3D12ExampleWindowEventFactory);
}