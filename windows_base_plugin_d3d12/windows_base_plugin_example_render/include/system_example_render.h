#pragma once
#include "windows_base_plugin_example_render/include/dll_config.h"
#include "windows_base/windows_base.h"

namespace wbp_example_render
{
    constexpr UINT DEPTH_STENCIL_FOR_DRAW = 0;

    const WBP_EXAMPLE_RENDER_API size_t &ExampleRenderSystemID();

    class WBP_EXAMPLE_RENDER_API ExampleRenderSystem : public wb::ISystem
    {
    public:
        ExampleRenderSystem() = default;
        ~ExampleRenderSystem() override = default;

        /***************************************************************************************************************
         * ISystem implementation
        /**************************************************************************************************************/

        const size_t &GetID() const override;
        void Initialize(wb::IAssetContainer &assetContainer) override;
        void Update(const wb::SystemArgument &args) override;
    };
}