#pragma once

#include <tuple>
#include <vector>

#include "types.h"

namespace imageit{ namespace ast
{   
    using V1 = base_fp;
    using V2 = std::tuple<base_fp, base_fp>;
    using V3 = std::tuple<base_fp, base_fp, base_fp>;
    using V4 = std::tuple<base_fp, base_fp, base_fp, base_fp>;

    using L1 = std::vector<V1>;
    using L2 = std::vector<V2>;
    using L3 = std::vector<V3>;
    using L4 = std::vector<V4>;

    using M1 = std::vector<L1>;
    using M2 = std::vector<L2>;
    using M3 = std::vector<L3>;
    using M4 = std::vector<L4>;

}}