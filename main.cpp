#include <cppdom/application.hpp>
#include <cppdom/elements.hpp>
#include <cppdom/application.hpp>
#include <cppdom/attributes.hpp>
#include <cppdom/util/function.hpp>
#include <cppdom/emscripten_fill/val_iteration.hpp>

#include <emscripten/bind.h>
#include <iostream>

using namespace emscripten;
using namespace std::placeholders;

class MyApp : public CppDom::Application
{
public:
    void render() override
    {
        using namespace CppDom::Attributes;
        using namespace CppDom::Elements;
        using namespace CppDom;
        using CppDom::Elements::div; // because there is a div in stdio.h in the global namespace      

        SharedObserver <std::string> buttonId{"0"};

        std::cout << "render\n";
        auto mydiv = 
        div {
            style=Style{
                "background"_cssa = "teal",
                "height"_cssa = "100vh"
            },
            className="PageRoot"
        }
        (
            div {className="PageHeader"}(),
            main_ {className="PageContent"}
            (
                button {
                    id=buttonId,
                    className="trialButton",
                    style=Style{
                        "height"_cssa = "50px",
                        "width"_cssa = "200px"
                    },
                    onClick=[&buttonId](auto event){
                        buttonId = "1";
                        std::cout << ::body();
                    }
                }("Click Me!"),
                a {href="https://www.google.de"}("Click Me!")
            )
        );

        auto body = ::body();
        mydiv.renderInto(body);
    }
};

int run() 
{
    MyApp app;
    app.render();

    return 0;
}

EMSCRIPTEN_BINDINGS(mymod) {
    function("run", &run);
}