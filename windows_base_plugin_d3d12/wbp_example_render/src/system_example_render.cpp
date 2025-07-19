#include "wbp_example_render/src/pch.h"
#include "wbp_example_render/include/system_example_render.h"

#include "wbp_d3d12/plugin.h"
#pragma comment(lib, "wbp_d3d12.lib")

const WBP_EXAMPLE_RENDER_API size_t &wbp_example_render::ExampleRenderSystemID()
{
    static size_t id = wb::IDFactory::CreateSystemID();
    return id;
}

const size_t &wbp_example_render::ExampleRenderSystem::GetID() const
{
    return wbp_example_render::ExampleRenderSystemID();
}

void wbp_example_render::ExampleRenderSystem::Initialize(wb::IAssetContainer &assetContainer)
{
    std::string message = wb::CreateMessage
    ({
        "ExampleRenderSystem initialized",
        "Push 'Space' to render random color"
    });
    wb::ConsoleLog(message);
}

void wbp_example_render::ExampleRenderSystem::Update(const wb::SystemArgument &args)
{
    // Get containers to use
    wb::IWindowContainer &windowContainer = args.containerStorage_.GetContainer<wb::IWindowContainer>();
    wb::IMonitorContainer &monitorContainer = args.containerStorage_.GetContainer<wb::IMonitorContainer>();

    // Get the window facade for the current window
    wb::IWindowFacade &window = windowContainer.Get(args.belongWindowID_);

    // Get the D3D12WindowFacade interface
    wbp_d3d12::ID3D12WindowFacade *d3d12WindowFacade = wb::As<wbp_d3d12::ID3D12WindowFacade>(&window);
    if (d3d12WindowFacade == nullptr)
    {
        // Skip if the window is not a D3D12 window
        return;
    }

    // Check if the window needs to resize
    if (window.NeedsResize())
    {
        d3d12WindowFacade->WaitForGPU();
        window.Resized();
    }

    // Get the keyboard and mouse monitors
    wb::IKeyboardMonitor *keyboardMonitor = nullptr;
    wb::IMouseMonitor *mouseMonitor = nullptr;
    for (const size_t &monitorID : window.GetMonitorIDs())
    {
        wb::IMonitor &monitor = monitorContainer.Get(monitorID);
        if (keyboardMonitor == nullptr) keyboardMonitor = wb::As<wb::IKeyboardMonitor>(&monitor);
        if (mouseMonitor == nullptr) mouseMonitor = wb::As<wb::IMouseMonitor>(&monitor);
    }

    if (keyboardMonitor != nullptr && keyboardMonitor->GetKeyDown(wb::KeyCode::Space))
    {
        d3d12WindowFacade->ResetCommand(nullptr);
        d3d12WindowFacade->SetBarrierToRenderTarget();
        d3d12WindowFacade->SetRenderTarget(DEPTH_STENCIL_FOR_DRAW);

        // Generate a random color
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, 255);
        float clearColor[4] = {
            static_cast<float>(dist(gen)) / 255.0f,
            static_cast<float>(dist(gen)) / 255.0f,
            static_cast<float>(dist(gen)) / 255.0f,
            1.0f // Alpha channel
        };

        d3d12WindowFacade->ClearViews(clearColor, DEPTH_STENCIL_FOR_DRAW);

        d3d12WindowFacade->SetBarrierToPresent();
        d3d12WindowFacade->CloseCommand();
        d3d12WindowFacade->WaitForGPU();

        // Get the gpu context
        wbp_d3d12::GPUContext &gpuContext = wbp_d3d12::GPUContext::GetInstance();
        if (!gpuContext.IsCreated())
        {
            std::string err = wb::CreateErrorMessage
            (
                __FILE__, __LINE__, __FUNCTION__,
                { "GPUContext is not created. Please initialize GPUContext before using it." }
            );
            wb::ConsoleLog(err);
            wb::ErrorNotify("WBP_EXAMPLE_RENDER", err);
            wb::ThrowRuntimeError(err);
        }

        std::vector<ID3D12CommandList*> commandLists;
        commandLists.push_back(d3d12WindowFacade->GetCommandList());
        wbp_d3d12::ExecuteCommand(gpuContext.GetCommandQueue(), commandLists.size(), commandLists);

        d3d12WindowFacade->Present();
        d3d12WindowFacade->WaitThisFrameForGPU();
    }
}

namespace wbp_example_render
{
    WB_REGISTER_SYSTEM(ExampleRenderSystem, ExampleRenderSystemID());

} // namespace wbp_example_render