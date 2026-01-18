#include "MountainCar.h"
#include <GL/freeglut.h>

// --- دالة مساعدة لرسم عجلة كاملة بتفاصيل (إطار + جنط) ---
void drawWheelWithRim(GLUquadric* quadric) {
    // 1. رسم الإطار الخارجي باللون الأسود
    glColor3f(0.05f, 0.05f, 0.05f);
    glPushMatrix();
    // الغطاء الخلفي (غير مرئي لكنه يجعل الشكل صلباً)
    glPushMatrix();
    glRotatef(180, 0, 1, 0);
    gluDisk(quadric, 0, 12, 20, 1);
    glPopMatrix();
    // جسم الإطار
    gluCylinder(quadric, 12, 12, 8, 20, 1);
    // الغطاء الأمامي
    glPushMatrix();
    glTranslatef(0, 0, 8);
    gluDisk(quadric, 0, 12, 20, 1);
    glPopMatrix();
    glPopMatrix();

    // 2. رسم الجنط المعدني الفضي في المنتصف
    glColor3f(0.7f, 0.7f, 0.7f);
    glPushMatrix();
    glTranslatef(0, 0, 8.1); // نبرزه قليلاً جداً للأمام
    gluDisk(quadric, 0, 8, 20, 1); // بنصف قطر أصغر (8)
    glPopMatrix();
}

MountainCar::MountainCar(Point position) {
    this->pos = position;
}

void MountainCar::draw() {
    GLUquadric* quadric = gluNewQuadric();

    glPushMatrix(); //  --- بداية مجموعة السيارة ---
    glTranslatef(this->pos.x, this->pos.y, this->pos.z);

    // --- 1. الهيكل الرئيسي ---
    // الجسم الأساسي
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
    glScalef(50, 20, 90);
    glutSolidCube(1);
    glPopMatrix();
    // مقصورة الركاب
    glColor3f(0.15f, 0.15f, 0.15f);
    glPushMatrix();
    glTranslatef(0, 18, -10);
    glScalef(48, 16, 60);
    glutSolidCube(1);
    glPopMatrix();

    // --- 2. العجلات ---
    glPushMatrix();
    glTranslatef(25, -8, 35); glRotatef(90, 0, 1, 0); drawWheelWithRim(quadric);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-25, -8, 35); glRotatef(-90, 0, 1, 0); drawWheelWithRim(quadric);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25, -8, -35); glRotatef(90, 0, 1, 0); drawWheelWithRim(quadric);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-25, -8, -35); glRotatef(-90, 0, 1, 0); drawWheelWithRim(quadric);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 5, -45.1); drawWheelWithRim(quadric);
    glPopMatrix();

    // --- 3. المصد الأمامي ---
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(0, -12, 46); glScalef(52, 4, 4); glutSolidCube(1);
    glPopMatrix();

    // --- 4. الزجاج الأمامي الشفاف ---
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.6f, 0.8f, 1.0f, 0.4f);
    glPushMatrix();
    glTranslatef(0, 18, 20); glRotatef(25, -1, 0, 0); glScalef(48, 15, 1); glutSolidCube(1);
    glPopMatrix();
    glDisable(GL_BLEND);

    // --- 5. الأضواء المضيئة ---
    glEnable(GL_LIGHTING);
    float whiteEmission[] = { 1.0, 1.0, 1.0, 1.0 };
    float redEmission[] = { 1.0, 0.0, 0.0, 1.0 };
    float noEmission[] = { 0.0, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_EMISSION, whiteEmission);
    glPushMatrix();
    glTranslatef(20, 0, 45.1); glScalef(6, 4, 1); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-20, 0, 45.1); glScalef(6, 4, 1); glutSolidCube(1);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, redEmission);
    glPushMatrix();
    glTranslatef(22, 0, -45.1); glScalef(4, 3, 1); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-22, 0, -45.1); glScalef(4, 3, 1); glutSolidCube(1);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
    glDisable(GL_LIGHTING);

    // --- 6. النوافذ الجانبية اللامعة ---
    glEnable(GL_LIGHTING);
    float glass_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float glass_shininess[] = { 128.0 };
    // اللون الأسود للزجاج سيأتي من glColorMaterial, لذا نضبط اللون هنا
    glColor3f(0.0f, 0.0f, 0.0f);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, glass_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, glass_shininess);

    // رسم النوافذ
    glPushMatrix();
    glTranslatef(24.1, 18, 5);  glScalef(1, 12, 25); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(24.1, 18, -25); glScalef(1, 12, 20); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-24.1, 18, 5);  glScalef(1, 12, 25); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-24.1, 18, -25); glScalef(1, 12, 20); glutSolidCube(1);
    glPopMatrix();

    // إعادة ضبط خصائص المادة
    float default_specular[] = { 0.0, 0.0, 0.0, 1.0 };
    float default_shininess[] = { 0.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, default_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, default_shininess);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    // --- 7. مقابض الأبواب والفواصل ---
    glColor3f(0.0f, 0.0f, 0.0f);
    // المقابض
    glPushMatrix();
    glTranslatef(25.1, 8, 10); glScalef(1, 1.5, 5); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(25.1, 8, -20); glScalef(1, 1.5, 5); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-25.1, 8, 10); glScalef(1, 1.5, 5); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-25.1, 8, -20); glScalef(1, 1.5, 5); glutSolidCube(1);
    glPopMatrix();

    // الخط الفاصل
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex3f(25.1, 26, -8); glVertex3f(25.1, -10, -8);
    glVertex3f(-25.1, 26, -8); glVertex3f(-25.1, -10, -8);
    glEnd();

    glPopMatrix(); // --- نهاية مجموعة السيارة ---
    gluDeleteQuadric(quadric);
}
