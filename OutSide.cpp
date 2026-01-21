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
    float roadEnd = roadZ + roadLength;
    float gapStart = 720.0f;
    float gapEnd = 900.0f;

    //// (Left Sidewalk)
    float leftX = roadX - (roadWidth / 2) - 40.0f;
    glPushMatrix();
    glTranslatef(leftX, -2.9f, roadZ + (roadLength / 2.0f));
    sw.draw(80.0f, 5.0f, roadLength, tex);
    glPopMatrix();

    //(Right Sidewalk)
    float rightX = roadX + (roadWidth / 2) + 40.0f;

    float rightPart1Length = gapStart - roadZ;
    glPushMatrix();
    glTranslatef(rightX, -2.9f, roadZ + (rightPart1Length / 2.0f));
    sw.draw(80.0f, 5.0f, rightPart1Length, tex);
    glPopMatrix();

    float rightPart2Length = roadEnd - gapEnd;
    glPushMatrix();
    glTranslatef(rightX, -2.9f, gapEnd + (rightPart2Length / 2.0f));
    sw.draw(80.0f, 5.0f, rightPart2Length, tex);
    glPopMatrix();
}

void CityLayout::drawSideSidewalks(Sidewalk& sw, GLuint tex) {
    float sideX = -525.0f;
    float sideZ = 550.0f;// بعد عن المبنى 
    float sideW = 550.0f;
    float sideL = 750.0f;
    float swWidth = 80.0f;

    glPushMatrix();
    glTranslatef(-550.0f + 500.0f, -2.9f, -450.0f);// بحرك ال z اذا بدي بعده عن المبنى 
    sw.draw(1000.0f, 5.0f, 100.0f, tex);
    glPopMatrix();

    glPushMatrix();
    float posX = sideX + (sideL / 2.0f);
    float posZ = sideZ + (sideW / 2.0f) + (swWidth / 2.0f);
    glTranslatef(posX, -2.85f, posZ);
    sw.draw(900.0f, 5.0f, 80.0f, tex);
    glPopMatrix();
}

void CityLayout::drawEnvironment(StreetLamp& lamp) {
    for (int i = 0; i < 2; i++) {
        float xBase = -500.0f + (i * 200.0f);
        float zPos = -600.0f;
        glPushMatrix();
        glTranslatef(xBase + 90.0f, -3.0f, zPos);
        glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        glScalef(3.5f, 3.5f, 3.5f);
        lamp.draw();
        glPopMatrix();
    }
}
void CityLayout::drawCityBuildings(StreetLamp& lamp, GLuint texBuilding, Texture& texStone) {
    float spacing = 400.0f;
    float startZ = -1500.0f;
    glColor3f(1.0f, 1.0f, 1.0f);
    float buildingX = 700.0f;
    for (int i = 0; i < 9; i++) {
        glColor3f(1.0f, 1.0f, 1.0f);
        float currentZ = startZ + (i * spacing);
        Cuboid building(Point(buildingX, -3.0f, currentZ), 300.0f, 200.0f, 200.0f);
        building.drawWithStretchTexture(texBuilding);

        if (i < 9) { 
            float lampZ = currentZ + (spacing / 2.0f);
            glPushMatrix();
            glTranslatef(buildingX - 100.0f, -3.0f, lampZ);
            glScalef(3.5f, 3.5f, 3.5f);
            glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
            lamp.draw();
            glPopMatrix();
        }
    }

    float buildingX2 = -1100.0f;
    float lampX = buildingX2 + 100.0f; // موقع العمود على محور X

    glPushMatrix();
    texStone.Use();
    glColor3f(1.0f, 1.0f, 1.0f);
    float floorWidth = 150.0f;         
    float shortenedLength = 8.5f * spacing; 

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(lampX, -2.95f, startZ);

    glTexCoord2f(1.5f, 0.0f);
    glVertex3f(lampX + floorWidth, -2.95f, startZ);

    glTexCoord2f(1.5f, 8.0f);
    glVertex3f(lampX + floorWidth, -2.95f, startZ + shortenedLength);

    glTexCoord2f(0.0f, 8.0f);
    glVertex3f(lampX, -2.95f, startZ + shortenedLength);
    glEnd();
    glPopMatrix();

    for (int i = 0; i < 9; i++) {
        glColor3f(1.0f, 1.0f, 1.0f);
        float currentZ = startZ + (i * spacing);
        Cuboid building(Point(buildingX2, -3.0f, currentZ), 300.0f,200.0f, 200.0f);
        building.drawWithStretchTexture(texBuilding);

        if (i < 9) {
            float lampZ = currentZ + (spacing / 2.0f);
            glPushMatrix();
            glTranslatef(buildingX2 + 100.0f, -3.0f, lampZ);
            glScalef(3.5f, 3.5f, 3.5f);
            lamp.draw();
            glPopMatrix();
        }
    }
}