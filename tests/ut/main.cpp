#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"
#include "trompeloeil/trompeloeil.hpp"

namespace trompeloeil
{
    template<>
    void reporter<specialized>::send(severity s, const char* file, unsigned long line, const char* msg)
    {
        std::ostringstream os;
        if (line) os << file << ':' << line << '\n';
        os << msg;
        auto failure = os.str();
        if (s == severity::fatal) {
            FAIL(failure);
        }
        else {
            CAPTURE(failure);
            CHECK(failure.empty());
        }
    }
}
