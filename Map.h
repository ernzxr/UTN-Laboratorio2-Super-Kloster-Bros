#pragma once
#include "Obstacle.h"
#include <vector>

class Map
{
private:
    std::vector<Obstacle*> vObstacles;
public:
	Map(b2World& world) {
        for (int i = 0; i < 20; i++) {
            Obstacle* obstacle = new Obstacle(world, { i * 40.0f, 560.0f });
            vObstacles.push_back(obstacle);
            if (i >= 15) {
                Obstacle* obstacle = new Obstacle(world, { i * 40.0f, 360.0f });
                vObstacles.push_back(obstacle);
            }
        }
    };
};

