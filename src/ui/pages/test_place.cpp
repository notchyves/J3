#include "test_place.hpp"

std::string_view test_place::id() {
    return "test-place";
}

std::string_view test_place::layout() {
    return R"(
        <rml>
        <head>
            <title>J3 - test place</title>
        </head>
        <body>
            <h1>J3</h1>
            <p>I wrote this text using harfbuzz, and you can tell because these characters I just wrote are overhanging</p>
            <p>a text box for demonstration purposes:</p>
            <input type="text"/>
        </body>
        </rml>
    )";
}

std::string_view test_place::styles() {
    return R"(
        body {
            font-family: Montserrat;
            background-color: #0F0F0F;
            color: #FFFFFF;
            padding: 2em 1em;
            position: absolute;
            width: 900px;
            height: 550px;
        }

        h1 {
            font-size: 32px;
            font-weight: bold;
        }

        p {
            font-size: 16px;
        }

        input.text {
            background-color: #fff;
            color: #555;
            border: 2px #999;
            padding: 5px;
            tab-index: auto;
            cursor: text;
            box-sizing: border-box;
            width: 200px;
            font-size: 14px;
        }
    )";
}
