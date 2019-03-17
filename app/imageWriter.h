#pragma once

#include <experimental/tuple>

#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL
#include <boost/gil/typedefs.hpp>
#include <boost/gil/extension/io/png_dynamic_io.hpp>

#include "types.h"

namespace imageit
{
    namespace detail{
        using boost::gil::rgba8_pixel_t;
        inline rgba8_pixel_t make_pixel(std::tuple<base_fp,base_fp,base_fp,base_fp> t)
        {
            return rgba8_pixel_t(std::get<0>(t)*255,
                                 std::get<1>(t)*255,
                                 std::get<2>(t)*255,
                                 std::get<3>(t)*255);
        }
    }

    template<typename M, typename Normalizer, typename Stream>
    inline auto write(Stream& stream, const M& m, Normalizer normalizer)
    {
        using namespace boost::gil;

        auto height = m.size();
        auto width  = (*m.begin()).size();
        rgb8_image_t img(width, height);
        auto view_v = view(img);

        for (int y=0; y<view_v.height(); ++y)
            for (int x=0; x<view_v.width(); ++x)
                view_v(x,y) = detail::make_pixel(normalizer(m[y][x]));

        return png_write_view(stream, view_v);
    }

}