#include <map>
#include <vector>

namespace numbers {

    auto plus = [](const complex& a, const complex& b) { return a + b; };
    auto minus = [](const complex& a, const complex& b) { return a - b; };
    auto multiply = [](const complex& a, const complex& b) { return a * b; };
    auto divide = [](const complex& a, const complex& b) { return a / b; };

    std::map<char, complex(*)(const complex&, const complex&)> funcs = {
            {'+', plus},
            {'-', minus},
            {'*', multiply},
            {'/', divide}
    };

    complex eval(const std::vector<std::string> &args, const complex &z) {
        complex_stack stack;

        complex z1;
        complex z2;

        for (auto const& s: args) {
            auto search = funcs.find(s[0]);
            if (search != funcs.end()) {
                z1 = +stack;
                stack = ~stack;
                z2 = +stack;
                stack = ~stack;
                z1 = search->second(z2, z1);
                stack = stack << z1;
            } else if (s[0] == '#') {
                z1 = +stack;
                stack = ~stack;
                stack = stack << (-z1);
            } else if (s[0] == '!') {
                z1 = +stack;
                stack = stack << z1;
            } else if (s[0] == 'z') {
                stack = stack << z;
            } else if (s[0] == '~') {
                z1 = +stack;
                stack = stack << (~z1);
            } else if (s[0] == ';') {
                stack = ~stack;
            } else {
                complex z3(s);
                stack = stack << z3;
            }
        }

        return +stack;
    }


}

