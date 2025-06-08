#include "test_place.hpp"

std::string_view test_place::id() {
    return "test_place";
}

std::string_view test_place::layout() {
    return R"(
        <rml>
        <head>
            <title>J3 - test place</title>
        </head>
        <body data-model="test_place_data">
            <h1>Counter</h1>
            <p>Current count: {{count}}</p>
            <button data-event-click="increment_count">Click me!</button>
        </body>
        </rml>
    )";
}

std::string_view test_place::styles() {
    return R"(
        body {
            background-color: #0F0F0F00;
            color: #FFFFFF;
        }
    )";
}

void test_place::bind_data(Rml::DataModelConstructor& dmc) {
    this->count = 2;
    
    dmc.Bind("count", &this->count);
    dmc.BindEventCallback("increment_count", &test_place::increment_counter, this);

    this->model_handle = dmc.GetModelHandle();
}
