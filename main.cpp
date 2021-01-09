#include <cppdom/application.hpp>
#include <cppdom/elements.hpp>
#include <cppdom/application.hpp>
#include <cppdom/attributes.hpp>
#include <cppdom/util/function.hpp>

#include <emscripten/bind.h>
#include <iostream>

using namespace emscripten;


class MyApp : public CppCom::Application
{
public:
    void render() override
    {
        using namespace CppCom::Attributes;
        using namespace CppCom::Elements;
        using CppCom::Elements::div; // because there is a div in stdio.h in the global namespace      

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
            div {className="PageContent"}
            (
                button {
                    className="trialButton",
                    style=Style{
                        "height"_cssa = "50px",
                        "width"_cssa = "200px"
                    },
                    onClick=[](auto event){
                        std::cout << "hello there\n";
                    }
                }(text{"Click Me!"})
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