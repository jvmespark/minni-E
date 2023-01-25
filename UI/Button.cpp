#include "Button.h"

Button::Button(std::string text_, std::string font_, float font_size_, std::function<void()> action, float w, float h, float x, float y) {
    text = text_;
    font = font_;
    font_size = font_size_;
    onClick = action;
    width = w;
    height = h;
    x_pos = x;
    y_pos = y;

    buttonRenderer = new TextRenderer(width, height);
    buttonRenderer -> Load(font, font_size);
}

void Button::render() {
    buttonRenderer->RenderText(text, x_pos, y_pos, 1.0f);
}

void Button::ProcessInput() {

}