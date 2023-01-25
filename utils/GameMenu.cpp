#include "GameMenu.h"

GameMenu::GameMenu(SpriteRenderer* renderer_, unsigned int width, unsigned int height) {
    renderer = renderer_;
    windowWidth = width;
    windowHeight = height;
    State = MAIN;

    // Add text rendering support:
    //  centered
    //  left aligned
    //  right aligned
    //  manually change

    ResourceManager::LoadTexture("../assets/backgrounds/background1.jpg", false, "MenuBackground");

    init();
}

void GameMenu::init() {
    Menu_Title = new TextRenderer(this->windowWidth, this->windowHeight);
    Menu_Title -> Load("../assets/fonts/ManilaSansBld.otf", 100);

    Menu_Subtitle = new TextRenderer(this->windowWidth, this->windowHeight);
    Menu_Subtitle -> Load("../assets/fonts/ManilaSansBld.otf", 50);

    buttonMap["play"] = new Button(
        "play", "../assets/fonts/ManilaSansBld.otf", 50, std::bind(&changeState, this, PLAY), this->windowWidth, this->windowHeight, this->windowWidth/2.2, this->windowHeight/2
    );
    buttonMap["settings"] = new Button(
        "settings", "../assets/fonts/ManilaSansBld.otf", 50, std::bind(&changeState, this, PLAY), this->windowWidth, this->windowHeight, this->windowWidth/2.2, this->windowHeight/1.65
    );
    buttonMap["exit"] = new Button(
        "exit", "../assets/fonts/ManilaSansBld.otf", 50, std::bind(&changeState, this, PLAY), this->windowWidth, this->windowHeight, this->windowWidth/2.2, this->windowHeight/1.4
    );
}

void GameMenu::render() {
    if (State == MAIN) {
        renderer->DrawSprite(ResourceManager::GetTexture("MenuBackground"), glm::vec2(0.0f, 0.0f), glm::vec2(this->windowWidth, this->windowHeight), 0.0f);
        Menu_Title->RenderText("Game Title", this->windowWidth/3.5, this->windowHeight/4, 1.0f);
        
        buttonMap["play"]->render();
        buttonMap["settings"]->render();
        buttonMap["exit"]->render();
    }
    if (State == SETTINGS) {}
}

void GameMenu::ProcessInput(const Uint8* kb) {
    if (kb[SDL_SCANCODE_P]) {
        State = PLAY;
    }
}

void GameMenu::ProcessInput(SDL_Event event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);
        
        //process input through buttons

        if (430 < x && x < 540) {
            if (260 < y && y < 320) {
                State = PLAY;
            }
        }
        if (435 < x && x < 520) {
            if (387 < y && y < 420) {
                State = EXIT;
            }
        }
        
       /*
        std::map<float, std::vector<float>>::iterator it;
        int button_num = 0;
        for (it = Main_Layout.begin(); it != Main_Layout.end(); it++) {
            if (y < it->first) {
                std::cout<<it->second[0]<<" "<<it->second[1]<<" "<<it->second[2]<<" "<<it->second[3]<<std::endl;
                std::cout<<x<<" "<<y<<std::endl;
                if (it->second[1] < x && x < it->second[0]) {
                    if (it->second[3] < y && y < it -> second[2]) {
                        switch(button_num) {
                            case 0: {
                                State = PLAY;
                                break;
                            }
                            case 1: {
                                State = EXIT;
                                break;
                            } 
                        }
                    }
                }
            }
            button_num++;
        }
        */
    }
}

int GameMenu::updateState() {
    switch(State) {
        case MAIN:
            return 1;
        case PLAY:
            return 0;
        case EXIT:
            return 4;
    }
}
