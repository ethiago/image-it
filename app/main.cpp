#include <iostream>
#include <string>
#include <vector>

#include <boost/variant/apply_visitor.hpp>

#include "imageWriter.h"
#include "normalizer.h"
#include "parser.h"

int main(int argc, char * argv[])
{
    std::string storage;
    std::cin >> std::noskipws;
    std::copy(
        std::istream_iterator<char>(std::cin),
        std::istream_iterator<char>(),
        std::back_inserter(storage)
    );

    auto matrix = imageit::parse(storage.begin(), storage.end());

    if(!matrix)
        throw std::runtime_error("no matix");

    std::string filename("file.png");
    boost::apply_visitor([filename](auto const& m){
        return imageit::write(/*std::cout*/filename, m, imageit::make_normalizer(imageit::computeLimits(m)));
    }, *matrix);
    
    std::cout << filename << std::endl;

    return 0;
}

