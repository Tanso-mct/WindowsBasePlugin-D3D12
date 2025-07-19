#pragma once

#ifdef WBPEXAMPLERENDER_EXPORTS
#define WBP_EXAMPLE_RENDER_API __declspec(dllexport)
#else
#define WBP_EXAMPLE_RENDER_API __declspec(dllimport)
#endif