#pragma once
#include "Point.h" //  السيارة لها موقع، لذلك نحتاج لكلاس النقطة

class MountainCar {
public:
    // Constructor: عند إنشاء سيارة، يجب أن نحدد أين ستوضع
    MountainCar(Point position);

    // دالة الرسم الرئيسية للسيارة
    void draw();

private:
    Point pos; //  متغير لتخزين موقع السيارة
    // لاحقاً سنضيف هنا متغيرات أخرى مثل زاوية دوران العجلات
};
