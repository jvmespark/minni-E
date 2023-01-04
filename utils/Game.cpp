#include "Game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../render/stb_image.h"

Game::Game() {}

Game::~Game() {
    clean();
    quit();
}

bool Game::init(const char* title, int x, int y, int width, int height, int flags) {
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, x, y, width, height, flags);

        if (window != 0) {
            SDL_GLContext Context = SDL_GL_CreateContext(window);
            if (Context != 0) {
                glewExperimental = GL_TRUE; 
                GLenum glewError = glewInit();
            }
            else {
                std::cerr<<"GL Context failed"<<std::endl;
                return false;
            }
        }
        else {
            std::cerr<<"Window failed"<<std::endl;
            return false;
        }

    }
    else {
        std::cerr<<"SDL Init failed"<<std::endl;
        return false;
    }

    shader = Shader("../render/shader_sources/Texture.vert", "../render/shader_sources/Texture.frag");

    running = true;
    windowFlags = flags;
    return true;
}

void renderTriangle() {
        float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("../assets/player/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Game::render() {
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    shader.use();

    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.f, 0.f, 1.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    renderTriangle();

    SDL_GL_SwapWindow(window);
}

void Game::update() {
    
}

void Game::handleEvents() {
    SDL_Event event;
 
    while(SDL_PollEvent(&event)) {
        bool mFullScreen = false;
        //if (event.type == SDL_WINDOWEVENT) {
        //    switch(event.window.event) {
        //        
        //    }
        //}
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN ) {
            if( mFullScreen ) {
                SDL_SetWindowFullscreen(window, windowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                mFullScreen = false;
            }
            else {
                SDL_SetWindowFullscreen(window, windowFlags);
                mFullScreen = true;
            }
        }
        if (event.type == SDL_QUIT) {
            quit();
        }
        //this is bad. fix it by just sending the key into it, and filtering on the other end.
        //switch keys
        //case: key == w
        //  player.processInput(PLAYER_UP, PLAYER_WALK);
        //case: key == space
        //  player.processInput(PLAYER_DASH);
        //case: mouse == left click
        //  player.processInput(PLAYER_ATTACK);
    }
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::quit() {
    running = false;
}

