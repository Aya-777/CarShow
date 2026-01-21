#pragma once
#include <GL/freeglut.h>
#include "Sidewalk.h"
#include "StreetLamp.h"
#include "Cuboid.h"

class CityLayout {
public:
    void drawAllSidewalks(Sidewalk& sw, StreetLamp& lamp, GLuint texSW);
    void drawCityBuildings(StreetLamp& lamp, GLuint texBuilding, Texture& texStone);
private:
    void drawMainSidewalks(Sidewalk& sw, GLuint tex);
    void drawSideSidewalks(Sidewalk& sw, GLuint tex);
    void drawEnvironment(StreetLamp& lamp);
};
