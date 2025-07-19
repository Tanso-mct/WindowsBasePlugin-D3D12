#include "example/src/pch.h"
#include "example/include/scene_example/system_scheduler.h"

#include "windows_base_plugin_example_render/plugin.h"
#pragma comment(lib, "windows_base_plugin_example_render.lib")

void example::ExampleSystemScheduler::Execute(wb::ISystemContainer &systemCont, wb::SystemArgument &args)
{
    systemCont.Get(wbp_example_render::ExampleRenderSystemID()).Update(args);
}