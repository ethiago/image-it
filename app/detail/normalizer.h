#pragma once

#include <algorithm>
#include <tuple>

#include "../ast.h"
#include "../types.h"

namespace imageit
{
    namespace detail
    {
        namespace ast = imageit::ast; 
        using result_type = ast::V4;

        template<typename ValT>
        inline result_type convert(const ValT& v);

        template<>
        inline result_type convert(const base_fp& v)
        { return std::make_tuple(v,v,v,1.0); }

        template<>
        inline result_type convert(const ast::V2& v)
        { return std::make_tuple(std::get<0>(v),std::get<1>(v), 0.0, 1.0); }

        template<>
        inline result_type convert(const ast::V3& v)
        { return std::make_tuple(std::get<0>(v),std::get<1>(v),std::get<2>(v), 1.0); }

        template<>
        inline result_type convert(const ast::V4& v)
        { return v; }

        template<typename T>
        inline T min(const T& a, const T& b);

        template<>
        inline ast::V1 min(const ast::V1& a, const ast::V1& b)
        { return std::min(a, b); }

        template<>
        inline ast::V2 min(const ast::V2& a, const ast::V2& b)
        {
            return ast::V2(
                std::min(std::get<0>(a), std::get<0>(b)),
                std::min(std::get<1>(a), std::get<1>(b))
            );
        }

        template<>
        inline ast::V3 min(const ast::V3& a, const ast::V3& b)
        {
            return ast::V3(
                std::min(std::get<0>(a), std::get<0>(b)),
                std::min(std::get<1>(a), std::get<1>(b)),
                std::min(std::get<2>(a), std::get<2>(b))
            );
        }

        template<>
        inline ast::V4 min(const ast::V4& a, const ast::V4& b)
        {
            return ast::V4(
                std::min(std::get<0>(a), std::get<0>(b)),
                std::min(std::get<1>(a), std::get<1>(b)),
                std::min(std::get<2>(a), std::get<2>(b)),
                std::min(std::get<3>(a), std::get<3>(b))
            );
        }

        	template<typename T>
        inline T max(const T& a, const T& b);

        template<>
        inline ast::V1 max(const ast::V1& a, const ast::V1& b)
        { return std::max(a, b); }

        template<>
        inline ast::V2 max(const ast::V2& a, const ast::V2& b)
        {
            return ast::V2(
                std::max(std::get<0>(a), std::get<0>(b)),
                std::max(std::get<1>(a), std::get<1>(b))
            );
        }

        template<>
        inline ast::V3 max(const ast::V3& a, const ast::V3& b)
        {
            return ast::V3(
                std::max(std::get<0>(a), std::get<0>(b)),
                std::max(std::get<1>(a), std::get<1>(b)),
                std::max(std::get<2>(a), std::get<2>(b))
            );
        }

        template<>
        inline ast::V4 max(const ast::V4& a, const ast::V4& b)
        {
            return ast::V4(
                std::max(std::get<0>(a), std::get<0>(b)),
                std::max(std::get<1>(a), std::get<1>(b)),
                std::max(std::get<2>(a), std::get<2>(b)),
                std::max(std::get<3>(a), std::get<3>(b))
            );
        }

        template<typename T>
        inline T normalize(const T& v, const T& min, const T& max);

        template<>
        inline ast::V1 normalize(const ast::V1& v, const ast::V1& min, const ast::V1& max)
        { return (v-min)/(max-min); }

        template<>
        inline ast::V2 normalize(const ast::V2& v, const ast::V2& min, const ast::V2& max)
        { 
            return std::make_tuple( 
                normalize( std::get<0>(v), std::get<0>(min), std::get<0>(max) ),
                normalize( std::get<1>(v), std::get<1>(min), std::get<1>(max) )
            );
        }

        template<>
        inline ast::V3 normalize(const ast::V3& v, const ast::V3& min, const ast::V3& max)
        { 
            return std::make_tuple( 
                normalize( std::get<0>(v), std::get<0>(min), std::get<0>(max) ),
                normalize( std::get<1>(v), std::get<1>(min), std::get<1>(max) ),
                normalize( std::get<2>(v), std::get<2>(min), std::get<2>(max) )
            );
        }

        template<>
        inline ast::V4 normalize(const ast::V4& v, const ast::V4& min, const ast::V4& max)
        {
            return std::make_tuple( 
                normalize( std::get<0>(v), std::get<0>(min), std::get<0>(max) ),
                normalize( std::get<1>(v), std::get<1>(min), std::get<1>(max) ),
                normalize( std::get<2>(v), std::get<2>(min), std::get<2>(max) ),
                normalize( std::get<3>(v), std::get<3>(min), std::get<3>(max) )
             );
        }

        
    }
}