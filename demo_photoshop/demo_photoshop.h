#ifndef DEMO_PHOTOSHOP_H
#define DEMO_PHOTOSHOP_H
#include <QMainWindow>
#include <QString>
QT_BEGIN_NAMESPACE
namespace Ui {
class demo_photoshop;
}
QT_END_NAMESPACE

class demo_photoshop : public QMainWindow
{
    Q_OBJECT

public:
    demo_photoshop(QWidget *parent = nullptr);
    ~demo_photoshop();

private slots:
    void on_horizontalSlider_rangeChanged(int min, int max);

private:
    Ui::demo_photoshop *ui;
};
class Image;

namespace ImageFilters {
void purple(Image& primary, QString& name);
void black_white(Image& primary, QString& name);
void invert_image(Image& primary, QString& name);
void flip(Image& primary, QString& name);
void crop(Image& primary, QString& name);
void rotate_image(Image& primary, QString& name);
void grayscale_image(Image& primary, QString& name);
void merge_image(Image& primary, QString& name);
void lighten_darken_image(Image& primary, QString& name);
void add_frame_to_image(Image& image, QString& name);
void add_frame_arboretum(Image& image, int* frame_color);
void add_frame_simple(Image& image, int* frame_color);
void Infra_Red(Image& primary, QString& name);
void resizing(Image& primary, QString& name);
void detect_edge(Image& primary, QString& name);
void blurImage(Image& primary, QString& name);
void sunny_filter(Image& primary, QString& name);
void oil_painting(Image& primary, QString& name);
void resize2_image(int new_width, int new_height, Image& image);
void filter_choices(QString filter_choice, Image& primary, QString& name);
void filters_menu(Image& primary, QString& name);
void asking_for_saving(Image& primary, QString& name);
void save_image(Image& primary, QString& name);
void load_image(Image& primary, QString& name);
void Cardiod(Image& image2, QString& name);
void center_light(Image& image, QString& name);
void rotate_frame(Image& image, QString& name);
QString valid_choice(QString filter_choice);
QString image_name_validate(QString name, QString& Image_name);
QString choice_load_save(QString choice);
QString choice_load_save_2(QString choice);
bool is_number(QString x);
bool validate_center_light(float num);
void Ball(Image& primary, QString& name);
void Pixelate(Image& primary, QString& name);
void Egg(Image& primary, QString& name);
int square(int x);
void rain_drop(Image& image, QString& name);
void skew(Image& image, QString& name);
float getValidFloatInput();
bool validate_rotate_frame(float num);

}
#endif
