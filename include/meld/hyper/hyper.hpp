//
// Created by Elankath, Tarun Ramakrishna on 15/11/20.
//

#ifndef HYPERMELD_HYPER_HPP
#define HYPERMELD_HYPER_HPP

#include <filesystem>
#include <functional>
#include <iostream>
#include <span>
#include <string>
#include <string_view>
#include <system_error>
#include <memory>

// TODO: figure out how to add documentation (not doxygen) but the fancy restructured text stuff.
namespace meld::hyper {
    using file_handler = std::function<void(const std::filesystem::path& download_file, const std::error_code& ec)>;
    using bytes_handler = std::function<void(const std::span<const std::byte>& bytes, const std::error_code& ec)>;
    struct http_client_data; //forward declare. this class is defined in the impl header.

    class http_client {
    public:
        http_client();
        //TODO: consider making this generic as get_body<T> . will need a conversion concept from std::byte->T
        //TODO: figure out how to document std::function in doxygen.
        //TODO: do I make concepts/typedefs/using declarations for these std::function callbacks ?
        /**
         * Invokes an HTTP(S) GET on the given \c url, gets the resource body as bytes and invokes the given \c body_callback
         * @param url resource url
         * @param handler a callable bytes_handler
         */
        void get_bytes(std::string_view url, bytes_handler handler);

        void download_to_dir(std::string_view url, const std::filesystem::path& download_dir, file_handler handler);

    private:
         std::unique_ptr<http_client_data> data_;
    };

    enum class hyper_errc {
        success = 0,
        connect_error = 1,
    };

    // Define a custom error code category derived from std::error_category
    class hyper_error_category : public std::error_category {
    public:
        // Return a short descriptive name for the category
        const char* name() const noexcept final { return "HyperError"; }

        // Return what each enum means in text
        std::string message(int c) const final {
            switch (static_cast<hyper_errc>(c)) {
            case hyper_errc::success:
                return "request successful";
            case hyper_errc::connect_error:
                return "connection error";
            default:
                return "unknown";
            }
        }

        // Allow generic error conditions to be compared to me
        virtual std::error_condition default_error_condition(int c) const noexcept override final {
            switch (static_cast<hyper_errc>(c)) {
            case hyper_errc::connect_error:
                return make_error_condition(std::errc::host_unreachable);
            default:
                // I have no mapping for this code
                return std::error_condition(c, *this);
            }
        }
    };

}

extern inline const meld::hyper::hyper_error_category& hyper_error_category() {
    static meld::hyper::hyper_error_category c;
    return c;
}

namespace std {
    // Tell the C++ 11 STL metaprogramming that enum ConversionErrc
    // is registered with the standard error code system
    template<>
    struct is_error_code_enum<meld::hyper::hyper_errc> : true_type {
    };
}
#endif //HYPERMELD_HYPER_HPP
