#pragma once //  للتأكد من أن هذا الملف يتم تضمينه مرة واحدة فقط
#include "Texture.h"
#include "MountainCar.h"

class MountainHall {
public:
    // Constructor: دالة البناء التي يتم استدعاؤها عند إنشاء كائن من هذا الكلاس
    MountainHall();

    // دالة الرسم الرئيسية التي ستحتوي على كل كود رسم الصالة
    void draw();

private:
    Texture rockWallTexture;
    Texture floorTexture;
    MountainCar mainCar;
};
