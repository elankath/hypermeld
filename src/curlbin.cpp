//
// Created by Elankath, Tarun Ramakrishna on 11/03/21.
//

#include "meld/hyper/impl/curlbin.hpp"
#include "meld/hyper/impl/util.hpp"
//#include <nes/process.hpp>
#include <process.hpp>
#include <iostream>
#include <string>
#include <string_view>
#include <system_error>

using namespace meld::hyper;
http_client::http_client()
   : data_{ new http_client_data }
{
}

void http_client::get_bytes( std::string_view url, bytes_handler handler )
{
   using namespace std;
   cout << "(get_bytes) uri" << url << ", handler" << handler.target_type().name() << endl;
}

void http_client::download_to_dir( std::string_view url, const std::filesystem::path& download_dir, file_handler handler )
{
   using namespace std;
   //       using namespace TinyProcessLib;
   cout << "(download_to_dir) uri: " << url << ", download_dir:" << download_dir << ", handler"
        << handler.target_type().name() << endl;
   cout << "Example 1a - the mandatory Hello World through a command" << endl;
   //        Process process1a("echo Hello World", "", [](const char* bytes, size_t n) {
   //            cout << "Output from stdout: " << string(bytes, n);
   //        });
}

/* static std::unique_ptr<http_client_data> create_client_data() { */
/*     std::string curl_bin = get_env_or_default("CURL_BIN", "curl"); */
/*     std::cout << "curl_bin set to: " << curl_bin; */
/*     return std::unique_ptr<http_client_data>(curl_bin); */
/* } */
