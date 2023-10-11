#pragma once

namespace Config
{
#ifdef LOCAL_BUILD
    constexpr bool localBuild = true;
#else
    constexpr bool localBuild = false;
#endif
};