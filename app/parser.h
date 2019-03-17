#pragma once

#include <tuple>
#include <vector>

#include <boost/optional/optional.hpp>

#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/variant/apply_visitor.hpp>

#include "ast.h"
#include "types.h"

namespace imageit{ namespace ast
{
    namespace x3 = boost::spirit::x3;

    struct M : x3::variant< M1, M2, M3, M4>
    {
        using base_type::base_type;
        using base_type::operator=;
    };

}}

namespace imageit{ namespace parser
{
    namespace x3 = boost::spirit::x3;

    using base_fp_parser_t = x3::real_parser<base_fp>;
    const base_fp_parser_t base_fp_parser = {};
}}

namespace imageit{ namespace parser
{
    namespace x3 = boost::spirit::x3;

    using x3::eol;
    //using base_fp_parser;

    auto const V1 = x3::rule<class V1, ast::V1>()
        = base_fp_parser | '(' >> base_fp_parser >> ')';

    auto const V2 = x3::rule<class V2, ast::V2>()
        = '(' >> base_fp_parser >> ',' >> base_fp_parser >> ')';

    auto const V3 = x3::rule<class V3, ast::V3>()
        = '(' >> base_fp_parser >> ',' >> base_fp_parser >> ',' >> base_fp_parser >> ')';

    auto const V4 = x3::rule<class V4, ast::V4>()
        = '(' >> base_fp_parser >> ',' >> base_fp_parser >> ',' >> base_fp_parser >> ',' >> base_fp_parser >> ')';

    auto const L1 = x3::rule<class L1, ast::L1>()
        = V1 % ',';

    auto const L2 = x3::rule<class L2, ast::L2>()
        = V2 % ',';

    auto const L3 = x3::rule<class L3, ast::L3>()
        = V3 % ',';
        
    auto const L4 = x3::rule<class L4, ast::L4>()
        = V4 % ',';

    auto const M1 = x3::rule<class M1, ast::M1>()
        = L1 % eol;

    auto const M2 = x3::rule<class M2, ast::M2>()
        = L2 % eol;
    
    auto const M3 = x3::rule<class M3, ast::M3>()
        = L3 % eol;

    auto const M4 = x3::rule<class M4, ast::M4>()
        = L4 % eol;

    auto const M = x3::rule<class M, ast::M>()
        = M1 | M2 | M3 | M4;  
}}

namespace imageit
{ 
    namespace detail
    {
        template<typename Ast, typename Parse, typename InputIt>
        inline boost::optional<Ast>
        parse(Parse&& parse, InputIt begin, InputIt end)
        {
            namespace x3 = boost::spirit::x3;

            using x3::ascii::blank;
            using x3::phrase_parse;
            
            Ast ast;
            bool r = phrase_parse(begin, end,
                                  std::forward<Parse>(parse), blank, ast);

            if (!r || begin != end) // fail if we did not get a full match
                return {};
            
            return std::move(ast);
        }

        inline bool allLinesHaveSameSize(const ast::M& m)
        {
            return boost::apply_visitor([](auto const& mat)
            {
                auto colSize = (*mat.begin()).size();
                return std::all_of(mat.begin(), mat.end(), 
                                    [colSize](auto const& l){ return l.size() == colSize; });
            }, m);
        }

    
    }

    template<typename InputIt>
    inline boost::optional<ast::M>
    parse(InputIt&& begin, InputIt&& end)
    {
        auto m =  detail::parse<ast::M>(parser::M,
                                     std::forward<InputIt>(begin),
                                     std::forward<InputIt>(end));
        if(m && detail::allLinesHaveSameSize(*m))
            return m;
        else
            return {};
    }
}