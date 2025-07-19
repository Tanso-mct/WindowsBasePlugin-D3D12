#include "pch.h"

#pragma comment(lib, "windows_base.lib")

#include "wbp_d3d12/include/window_d3d12_facade.h"
#include "wbp_d3d12/include/gpu_facade.h"
#include "wbp_d3d12/include/swap_chain_context.h"
#include "wbp_d3d12/include/render_target_context.h"
#include "wbp_d3d12/include/fence_context.h"
#include "wbp_d3d12/include/d3d12_helpers.h"
#pragma comment(lib, "wbp_d3d12.lib")

namespace
{
    const size_t &MockD3D12WindowID()
    {
        static size_t id = wb::IDFactory::CreateWindowID();
        return id;
    }

    constexpr UINT RENDER_TARGET_COUNT = 2;
    constexpr UINT DEPTH_STENCIL_COUNT = 1;

    constexpr UINT DEPTH_STENCIL_FOR_DRAW = 0;

    class MockD3D12WindowFacadeFactory : public wb::IWindowFacadeFactory
    {
    public:
        MockD3D12WindowFacadeFactory() = default;
        ~MockD3D12WindowFacadeFactory() override = default;

        std::unique_ptr<wb::IWindowFacade> Create() const override
        {
            std::unique_ptr<wb::IWindowFacade> facade 
                = std::make_unique<wbp_d3d12::WindowD3D12Facade>(RENDER_TARGET_COUNT, DEPTH_STENCIL_COUNT);

            {
                std::unique_ptr<wb::IWindowContext> context = std::make_unique<wb::WindowContext>();
                context->Name() = L"Mock D3D12 Window";

                facade->SetContext(std::move(context));
            }

            {
                wbp_d3d12::ID3D12WindowFacade *d3d12WindowFacade = wb::As<wbp_d3d12::ID3D12WindowFacade>(facade.get());
                
                std::unique_ptr<wbp_d3d12::ISwapChainContext> swapChainContext = std::make_unique<wbp_d3d12::SwapChainContext>();
                d3d12WindowFacade->SetSwapChainContext(std::move(swapChainContext));

                std::unique_ptr<wbp_d3d12::IRenderTargetContext> renderTargetContext = std::make_unique<wbp_d3d12::RenderTargetContext>();
                d3d12WindowFacade->SetRenderTargetContext(std::move(renderTargetContext));

                std::unique_ptr<wbp_d3d12::IFenceContext> fenceContext = std::make_unique<wbp_d3d12::FenceContext>();
                d3d12WindowFacade->SetFenceContext(std::move(fenceContext));
            }

            return facade;
        }
    };

    class MockD3D12WindowEventFactory : public wb::IWindowEventFactory
    {
    public:
        MockD3D12WindowEventFactory() = default;
        ~MockD3D12WindowEventFactory() override = default;

        std::unique_ptr<wb::IWindowEvent> Create() const override
        {
            return nullptr;
        }
    };

    WB_REGISTER_WINDOW(MockD3D12WindowID, MockD3D12WindowFacadeFactory, MockD3D12WindowEventFactory);
}

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_PAINT:
        break;

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}

TEST(WindowD3D12Facade, Create)
{
    {
        // Get the gpu facade factory from registry
        wb::ISharedFacadeFactory &factory = wb::gSharedFacadeRegistry.GetFactory(wbp_d3d12::GPUFacadeID());

        // Create GPUFacade instance
        std::unique_ptr<wb::ISharedFacade> gpuFacade = factory.Create();

    } // GPUContext will be created here. GPUContext is a singleton, so it will not be destroyed until the program ends.

    // Get the window facade factory from registry
    wb::IWindowFacadeFactory &windowFactory = wb::gWindowRegistry.GetFacadeFactory(MockD3D12WindowID());

    // Create WindowD3D12Facade instance
    std::unique_ptr<wb::IWindowFacade> windowFacade = windowFactory.Create();

    // Create the window
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = windowFacade->GetName().data();
    windowFacade->Create(wc);
    
    // Show the window
    windowFacade->Show();

    // Destroy the window
    windowFacade->Destroy();
    windowFacade->Destroyed();
}

TEST(WindowD3D12Facade, Resize)
{
    {
        // Get the gpu facade factory from registry
        wb::ISharedFacadeFactory &factory = wb::gSharedFacadeRegistry.GetFactory(wbp_d3d12::GPUFacadeID());

        // Create GPUFacade instance
        std::unique_ptr<wb::ISharedFacade> gpuFacade = factory.Create();

    } // GPUContext will be created here. GPUContext is a singleton, so it will not be destroyed until the program ends.

    // Get the window facade factory from registry
    wb::IWindowFacadeFactory &windowFactory = wb::gWindowRegistry.GetFacadeFactory(MockD3D12WindowID());

    // Create WindowD3D12Facade instance
    std::unique_ptr<wb::IWindowFacade> windowFacade = windowFactory.Create();

    // Create the window
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = windowFacade->GetName().data();
    windowFacade->Create(wc);
    
    // Show the window
    windowFacade->Show();

    // Resize the window
    UINT newWidth = 100;
    UINT newHeight = 100;
    windowFacade->Resize(newWidth, newHeight);

    EXPECT_TRUE(windowFacade->NeedsResize());
    windowFacade->Resized();

    // Destroy the window
    windowFacade->Destroy();
    windowFacade->Destroyed();
}

TEST(WindowD3D12Facade, ClearAndPresent)
{
    {
        // Get the gpu facade factory from registry
        wb::ISharedFacadeFactory &factory = wb::gSharedFacadeRegistry.GetFactory(wbp_d3d12::GPUFacadeID());

        // Create GPUFacade instance
        std::unique_ptr<wb::ISharedFacade> gpuFacade = factory.Create();

    } // GPUContext will be created here. GPUContext is a singleton, so it will not be destroyed until the program ends.

    // Get the window facade factory from registry
    wb::IWindowFacadeFactory &windowFactory = wb::gWindowRegistry.GetFacadeFactory(MockD3D12WindowID());

    // Create WindowD3D12Facade instance
    std::unique_ptr<wb::IWindowFacade> windowFacade = windowFactory.Create();

    // Create the window
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.lpszClassName = windowFacade->GetName().data();
    windowFacade->Create(wc);
    
    // Show the window
    windowFacade->Show();

    {
        // Get the D3D12WindowFacade interface
        wbp_d3d12::ID3D12WindowFacade *d3d12WindowFacade = wb::As<wbp_d3d12::ID3D12WindowFacade>(windowFacade.get());
        
        d3d12WindowFacade->ResetCommand(nullptr);
        d3d12WindowFacade->SetBarrierToRenderTarget();
        d3d12WindowFacade->SetRenderTarget(DEPTH_STENCIL_FOR_DRAW);

        // Create a clear color
        const float clearColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
        d3d12WindowFacade->ClearViews(clearColor, DEPTH_STENCIL_FOR_DRAW);

        d3d12WindowFacade->SetBarrierToPresent();
        d3d12WindowFacade->CloseCommand();
        d3d12WindowFacade->WaitForGPU();

        // Get the gpu context
        wbp_d3d12::GPUContext &gpuContext = wbp_d3d12::GPUContext::GetInstance();
        EXPECT_EQ(gpuContext.IsCreated(), true);

        std::vector<ID3D12CommandList*> commandLists;
        commandLists.push_back(d3d12WindowFacade->GetCommandList());
        wbp_d3d12::ExecuteCommand(gpuContext.GetCommandQueue(), commandLists.size(), commandLists);

        d3d12WindowFacade->Present();
        d3d12WindowFacade->WaitThisFrameForGPU();
    }

    // Destroy the window
    windowFacade->Destroy();
    windowFacade->Destroyed();
}