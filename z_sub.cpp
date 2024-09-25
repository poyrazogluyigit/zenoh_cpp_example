#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#define ZENOHCXX_ZENOHC
#include "zenoh.hxx"

using namespace zenoh;
using namespace std::chrono_literals;

const char *kind_to_str(SampleKind kind) {
    switch (kind) {
        case SampleKind::Z_SAMPLE_KIND_PUT:
            return "PUT";
        case SampleKind::Z_SAMPLE_KIND_DELETE:
            return "DELETE";
        default:
            return "UNKNOWN";
    }
}

void data_handler(const Sample &sample) {
    std::cout << ">> [Subscriber] Received " << kind_to_str(sample.get_kind()) << " ('"
              << sample.get_keyexpr().as_string_view() << "' : '" << sample.get_payload().deserialize<std::string>()
              << "')\n";
}

int main(int, char **){

    const char *expr = "demo/example/simple";

    Config config = Config::create_default();
    auto session = Session::open(std::move(config));

    KeyExpr keyexpr(expr);

    std::cout << "Declaring subscriber on '" << keyexpr.as_string_view() << "'..." << std::endl;
    auto subscriber = session.declare_subscriber(keyexpr, &data_handler, closures::none);
    std::cout << "Subscriber on '" << subscriber.get_keyexpr().as_string_view() << "' declared" << std::endl;

    while (true) {
        std::this_thread::sleep_for(1s);
    }

    return 0;

}