#include "GameLevel.h"

void GameLevel::Load(const char *file, unsigned int levelWidth, unsigned int levelHeight) {
    // clear old data
    this->Bricks.clear();
    // load from file
    unsigned int tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line)) // read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode) // read each word separated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::Draw(SpriteRenderer &renderer) {
    for (GameObject &tile : this->Bricks)
        if (!tile.Destroyed)
            tile.Draw(renderer);
}

bool GameLevel::IsCompleted() {
    for (GameObject &tile : this->Bricks)
        if (!tile.IsSolid && !tile.Destroyed)
            return false;
    return true;
}

void GameLevel::translate(float x, float y) {
    for (GameObject &tile : this->Bricks) {
        tile.Position.x += x;
        tile.Position.y += y;
    }
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight) {
    // calculate dimensions
    height = tileData.size();
    width = tileData[0].size(); // note we can index vector at [0] since this function is only called if height > 0
    unit_width = levelWidth / static_cast<float>(32);
    unit_height = levelHeight / static_cast<float>(18); 
    boundaryHeight = height * unit_height;
    boundaryWidth = width * unit_width;
    std::vector<std::string> blockMap= {"grass","stone"};
    // initialize level tiles based on tileData		
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            if (tileData[y][x] != 0) {
                glm::vec2 pos(unit_width * x, unit_height * y);
                glm::vec2 size(unit_width, unit_height);
                GameObject obj(pos, size, ResourceManager::GetTexture(blockMap[tileData[y][x]]), glm::vec3(0.8f, 0.8f, 0.7f));
                obj.IsSolid = true;
                this->Bricks.push_back(obj);
            }
        }
    }
}