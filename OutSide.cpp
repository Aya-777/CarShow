#include "OutSide.h"

void CityLayout::drawAllSidewalks(Sidewalk& sw, StreetLamp& lamp, GLuint texSW) {
    drawMainSidewalks(sw, texSW);
    drawSideSidewalks(sw, texSW);
    drawEnvironment(lamp);
}

void CityLayout::drawMainSidewalks(Sidewalk& sw, GLuint tex) {
    float roadX = -700.0f;
    float roadZ = -2000.0f;
    float roadWidth = 200.0f;
    float roadLength = 4000.0f;

    // left
    glPushMatrix();
    glTranslatef(roadX - (roadWidth / 2) - 40.0f, -2.9f, roadZ + (roadLength / 2));
    sw.draw(80.0f, 5.0f, roadLength, tex);
    glPopMatrix();

    // right
    glPushMatrix();
    glTranslatef(roadX + (roadWidth / 2) + 40.0f, -2.9f, roadZ + (roadLength / 2));
    sw.draw(80.0f, 5.0f, roadLength, tex);
    glPopMatrix();
}

void CityLayout::drawSideSidewalks(Sidewalk& sw, GLuint tex) {
    float sideX = -606.0f;
    float sideZ = 440.0f;
    float sideW = 80.0f;
    float sideL = 760.0f;
    float swWidth = 80.0f;

    glPushMatrix();
    glTranslatef(-550.0f + 500.0f, -2.9f, -380.0f);
    sw.draw(1000.0f, 5.0f, 80.0f, tex);
    glPopMatrix();

    glPushMatrix();
    float posX = sideX + (sideL / 2.0f);
    float posZ = sideZ + (sideW / 2.0f) + (swWidth / 2.0f);
    glTranslatef(posX, -2.85f, posZ);
    sw.draw(760.0f, 5.0f, 80.0f, tex);
    glPopMatrix();
}

void CityLayout::drawEnvironment(StreetLamp& lamp) {
    for (int i = 0; i < 2; i++) {
        float xBase = -500.0f + (i * 200.0f);
        float zPos = -450.0f;
        glPushMatrix();
        glTranslatef(xBase + 100.0f, -3.0f, zPos);
        glScalef(2.5f, 2.5f, 2.5f);
        lamp.draw();
        glPopMatrix();
    }
}
void CityLayout::drawCityBuildings(StreetLamp& lamp, GLuint texBuilding) {
    float spacing = 300.0f;
    float startZ = -1500.0f;

    float buildingX = 600.0f;
    for (int i = 0; i < 10; i++) {
        float currentZ = startZ + (i * spacing);
        Cuboid building(Point(buildingX, -3.0f, currentZ), 200.0f, 150.0f, 150.0f);
        building.drawWithStretchTexture(texBuilding);

        if (i < 9) { 
            float lampZ = currentZ + (spacing / 2.0f);
            glPushMatrix();
            glTranslatef(buildingX - 100.0f, -3.0f, lampZ);
            glScalef(2.5f, 2.5f, 2.5f);
            glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
            lamp.draw();
            glPopMatrix();
        }
    }

    float buildingX2 = -1100.0f;
    for (int i = 0; i < 10; i++) {
        float currentZ = startZ + (i * spacing);
        Cuboid building(Point(buildingX2, -3.0f, currentZ), 200.0f, 150.0f, 150.0f);
        building.drawWithStretchTexture(texBuilding);

        if (i < 9) {
            float lampZ = currentZ + (spacing / 2.0f);
            glPushMatrix();
            glTranslatef(buildingX2 + 100.0f, -3.0f, lampZ);
            glScalef(2.5f, 2.5f, 2.5f);
            lamp.draw();
            glPopMatrix();
        }
    }
}