#pragma once

#include "detail/normalizer.h"

namespace imageit
{
    template<typename Mat>
    inline auto
    computeLimits(const Mat& mat)
    {
        auto& first = *(mat.begin());
        
        auto limits = std::make_pair(first[0], first[0]);

        auto height = mat.size();
        auto width  = first.size();

        for(std::size_t y = 0; y < height; ++y)
        {
            for(std::size_t x = 0; x < width; ++x)
            {
                limits.first = detail::min(limits.first, mat[y][x]);
                limits.second = detail::max(limits.second, mat[y][x]);
            }
        }

        return limits;
    }
    
    template<typename T>
    struct Normalizer
    {
        Normalizer() = default;
        Normalizer(const Normalizer&) = default;

        detail::result_type operator()(const T& value)
        { return detail::convert( detail::normalize( value, limits.first, limits.second )); }
        
        std::pair<T, T> limits;
    };

    template<typename T>
    inline Normalizer<T> make_normalizer(std::pair<T, T> limits)
    {
        return Normalizer<T>{limits};
    }
}