#pragma once
#include "MountainCar.h"

class MountainHall {
public:
    MountainHall();
    void draw();
private:
    MountainCar mainCar;       // السيارة الأولى (المغلقة)
    MountainCar convertibleCar; // السيارة الثانية (المكشوفة)
};

