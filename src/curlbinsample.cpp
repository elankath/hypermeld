#include <iostream>
#include <string>
#include "meld/hyper/hyper.hpp"
#include "meld/hyper/impl/curlbin.hpp"
#include "prettyprint.hpp"

// TODO: convert sample to test-case using doctest lib.
int main() {
    using namespace meld::hyper;
    using namespace std;
    std::string curl_bin = std::getenv("CURL_BIN");
    if (curl_bin.empty()) {
        std::cout << "CURL_BIN env not set. Defaulting to curl";
        curl_bin = "curl";
    }
    http_client client;
    std::string uri {"https://file-examples-com.github.io/uploads/2017/02/file-sample_100kB.doc"};
    client.get_bytes(uri, [](auto& bytes, auto& ec) {
        cout << "ec: " << ec << ", bytes.data(): " << bytes.data() << endl;
//        cout << "bytes: " << bytes << ", ec: " << ec;
    });
//    client.download_to_dir(url, [](auto& bytes, auto& ec) { });
    return 0;
}


