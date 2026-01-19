#include "MountainCar.h"
#include <GL/freeglut.h>

// -----------------------------------------------------------------------------
// - دالة مساعدة لرسم عجلة كاملة (إطار أسود + جنط فضي)
// - يتم استدعاؤها 5 مرات لتجنب تكرار الكود.
// -----------------------------------------------------------------------------
void drawWheelWithRim(GLUquadric* quadric) {
    // --- 1. رسم الإطار الخارجي باللون الأسود ---
    glColor3f(0.05f, 0.05f, 0.05f); // لون أسود داكن للإطارات
    glPushMatrix(); // نبدأ مجموعة الإطار

    // الغطاء الخلفي للعجلة (لجعلها تبدو صلبة وغير مفرغة)
    glPushMatrix();
    glRotatef(180, 0, 1, 0); // نديره 180 درجة ليواجه الداخل
    gluDisk(quadric, 0, 12, 20, 1); // (الأداة، نصف القطر الداخلي، الخارجي، الدقة، الحلقات)
    glPopMatrix();

    // جسم الإطار الأسطواني
    gluCylinder(quadric, 12, 12, 8, 20, 1); // (الأداة، نصف القطر، نصف القطر، العرض، الدقة، الدقة)

    // الغطاء الأمامي للعجلة
    glPushMatrix();
    glTranslatef(0, 0, 8); // ننتقل إلى نهاية الأسطوانة (بمقدار عرضها)
    gluDisk(quadric, 0, 12, 20, 1);
    glPopMatrix();

    glPopMatrix(); // ننهي مجموعة الإطار

    // --- 2. رسم الجنط المعدني الفضي في المنتصف ---
    glColor3f(0.7f, 0.7f, 0.7f); // لون فضي لامع
    glPushMatrix();
    glTranslatef(0, 0, 8.1); // نبرزه قليلاً جداً للأمام (0.1) ليكون فوق سطح الإطار
    gluDisk(quadric, 0, 8, 20, 1); // نرسمه بنصف قطر أصغر (8)
    glPopMatrix();
}


// -----------------------------------------------------------------------------
// - Constructor: دالة البناء التي يتم استدعاؤها عند إنشاء كائن من هذا الكلاس
// -----------------------------------------------------------------------------
MountainCar::MountainCar(Point position) {
    this->pos = position; // نخزن موقع السيارة الذي تم تمريره
}


// -----------------------------------------------------------------------------
// - دالة الرسم الرئيسية للسيارة
// - تحتوي على كل أوامر رسم أجزاء السيارة وتفاصيلها.
// -----------------------------------------------------------------------------
void MountainCar::draw() {
    // --- 1. تعريف الأدوات والمواد مرة واحدة فقط في بداية الدالة ---
    GLUquadric* quadric = gluNewQuadric();
    // مواد الإضاءة الذاتية (Emission)
    float whiteEmission[] = { 1.0, 1.0, 1.0, 1.0 };
    float redEmission[] = { 1.0, 0.0, 0.0, 1.0 };
    float yellowEmission[] = { 1.0, 1.0, 0.0, 1.0 };
    float noEmission[] = { 0.0, 0.0, 0.0, 1.0 };
    // مواد الزجاج اللامع
    float glass_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float glass_shininess[] = { 128.0 };
    float default_specular[] = { 0.0, 0.0, 0.0, 1.0 };
    float default_shininess[] = { 0.0 };

    // --- 2. التحويلات الأساسية للسيارة (الموقع والدوران) ---
    glPushMatrix(); // نبدأ مجموعة تحويلات السيارة (مهم جداً)
    // أولاً: ننقل السيارة بالكامل إلى موقعها في العالم
    glTranslatef(this->pos.x, this->pos.y, this->pos.z);

    // ثانياً: ندور السيارة بالكامل لتواجه المدخل
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);

    // --- 3. الهيكل الرئيسي ---
    // الجسم الأساسي (الشاسيه)
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
    glScalef(50, 20, 90); glutSolidCube(1);
    glPopMatrix();
    // مقصورة الركاب
    glColor3f(0.15f, 0.15f, 0.15f);
    glPushMatrix();
    glTranslatef(0, 18, -10); glScalef(48, 16, 60); glutSolidCube(1);
    glPopMatrix();

    // --- 4. العجلات ---
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
    // الإطار الاحتياطي (تم تصحيح موقعه ليبرز للخارج)
    glPushMatrix();
    glTranslatef(0, 5, -50.0f); drawWheelWithRim(quadric);
    glPopMatrix();

    // --- 5. المصد الأمامي ---
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(0, -12, 46); glScalef(52, 4, 4); glutSolidCube(1);
    glPopMatrix();

    // --- 6. الزجاج الأمامي (باستخدام GL_QUADS لتجنب الاختراق وبميلان صحيح) ---
    glEnable(GL_BLEND); // تفعيل الشفافية
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.6f, 0.8f, 1.0f, 0.4f); // لون زجاجي مع شفافية
    glBegin(GL_QUADS);
    glVertex3f(-24.0f, 26.0f, 20.0f); // الركن العلوي الأيسر (متصل بالمقصورة)
    glVertex3f(24.0f, 26.0f, 20.0f); // الركن العلوي الأيمن (متصل بالمقصورة)
    glVertex3f(24.0f, 10.0f, 22.0f); // الركن السفلي الأيمن (متصل بالجسم، تم تصحيح ميله)
    glVertex3f(-24.0f, 10.0f, 22.0f); // الركن السفلي الأيسر (متصل بالجسم، تم تصحيح ميله)
    glEnd();
    glDisable(GL_BLEND); // تعطيل الشفافية

    // --- 7. الأضواء الرئيسية (باستخدام Emission) ---
    glEnable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_EMISSION, whiteEmission); // تفعيل الإضاءة البيضاء
    glPushMatrix();
    glTranslatef(20, 0, 45.1); glScalef(6, 4, 1); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-20, 0, 45.1); glScalef(6, 4, 1); glutSolidCube(1);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, redEmission); // تفعيل الإضاءة الحمراء
    glPushMatrix();
    glTranslatef(22, 0, -45.1); glScalef(4, 3, 1); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-22, 0, -45.1); glScalef(4, 3, 1); glutSolidCube(1);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission); // إطفاء الإضاءة
    glDisable(GL_LIGHTING);

    // --- 8. النوافذ الجانبية اللامعة (باستخدام Specular Material) ---
    glEnable(GL_LIGHTING);
    glColor3f(0.0f, 0.0f, 0.0f);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
    glMaterialfv(GL_FRONT, GL_SPECULAR, glass_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, glass_shininess);
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
    glMaterialfv(GL_FRONT, GL_SPECULAR, default_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, default_shininess);
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    // --- 9. مقابض الأبواب والفواصل ---
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

    // --- 10. التفاصيل النهائية (مرايا، شبك، قضبان، مصابيح ضباب) ---
    // المرايا
    glColor3f(0.15f, 0.15f, 0.15f);
    glPushMatrix();
    glTranslatef(26, 15, 15); glScalef(4, 8, 4); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-26, 15, 15); glScalef(4, 8, 4); glutSolidCube(1);
    glPopMatrix();
    // الشبك الأمامي
    glColor3f(0.05f, 0.05f, 0.05f);
    glPushMatrix();
    glTranslatef(0, 0, 45.2); glScalef(40, 12, 1); glutSolidCube(1);
    glPopMatrix();
    // قضبان السقف
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(20, 26.5, -10); glScalef(2, 1, 58); glutSolidCube(1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-20, 26.5, -10); glScalef(2, 1, 58); glutSolidCube(1);
    glPopMatrix();
    // مصابيح الضباب (تم تصحيح موقعها واستخدام كرة لإظهارها)
    glEnable(GL_LIGHTING);
    glMaterialfv(GL_FRONT, GL_EMISSION, yellowEmission);
    glPushMatrix();
    glTranslatef(15, -12, 48.5f); // تم إبرازها للأمام
    glutSolidSphere(2.5, 20, 20); // استخدام كرة لضمان ظهورها
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-15, -12, 48.5f);
    glutSolidSphere(2.5, 20, 20);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, noEmission);
    glDisable(GL_LIGHTING);

    // --- 11. نهاية الرسم ---
    glPopMatrix(); // ننهي مجموعة تحويلات السيارة
    gluDeleteQuadric(quadric); // نحذف أداة الرسم
}
