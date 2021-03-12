//
// Created by Elankath, Tarun Ramakrishna on 11/03/21.
//

#ifndef HYPERMELD_UTIL_HPP
#define HYPERMELD_UTIL_HPP

#include <string>
#include <string_view>
inline std::string get_env_or_default(std::string_view name, std::string_view def_val) {
    std::string val { std::getenv(name.data())};
    if (val.empty()) {
        val = def_val;
    }
    return val;
}
#endif //HYPERMELD_UTIL_HPP
