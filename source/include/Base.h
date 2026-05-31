#ifndef BASE_H
#define BASE_H

#include <cassert>
#include <stdexcept> 
#include <queue>
#include <vector>
#include <utility>
#include <memory>
#include <iostream>
#include <random>
#include <algorithm>
#include <string>


#define THROW_IF_ZERO(value)                                                    \
    do {                                                                        \
        if ((value) == 0) {                                                     \
            throw std::runtime_error(                                           \
                std::string("Zero value error in ") + __FILE__ + ":" +          \
                std::to_string(__LINE__) + ": " + #value + " is zero"           \
            );                                                                  \
        }                                                                       \
    } while(0)

#endif
