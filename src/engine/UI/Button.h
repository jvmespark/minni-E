#ifndef BUTTON_H
#define BUTTON_H

#include "../../common/common_headers.h"
#include "../render/TextRenderer.h"

#include <functional>
#include <iostream>
#include <string>

class Button {
    public:
        Button() {}
        Button(std::string text_, std::string font_, float font_size_, std::function<void()> action, float w, float h, float x, float y);
        //Button(text, function parameter of action, size, positions);

        void render();
        void ProcessInput();
        void click() { onClick(); }
        // void click(); activate onClick function
        // void hover(); change background color
        // processinputs
    private:
        // function passed as parameter
        std::string text, font;
        std::function<void()> onClick; 
        float font_size, width, height, x_pos, y_pos;

        TextRenderer* buttonRenderer;
};

#endif