#include "example/src/pch.h"
#include "example/include/window_d3d12_example/monitor_mouse.h"

const size_t &example::D3D12ExampleMouseMonitorID()
{
    static size_t id = wb::IDFactory::CreateMonitorID();
    return id;
}

namespace example
{
    WB_REGISTER_MONITOR(D3D12ExampleMouseMonitorID, wb::DefaultMouseMonitorFactoryID());
}