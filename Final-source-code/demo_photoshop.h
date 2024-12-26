#ifndef VISUALVORTEX_H
#define VISUALVORTEX_H

#include <QMainWindow>
#include <QString>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include <QLabel>
#include <QStack>  // For undo/redo stacks
#include <QVector>
#include <QPushButton>
#include <QMouseEvent>
#include <QCursor>
QT_BEGIN_NAMESPACE
namespace Ui {
class demo_photoshop;
}
QT_END_NAMESPACE

class demo_photoshop : public QMainWindow
{
    Q_OBJECT


public:
    explicit demo_photoshop(QWidget *parent = nullptr);
    // demo_photoshop(QWidget *parent = nullptr);
    ~demo_photoshop();



private slots:
    void on_pushButton_2_clicked();
    void on_save_btn_clicked();
    void on_del_btn_clicked();
    void zoomIn();
    void zoomOut();
    void on_tabs_menu_tabCloseRequested(int index);
    void on_tabs_menu_currentChanged(int index);
    void on_ChangeCurrentPhoto_clicked();
    void on_Invert_image_clicked();
    void on_Black_White_clicked();
    void on_Sunny_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void green_filter(QImage &image, int degree);
    void on_applyButton_clicked(); // Triggered when 'Apply' is clicked for a filter
    void on_cancelButton_clicked(); // Triggered when 'Cancel' is clicked for a filter
    void on_Clear_clicked();
    void Egg(QImage &image);


    void on_Show_original_image_stateChanged(int state);
    // Undo and Redo slots
    void on_undo_clicked();  // Undo button clicked
    void on_redo_clicked();  // Redo button clicked
    void applyCannyEdgeDetection(QImage &image);
    void on_hideUI_stateChanged(int state);
    void applyGaussianBlur(QImage &image);
    void on_Heart_frame_clicked();
    QImage calculateGradients(const QImage &image);
    void performEdgeTracking(QImage &image);
    QImage nonMaximumSuppression(const QImage &image);
    void on_Rain_Drop_clicked();
    QImage applyDoubleThreshold(const QImage &image);
    void on_Infra_Red_clicked();

    void on_Grayscale_clicked();

    void on_Oil_painting_clicked();

    void on_Ball_clicked();
    void Show();
    void Hide_2();
    void is_bool_slider_off();

    void on_Blur_clicked();
    void lighten_darken_image(QImage &image, int degree);

    void on_Lighten_Darken_clicked();
    void pixelate(QImage &image, int slideValue);
    void skew(QImage &image, double angle);
    void on_Pixelate_clicked();

    void on_Skew_clicked();

    void on_rotateRightButton_clicked();
    void on_rotateLeftButton_clicked();
    void centerLight(QImage &image, float intensity);
    void on_Center_Light_clicked();
    void rotateCamera(QImage &image, float angle);

    void on_Lost_Signal_clicked();

    void on_Vintage_clicked();
    void applyVintageEffect(QImage &image);
    void on_TV_clicked();
    void applyLostSignalEffect(QImage &image);
    void applyFancyFrame(QImage &image, QColor frameColor, QColor frameColor2, int frameSize);
    void on_Rotate_Camera_clicked();
    void rotateFrame(QImage &image, float angle);
    void on_Rotate_Frame_clicked();

    void on_Egg_clicked();

    void on_Detect_Edge_clicked();




    void applyVerticalFlip(QImage &image);
    void on_vertical_flip_clicked();
    void applyHorizontalFlip(QImage &image);
    void on_horiozontal_flip_clicked();
    void on_Flip_clicked();

    void on_Wave_Horizontal_clicked();

    void on_Wave_Vertical_clicked();

    void on_Frequency_textChanged(const QString &arg1);
    void wave(QImage& image, float frequency, float height, const std::string& orientation);
    void on_Height_textChanged(const QString &arg1);
    void on_Wave_clicked();

    void on_Upload_Second_clicked();

    void on_Merge_Primary_clicked();

    void on_Merge_Secondary_clicked();

    void on_Merge_clicked();
    void mergeImages(const QImage &primary, const QImage &secondary, bool usePrimaryDimensions);

    void on_Resize_clicked();

    void on_Width_textChanged(const QString &arg1);

    void on_Height_2_textChanged(const QString &arg1);

    void on_Apply_resize_clicked();

    void on_Cancel_resize_clicked();



    void on_Modes_clicked(bool checked);

    void updateImageProperties(const QImage &currentImage);
    void resizeImage(const QSize &newSize);

    void on_Frames_2_clicked();

    void on_selectColor_clicked();
    void on_Crop_clicked();


    // New function for managing image history
    void updateImageHistory(const QImage &img);  // Updated to take QImage as parameter
    void updateDisplayedImage(const QImage &img);  // Updates the displayed image in the UI






    void on_CropTools_clicked();

    void on_Green_clicked();

    void on_Simple_clicked();

    void on_Arboretum_clicked();

    void on_Fancy_clicked();

    void on_Circle_Frame_clicked();

private:
    int historyIndex;
    Ui::demo_photoshop *ui;
    QImage originalImage;  // Store the original image
    QImage OG;
    QImage currentImage;
    QLabel *imageLabel;
    QVector<int> findProperties(QVector<QVector<int>> &imgArray, unsigned int &rows, unsigned int &cols);
    int bfSearch(QVector<int> &posn, QVector<QVector<int>> &explored, unsigned int &rows, unsigned int &cols, QVector<QVector<int>> &imgArray);
    QImage secondaryImage;  // Store the secondary image for merging
    // You can add other member variables if needed
    enum FrameType { Simple, Arboretum, Fancy, CircleFrame };
    FrameType currentFrameType;
    int square(int value){return value*value;};
    // New member variable to track inverted state
    bool isInverted = false;
    bool isBlackWhiteApplied = false;
    bool isBlurred=false;
    bool isPixelateApplied = false;
    bool isskewed = false;
    bool isrotatecamera = false;
    bool isrotateframe = false;
    void applyBlackWhiteFilter(QLabel *tabImageLabel);
    void sunny_filter(QImage &image, int degree);
    bool isGreenApplied = false;
    bool isSunnyApplied = false; // Flag to check if sunny filter is applied
    void blurImage(QImage &image,int degree);
    bool isPurpleApplied= false;
    bool isLighten_darkenapplied = false;
    bool iscenterlight = false;
    // Undo and Redo stacks
    QStack<QImage> undoStack;  // To store previous states for undo
    QStack<QImage> redoStack;  // To store undone states for redo
void applyFancyFrame(QImage &image, QColor frameColor, QColor frameColor2);
    // Maximum number of undo steps
    const int maxUndoSteps = 30;  // Maximum number of undo steps

    QVector<QImage> imageHistory;  // Stores the undo history
    QVector<QImage> redoHistory;   // Stores the redo history



    // try crop with mouse
    // variables
    QPoint startPoint;
    QPoint endPoint;
    bool isCropping;

};

// Helper function to invert an image
void invert_image(QPixmap& pixmap);

#endif // VISUALVORTEX_H
