#include <QFileDialog>
#include <QPixmap>
#include <QImage>
#include <QMessageBox>
#include <QStatusBar>
#include <QColor>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QQueue>
#include <QStack>
#include <algorithm>
#include <QScrollArea>
#include <QColorDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QColor>
#include <QPainter>
#include "demo_photoshop.h"
#include "ui_demo_photoshop.h"
#include "Image_Class.h"

demo_photoshop::demo_photoshop(QWidget *parent)
    : QMainWindow(parent),
    historyIndex(-1)
    , ui(new Ui::demo_photoshop)
     // Initialize imageLabel in the initializer list
{
    ui->setupUi(this);
    setWindowTitle("VisualVortex");
    setWindowIcon(QIcon(":/Button Icons/QT Photos/images_application.jfif"));
    // Light mode: green buttons on white background
    // Ensure QScrollArea resizes dynamically
    ui->scrollAreaImage->setWidgetResizable(true);

    // Enable the QLabel to scale its contents when resized
    ui->Image->setScaledContents(true);
    qApp->setStyleSheet(
        "QMainWindow { background-color: #F5F5F5; color: #000000; border: none; }"  // Main window background
        "QMenuBar { background-color: #f0f0f0; color: #000000; padding: 5px; border-bottom: 2px solid #ccc; }"  // Menu bar
        "QMenuBar::item { spacing: 5px; padding: 10px; }"  // Menu item styling
        "QMenu { background-color: #ffffff; border: 1px solid #ccc; border-radius: 5px; }"  // Menu background
        "QMenu::item { padding: 8px 12px; }"  // Menu item spacing
        "QMenu::item:selected { background-color: #A020F0; color: #ffffff; }"  // Selected menu item
        "QPushButton { background-color: #A020F0; color: #ffffff; border: none; padding: 8px; border-radius: 10px; box-shadow: 0px 6px 20px rgba(0, 0, 0, 0.3); transition: background-color 0.3s, transform 0.3s, box-shadow 0.3s; }"
        "QPushButton:hover { background-color: #B55EB5; transform: translateY(-6px); box-shadow: 0px 8px 20px rgba(0, 0, 0, 0.5); }"
        "QPushButton:pressed { background-color: #8B008B; transform: translateY(2px); box-shadow: 0px 4px 12px rgba(0, 0, 0, 0.3); }"
        "QTabWidget { border: 1px solid #ccc; border-radius: 8px; background: qlineargradient(y1:0, y2:1, stop:0 #ffffff, stop:1 #f0f0f0); }"
        "QTabBar::tab { background-color: #f0f0f0; color: #000000; padding: 10px; border: 1px solid #ccc; border-bottom: none; border-radius: 5px 5px 0 0; transition: background-color 0.3s, transform 0.3s; }"
        "QTabBar::tab:selected { background-color: #A020F0; color: white; font-weight: bold; }"
        "QToolBox { background-color: #ffffff; border: 1px solid #ccc; border-radius: 10px; padding: 5px; }"
        "QToolBox::title { background-color: #f0f0f0; color: #000000; padding: 10px; border: none; border-radius: 5px; font-weight: bold; }"
        "QToolBox::item { background-color: #f0f0f0; color: #000000; padding: 10px; border: 1px solid #ccc; border-radius: 5px; transition: background-color 0.3s, transform 0.3s; }"
        "QToolBox::item:hover { background-color: #D3D3D3; transform: scale(1.05); box-shadow: 0px 6px 12px rgba(0, 0, 0, 0.5); }"
        "QToolBox::item:selected { background-color: #A020F0; color: white; }"
        "QLabel { color: #000000; font-size: 14px; font-weight: bold; }"
        "QMainWindow { background-color: #F5F5F5; color: #000000; border: none; }"  // Main window background
        "QMenuBar { background-color: #f0f0f0; color: #000000; padding: 5px; border-bottom: 2px solid #ccc; }"  // Menu bar
        "QMenuBar::item { spacing: 5px; padding: 10px; }"  // Menu item styling
        "QMenu { background-color: #ffffff; border: 1px solid #ccc; border-radius: 5px; }"  // Menu background
        "QMenu::item { padding: 8px 12px; }"  // Menu item spacing
        "QMenu::item:selected { background-color: #A020F0; color: #ffffff; }"  // Selected menu item
        "QPushButton { background-color: #A020F0; color: #ffffff; border: none; padding: 8px; border-radius: 10px; box-shadow: 0px 6px 20px rgba(0, 0, 0, 0.3); transition: background-color 0.3s, transform 0.3s, box-shadow 0.3s; }"
        "QPushButton:hover { background-color: #B55EB5; transform: translateY(-6px); box-shadow: 0px 8px 20px rgba(0, 0, 0, 0.5); }"
        "QPushButton:pressed { background-color: #8B008B; transform: translateY(2px); box-shadow: 0px 4px 12px rgba(0, 0, 0, 0.3); }"
        "QTabWidget { border: 1px solid #ccc; border-radius: 8px; background: qlineargradient(y1:0, y2:1, stop:0 #ffffff, stop:1 #f0f0f0); }"
        "QTabBar::tab { background-color: #f0f0f0; color: #000000; padding: 10px; border: 1px solid #ccc; border-bottom: none; border-radius: 5px 5px 0 0; transition: background-color 0.3s, transform 0.3s; }"
        "QTabBar::tab:selected { background-color: #A020F0; color: white; font-weight: bold; }"
        "QToolBox { background-color: #ffffff; border: 1px solid #ccc; border-radius: 10px; box-shadow: 0px 6px 20px rgba(0, 0, 0, 0.3); padding: 5px; }"
        "QToolBox::title { background-color: #f0f0f0; color: #000000; padding: 10px; border: none; border-radius: 5px; font-weight: bold; }"
        "QToolBox::item { background-color: #f0f0f0; color: #000000; padding: 10px; border: 1px solid #ccc; border-radius: 5px; transition: background-color 0.3s, transform 0.3s; }"
        "QToolBox::item:hover { background-color: #D3D3D3; transform: scale(1.05); box-shadow: 0px 6px 12px rgba(0, 0, 0, 0.5); }"
        "QToolBox::item:selected { background-color: #A020F0; color: white; }"
        "QLabel { color: #000000; font-size: 14px; font-weight: bold; }"
        "QDoubleSpinBox, QSpinBox {"
        "   background-color: #ffffff;"
        "   color: #000000;"
        "   border: 1px solid #ccc;"
        "   border-radius: 5px;"
        "   padding: 5px;"
        "   selection-background-color: #A020F0;"
        "   selection-color: #ffffff;"
        "   transition: background-color 0.3s, border 0.3s;"
        "}"
        "QDoubleSpinBox:hover, QSpinBox:hover {"
        "   border: 1px solid #A020F0;"
        "}"
        "QGroupBox {"
        "   background-color: #ffffff;"
        "   color: #000000;"
        "   border: 1px solid #ccc;"
        "   border-radius: 10px;"
        "   padding: 10px;"
        "}"
        "QSlider::groove:horizontal {"
        "   background: #ccc;"
        "   height: 8px;"
        "   border-radius: 4px;"
        "}"
        "QSlider::handle:horizontal {"
        "   background: #A020F0;"
        "   border: 1px solid #ccc;"
        "   width: 16px;"
        "   margin: -4px 0;"
        "   border-radius: 8px;"
        "   transition: background 0.3s, transform 0.3s;"
        "}"
        "QSlider::handle:horizontal:hover {"
        "   background: #B55EB5;"
        "   transform: scale(1.1);"
        "}"
        "QSlider::sub-page:horizontal {"
        "   background: #A020F0;"
        "   border-radius: 4px;"
        "}"
        );
    ui->Center_Light->setIcon(QIcon(":/Button Icons/QT Photos/26603f5bbc37f5b46fa581d8df1be6d7.jpg"));
    ui->Rotate_Camera->setIcon(QIcon(":/Button Icons/QT Photos/565888.png"));
    ui->Resize->setIcon(QIcon(":/Button Icons/QT Photos/1014901.png"));
    ui->Rotate_Frame->setIcon(QIcon(":/Button Icons/QT Photos/download (1).png"));
    ui->Lost_Signal->setIcon(QIcon(":/Button Icons/QT Photos/9710797.png"));
    ui->Blur->setIcon(QIcon(":/Button Icons/QT Photos/1398140566_preview_3b2f.png"));
    ui->ChangeCurrentPhoto->setIcon(QIcon(":/Button Icons/QT Photos/another-change-3-512.png"));
    ui->Black_White->setIcon(QIcon(":/Button Icons/QT Photos/black-and-white.png"));
    ui->Lighten_Darken->setIcon(QIcon(":/Button Icons/QT Photos/brightness_5465005.png"));
    ui->cancelButton->setIcon(QIcon(":/Button Icons/QT Photos/cancel.png"));
    ui->Clear->setIcon(QIcon(":/Button Icons/QT Photos/clear.png"));
    ui->Skew->setIcon(QIcon(":/Button Icons/QT Photos/download (2).png"));
    ui->Pixelate->setIcon(QIcon(":/Button Icons/QT Photos/download (3).png"));
    ui->Ball->setIcon(QIcon(":/Button Icons/QT Photos/download (4).png"));
    ui->Merge->setIcon(QIcon(":/Button Icons/QT Photos/download (5).png"));
    ui->Rain_Drop->setIcon(QIcon(":/Button Icons/QT Photos/download.png"));
    ui->applyButton->setIcon(QIcon(":/Button Icons/QT Photos/emblemdefault_93502.png"));
    ui->Flip->setIcon(QIcon(":/Button Icons/QT Photos/Flip-2-icon-01.png"));
    ui->Heart_frame->setIcon(QIcon(":/Button Icons/QT Photos/heart.png"));
    ui->Hide->setIcon(QIcon(":/Button Icons/QT Photos/download (8).png"));
    ui->Wave->setIcon(QIcon(":/Button Icons/QT Photos/Iconarchive-Seaside-Water-Wave.512.png"));
    ui->Green->setIcon(QIcon(":/Button Icons/QT Photos/icone-d-image-violet.png"));
    ui->rotateLeftButton->setIcon(QIcon(":/Button Icons/QT Photos/icon-rotate-right-90-512.png"));
    ui->rotateRightButton->setIcon(QIcon(":/Button Icons/QT Photos/icon-rotate-left-90-512.png"));
    ui->Grayscale->setIcon(QIcon(":/Button Icons/QT Photos/image-512.png"));
    ui->Detect_Edge->setIcon(QIcon(":/Button Icons/QT Photos/images (1).png"));
    ui->Egg->setIcon(QIcon(":/Button Icons/QT Photos/images (2).png"));
    ui->Frames_2->setIcon(QIcon(":/Button Icons/QT Photos/1438744.png"));
    ui->CropTools->setIcon(QIcon(":/Button Icons/QT Photos/images.png"));
    ui->Invert_image->setIcon(QIcon(":/Button Icons/QT Photos/invert-colors.png"));
    ui->Oil_painting->setIcon(QIcon(":/Button Icons/QT Photos/oil.png"));
    ui->Show_original_image->setIcon(QIcon(":/Button Icons/QT Photos/download (10).png"));
    ui->Infra_Red->setIcon(QIcon(":/Button Icons/QT Photos/picture-512.png"));
    ui->Vintage->setIcon(QIcon(":/Button Icons/QT Photos/retro-vintage-photo-camera-icon-illustration-vector.jpg"));
    ui->Sunny->setIcon(QIcon(":/Button Icons/QT Photos/sun_1400310.png"));
    ui->TV->setIcon(QIcon(":/Button Icons/QT Photos/tv.png"));
    ui->horiozontal_flip->setIcon(QIcon(":/Button Icons/QT Photos/3536773-200.png"));
    ui->Wave_Horizontal->setIcon(QIcon(":/Button Icons/QT Photos/3536773-200.png"));
    ui->vertical_flip->setIcon(QIcon(":/Button Icons/QT Photos/282947-200.png"));
    ui->Wave_Vertical->setIcon(QIcon(":/Button Icons/QT Photos/282947-200.png"));
    ui->Upload_Second->hide();
    ui->Merge_Secondary->hide();
    ui->Merge_Primary->hide();
    ui->Frequency->hide();
    ui->Height_Label->hide();
    ui->Frequency_Label->hide();
    ui->Height->hide();
    ui->Wave_Vertical->hide();
    ui->Wave_Horizontal->hide();
    ui->rotateLeftButton->hide();
    ui->rotateRightButton->hide();
    ui->Vintage->hide();
    ui->Lost_Signal->hide();
    ui->SliderBox->hide();
    ui->Show_original_image->hide();
    ui->undo->hide();
    ui->redo->hide();
    ui->toolBox->hide();
    ui->Clear->hide();
    ui->label->hide();
    ui->frame->hide();
    ui->save_btn->hide();
    ui->ChangeCurrentPhoto->hide();
    ui->Hide->hide();
    ui->vertical_flip->hide();
    ui->horiozontal_flip->hide();
    ui->Apply_resize->hide();
    ui->Cancel_resize->hide();
    ui->Height_2->hide();
    ui->Height_Label_2->hide();
    ui->Width_Label->hide();
    ui->Width->hide();
    ui->selectColor->hide();
    ui->frameSizeSpinBox->hide();
    ui->Simple->hide();
    ui->Arboretum->hide();
    ui->Fancy->hide();
    ui->Circle_Frame->hide();
    ui->Crop->hide();
    ui->startXInput->hide();
    ui->startYInput->hide();
    ui->widthInput->hide();
    ui->heightInput->hide();
    ui->starting_points->hide();
    ui->cropped_dims->hide();
    ui->X_cord->hide();
    ui->Y_cord->hide();
    ui->Hight_crop->hide();
    ui->Width_crop->hide();
    // Initialize the status bar for displaying messages
    statusBar()->showMessage("Ready");
    //ui->SliderBox->hide();
    // Initialize with no tabs
    ui->tabs_menu->clear();

    // Get the existing layout
    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(ui->Image->layout());

    // If the layout is not a QVBoxLayout, you may need to use a different approach
    if (layout) {
        // Add the imageLabel to the existing layout
        layout->addWidget(imageLabel);
    } else {
        // If the layout is not a QVBoxLayout, you can try to get the layout of the specific widget
        // where you want to add the imageLabel
        QWidget *widget = ui->pushButton_2->parentWidget();
        if (widget) {
            layout = qobject_cast<QVBoxLayout*>(widget->layout());
            if (layout) {
                layout->addWidget(imageLabel);
            }
        }
    }

    // Connect the tab close request signal to the corresponding slot
    connect(ui->tabs_menu, &QTabWidget::tabCloseRequested, this, &demo_photoshop::on_tabs_menu_tabCloseRequested);
    connect(ui->tabs_menu, &QTabWidget::currentChanged, this, &demo_photoshop::on_tabs_menu_currentChanged);
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &demo_photoshop::on_horizontalSlider_valueChanged);
    connect(ui->Show_original_image, &QCheckBox::stateChanged, this, &demo_photoshop::on_Show_original_image_stateChanged);


    // In the constructor (demo_photoshop)
    connect(ui->Hide, &QCheckBox::stateChanged, this, &demo_photoshop::on_hideUI_stateChanged);

    QIcon myIcon(":/Button Icons/QT Photos/color-wheel.png");
    ui->toolBox->setItemIcon(0,myIcon);
    QIcon myIcon1(":/Button Icons/QT Photos/download (6).png");
    ui->toolBox->setItemIcon(1,myIcon1);
    QIcon myIcon2(":/Button Icons/QT Photos/download (7).png");
    ui->toolBox->setItemIcon(2,myIcon2);
    QIcon myIcon3(":/Button Icons/QT Photos/images (3).png");
    ui->toolBox->setItemIcon(3,myIcon3);
    ui->Modes->setIcon(QIcon(":/Button Icons/QT Photos/download (9).png"));
    ui->Merge_Primary->setIcon(QIcon(":/Button Icons/QT Photos/download (5).png"));
    ui->Merge_Secondary->setIcon(QIcon(":/Button Icons/QT Photos/download (5).png"));





}

demo_photoshop::~demo_photoshop()
{
    delete ui;
}

void demo_photoshop::on_pushButton_2_clicked() {
    // Create a new tab with the name "Image"
    QWidget *newTab = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(newTab);
    QLabel *emptyImageLabel = new QLabel();  // An empty label for future images

    // Set alignment for the empty label (centered)
    emptyImageLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(emptyImageLabel);

    // Add the tab to the tab widget and set the name "Image"
    ui->tabs_menu->addTab(newTab, "Image");


    // Update the status bar
    statusBar()->showMessage("Opened new tab: Image");
    int currentIndex = ui->tabs_menu->currentIndex();

    if (currentIndex >= 0) {
        // Prompt user to select an image file
        QString file_name = QFileDialog::getOpenFileName(this, "Open Image File", "", "Images (*.png *.xpm *.jpg);;All Files (*)");

        if (!file_name.isEmpty()) {
            // Load the selected image
            QImage img(file_name);
            OG = img; // Store the original image
            originalImage = img;
            imageHistory.clear();
            historyIndex = -1;
            updateImageHistory(img);

            // Check if the image loaded successfully
            if (img.isNull()) {
                QMessageBox::warning(this, "Error", "Failed to load image.");
                return;
            }

            // Find and update the QLabel inside the current tab
            QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
            imageLabel = currentTab->findChild<QLabel*>(); // Ensure this is the correct QLabel

            if (imageLabel) {
                // Set the pixmap directly without scaling to show the original size
                imageLabel->setPixmap(QPixmap::fromImage(img));

                // Adjust QLabel size to fit the image
                imageLabel->setScaledContents(true);
                imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                imageLabel->setAlignment(Qt::AlignCenter);
            } else {
                QMessageBox::warning(this, "Error", "Image label not found in current tab.");
                return;
            }

            // Update the tab title to the new image's filename
            ui->tabs_menu->setTabText(currentIndex, QFileInfo(file_name).fileName());

            // Update the dimensions and additional properties
            unsigned int cols = img.width();
            unsigned int rows = img.height();
            unsigned int numBlackPixels = 0;
            QVector<QVector<int>> imgArray(rows, QVector<int>(cols, 0));

            // Analyze the image for dark pixels
            for (unsigned int i = 0; i < rows; i++) {
                for (unsigned int j = 0; j < cols; j++) {
                    QColor clrCurrent(img.pixel(j, i));
                    int r = clrCurrent.red();
                    int g = clrCurrent.green();
                    int b = clrCurrent.blue();
                    int a = clrCurrent.alpha();
                    if ((r + g + b) < 20 && a > 240) {
                        imgArray[i][j] = 1;
                        numBlackPixels += 1;
                    }
                }
            }

            // Update the labels with image information
            ui->dims->setText(QString("W: %1 H: %2").arg(cols).arg(rows));
            float pD = (((float)numBlackPixels) / ((float)(cols * rows))) * 100;
            ui->PerecentDark->setText(QString::number(pD, 'f', 2) + "%");

            // Update the blobs and area information
            QVector<int> results = this->findProperties(imgArray, rows, cols);
            ui->Nblobs->setText(QString::number(results[0]));
            ui->MaxBlodArea->setText(QString::number(results[1]));



            // Show the relevant buttons
            ui->pushButton_2->hide();
            ui->ChangeCurrentPhoto->show();
            ui->Show_original_image->show();
            ui->undo->show();
            ui->redo->show();
            ui->toolBox->show();
            ui->Clear->show();
            ui->label->show();
            ui->frame->show();
            ui->save_btn->show();
            ui->Hide->show();
            ui->rotateLeftButton->show();
            ui->rotateRightButton->show();

        } else {
            QMessageBox::information(this, "Info", "No file selected.");

            int indexToClose = ui->tabs_menu->currentIndex(); // Get the index of the current tab
            if (indexToClose != -1) { // Ensure the index is valid
                on_tabs_menu_tabCloseRequested(indexToClose); // Call your function to close the tab
            }
        }

    } else {
        QMessageBox::information(this, "Info", "No tab selected.");
    }


}










QVector<int> demo_photoshop::findProperties(QVector<QVector<int>> &imgArray, unsigned int &rows, unsigned int &cols)
{
    int numIslands = 0;
    int maxArea = 0;
    int area = 0;
    // Create a 2D array to keep track of explored positions
    QVector<QVector<int>> explored(rows, QVector<int>(cols, 0));

    // Loop through each position in the image
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < cols; j++) {
            if (imgArray[i][j] == 1 && explored[i][j] == 0) {
                QVector<int> posn{static_cast<int>(i), static_cast<int>(j)};
                area = this->bfSearch(posn, explored, rows, cols, imgArray);

                // Update max area if the current blob's area is larger
                if (area > maxArea) {
                    maxArea = area;
                }
                numIslands += 1;
            }
        }
    }

    QVector<int> results{numIslands, maxArea};
    return results;
}

int demo_photoshop::bfSearch(QVector<int> &posn, QVector<QVector<int>> &explored, unsigned int &rows, unsigned int &cols, QVector<QVector<int>> &imgArray)
{
    // Potential moves: up/down/left/right
    QVector<QVector<int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int islandArea = 0;
    QQueue<QVector<int>> not_explored;
    not_explored.enqueue(posn); // Add the starting position to the queue
    explored[posn[0]][posn[1]] = 1; // Mark the starting position as explored

    while (!not_explored.isEmpty()) {
        QVector<int> current = not_explored.dequeue();
        int x = current[0];
        int y = current[1];
        islandArea++;

        for (const QVector<int> &direction : directions) {
            int nx = x + direction[0];
            int ny = y + direction[1];

            if (nx >= 0 && nx < int(rows) && ny >= 0 && ny < int(cols) && imgArray[nx][ny] == 1 && explored[nx][ny] == 0) {
                not_explored.enqueue(QVector<int>{nx, ny});
                explored[nx][ny] = 1; // Mark this position as explored
            }
        }
    }

    return islandArea;
}

void demo_photoshop::on_save_btn_clicked()
{
    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab
        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            // Prompt user for file location and name
            QString filePath = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("PNG Files (*.png);;JPEG Files (*.jpg *.jpeg);;All Files (*)"));

            // If the user selected a file path
            if (!filePath.isEmpty()) {
                // Convert the current QPixmap to QImage
                QImage image = tabImageLabel->pixmap().toImage();

                // Save the image to the chosen file path
                if (image.save(filePath)) {
                    QMessageBox::information(this, tr("Save Image"), tr("Image saved successfully."));
                } else {
                    QMessageBox::warning(this, tr("Save Image"), tr("Failed to save image. Please try again."));
                }
            }
        } else {
            QMessageBox::warning(this, tr("Save Image"), tr("No image available to save."));
        }
    }
}

void demo_photoshop::on_del_btn_clicked()
{
    // Confirm if the user wants to delete the image
    int result = QMessageBox::question(this, "Delete Image", "Are you sure you want to delete the image?", QMessageBox::Yes | QMessageBox::No);

    if (result == QMessageBox::Yes) {
        // Clear the QLabel by setting an empty QPixmap
        ui->Image->clear();
        // Inform the user that the image was deleted
        QMessageBox::information(this, "Success", "Image deleted.");
        // Update the status bar message
        statusBar()->showMessage("Image deleted");
    }
}

// Initialize zoom factors
const double ZOOM_FACTOR = 1.2;

void demo_photoshop::zoomIn() {
    QPixmap pixmap = ui->Image->pixmap(); // Get the QPixmap object from QLabel
    if (!pixmap.isNull()) {
        QPixmap scaledPix = pixmap.scaled(pixmap.size() * ZOOM_FACTOR, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->Image->setPixmap(scaledPix);
    }
}

void demo_photoshop::zoomOut() {
    QPixmap pixmap = ui->Image->pixmap(); // Get the QPixmap object from QLabel
    if (!pixmap.isNull()) {
        QPixmap scaledPix = pixmap.scaled(pixmap.size() / ZOOM_FACTOR, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->Image->setPixmap(scaledPix);
    }
}


void demo_photoshop::on_tabs_menu_tabCloseRequested(int index)
{
    // Debugging information
    qDebug() << "Requested to close tab at index:" << index;
    qDebug() << "Total tabs before close:" << ui->tabs_menu->count();

    // Ensure the index is valid
    if (index >= 0 && index < ui->tabs_menu->count()) {
        // Remove the specified tab
        ui->tabs_menu->removeTab(index);
    }
    ui->SliderBox->hide();
    ui->Show_original_image->hide();
    ui->Merge_Secondary->hide();
    ui->Merge_Primary->hide();
    ui->undo->hide();
    ui->redo->hide();
    ui->toolBox->hide();
    ui->Clear->hide();
    ui->Vintage->hide();
    ui->Lost_Signal->hide();
    ui->label->hide();
    ui->frame->hide();
    ui->save_btn->hide();
    ui->ChangeCurrentPhoto->hide();
    ui->Hide->hide();
    ui->rotateLeftButton->hide();
    ui->rotateRightButton->hide();
    ui->pushButton_2->show();
    ui->vertical_flip->hide();
    ui->horiozontal_flip->hide();
    ui->Upload_Second->hide();
    ui->Frequency->hide();
    ui->Height_Label->hide();
    ui->Frequency_Label->hide();
    ui->Height->hide();
    ui->Wave_Vertical->hide();
    ui->Wave_Horizontal->hide();
    ui->Apply_resize->hide();
    ui->Cancel_resize->hide();
    ui->Height_2->hide();
    ui->Height_Label_2->hide();
    ui->Width_Label->hide();
    ui->Width->hide();
    ui->selectColor->hide();
    ui->frameSizeSpinBox->hide();
    ui->Crop->hide();
    ui->startXInput->hide();
    ui->startYInput->hide();
    ui->widthInput->hide();
    ui->heightInput->hide();
    ui->starting_points->hide();
    ui->cropped_dims->hide();
    ui->X_cord->hide();
    ui->Y_cord->hide();
    ui->Hight_crop->hide();
    ui->Width_crop->hide();
    ui->Simple->hide();
    ui->Arboretum->hide();
    ui->Fancy->hide();
    ui->Circle_Frame->hide();
    qDebug() << "Total tabs after close:" << ui->tabs_menu->count();
}















void demo_photoshop::on_ChangeCurrentPhoto_clicked()
{
    int currentIndex = ui->tabs_menu->currentIndex();

    if (currentIndex >= 0) {
        // Prompt user to select an image file
        QString file_name = QFileDialog::getOpenFileName(this, "Open Image File", "", "Images (*.png *.xpm *.jpg);;All Files (*)");

        if (!file_name.isEmpty()) {
            // Load the selected image
            QImage img(file_name);
            OG = img; // Store the original image
            originalImage = img;
            imageHistory.clear();
            historyIndex = -1;
            updateImageHistory(img);

            // Check if the image loaded successfully
            if (img.isNull()) {
                QMessageBox::warning(this, "Error", "Failed to load image.");
                return;
            }

            // Find and update the QLabel inside the current tab
            QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
            imageLabel = currentTab->findChild<QLabel*>(); // Ensure this is the correct QLabel

            if (imageLabel) {
                // Set the pixmap directly without scaling to show the original size
                imageLabel->setPixmap(QPixmap::fromImage(img));

                // Adjust QLabel size to fit the image
                imageLabel->setScaledContents(true);
                imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                imageLabel->setAlignment(Qt::AlignCenter);
            } else {
                QMessageBox::warning(this, "Error", "Image label not found in current tab.");
                return;
            }

            // Update the tab title to the new image's filename
            ui->tabs_menu->setTabText(currentIndex, QFileInfo(file_name).fileName());

            // Update the dimensions and additional properties
            unsigned int cols = img.width();
            unsigned int rows = img.height();
            unsigned int numBlackPixels = 0;
            QVector<QVector<int>> imgArray(rows, QVector<int>(cols, 0));

            // Analyze the image for dark pixels
            for (unsigned int i = 0; i < rows; i++) {
                for (unsigned int j = 0; j < cols; j++) {
                    QColor clrCurrent(img.pixel(j, i));
                    int r = clrCurrent.red();
                    int g = clrCurrent.green();
                    int b = clrCurrent.blue();
                    int a = clrCurrent.alpha();
                    if ((r + g + b) < 20 && a > 240) {
                        imgArray[i][j] = 1;
                        numBlackPixels += 1;
                    }
                }
            }

            // Update the labels with image information
            ui->dims->setText(QString("W: %1 H: %2").arg(cols).arg(rows));
            float pD = (((float)numBlackPixels) / ((float)(cols * rows))) * 100;
            ui->PerecentDark->setText(QString::number(pD, 'f', 2) + "%");

            // Update the blobs and area information
            QVector<int> results = this->findProperties(imgArray, rows, cols);
            ui->Nblobs->setText(QString::number(results[0]));
            ui->MaxBlodArea->setText(QString::number(results[1]));
            ui->Show_original_image->show();
            ui->undo->show();
            ui->redo->show();
            ui->toolBox->show();
            ui->Clear->show();
            ui->label->show();
            ui->frame->show();
            ui->save_btn->show();
            ui->Hide->show();
            ui->rotateLeftButton->show();
            ui->rotateRightButton->show();

        } else {
            QMessageBox::information(this, "Info", "No file selected.");
        }

    } else {
        QMessageBox::information(this, "Info", "No tab selected.");
    }
}

void demo_photoshop::on_tabs_menu_currentChanged(int index)
{
    if (index >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(index);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();
        if (tabImageLabel) {
            QPixmap pix = tabImageLabel->pixmap();
            if (!pix.isNull()) {
                QImage img = pix.toImage();
                unsigned int cols = img.width();
                unsigned int rows = img.height();
                unsigned int numBlackPixels = 0;
                QVector<QVector<int>> imgArray(rows, QVector<int>(cols, 0));

                for (unsigned int i = 0; i < rows; i++) {
                    for (unsigned int j = 0; j < cols; j++) {
                        QColor clrCurrent(img.pixel(j, i));
                        int r = clrCurrent.red();
                        int g = clrCurrent.green();
                        int b = clrCurrent.blue();
                        int a = clrCurrent.alpha();
                        if ((r + g + b) < 20 && a > 240) {
                            imgArray[i][j] = 1;
                            numBlackPixels += 1;
                        }
                    }
                }

                ui->dims->setText(QString("W: %1 H: %2").arg(cols).arg(rows));
                float pD = (((float)numBlackPixels) / ((float)(cols * rows))) * 100;
                ui->PerecentDark->setText(QString::number(pD, 'f', 2) + "%");

                QVector<int> results = this->findProperties(imgArray, rows, cols);
                ui->Nblobs->setText(QString::number(results[0]));
                ui->MaxBlodArea->setText(QString::number(results[1]));
            }
        }
    }
}
void invert_image(QPixmap& pixmap) {
    if (!pixmap.isNull()) {
        QImage image = pixmap.toImage();
        image.invertPixels();  // Invert the colors
        pixmap = QPixmap::fromImage(image);  // Update the QPixmap

    }
}


void demo_photoshop::on_Invert_image_clicked() {
    ui->SliderBox->hide();
    is_bool_slider_off();
    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab
        if (tabImageLabel) {
            QPixmap pixmap = tabImageLabel->pixmap();  // Get the current image
            if (!isInverted) {  // Check if the image is not already inverted
                invert_image(pixmap);  // Invert the image
                tabImageLabel->setPixmap(pixmap);  // Update the QLabel with the inverted image
                tabImageLabel->update();  // Refresh the QLabel
                qDebug() << "Image inverted and QLabel updated.";
                originalImage = pixmap.toImage();  // Save the inverted image to originalImage
                updateImageHistory(originalImage);  // Update history with the inverted image
                updateImageProperties(originalImage);

            } else {
                // QMessageBox::information(this, "Info", "Image has already been inverted.");
            }
        }
    } else {
        QMessageBox::information(this, "Info", "No tab selected.");
    }
}

void demo_photoshop::on_Black_White_clicked() {
    ui->SliderBox->hide();
    is_bool_slider_off();
    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab
        if (tabImageLabel) {
            applyBlackWhiteFilter(tabImageLabel);  // Apply black and white filter
            tabImageLabel->update();  // Refresh the QLabel
        }
    } else {
        QMessageBox::information(this, "Info", "No tab selected.");
    }
}

void demo_photoshop::applyBlackWhiteFilter(QLabel *tabImageLabel) {
    if (tabImageLabel) {
        QPixmap pixmap = tabImageLabel->pixmap();
        if (!pixmap.isNull()) {
            QImage image = pixmap.toImage();
            int width = image.width();
            int height = image.height();

            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    QColor color = image.pixel(i, j);
                    int avg = (color.red() + color.green() + color.blue()) / 3;  // Average of RGB values
                    if (avg > 127) {
                        // Set to white
                        image.setPixel(i, j, qRgb(255, 255, 255));
                    } else {
                        // Set to black
                        image.setPixel(i, j, qRgb(0, 0, 0));
                    }
                }
            }
            originalImage = image;  // Save the processed image to originalImage
            updateImageHistory(originalImage);  // Update history with the new image
            tabImageLabel->setPixmap(QPixmap::fromImage(image));  // Update the QLabel with the new image
            tabImageLabel->update();  // Refresh the QLabel
            updateImageProperties(originalImage);
        }
    }
}

void demo_photoshop::on_horizontalSlider_valueChanged(int value) {
    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab

        if (tabImageLabel) {
            // Only modify the image if the original image is set
            if (!originalImage.isNull()) {
                QImage image = originalImage.copy();  // Start from the original image

                // Apply filters based on the current state
                if (isSunnyApplied) {
                    sunny_filter(image, value);  // Apply the sunny filter with the slider value
                }
                else if (isBlurred) {
                    blurImage(image, value);  // Apply the blur filter with the slider value
                }
                else if (isGreenApplied) {
                    green_filter(image, value);  // Apply the purple filter with the slider value
                }
                else if (isLighten_darkenapplied) {
                    // Apply lightening or darkening based on slider position
                    if (value > 0) {
                        lighten_darken_image(image, value);  // Lighten the image
                    } else if (value < 0) {
                        lighten_darken_image(image, value);  // Darken the image
                    }
                }
                else if (isPixelateApplied) {
                    pixelate(image, value);
                }
                else if (isskewed) {
                    skew(image, value);
                }
                else if (isrotatecamera) {
                    rotateCamera(image, value);
                }
                else if (isrotateframe) {
                    rotateFrame(image, value);
                }
                else if (iscenterlight) {
                    centerLight(image, value);
                }

                // Directly update the QLabel with the image without scaling
                QPixmap pixmap = QPixmap::fromImage(image);
                tabImageLabel->setPixmap(pixmap);  // Update the QLabel with the image

                updateImageProperties(originalImage);  // Update the image properties
            }
        }
    }
}
void demo_photoshop::pixelate(QImage &image, int slideValue) {
    if (slideValue == 0) {
        return;  // Exit the function without applying the filter
    }
    // Calculate the block size based on the slider value
    int blockSize = (slideValue / 100.0) * std::min(image.width(), image.height());

    for (int i = 0; i < image.width(); i += blockSize) {
        for (int j = 0; j < image.height(); j += blockSize) {
            int R = 0, G = 0, B = 0, count = 0;

            // Accumulate colors within the block
            for (int k = 0; k < blockSize && (i + k) < image.width(); ++k) {
                for (int l = 0; l < blockSize && (j + l) < image.height(); ++l) {
                    QColor color = image.pixel(i + k, j + l);
                    R += color.red();
                    G += color.green();
                    B += color.blue();
                    count++;
                }
            }

            // Average the colors
            if (count > 0) {
                R /= count;
                G /= count;
                B /= count;

                // Set the block to the averaged color
                for (int k = 0; k < blockSize && (i + k) < image.width(); ++k) {
                    for (int l = 0; l < blockSize && (j + l) < image.height(); ++l) {
                        image.setPixel(i + k, j + l, qRgb(R, G, B));
                    }
                }
            }
        }
    }
}


void demo_photoshop::on_Pixelate_clicked()
{
    Hide_2();
    ui->horizontalSlider->setValue(0);  // Set initial slider value to 100
    ui->horizontalSlider->setRange(0, 50);  // Set the range of the slider for pixelation

    isPixelateApplied = true;

    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab
        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage();  // Store the original image
            QImage image = originalImage.copy();  // Make a copy of the original image to apply the filter
            pixelate(image, ui->horizontalSlider->value());  // Apply the pixelation filter initially
            tabImageLabel->setPixmap(QPixmap::fromImage(image));  // Update the QLabel with the filtered image
            updateImageProperties(originalImage);
        }
    }
}


void demo_photoshop::lighten_darken_image(QImage &image, int degree) {
    if (degree == 0) {
        return;  // Exit the function without applying the filter
    }
    double change = static_cast<double>(degree);

    // Cap the change to a maximum of 100 and a minimum of -100
    if (change > 100) change = 100;
    if (change < -100) change = -100;

    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            QColor color = image.pixel(i, j);
            int red, green, blue;

            if (change > 0) { // Lighten
                red = std::min(255, static_cast<int>(color.red() * (1 + change / 100)));
                green = std::min(255, static_cast<int>(color.green() * (1 + change / 100)));
                blue = std::min(255, static_cast<int>(color.blue() * (1 + change / 100)));
            } else { // Darken
                red = std::max(0, static_cast<int>(color.red() * (1 + change / 100)));
                green = std::max(0, static_cast<int>(color.green() * (1 + change / 100)));
                blue = std::max(0, static_cast<int>(color.blue() * (1 + change / 100)));
            }

            image.setPixel(i, j, qRgb(red, green, blue));
        }
    }
}
void demo_photoshop::on_Lighten_Darken_clicked()
{
    Hide_2();
    ui->horizontalSlider->setValue(0);  // Set initial slider value to 0
    ui->horizontalSlider->setRange(-100, 100);  // Set the range of the slider
    isLighten_darkenapplied = true;
    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab
        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage();  // Store the original image
            QImage image = originalImage.copy();  // Make a copy of the original image to apply the filter
            lighten_darken_image(image, ui->horizontalSlider->value());  // Apply the sunny filter initially
            tabImageLabel->setPixmap(QPixmap::fromImage(image));  // Update the QLabel with the filtered image
            updateImageProperties(originalImage);
        }
    }
}
void demo_photoshop::green_filter(QImage &image, int degree) {
    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            QColor color = image.pixel(i, j);
            // Adjust the red and blue components based on the degree
            int red = std::min(255, color.red() + degree);
            int green = std::max(0,color.green()-(degree+15));
            int blue = std::min(255, color.blue() + degree);
            image.setPixel(i, j, qRgb(red, green, blue));
        }
    }
}

void demo_photoshop::on_Green_clicked() {
    Hide_2();
    ui->horizontalSlider->setValue(0);  // Set initial slider value to 1
    ui->horizontalSlider->setRange(0, 100);  // Set the range of the slider

    // Set isGreenApplied to true, indicating that the green filter is active
    isGreenApplied = true;

    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab
        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage();  // Store the original image
            QImage image = originalImage.copy();  // Make a copy of the original image to apply the filter
            green_filter(image, ui->horizontalSlider->value());  // Apply the green filter with the current slider value
            tabImageLabel->setPixmap(QPixmap::fromImage(image));  // Update the QLabel with the filtered image
            updateImageProperties(originalImage);
            ui->horizontalSlider->setValue(0);  // Reset the slider value to 0
        }
    }
}
void demo_photoshop::sunny_filter(QImage &image, int degree) {
    if (degree == 0) {
        return;  // Exit the function without applying the filter
    }
    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            QColor color = image.pixel(i, j);
            // Adjust the color values based on the degree
            int red = std::min(255, color.red() + degree);
            int green = std::min(255, color.green() + degree);
            int blue = std::max(0, color.blue() - degree);
            image.setPixel(i, j, qRgb(red, green, blue));
        }
    }
}

void demo_photoshop::on_Sunny_clicked() {
    Hide_2();
    ui->horizontalSlider->setValue(0);  // Set initial slider value to 0
    ui->horizontalSlider->setRange(0, 100);  // Set the range of the slider

    // Set isSunnyApplied to true, indicating that the sunny filter is active
    isSunnyApplied = true;

    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab
        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage();  // Store the original image
            QImage image = originalImage.copy();  // Make a copy of the original image to apply the filter
            sunny_filter(image, ui->horizontalSlider->value());  // Apply the sunny filter initially
            tabImageLabel->setPixmap(QPixmap::fromImage(image));  // Update the QLabel with the filtered image
            updateImageProperties(originalImage);
        }
    }
}









void demo_photoshop::on_applyButton_clicked() {
    Show();
    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab
        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            // Update originalImage to the current image, finalizing the changes
            originalImage = tabImageLabel->pixmap().toImage();
            updateImageHistory(originalImage);  // Update history with the applied image
            updateImageProperties(originalImage);
        }
        ui->horizontalSlider->setValue(0);
    }




    // Reset filter-specific flags
    is_bool_slider_off();
}

void demo_photoshop::Hide_2(){
    ui->SliderBox->show();
    ui->Show_original_image->hide();
    ui->undo->hide();
    ui->redo->hide();
    ui->toolBox->hide();
    ui->Clear->hide();
    ui->label->hide();
    ui->frame->hide();
    ui->save_btn->hide();
    ui->ChangeCurrentPhoto->hide();
    ui->Hide->hide();
    ui->rotateLeftButton->hide();
    ui->rotateRightButton->hide();
    ui->vertical_flip->hide();
    ui->horiozontal_flip->hide();
}

void demo_photoshop::Show(){
    ui->SliderBox->hide();
    ui->Show_original_image->show();
    ui->undo->show();
    ui->redo->show();
    ui->toolBox->show();
    ui->Clear->show();
    ui->label->show();
    ui->frame->show();
    ui->save_btn->show();
    ui->ChangeCurrentPhoto->show();
    ui->Hide->show();
    ui->rotateLeftButton->show();
    ui->rotateRightButton->show();
    //ui->vertical_flip->show();
    //ui->horiozontal_flip->show();
}

void demo_photoshop::on_cancelButton_clicked() {
    Show();
    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab
        if (tabImageLabel && !originalImage.isNull()) {
            tabImageLabel->setPixmap(QPixmap::fromImage(originalImage));  // Revert to the original image
            updateImageProperties(originalImage);
        }
    }
    // Reset filter-specific flags
    is_bool_slider_off();
    ui->horizontalSlider->setValue(0);
}







void demo_photoshop::updateDisplayedImage(const QImage &img) {
    if (imageLabel) {
        // Convert QImage to QPixmap
        QPixmap pixmap = QPixmap::fromImage(img);

        // Set the original pixmap to QLabel without resizing
        imageLabel->setPixmap(pixmap);

        // Align the image to the center of QLabel
        imageLabel->setAlignment(Qt::AlignCenter);

        // Set QLabel's size policy to allow it to resize freely
        imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

        // If QLabel is inside a QScrollArea, ensure the scroll area resizes properly
        if (QScrollArea* scrollArea = qobject_cast<QScrollArea*>(imageLabel->parentWidget())) {
            scrollArea->setWidgetResizable(true); // Allow the scroll area to resize with the image
        }

        // Optionally adjust the size of QLabel to fit the pixmap exactly
        // imageLabel->adjustSize(); // Remove or comment this line if you want to maintain the original label size
    } else {
        qDebug() << "Image label is null.";
    }
}







void demo_photoshop::updateImageHistory(const QImage &img) {
    if (imageHistory.isEmpty() || imageHistory[historyIndex] != img) {
        if (historyIndex < imageHistory.size() - 1) {
            imageHistory.erase(imageHistory.begin() + historyIndex + 1, imageHistory.end());
        }
        imageHistory.push_back(img);
        historyIndex++;
        if (imageHistory.size() > maxUndoSteps) {
            imageHistory.erase(imageHistory.begin());
            historyIndex--;
        }
        redoHistory.clear();
    }
}







void demo_photoshop::on_undo_clicked() {
    if (historyIndex > 0) {
        redoHistory.push_back(imageHistory[historyIndex]);
        historyIndex--;
        if (historyIndex >= 0) {
            const QImage &previousImage = imageHistory[historyIndex];
            updateDisplayedImage(previousImage);
            updateImageProperties(previousImage);
        }
    } else {
        qDebug() << "No action to undo.";
    }
}

void demo_photoshop::on_redo_clicked() {
    if (!redoHistory.isEmpty()) {
        const QImage &redoImage = redoHistory.last();
        imageHistory.push_back(redoImage);
        historyIndex++;
        redoHistory.pop_back();
        updateDisplayedImage(redoImage);
        updateImageProperties(redoImage);
    } else {
        qDebug() << "No action to redo.";
    }
}

void demo_photoshop::on_Clear_clicked() {
    if (!OG.isNull()) {
        // Clear all history
        imageHistory.clear();
        undoStack.clear();
        redoHistory.clear();
        redoStack.clear();

        // Reset originalImage to OG
        originalImage = OG;

        // Update any necessary states
        is_bool_slider_off();

        // Update the displayed image to the original
        updateDisplayedImage(originalImage);

        // Reset history index
        historyIndex = -1;

        // Optionally, you might want to reset the slider position
        ui->horizontalSlider->setValue(0);  // Reset slider to 0 or a default value
        updateImageProperties(originalImage);
    } else {
        qDebug() << "Original image (OG) is null.";
        QMessageBox::warning(this, "Warning", "No original image to revert to.");

        updateImageProperties(originalImage); // for dubgging
    }
}






void demo_photoshop::on_Show_original_image_stateChanged(int state)
{
    if (state == Qt::Checked) {
        qDebug() << "Showing original image";
        updateDisplayedImage(OG);  // Show original image
    } else if (state == Qt::Unchecked) {
        qDebug() << "Showing modified image";
        updateDisplayedImage(originalImage);  // Show modified image
        updateImageProperties(originalImage);
    }
}

void demo_photoshop::on_hideUI_stateChanged(int state)
{
    if (state == Qt::Checked) {
        ui->Clear->hide();
        ui->redo->hide();
        ui->undo->hide();
        ui->toolBox->hide();
        ui->SliderBox->hide();
        ui->Show_original_image->hide();
        ui->label->hide();
        ui->frame->hide();
        ui->save_btn->hide();
        ui->ChangeCurrentPhoto->hide();
        ui->rotateLeftButton->hide();
        ui->rotateRightButton->hide();
    } else if (state == Qt::Unchecked) {

        if(isSunnyApplied ||isBlurred||isPurpleApplied||isLighten_darkenapplied||isPixelateApplied) {ui->SliderBox->show();}
        ui->Show_original_image->show();
        ui->label->show();
        ui->Clear->show();
        ui->redo->show();
        ui->undo->show();
        ui->frame->show();
        ui->toolBox->show();
        ui->save_btn->show();
        ui->ChangeCurrentPhoto->show();
        ui->rotateLeftButton->show();
        ui->rotateRightButton->show();
    }
}

int square(int x){return x*x;}
void rain_drop(QPixmap &pixmap) {
    if (!pixmap.isNull()) {
        QImage image = pixmap.toImage();  // Convert QPixmap to QImage
        float coef = 100.0 / std::min(image.width(), image.height());

        for (int i = 0; i < image.width(); ++i) {
            for (int j = 0; j < image.height(); ++j) {
                float c = coef * std::sqrt((i - image.width() / 2) * (i - image.width() / 2) +
                                           (j - image.height() / 2) * (j - image.height() / 2));
                float z = 0.8 * (std::sin(c) / c + 0.24);

                // Get original pixel values
                QRgb pixel = image.pixel(i, j);
                int r = qRed(pixel);
                int g = qGreen(pixel);
                int b = qBlue(pixel);

                // Apply the effect
                r = std::min(255, static_cast<int>(r * z * 3));
                g = std::min(255, static_cast<int>(g * z * 3));
                b = std::min(255, static_cast<int>(b * z * 3));

                // Set modified pixel values
                image.setPixel(i, j, qRgb(r, g, b));
            }
        }

        pixmap = QPixmap::fromImage(image);  // Update the QPixmap with the processed image
    }
}


void demo_photoshop::on_Rain_Drop_clicked()
{
        int currentIndex = ui->tabs_menu->currentIndex(); // Get the current tab index
        if (currentIndex >= 0) {
            QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
            QLabel *tabImageLabel = currentTab->findChild<QLabel*>(); // Get the QLabel in the current tab
            if (tabImageLabel) {
                QPixmap pixmap = tabImageLabel->pixmap(); // Get the current image
                if (!pixmap.isNull()) { // Ensure the pixmap is not null
                    rain_drop(pixmap); // Apply the rain drop effect
                    tabImageLabel->setPixmap(pixmap); // Update the QLabel with the modified image
                    tabImageLabel->update(); // Refresh the QLabel

                    // Save the current image to history for undo
                    originalImage = pixmap.toImage(); // Store the original image
                    updateImageHistory(originalImage); // Update history with the original image
                    updateImageProperties(originalImage);
                } else {
                    QMessageBox::warning(this, "Warning", "No image to apply the effect.");
                }
            }
        } else {
            QMessageBox::information(this, "Info", "No tab selected.");
        }
}
void Infra_Red(QImage &image, const QString &name) {
    // Loop through each pixel
    for (int i = 0; i < image.width(); i++) {
        for (int j = 0; j < image.height(); j++) {
            QRgb pixel = image.pixel(i, j);

            // Get original color values
            int red = qRed(pixel);
            int green = qGreen(pixel);
            int blue = qBlue(pixel);

            // Apply Infrared effect
            green = 255 - red;
            blue = 255 - red;
            red = 255;

            // Set new pixel values
            image.setPixel(i, j, qRgb(red, green, blue));
        }
    }

    // Assuming a function to handle saving the image
    // asking_for_saving(image, name); // Uncomment this line if you have a saving function
}




void demo_photoshop::on_Infra_Red_clicked()
{
    int currentIndex = ui->tabs_menu->currentIndex(); // Get the current tab index
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>(); // Get the QLabel in the current tab
        QPixmap pixmap = tabImageLabel->pixmap();
        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            QImage img=pixmap.toImage();  // Store the original image
            QString name = "infra_red_image.png"; // Default name for saving the image
            Infra_Red(img, name); // Apply the Infrared effect

            // Update the originalImage with the processed image
            originalImage = img;

            // Update displayed image and history
            updateDisplayedImage(originalImage);
            updateImageHistory(originalImage);
            updateImageProperties(originalImage);

            // Update the QLabel with the modified image
            // tabImageLabel->setPixmap(QPixmap::fromImage(originalImage)); // Update the displayed image
        }
    }
}

void grayscale_image(QPixmap &pixmap) {
    if (!pixmap.isNull()) {
        QImage image = pixmap.toImage();  // Convert QPixmap to QImage

        // Loop through each pixel
        for (int i = 0; i < image.width(); i++) {
            for (int j = 0; j < image.height(); j++) {
                QRgb pixel = image.pixel(i, j);

                // Calculate the average of RGB values
                unsigned int avg = (qRed(pixel) + qGreen(pixel) + qBlue(pixel)) / 3;

                // Set each color component to the average
                image.setPixel(i, j, qRgb(avg, avg, avg));
            }
        }

        pixmap = QPixmap::fromImage(image);  // Update the QPixmap with the modified image
    }
}

void demo_photoshop::on_Grayscale_clicked() {
    ui->SliderBox->hide();  // Hide any sliders, if applicable
    is_bool_slider_off();   // Ensure the slider state is off
    int currentIndex = ui->tabs_menu->currentIndex(); // Get the current tab index

    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>(); // Get the QLabel in the current tab

        if (tabImageLabel) {
            QPixmap pixmap = tabImageLabel->pixmap(); // Get the current image
            if (!pixmap.isNull()) { // Ensure the pixmap is not null
                grayscale_image(pixmap); // Call your grayscale function
                // Save the current image to history for undo
                originalImage = pixmap.toImage(); // Store the original image
                updateImageHistory(originalImage); // Update history with the original image
                tabImageLabel->setPixmap(pixmap); // Update the QLabel with the modified image
                tabImageLabel->update(); // Refresh the QLabel
                updateImageProperties(originalImage);
                qDebug() << "Grayscale effect applied and QLabel updated.";
            } else {
                QMessageBox::warning(this, "Warning", "No image to apply the effect.");
            }
        }
    } else {
        QMessageBox::information(this, "Info", "No tab selected.");
    }
}

void oil_painting(QPixmap &pixmap) {
    if (!pixmap.isNull()) {
        QImage image = pixmap.toImage();  // Convert QPixmap to QImage

        int width = image.width();
        int height = image.height();

        // Resize if necessary
        if (width > 1000 || height > 1000) {
            image = image.scaled(1000, 1000, Qt::KeepAspectRatio, Qt::SmoothTransformation);
            width = image.width();
            height = image.height();
        }

        double intensity_level = 5.0; // Intensity levels used for effect
        int radius = 2; // Radius for 5x5 neighborhood
        int intensity_size = 256; // Maximum intensity value (0-255)

        for (int i = radius; i < width - radius; ++i) {
            for (int j = radius; j < height - radius; ++j) {
                std::vector<int> cur_intensity_count(intensity_size, 0);
                std::vector<int> average_R(intensity_size, 0);
                std::vector<int> average_G(intensity_size, 0);
                std::vector<int> average_B(intensity_size, 0);

                for (int k = i - radius; k <= i + radius; ++k) {
                    for (int l = j - radius; l <= j + radius; ++l) {
                        // Get pixel values
                        QRgb pixel = image.pixel(k, l);
                        int R = qRed(pixel);
                        int G = qGreen(pixel);
                        int B = qBlue(pixel);
                        int cur_intensity = static_cast<int>((static_cast<double>(R + G + B) / 3.0) * intensity_level / 255.0);

                        // Safeguard for intensity bounds
                        cur_intensity = std::max(0, std::min(255, cur_intensity));

                        // Update counts and averages
                        cur_intensity_count[cur_intensity]++;
                        average_R[cur_intensity] += R;
                        average_G[cur_intensity] += G;
                        average_B[cur_intensity] += B;
                    }
                }

                // Find the maximum intensity count
                int mx_intensity_count = 0, mx_intensity_index = 0;
                for (int M = 0; M < intensity_size; ++M) {
                    if (cur_intensity_count[M] > mx_intensity_count) {
                        mx_intensity_count = cur_intensity_count[M];
                        mx_intensity_index = M;
                    }
                }

                // Assign averaged values to the pixel
                if (mx_intensity_count > 0) {
                    image.setPixel(i, j, qRgb(
                                             average_R[mx_intensity_index] / mx_intensity_count,
                                             average_G[mx_intensity_index] / mx_intensity_count,
                                             average_B[mx_intensity_index] / mx_intensity_count
                                             ));
                }
            }
        }

        pixmap = QPixmap::fromImage(image);  // Update the QPixmap with the modified image
    }
}



void demo_photoshop::on_Oil_painting_clicked()
{
    ui->SliderBox->hide();  // Hide any sliders, if applicable
    is_bool_slider_off();   // Ensure the slider state is off
    int currentIndex = ui->tabs_menu->currentIndex(); // Get the current tab index

    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>(); // Get the QLabel in the current tab

        if (tabImageLabel) {
            QPixmap pixmap = tabImageLabel->pixmap(); // Get the current image

            if (!pixmap.isNull()) { // Ensure the pixmap is not null
                oil_painting(pixmap); // Call your oil painting function
                // Save the current image to history for undo
                originalImage = pixmap.toImage(); // Store the original image
                updateImageHistory(originalImage); // Update history with the original image
                updateImageProperties(originalImage);



                // Update the QLabel with the modified image
                tabImageLabel->setPixmap(pixmap); // Update the QLabel with the modified image
                tabImageLabel->update(); // Refresh the QLabel
                qDebug() << "Oil painting effect applied and QLabel updated.";
            } else {
                QMessageBox::warning(this, "Warning", "No image to apply the effect.");
            }
        }
    } else {
        QMessageBox::information(this, "Info", "No tab selected.");
    }
}

void Ball(QPixmap &pixmap) {
    if (!pixmap.isNull()) {
        QImage primary = pixmap.toImage();  // Convert QPixmap to QImage
        int size = std::min(primary.width(), primary.height());
        QImage image2(size, size, QImage::Format_RGB888); // Create a square image

        // Assign the half radius
        int r = size / 2;

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                double dist = sqrt((i - r) * (i - r) + (j - r) * (j - r));
                if (dist <= r) {
                    double ball = sqrt((r * r - dist * dist) / (r * r));
                    QRgb pixel = primary.pixel(i * primary.width() / size, j * primary.height() / size); // Scale back to original size
                    image2.setPixel(i, j, qRgb(
                                              qBound(0, int(qRed(pixel) * ball), 255),
                                              qBound(0, int(qGreen(pixel) * ball), 255),
                                              qBound(0, int(qBlue(pixel) * ball), 255)
                                              ));
                } else {
                    image2.setPixel(i, j, qRgb(0, 0, 0)); // Set pixels outside the ball to black
                }
            }
        }

        pixmap = QPixmap::fromImage(image2);  // Update the QPixmap with the processed image
    }
}


void demo_photoshop::on_Ball_clicked() {
    int currentIndex = ui->tabs_menu->currentIndex(); // Get the current tab index
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>(); // Get the QLabel in the current tab
        if (tabImageLabel) {
            QPixmap pixmap = tabImageLabel->pixmap(); // Get the current image
            if (!pixmap.isNull()) { // Ensure the pixmap is not null
                Ball(pixmap); // Apply the ball effect
                tabImageLabel->setPixmap(pixmap); // Update the QLabel with the modified image
                tabImageLabel->update(); // Refresh the QLabel
                qDebug() << "Ball effect applied and QLabel updated.";

                // Save the current image to history for undo
                originalImage = pixmap.toImage(); // Store the original image
                updateImageHistory(originalImage); // Update history with the original image
                updateImageProperties(originalImage);
            } else {
                QMessageBox::warning(this, "Warning", "No image to apply the effect.");
            }
        }
    } else {
        QMessageBox::information(this, "Info", "No tab selected.");
    }
}


void demo_photoshop::is_bool_slider_off(){
    isSunnyApplied=false;
    isBlurred=false;
    isPurpleApplied=false;
    isLighten_darkenapplied=false;
    isPixelateApplied=false;
    isskewed=false;
    isrotatecamera = false;
    isrotateframe = false;
    iscenterlight = false;
    isGreenApplied = false;
    ui->horizontalSlider->setValue(0);  // Reset the slider value to 0
}
void demo_photoshop::skew(QImage &image, double degree) {
    if (degree == 0) {
        return;  // Exit the function without applying the filter
    }
    // Convert degree into radians for skew angle
    double angle = static_cast<double>(degree) * M_PI / 180.0;
    double slope = tan(angle);

    int width = image.width();
    int height = image.height();

    // Adjust canvas size depending on whether we skew left or right
    int newWidth;
    int shiftAmount;

    if (slope > 0) {
        // Skew to the right
        newWidth = width + static_cast<int>(height * slope);
        shiftAmount = 0;
    } else {
        // Skew to the left
        newWidth = width + static_cast<int>(fabs(height * slope));
        shiftAmount = static_cast<int>(fabs(height * slope));  // Shift the image to the right to prevent clipping
    }

    // Create a new image to store the skewed result
    QImage skewedImage(newWidth, height, QImage::Format_ARGB32);
    skewedImage.fill(Qt::transparent);  // Fill with transparent background

    for (int y = 0; y < height; ++y) {
        int shift = static_cast<int>(y * slope);  // Calculate horizontal shift based on slope
        for (int x = 0; x < width; ++x) {
            // Apply the shift and ensure pixels remain within bounds
            int newX = x + shift + shiftAmount;
            if (newX >= 0 && newX < newWidth) {
                skewedImage.setPixel(newX, y, image.pixel(x, y));
            }
        }
    }

    image = skewedImage;  // Update the input image with the skewed result
}

void demo_photoshop::on_Skew_clicked() {
    Hide_2();
    ui->horizontalSlider->setValue(0);  // Set initial slider value to 0
    ui->horizontalSlider->setRange(-85, 85);  // Set the range of the slider to control skew angle

    isskewed = true;  // Set flag indicating that skew is active

    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab
        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage();  // Store the original image
            QImage image = originalImage.copy();  // Make a copy of the original image to apply the filter
            updateImageProperties(originalImage);
            skew(image, ui->horizontalSlider->value());  // Apply the skew filter initially
            tabImageLabel->setPixmap(QPixmap::fromImage(image));  // Update the QLabel with the skewed image
        }
    }
}



void demo_photoshop::blurImage(QImage &image, int degree) {
    if (degree == 0) {
        return;  // Exit the function without applying the filter
    }
    int kernelSize = qMax(1, degree / 10); // Example: Degree affects kernel size (minimum of 1)
    int iterations = 3; // You can also adjust this based on degree if desired
    int width = image.width();
    int height = image.height();
    QImage after = image.copy();

    // Applying blur for the specified number of iterations
    for (int iter = 0; iter < iterations; iter++) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                int sum[4] = {0}; // for RGBA channels
                int count = 0;

                for (int m = -kernelSize; m <= kernelSize; m++) {
                    for (int n = -kernelSize; n <= kernelSize; n++) {
                        int x = i + m;
                        int y = j + n;

                        if (x >= 0 && x < width && y >= 0 && y < height) {
                            QColor color(after.pixel(x, y));
                            sum[0] += color.red();
                            sum[1] += color.green();
                            sum[2] += color.blue();
                            sum[3] += color.alpha();
                            count++;
                        }
                    }
                }

                // Average the colors
                if (count > 0) {
                    image.setPixel(i, j, qRgba(sum[0] / count, sum[1] / count, sum[2] / count, sum[3] / count));
                }
            }
        }
        after = image; // Update after for the next iteration
    }
}

void demo_photoshop::on_Blur_clicked()
{
    Hide_2();
    ui->horizontalSlider->setValue(0);  // Set initial slider value to 0
    ui->horizontalSlider->setRange(0, 50);  // Set the range of the slider

    // Set isSunnyApplied to true, indicating that the sunny filter is active
    isBlurred = true;

    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab
        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage();  // Store the original image
            QImage image = originalImage.copy();  // Make a copy of the original image to apply the filter
            updateImageProperties(originalImage);
            blurImage(image, ui->horizontalSlider->value());  // Apply the sunny filter initially
            tabImageLabel->setPixmap(QPixmap::fromImage(image));  // Update the QLabel with the filtered image
        }
    }
}
void Cardiod(QImage& image) {
    int width = image.width();
    int height = image.height();
    QImage outputImage(1000, 1000, QImage::Format_RGB888); // Create a 1000x1000 output image

    double d1 = static_cast<double>(width) / 1000.0;
    double d2 = static_cast<double>(height) / 1000.0;

    float angle = 45 * M_PI / 180;   // Convert degrees to radians
    float angle2 = 315 * M_PI / 180; // Convert degrees to radians

    float cosAng = cos(angle);
    float sinAng = sin(angle);
    float cosAng2 = cos(angle2);
    float sinAng2 = sin(angle2);

    float k, k2;

    // Iterate over each pixel in the 1000x1000 output image
    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 1000; ++j) {
            if (0.7 * square(i - 500) + square((575 - j) - 13.416 * sqrt(abs(i - 500))) > 175000) {
                k = 0.7 * square(cosAng * (i - 150) + sinAng * (j - 850)) +
                    square((sinAng * (i - 150) + cosAng * (850 - j)) - 4 * sqrt(abs(cosAng * (i - 150) + sinAng * (j - 850))));
                k2 = 0.7 * square(cosAng2 * (i - 850) + sinAng2 * (j - 850)) +
                     square((sinAng2 * (i - 850) + cosAng2 * (850 - j)) - 4 * sqrt(abs(cosAng2 * (i - 850) + sinAng2 * (j - 850))));

                // Apply colors based on the cardioid shapes
                if (k < 500 || k2 < 500) {
                    outputImage.setPixel(i, j, qRgb(200, 185, 255));
                } else if (k < 1000 || k2 < 1000) {
                    outputImage.setPixel(i, j, qRgb(255, 70, 180));
                } else if (k < 2000 || k2 < 2000) {
                    outputImage.setPixel(i, j, qRgb(255, 0, 100));
                } else if (k < 3000 || k2 < 3000) {
                    outputImage.setPixel(i, j, qRgb(255, 0, 10));
                } else if (k < 4000 || k2 < 4000) {
                    outputImage.setPixel(i, j, qRgb(255, 105, 33));
                } else if (k < 5000 || k2 < 5000) {
                    outputImage.setPixel(i, j, qRgb(255, 120, 50));
                } else {
                    outputImage.setPixel(i, j, qRgb(255, 255, 255)); // Fill with white if out of bounds
                }
            } else {
                // Map original image pixels to the new image
                int srcX = static_cast<int>(i * d1);
                int srcY = static_cast<int>(j * d2);

                if (srcX < width && srcY < height) {
                    QRgb originalColor = image.pixel(srcX, srcY);
                    outputImage.setPixel(i, j, originalColor); // Use original pixel colors outside the shape
                } else {
                    outputImage.setPixel(i, j, qRgb(255, 255, 255)); // Fill with white if out of bounds
                }
            }
        }
    }

    image = outputImage; // Replace the original image with the modified one

    // Call function to save image - change this based on how saving works in your project
    // For example: saveImage(outputImage, name);
}


void demo_photoshop::on_Heart_frame_clicked() {
    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab
        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage();  // Store the original image
            QImage image = originalImage.copy();  // Copy the original image

            // Apply the Vintage effect
            Cardiod(image);
            tabImageLabel->setPixmap(QPixmap::fromImage(image));  // Update the label with the processed image

            // Update image history and display
            originalImage = image;
            updateImageHistory(originalImage);
            updateDisplayedImage(originalImage); // Function to update the displayed image
            updateImageProperties(originalImage);
        }
    }
}



void demo_photoshop::on_rotateRightButton_clicked() {
    int currentIndex = ui->tabs_menu->currentIndex(); // Get the current tab index
    QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
    QLabel *tabImageLabel = currentTab->findChild<QLabel*>(); // Get the QLabel in the current tab
    if (!tabImageLabel) {
        qDebug() << "No QLabel found in the current tab.";
        return; // Exit if QLabel is not found
    }

    // Get the current image from QLabel's pixmap
    QImage currentImage = tabImageLabel->pixmap().toImage();

    // Create a new QImage for the rotated image
    QImage rotatedImage(currentImage.height(), currentImage.width(), currentImage.format());

    // Rotate the image 90 degrees to the right
    for (int i = 0; i < currentImage.width(); ++i) {
        for (int j = 0; j < currentImage.height(); ++j) {
            QColor pixelColor = currentImage.pixel(i, j); // Get pixel color
            rotatedImage.setPixel(j, currentImage.width() - 1 - i, pixelColor.rgb()); // Rotate
        }
    }

    // Update the QLabel with the rotated image
    tabImageLabel->setPixmap(QPixmap::fromImage(rotatedImage)); // Update the displayed image
}

void demo_photoshop::on_rotateLeftButton_clicked() {
    int currentIndex = ui->tabs_menu->currentIndex(); // Get the current tab index
    QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
    QLabel *tabImageLabel = currentTab->findChild<QLabel*>(); // Get the QLabel in the current tab
    if (!tabImageLabel) {
        qDebug() << "No QLabel found in the current tab.";
        return; // Exit if QLabel is not found
    }

    // Get the current image from QLabel's pixmap
    QImage currentImage = tabImageLabel->pixmap().toImage();

    // Create a new QImage for the rotated image
    QImage rotatedImage(currentImage.height(), currentImage.width(), currentImage.format());

    // Rotate the image 90 degrees to the left
    for (int i = 0; i < currentImage.width(); ++i) {
        for (int j = 0; j < currentImage.height(); ++j) {
            QColor pixelColor = currentImage.pixel(i, j); // Get pixel color
            rotatedImage.setPixel(currentImage.height() - 1 - j, i, pixelColor.rgb()); // Rotate
        }
    }

    // Update the QLabel with the rotated image
    tabImageLabel->setPixmap(QPixmap::fromImage(rotatedImage)); // Update the displayed image
}


void demo_photoshop::on_Lost_Signal_clicked() {
    Hide_2(); // Hide the current filter options, similar to other filter functions

    // Set flag to indicate that the Lost Signal filter is active


    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab
        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage();  // Store the original image
            QImage image = originalImage.copy();  // Copy the original image

            // Apply the Lost Signal effect
            applyLostSignalEffect(image);
            tabImageLabel->setPixmap(QPixmap::fromImage(image));  // Update the label with the processed image

            // Update image history and display
            originalImage = image;
            updateImageHistory(originalImage);
            updateDisplayedImage(originalImage); // Function to update the displayed image
            updateImageProperties(originalImage);
        }
    }
    ui->Vintage->hide();
    ui->Lost_Signal->hide();
    Show(); // Show UI elements again after applying the filter
}

// Separate function for applying the Lost Signal effect
void demo_photoshop::applyLostSignalEffect(QImage &image) {
    int numbers[] = {0, 255, 127, 7, 7, 7, 7, 7}; // Predefined values
    int array_size = sizeof(numbers) / sizeof(numbers[0]);

    srand(time(0)); // Seed the random number generator

    // Check image size to determine the block size for the effect
    int blockSize = (image.width() >= 3000 || image.height() >= 3000) ? 3 : 1;

    for (int i = 0; i < image.width(); i += blockSize) {
        for (int j = 0; j < image.height(); j += blockSize) {
            int random_index = rand() % array_size;
            int random_number = numbers[random_index];

            if (random_number != 7) {
                // Apply the effect in the defined block size
                for (int k = i; k < i + blockSize && k < image.width(); ++k) {
                    for (int l = j; l < j + blockSize && l < image.height(); ++l) {
                        image.setPixelColor(k, l, QColor(random_number, random_number, random_number));
                    }
                }
            }
        }
    }
}

void demo_photoshop::on_Vintage_clicked() {
    Hide_2(); // Hide the current filter options, similar to other filter functions

    // Set flag to indicate that the Vintage filter is active


    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab
        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage();  // Store the original image
            QImage image = originalImage.copy();  // Copy the original image

            // Apply the Vintage effect
            applyVintageEffect(image);
            tabImageLabel->setPixmap(QPixmap::fromImage(image));  // Update the label with the processed image

            // Update image history and display
            originalImage = image;
            updateImageHistory(originalImage);
            updateDisplayedImage(originalImage); // Function to update the displayed image
            updateImageProperties(originalImage);
        }
    }
    ui->Vintage->hide();
    ui->Lost_Signal->hide();
    Show(); // Show UI elements again after applying the filter
}

// Separate function for applying the Vintage effect
void demo_photoshop::applyVintageEffect(QImage &image) {
    float coef;
    for (int i = 0; i < image.height(); ++i) {
        coef = 3 * abs(0.3 * sin(i)); // Vintage effect calculation
        for (int j = 0; j < image.width(); ++j) {
            int red = qMin(255, static_cast<int>(image.pixelColor(j, i).red() * coef));
            int green = qMin(255, static_cast<int>(image.pixelColor(j, i).green() * coef));
            int blue = qMin(255, static_cast<int>(image.pixelColor(j, i).blue() * coef));

            image.setPixelColor(j, i, QColor(red, green, blue));
        }
    }
}




void demo_photoshop::on_TV_clicked()
{
    Hide_2();
    ui->SliderBox->hide();
    ui->Vintage->show();
    ui->Lost_Signal->show();
}
void demo_photoshop::rotateCamera(QImage &image, float angle) {
    // Convert angle from degrees to radians
    angle = angle * 3.1415927 / 180;

    // Calculate cosine and sine of the angle
    float cosA = cos(angle);
    float sinA = sin(angle);

    int width = image.width();
    int height = image.height();

    // Compute new image dimensions (bounding box of the rotated image)
    int newWidth = std::abs(width * cosA) + std::abs(height * sinA);
    int newHeight = std::abs(height * cosA) + std::abs(width * sinA);

    // Create a new image with the calculated dimensions
    QImage rotatedImage(newWidth, newHeight, QImage::Format_RGB32);
    rotatedImage.fill(Qt::white);  // Fill with a background color

    // Center of the original and new images
    QPoint centerOriginal(width / 2, height / 2);
    QPoint centerNew(newWidth / 2, newHeight / 2);

    // Map each pixel of the new image to the original image
    for (int x = 0; x < newWidth; ++x) {
        for (int y = 0; y < newHeight; ++y) {
            // Translate coordinates to the center
            int dx = x - centerNew.x();
            int dy = y - centerNew.y();

            // Apply reverse rotation to map new coordinates back to the original image
            int origX = cosA * dx + sinA * dy + centerOriginal.x();
            int origY = -sinA * dx + cosA * dy + centerOriginal.y();

            // Check if the mapped coordinates are within the original image bounds
            if (origX >= 0 && origX < width && origY >= 0 && origY < height) {
                rotatedImage.setPixel(x, y, image.pixel(origX, origY));
            }
        }
    }

    // Return the rotated image
    image = rotatedImage;
}
void demo_photoshop::on_Rotate_Camera_clicked() {
    Hide_2();
    ui->horizontalSlider->setValue(0);  // Set initial slider value to 0
    ui->horizontalSlider->setRange(-45, 45);  // Set range between -45 and 45 degrees

    isrotatecamera = true;  // Indicating the rotate camera filter is applied

    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab

        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            // Store the original image for future rotation updates
            originalImage = tabImageLabel->pixmap().toImage();

            // Initialize rotation
            QImage image = originalImage.copy();  // Copy the original image to apply the filter
            rotateCamera(image, ui->horizontalSlider->value());  // Apply the rotate camera effect
            tabImageLabel->setPixmap(QPixmap::fromImage(image));  // Update the QLabel with the filtered image
            updateImageProperties(originalImage);
        }
    }
}
void demo_photoshop::rotateFrame(QImage &image, float angle) {
    int width = image.width();
    int height = image.height();

    QImage after = image.copy();

    if (angle < 0) {
        if (height >= width) {
            angle = abs(angle);
            angle = angle * 3.141593 / 180;
            float slope = tan(1.570796 - angle);
            float slope2 = -1 / slope;
            int y = width * sin(angle);
            int x = (height - y) / slope;
            int d1 = height - y;
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    if (j > slope * i + y || j < slope * (i - width + x) || j < slope2 * i + y || j > slope2 * (i - width) + d1) {
                        image.setPixel(i, j, qRgb(255, 255, 255));
                    }
                }
            }
        } else {
            angle = -angle * 3.1415927 / 180;
            int y = width * sin(angle);
            float slope = tan(angle);
            float slope2 = -1 / slope;
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    if (j < slope * (-i + width - y) || j < slope2 * (-i + width - y) || j > slope * (y - i) + height || j > slope2 * (y - i) + height) {
                        image.setPixel(i, j, qRgb(255, 255, 255));
                    }
                }
            }
        }
    } else {
        if (height >= width) {
            angle = angle * 3.141593 / 180;
            float slope = tan(angle);
            float slope2 = -1 / slope;
            int y = width * sin(angle);
            int x = (height - y) * slope;
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    if (j > slope2 * (i - width) + y || j < slope2 * i + height - y || j > slope * i + height - y || j < slope * (i - width) + y) {
                        image.setPixel(i, j, qRgb(255, 255, 255));
                    }
                }
            }
        } else {
            angle = angle * 3.1415927 / 180;
            int y = width * sin(angle);
            float slope = tan(angle);
            float slope2 = -1 / tan(angle);
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    if (j < slope * (i - y) || j < slope2 * (i - y) || j > slope * (i - width + y) + height || j > slope2 * (i - width + y) + height) {
                        image.setPixel(i, j, qRgb(255, 255, 255));
                    }
                }
            }
        }
    }
}

void demo_photoshop::on_Rotate_Frame_clicked()
{
    Hide_2();
    ui->horizontalSlider->setValue(0);  // Set initial slider value to 0
    ui->horizontalSlider->setRange(-45, 45);  // Set range between -45 and 45 degrees

    isrotateframe = true;  // Indicating the rotate frame filter is applied

    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab

        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage();  // Store the original image
            QImage image = originalImage.copy();  // Copy the original image to apply the filter
            rotateFrame(image, ui->horizontalSlider->value());  // Apply the rotate frame effect
            tabImageLabel->setPixmap(QPixmap::fromImage(image));  // Update the QLabel with the filtered image
            updateImageProperties(originalImage);
        }
    }
}
void demo_photoshop::centerLight(QImage &image, float c) {
    int a = image.width() >> 1;  // Center of the image width
    int b = image.height() >> 1; // Center of the image height
    float A = image.width() * 0.707107;  // Scaling factor for width
    float B = image.height() * 0.707107; // Scaling factor for height
    A *= A; // Square A
    B *= B; // Square B
    float z;

    for (int i = 0; i < image.height(); ++i) {
        for (int j = 0; j < image.width(); ++j) {
            // Compute the z factor based on the distance from the center
            z = c * sqrt(1 - static_cast<float>((j - a) * (j - a)) / A - static_cast<float>((i - b) * (i - b)) / B);

            // Get the current pixel's red, green, and blue values
            int red = qMin(255, static_cast<int>(image.pixelColor(j, i).red() * (1 + z)));
            int green = qMin(255, static_cast<int>(image.pixelColor(j, i).green() * (1 + z)));
            int blue = qMin(255, static_cast<int>(image.pixelColor(j, i).blue() * (1 + z)));

            // Set the new pixel color
            image.setPixelColor(j, i, QColor(red, green, blue));
        }
    }
}
void demo_photoshop::on_Center_Light_clicked()
{
    Hide_2();
    ui->horizontalSlider->setValue(0);  // Set initial slider value to 50 (avoid 0)
    ui->horizontalSlider->setRange(0, 5);  // Set the range of the slider

    iscenterlight = true;

    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab
        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage();  // Store the original image
            QImage image = originalImage.copy();  // Create a copy of the original image

            float sliderValue = ui->horizontalSlider->value() / 100.0;  // Normalize slider value
            centerLight(image, sliderValue);  // Apply the center light filter with normalized value

            originalImage = image;  // Update the original image with the filtered copy
            tabImageLabel->setPixmap(QPixmap::fromImage(originalImage));  // Update the QLabel with the filtered image
            tabImageLabel->update();  // Force UI update to reflect the changes
            updateImageProperties(originalImage);  // Update any image properties as needed
        }
    }
}




void demo_photoshop::Egg(QImage &image){
    int width = image.width();
    int height = image.height();
    QImage image2(width, height, image.format());

    int a = width >> 1;  // Half the width (a)
    int b = height >> 1; // Half the height (b)
    float a2 = a * a;    // a^2
    float b2 = b * b;    // b^2
    float d, d2, z, y;

    for (int i = 0; i < width; ++i) {
        d = height * sqrt(1 - (float)(i - a) / a2);  // Distance calculation

        for (int j = 0; j < height; ++j) {
            y = square(j - b) / b2 + square(i - a) / a2;  // Elliptical equation check

            if (y > 1) {
                image2.setPixel(i, j, qRgb(255, 255, 255));  // Set background to white if outside ellipse
            } else {
                z = sqrt(1 - y);

                if (d != 0)
                    d2 = (j + (b * sqrt(1 - square(i - a) / a2) - b)) / d;

                // Get the pixel values from the original image and apply the transformation
                int new_i = i;
                int new_j = d2 * height;
                if (new_j >= 0 && new_j < height) {
                    QColor pixelColor = QColor(image.pixel(new_i, new_j));
                    int r = pixelColor.red() * z;
                    int g = pixelColor.green() * z;
                    int b = pixelColor.blue() * z;
                    image2.setPixel(i, j, qRgb(r, g, b));
                }
            }
        }
    }

    image = image2;  // Replace the original image with the filtered one
}
void demo_photoshop::on_Egg_clicked() {
    int currentIndex = ui->tabs_menu->currentIndex(); // Get the current tab index
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>(); // Get the QLabel in the current tab
        if (tabImageLabel) {
            QPixmap pixmap = tabImageLabel->pixmap(); // Get the current image
            if (!pixmap.isNull()) { // Ensure the pixmap is not null
                QImage image = pixmap.toImage(); // Convert pixmap to QImage for processing

                Egg(image); // Apply the Egg effect to the QImage

                // Update the QLabel with the transformed image
                tabImageLabel->setPixmap(QPixmap::fromImage(image)); // Set the modified image back to the QLabel
                tabImageLabel->update(); // Refresh the QLabel to show changes

                // Save the current image to history for undo
                originalImage = image; // Store the original image
                updateImageHistory(originalImage); // Update history with the original image
                updateImageProperties(originalImage);
            } else {
                QMessageBox::warning(this, "Warning", "No image to apply the effect.");
            }
        }
    } else {
        QMessageBox::information(this, "Info", "No tab selected.");
    }
}

void demo_photoshop::on_Detect_Edge_clicked()
{
    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();

        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage();
            QImage image = originalImage.copy();  // Copy original image

            applyCannyEdgeDetection(image);  // Apply Canny Edge Detection algorithm

            tabImageLabel->setPixmap(QPixmap::fromImage(image));  // Update the image in the label
            originalImage = image;  // Save the updated image
            updateImageHistory(originalImage);
            updateDisplayedImage(originalImage);  // Update the displayed image
            updateImageProperties(originalImage);
        }
    }
}

void demo_photoshop::applyCannyEdgeDetection(QImage &image) {
    // 1. Convert to Grayscale
    for (int i = 0; i < image.width(); ++i) {
        for (int j = 0; j < image.height(); ++j) {
            int gray = qGray(image.pixel(i, j));
            image.setPixel(i, j, qRgb(gray, gray, gray));  // Set the pixel to grayscale
        }
    }

    // 2. Apply Gaussian Blur to reduce noise
    applyGaussianBlur(image);

    // 3. Calculate gradients using Sobel operator
    QImage gradientImage = calculateGradients(image);

    // 4. Perform Non-Maximum Suppression
    QImage nonMaxSuppressed = nonMaximumSuppression(gradientImage);

    // 5. Double Thresholding
    QImage thresholded = applyDoubleThreshold(nonMaxSuppressed);

    // 6. Edge Tracking by Hysteresis
    performEdgeTracking(thresholded);

    image = thresholded;  // Set the final processed image back to the original image
}

void demo_photoshop::applyGaussianBlur(QImage &image) {
    // Use a smaller kernel or adjust the kernel values for less blurring
    int kernel[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };
    int kernelSize = 3;  // Smaller kernel
    int kernelSum = 16;  // Adjusted sum for the smaller kernel

    QImage blurred = image.copy();

    for (int x = kernelSize / 2; x < image.width() - kernelSize / 2; ++x) {
        for (int y = kernelSize / 2; y < image.height() - kernelSize / 2; ++y) {
            int sum = 0;
            for (int i = 0; i < kernelSize; ++i) {
                for (int j = 0; j < kernelSize; ++j) {
                    int pixelValue = qGray(image.pixel(x + i - kernelSize / 2, y + j - kernelSize / 2));
                    sum += pixelValue * kernel[i][j];
                }
            }
            int newPixelValue = sum / kernelSum;
            blurred.setPixel(x, y, qRgb(newPixelValue, newPixelValue, newPixelValue));
        }
    }
    image = blurred;
}

QImage demo_photoshop::calculateGradients(const QImage &image) {
    // Sobel kernels for gradient calculation
    int sobelX[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int sobelY[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    QImage gradientImage = image.copy();

    for (int x = 1; x < image.width() - 1; ++x) {
        for (int y = 1; y < image.height() - 1; ++y) {
            int gradientX = 0;
            int gradientY = 0;

            // Apply Sobel operator
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    int pixelValue = qGray(image.pixel(x + i - 1, y + j - 1));
                    gradientX += pixelValue * sobelX[i][j];
                    gradientY += pixelValue * sobelY[i][j];
                }
            }

            int magnitude = qMin(255, static_cast<int>(sqrt(gradientX * gradientX + gradientY * gradientY)*2));
            gradientImage.setPixel(x, y, qRgb(magnitude, magnitude, magnitude));  // Keep original magnitude
        }
    }
    return gradientImage;
}

QImage demo_photoshop::applyDoubleThreshold(const QImage &image) {
    QImage thresholded = image.copy();
    int strongThreshold = 250;  // Stronger threshold
    int weakThreshold = 150;      // Stronger threshold

    for (int x = 0; x < thresholded.width(); ++x) {
        for (int y = 0; y < thresholded.height(); ++y) {
            int pixelValue = qGray(thresholded.pixel(x, y));
            if (pixelValue >= strongThreshold) {
                thresholded.setPixel(x, y, qRgb(0, 0, 0));  // Strong edge
            } else if (pixelValue >= weakThreshold) {
                thresholded.setPixel(x, y, qRgb(192, 192, 192));  // Weak edge
            } else {
                thresholded.setPixel(x, y, qRgb(255, 255, 255));  // Irrelevant
            }
        }
    }
    return thresholded;
}



void demo_photoshop::performEdgeTracking(QImage &image) {
    // Extend edge tracking to connect more weak edges to strong ones
    for (int x = 1; x < image.width() - 1; ++x) {
        for (int y = 1; y < image.height() - 1; ++y) {
            int pixelValue = qGray(image.pixel(x, y));
            if (pixelValue == 192) {  // If it's a weak edge
                // Check surrounding pixels for strong edges, expanding to diagonals
                if (qGray(image.pixel(x - 1, y)) == 0 ||
                    qGray(image.pixel(x + 1, y)) == 0 ||
                    qGray(image.pixel(x, y - 1)) == 0 ||
                    qGray(image.pixel(x, y + 1)) == 0 ||
                    qGray(image.pixel(x - 1, y - 1)) == 0 ||
                    qGray(image.pixel(x - 1, y + 1)) == 0 ||
                    qGray(image.pixel(x + 1, y - 1)) == 0 ||
                    qGray(image.pixel(x + 1, y + 1)) == 0) {
                    image.setPixel(x, y, qRgb(0, 0, 0));  // Connect to strong edge (black)
                } else {
                    image.setPixel(x, y, qRgb(255, 255, 255));  // Otherwise, set to white
                }
            }
        }
    }
}



QImage demo_photoshop::nonMaximumSuppression(const QImage &image) {
    QImage suppressed = image.copy();
    int width = image.width();
    int height = image.height();

    for (int x = 1; x < width - 1; ++x) {
        for (int y = 1; y < height - 1; ++y) {
            int centerValue = qGray(suppressed.pixel(x, y));
            // Get neighboring pixel values
            int p1 = qGray(suppressed.pixel(x - 1, y));    // left
            int p2 = qGray(suppressed.pixel(x + 1, y));    // right
            int p3 = qGray(suppressed.pixel(x, y - 1));    // top
            int p4 = qGray(suppressed.pixel(x, y + 1));    // bottom

            // Suppress the pixel if it's not a local maximum
            if (centerValue < p1 || centerValue < p2 || centerValue < p3 || centerValue < p4) {
                suppressed.setPixel(x, y, qRgb(0, 0, 0));  // Set to black
            }
        }
    }
    return suppressed;
}
void demo_photoshop::applyVerticalFlip(QImage &image) {
    int width = image.width();
    int height = image.height();

    // Create a new image to store the flipped result
    QImage flippedImage = image.copy();

    // Loop through the image vertically
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            // Get the pixel from the opposite vertical position
            QColor pixelColor = image.pixelColor(i, height - 1 - j);

            // Set the pixel at the current position in the flipped image
            flippedImage.setPixelColor(i, j, pixelColor);
        }
    }

    // Update the original image with the flipped result
    image = flippedImage;
}

void demo_photoshop::on_vertical_flip_clicked()
{
    Hide_2();  // Hide current filter options

    // Get the index of the currently selected tab
    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        // Get the current tab and find the QLabel that displays the image
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get QLabel in the current tab

        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            // Store the original image
            originalImage = tabImageLabel->pixmap().toImage();
            QImage image = originalImage.copy();  // Create a copy to work on

            // Apply the vertical flip effect
            applyVerticalFlip(image);

            // Update the label with the vertically flipped image
            tabImageLabel->setPixmap(QPixmap::fromImage(image));

            // Update image history and the display
            originalImage = image;
            updateImageHistory(originalImage);
            updateDisplayedImage(originalImage); // Function to refresh the displayed image
            updateImageProperties(originalImage);

        }
    }

    ui->vertical_flip->hide();
    ui->horiozontal_flip->hide();
    Show();
}

void demo_photoshop::applyHorizontalFlip(QImage &image) {
    int width = image.width();
    int height = image.height();

    // Create a new image to store the horizontally flipped result
    QImage flippedImage = image.copy();

    // Loop through each pixel of the image
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            // Get the pixel color from the opposite horizontal position
            QColor pixelColor = image.pixelColor(width - 1 - i, j);

            // Set the pixel at the current position in the flipped image
            flippedImage.setPixelColor(i, j, pixelColor);
        }
    }

    // Update the original image with the horizontally flipped result
    image = flippedImage;
}


void demo_photoshop::on_horiozontal_flip_clicked()
{
    Hide_2();  // Hide current filter options

    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get QLabel in the current tab

        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage();
            QImage image = originalImage.copy();  // Create a copy of the image

            // Apply the horizontal flip effect
            applyHorizontalFlip(image);

            // Update the QLabel with the horizontally flipped image
            tabImageLabel->setPixmap(QPixmap::fromImage(image));

            // Update image history and the display
            originalImage = image;
            updateImageHistory(originalImage);
            updateDisplayedImage(originalImage);
            updateImageProperties(originalImage);
        }
    }

    ui->vertical_flip->hide();
    ui->horiozontal_flip->hide();
    Show();  // Show UI elements again after applying the filter
}


void demo_photoshop::on_Flip_clicked()
{
    Hide_2();
    ui->SliderBox->hide();
    ui->vertical_flip->show();
    ui->horiozontal_flip->show();
}

void demo_photoshop::on_Wave_Vertical_clicked()
{
    // Retrieve the current frequency and height from spin boxes
    float frequency = ui->Frequency->value(); // Get the value directly
    float height = ui->Height->value(); // Get the value directly

    // Retrieve the original image from the current tab
    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get QLabel in the current tab

        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage(); // Store original image
            QImage image = originalImage.copy(); // Create a copy to work on

            // Call the wave function with the current values
            wave(image, frequency, height, "Vertical Wave");

            // Update the label with the new image
            tabImageLabel->setPixmap(QPixmap::fromImage(image));

            // Update image history and the display
            originalImage = image;
            updateImageHistory(originalImage);
            updateDisplayedImage(originalImage); // Refresh the displayed image
            ui->Frequency->hide();
            ui->Height->hide();
            ui->Wave_Vertical->hide();
            ui->Wave_Horizontal->hide();
            ui->Height_Label->hide();
            ui->Frequency_Label->hide();
            Show();
            updateImageProperties(originalImage);
        }
    }
}

// Slot for the horizontal button click
void demo_photoshop::on_Wave_Horizontal_clicked()
{
    // Retrieve the current frequency and height from spin boxes
    float frequency = ui->Frequency->value(); // Get the value directly
    float height = ui->Height->value(); // Get the value directly

    // Retrieve the original image from the current tab
    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get QLabel in the current tab

        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage(); // Store original image
            QImage image = originalImage.copy(); // Create a copy to work on

            // Call the wave function with the current values
            wave(image, frequency, height, "Horizontal Wave");

            // Update the label with the new image
            tabImageLabel->setPixmap(QPixmap::fromImage(image));

            // Update image history and the display
            originalImage = image;
            updateImageHistory(originalImage);
            updateDisplayedImage(originalImage); // Refresh the displayed image
            updateImageProperties(originalImage);
            ui->Frequency->hide();
            ui->Height->hide();
            ui->Wave_Vertical->hide();
            ui->Wave_Horizontal->hide();
            ui->Height_Label->hide();
            ui->Frequency_Label->hide();
            Show();
        }
    }
}






void demo_photoshop::on_Frequency_textChanged(const QString &arg1)
{

}


void demo_photoshop::on_Height_textChanged(const QString &arg1)
{

}

void demo_photoshop::wave(QImage& image, float frequency, float height, const std::string& orientation)
{
    int originalWidth = image.width();
    int originalHeight = image.height();
    float arcoef = height;

    if (orientation == "Vertical Wave") {
        float n = frequency;
        n = originalHeight / n;
        float coef = 6.28318531 / n;

        // Create new image with original width + additional space for wave effect
        QImage image2=image.copy();

        for (int j = 0; j < originalHeight; ++j) {
            int y = arcoef * cos(coef * j) + arcoef; // Calculate wave offset
            for (int i = 0; i < image2.width(); ++i) {
                if (i < y) {
                    image2.setPixel(i, j, image.pixel(0, j)); // Left edge
                }
                else if (i >= y + originalWidth) {
                    image2.setPixel(i, j, image.pixel(originalWidth - 1, j)); // Right edge
                }
                else {
                    image2.setPixel(i, j, image.pixel(i - y, j)); // Apply wave effect
                }
            }
        }
        image = image2; // Update original image
    }
    else if (orientation == "Horizontal Wave") {
        float n = frequency;
        n = originalWidth / n;
        float coef = 6.28318531 / n;

        // Create new image with original height + additional space for wave effect
        QImage image2=image.copy();

        for (int i = 0; i < originalWidth; ++i) {
            int y = arcoef * cos(coef * i) + arcoef; // Calculate wave offset
            for (int j = 0; j < image2.height(); ++j) {
                if (j < y) {
                    image2.setPixel(i, j, image.pixel(i, 0)); // Top edge
                }
                else if (j >= y + originalHeight) {
                    image2.setPixel(i, j, image.pixel(i, originalHeight - 1)); // Bottom edge
                }
                else {
                    image2.setPixel(i, j, image.pixel(i, j - y)); // Apply wave effect
                }
            }
        }
        image = image2; // Update original image
    }
}




void demo_photoshop::on_Wave_clicked()
{
    Hide_2();
    ui->SliderBox->hide();
    ui->Frequency->show();
    ui->Height->show();
    ui->Wave_Vertical->show();
    ui->Wave_Horizontal->show();
    ui->Frequency_Label->show();
    ui->Height_Label->show();
    ui->Frequency->setRange(1, 500); // Minimum 1, Maximum 500
    ui->Height->setRange(1, 500);    // Minimum 1, Maximum 500
}

// void demo_photoshop::resizeImage(QImage &image, int newWidth, int newHeight) {
//     // Resizing logic, such as using QImage::scaled
//     image = image.scaled(newWidth, newHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//     updateDisplayedImage(image); // Update the displayed image in the UI after resizing
// }


void demo_photoshop::on_Upload_Second_clicked()
{
    // Show the merge buttons


    // Open the file dialog to select an image
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Images (*.png *.xpm *.jpg *.bmp *.gif)"));

    // Check if a file was selected
    if (!fileName.isEmpty()) {
        secondaryImage.load(fileName);  // Load the secondary image into the variable
        qDebug() << "Secondary image uploaded:" << fileName;

        // Hide the upload button after successfully uploading
        ui->Upload_Second->hide();
        ui->Merge_Secondary->show();
        ui->Merge_Primary->show();
    } else {
        // Show an error message if no image is selected
        QMessageBox::warning(this, tr("No Image Selected"), tr("Please select an image to upload."));
    }
}


void demo_photoshop::on_Merge_Primary_clicked()
{
    ui->Merge_Secondary->hide();
    ui->Merge_Primary->hide();
    int currentIndex = ui->tabs_menu->currentIndex();

        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get QLabel in the current tab

        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage(); // Store original image
        }
    mergeImages(originalImage, secondaryImage, true);
    Show();
}


void demo_photoshop::on_Merge_Secondary_clicked()
{
    ui->Merge_Secondary->hide();
    ui->Merge_Primary->hide();
    int currentIndex = ui->tabs_menu->currentIndex();

    QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
    QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get QLabel in the current tab

    if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
        originalImage = tabImageLabel->pixmap().toImage(); // Store original image
    }
    mergeImages(originalImage, secondaryImage, false);
    Show();
}


void demo_photoshop::on_Merge_clicked()
{
    Hide_2();
    ui->SliderBox->hide();
    ui->Upload_Second->show();
}

void demo_photoshop::mergeImages(const QImage &primary, const QImage &secondary, bool usePrimaryDimensions)
{
    // Resize based on the selected dimension
    QImage resizedPrimary;
    QImage resizedSecondary;

    if (usePrimaryDimensions) {
        // Resize secondary image to match primary dimensions
        resizedSecondary = secondary.scaled(primary.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        resizedPrimary = primary;  // Keep primary as is
    } else {
        // Resize primary image to match secondary dimensions
        resizedPrimary = primary.scaled(secondary.size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        resizedSecondary = secondary;  // Keep secondary as is
    }

    // Create a new image for the merged result
    QSize targetSize = usePrimaryDimensions ? primary.size() : secondary.size();
    QImage mergedImage(targetSize, QImage::Format_ARGB32);
    mergedImage.fill(Qt::transparent);  // Fill with transparent background

    // Simple blend logic: averaging the pixel values
    for (int y = 0; y < targetSize.height(); ++y) {
        for (int x = 0; x < targetSize.width(); ++x) {
            // Get pixel colors from the resized primary and secondary images
            QColor primaryColor = (x < resizedPrimary.width() && y < resizedPrimary.height()) ? QColor(resizedPrimary.pixel(x, y)) : QColor(0, 0, 0, 0);
            QColor secondaryColor = (x < resizedSecondary.width() && y < resizedSecondary.height()) ? QColor(resizedSecondary.pixel(x, y)) : QColor(0, 0, 0, 0);

            // Avoid blending with fully transparent pixels
            if (primaryColor.alpha() == 0 && secondaryColor.alpha() == 0) {
                mergedImage.setPixel(x, y, qRgba(0, 0, 0, 0));  // Set to transparent
            } else {
                // Average the colors only if at least one pixel is not fully transparent
                int r = (primaryColor.red() + secondaryColor.red()) / 2;
                int g = (primaryColor.green() + secondaryColor.green()) / 2;
                int b = (primaryColor.blue() + secondaryColor.blue()) / 2;
                int a = qMax(primaryColor.alpha(), secondaryColor.alpha());  // Use max alpha for blending

                mergedImage.setPixel(x, y, qRgba(r, g, b, a));
            }
        }
    }

    // Update the displayed image
    updateDisplayedImage(mergedImage);
    updateImageHistory(mergedImage);
    originalImage = mergedImage;  // Update original image to merged result
    updateImageProperties(originalImage);
}




void demo_photoshop::on_Resize_clicked()
{
    Hide_2();
    ui->SliderBox->hide();
    ui->Width->show();
    ui->Height_2->show();
    ui->Width_Label->show();
    ui->Height_Label_2->show();
    ui->Height_2->setRange(100,5000);
    ui->Width->setRange(100,7000);
    ui->Apply_resize->show();
    ui->Cancel_resize->show();

}


void demo_photoshop::on_Width_textChanged(const QString &arg1)
{

}


void demo_photoshop::on_Height_2_textChanged(const QString &arg1)
{

}


void demo_photoshop::on_Apply_resize_clicked() {
    // Get the new width and height from the spinboxes
    int newWidth = ui->Width->value();
    int newHeight = ui->Height_2->value();

    // Get the current image from the QLabel in the active tab
    int currentIndex = ui->tabs_menu->currentIndex();
    QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
    QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Find QLabel in the current tab

    if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
        originalImage = tabImageLabel->pixmap().toImage(); // Store the original image
    }

    if (!originalImage.isNull()) {
        // 1. Resize the image to the exact dimensions provided by the user
        QImage resizedImage = originalImage.scaled(newWidth, newHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        // 2. Update the QLabel to display the resized image fully
        QPixmap pixmap = QPixmap::fromImage(resizedImage);
        tabImageLabel->setPixmap(pixmap);
        tabImageLabel->setAlignment(Qt::AlignCenter); // Ensure the image is centered in the QLabel
        tabImageLabel->setScaledContents(true);  // Force QLabel to scale the image to fit its dimensions

        // 3. Store the resized image for saving or further actions
        originalImage = resizedImage;

        // 4. Update the image history for undo/redo functionality
        updateImageHistory(resizedImage);

        // 5. Hide Apply/Cancel buttons and related UI elements
        ui->Apply_resize->hide();
        ui->Cancel_resize->hide();
        ui->Height_2->hide();
        ui->Height_Label_2->hide();
        ui->Width_Label->hide();
        ui->Width->hide();

        // 6. Update image properties based on the resized image
        unsigned int cols = resizedImage.width();
        unsigned int rows = resizedImage.height();
        unsigned int numBlackPixels = 0;
        QVector<QVector<int>> imgArray(rows, QVector<int>(cols, 0));

        // Analyze the image for dark pixels
        for (unsigned int i = 0; i < rows; i++) {
            for (unsigned int j = 0; j < cols; j++) {
                QColor clrCurrent(resizedImage.pixel(j, i));
                int r = clrCurrent.red();
                int g = clrCurrent.green();
                int b = clrCurrent.blue();
                int a = clrCurrent.alpha();
                if ((r + g + b) < 20 && a > 240) {
                    imgArray[i][j] = 1;
                    numBlackPixels += 1;
                }
            }
        }

        // 7. Update the labels with image information
        ui->dims->setText(QString("W: %1 H: %2").arg(cols).arg(rows));
        float pD = (((float)numBlackPixels) / ((float)(cols * rows))) * 100;
        ui->PerecentDark->setText(QString::number(pD, 'f', 2) + "%");

        // Update the blobs and area information
        QVector<int> results = this->findProperties(imgArray, rows, cols);
        ui->Nblobs->setText(QString::number(results[0]));
        ui->MaxBlodArea->setText(QString::number(results[1]));

        // 8. Display the final resized image
        Show();
    } else {
        qDebug() << "No image loaded to resize!";
    }
}



void demo_photoshop::on_Cancel_resize_clicked()
{
    ui->Apply_resize->hide();
    ui->Cancel_resize->hide();
    ui->Height_2->hide();
    ui->Height_Label_2->hide();
    ui->Width_Label->hide();
    ui->Width->hide();
    Show();
}


void demo_photoshop::on_Modes_clicked(bool isDarkMode)
{
    if (isDarkMode)
    {
        // Dark mode: Enhanced QMainWindow and UI elements
        qApp->setStyleSheet(
            "QMainWindow { background-color: #1A1A1A; color: #E0E0E0; border: none; }"
            "QMenuBar { background-color: #1E1E1E; color: #E0E0E0; padding: 5px; border-bottom: 2px solid #444; }"
            "QMenuBar::item { spacing: 5px; padding: 10px; }"
            "QMenu { background-color: #1E1E1E; border: 1px solid #444; border-radius: 5px; }"
            "QMenu::item { padding: 8px 12px; }"
            "QMenu::item:selected { background-color: #26C6DA; color: #ffffff; }"
            "QRadioButton, QCheckBox { color: #ffffff; }"
            "QPushButton { background-color: #26C6DA; color: #ffffff; border: none; padding: 8px; border-radius: 10px; box-shadow: 0px 6px 20px rgba(0, 0, 0, 0.6); transition: background-color 0.3s, transform 0.3s, box-shadow 0.3s; }"
            "QPushButton:hover { background-color: #00B0B8; transform: translateY(-6px); box-shadow: 0px 8px 24px rgba(0, 0, 0, 0.7); }"
            "QPushButton:pressed { background-color: #0097A7; transform: translateY(2px); box-shadow: 0px 4px 12px rgba(0, 0, 0, 0.5); }"
            "QTabWidget { border: 1px solid #444; border-radius: 8px; background: qlineargradient(y1:0, y2:1, stop:0 #2A2A2A, stop:1 #1E1E1E); }"
            "QTabBar::tab { background-color: #1E1E1E; color: #E0E0E0; padding: 10px; border: 1px solid #444; border-bottom: none; border-radius: 5px 5px 0 0; transition: background-color 0.3s, transform 0.3s; }"
            "QTabBar::tab:selected { background-color: #26C6DA; color: white; font-weight: bold; }"
            "QToolBox { background-color: #1E1E1E; border: 1px solid #444; border-radius: 10px; box-shadow: 0px 6px 20px rgba(0, 0, 0, 0.5); padding: 5px; }"
            "QToolBox::title { background-color: #2A2A2A; color: #E0E0E0; padding: 10px; border: none; border-radius: 5px; font-weight: bold; }"
            "QToolBox::item { background-color: #1E1E1E; color: #E0E0E0; padding: 10px; border: 1px solid #444; border-radius: 5px; transition: background-color 0.3s, transform 0.3s; }"
            "QToolBox::item:hover { background-color: #2A2A2A; transform: scale(1.05); box-shadow: 0px 6px 20px rgba(0, 0, 0, 0.6); }"
            "QToolBox::item:selected { background-color: #26C6DA; color: white; }"
            "QLabel { color: #E0E0E0; font-size: 14px; font-weight: bold; }"
            "QDoubleSpinBox, QSpinBox {"
            "   background-color: #2A2A2A;"
            "   color: #E0E0E0;"
            "   border: 1px solid #444;"
            "   border-radius: 5px;"
            "   padding: 5px;"
            "   selection-background-color: #26C6DA;"
            "   selection-color: #ffffff;"
            "   transition: background-color 0.3s, border 0.3s;"
            "}"
            "QDoubleSpinBox:hover, QSpinBox:hover {"
            "   border: 1px solid #26C6DA;"
            "}"
            "QGroupBox {"
            "   background-color: #1E1E1E;"
            "   color: #E0E0E0;"
            "   border: 1px solid #444;"
            "   border-radius: 10px;"
            "   padding: 10px;"
            "}"
            "QSlider::groove:horizontal {"
            "   background: #444;"
            "   height: 8px;"
            "   border-radius: 4px;"
            "}"
            "QSlider::handle:horizontal {"
            "   background: #26C6DA;"
            "   border: 1px solid #444;"
            "   width: 16px;"
            "   margin: -4px 0;"
            "   border-radius: 8px;"
            "   transition: background 0.3s, transform 0.3s;"
            "}"
            "QSlider::handle:horizontal:hover {"
            "   background: #00B0B8;"
            "   transform: scale(1.1);"
            "}"
            "QSlider::sub-page:horizontal {"
            "   background: #26C6DA;"
            "   border-radius: 4px;"
            "}"
            "QColorDialog { background-color: #1E1E1E; }"
            "QColorDialog QLabel { color: #E0E0E0; }"
            "QColorDialog QPushButton { background-color: #26C6DA; color: #ffffff; border: none; }"
            "QColorDialog QPushButton:hover { background-color: #00B0B8; }"
            "QColorDialog QPushButton:pressed { background-color: #0097A7; }"

            );
    }
    else
    {
        // Light mode: Enhanced QMainWindow and UI elements
        qApp->setStyleSheet(
            "QMainWindow { background-color: #F5F5F5; color: #000000; border: none; }"
            "QMenuBar { background-color: #f0f0f0; color: #000000; padding: 5px; border-bottom: 2px solid #ccc; }"
            "QMenuBar::item { spacing: 5px; padding: 10px; }"
            "QMenu { background-color: #ffffff; border: 1px solid #ccc; border-radius: 5px; }"
            "QMenu::item { padding: 8px 12px; }"
            "QMenu::item:selected { background-color: #A020F0; color: #ffffff; }"
            "QPushButton { background-color: #A020F0; color: #ffffff; border: none; padding: 8px; border-radius: 10px; box-shadow: 0px 6px 20px rgba(0, 0, 0, 0.3); transition: background-color 0.3s, transform 0.3s, box-shadow 0.3s; }"
            "QPushButton:hover { background-color: #B55EB5; transform: translateY(-6px); box-shadow: 0px 8px 20px rgba(0, 0, 0, 0.5); }"
            "QPushButton:pressed { background-color: #8B008B; transform: translateY(2px); box-shadow: 0px 4px 12px rgba(0, 0, 0, 0.3); }"
            "QTabWidget { border: 1px solid #ccc; border-radius: 8px; background: qlineargradient(y1:0, y2:1, stop:0 #ffffff, stop:1 #f0f0f0); }"
            "QTabBar::tab { background-color: #f0f0f0; color: #000000; padding: 10px; border: 1px solid #ccc; border-bottom: none; border-radius: 5px 5px 0 0; transition: background-color 0.3s, transform 0.3s; }"
            "QTabBar::tab:selected { background-color: #A020F0; color: white; font-weight: bold; }"
            "QToolBox { background-color: #ffffff; border: 1px solid #ccc; border-radius: 10px; box-shadow: 0px 6px 20px rgba(0, 0, 0, 0.3); padding: 5px; }"
            "QToolBox::title { background-color: #f0f0f0; color: #000000; padding: 10px; border: none; border-radius: 5px; font-weight: bold; }"
            "QToolBox::item { background-color: #f0f0f0; color: #000000; padding: 10px; border: 1px solid #ccc; border-radius: 5px; transition: background-color 0.3s, transform 0.3s; }"
            "QToolBox::item:hover { background-color: #E0E0E0; transform: scale(1.05); box-shadow: 0px 6px 20px rgba(0, 0, 0, 0.3); }"
            "QToolBox::item:selected { background-color: #A020F0; color: white; }"
            "QLabel { color: #000000; font-size: 14px; font-weight: bold; }"
            "QDoubleSpinBox, QSpinBox {"
            "   background-color: #ffffff;"
            "   color: #000000;"
            "   border: 1px solid #ccc;"
            "   border-radius: 5px;"
            "   padding: 5px;"
            "   selection-background-color: #A020F0;"
            "   selection-color: #ffffff;"
            "   transition: background-color 0.3s, border 0.3s;"
            "}"
            "QDoubleSpinBox:hover, QSpinBox:hover {"
            "   border: 1px solid #A020F0;"
            "}"
            "QGroupBox {"
            "   background-color: #ffffff;"
            "   color: #000000;"
            "   border: 1px solid #ccc;"
            "   border-radius: 10px;"
            "   padding: 10px;"
            "}"
            "QSlider::groove:horizontal {"
            "   background: #ccc;"
            "   height: 8px;"
            "   border-radius: 4px;"
            "}"
            "QSlider::handle:horizontal {"
            "   background: #A020F0;"
            "   border: 1px solid #ccc;"
            "   width: 16px;"
            "   margin: -4px 0;"
            "   border-radius: 8px;"
            "   transition: background 0.3s, transform 0.3s;"
            "}"
            "QSlider::handle:horizontal:hover {"
            "   background: #B55EB5;"
            "   transform: scale(1.1);"
            "}"
            "QSlider::sub-page:horizontal {"
            "   background: #A020F0;"
            "   border-radius: 4px;"
            "}"
            "QColorDialog { background-color: #ffffff; }"
            "QColorDialog QLabel { color: #000000; }"
            "QColorDialog QPushButton { background-color: #A020F0; color: #ffffff; border: none; }"
            "QColorDialog QPushButton:hover { background-color: #B55EB5; }"
            "QColorDialog QPushButton:pressed { background-color: #8B008B; }"

            );
    }
}











void demo_photoshop::updateImageProperties(const QImage &currentImage) {
    // Update image properties based on the current image
    unsigned int cols = currentImage.width();
    unsigned int rows = currentImage.height();
    unsigned int numBlackPixels = 0;
    QVector<QVector<int>> imgArray(rows, QVector<int>(cols, 0));

    // Analyze the image for dark pixels
    for (unsigned int i = 0; i < rows; i++) {
        for (unsigned int j = 0; j < cols; j++) {
            QColor clrCurrent(currentImage.pixel(j, i));
            int r = clrCurrent.red();
            int g = clrCurrent.green();
            int b = clrCurrent.blue();
            int a = clrCurrent.alpha();
            if ((r + g + b) < 20 && a > 240) {
                imgArray[i][j] = 1;
                numBlackPixels += 1;
            }
        }
    }

    // Update the labels with image information
    ui->dims->setText(QString("W: %1 H: %2").arg(cols).arg(rows));
    float pD = (((float)numBlackPixels) / ((float)(cols * rows))) * 100;
    ui->PerecentDark->setText(QString::number(pD, 'f', 2) + "%");

    // Update the blobs and area information
    QVector<int> results = this->findProperties(imgArray, rows, cols);
    ui->Nblobs->setText(QString::number(results[0]));
    ui->MaxBlodArea->setText(QString::number(results[1]));
}


void demo_photoshop::resizeImage(const QSize &newSize)
{
    // This resizes the QLabel to fit the scroll area
    ui->Image->resize(newSize);

    // Ensure that the scroll area responds to QLabel resizing
    ui->scrollAreaImage->ensureVisible(0, 0);
}
void demo_photoshop::on_Frames_2_clicked()
{
    Hide_2();
    ui->SliderBox->hide();
    ui->Simple->show();
    ui->Arboretum->show();
    ui->Fancy->show();
    ui->Circle_Frame->show();

}

void demo_photoshop::on_Simple_clicked()
{
    currentFrameType=Simple;
    ui->selectColor->show();
    ui->frameSizeSpinBox->show();
    ui->Simple->hide();
    ui->Arboretum->hide();
    ui->Fancy->hide();
    ui->Circle_Frame->hide();
}


void demo_photoshop::on_Arboretum_clicked()
{
    currentFrameType=Arboretum;
    ui->selectColor->show();
    ui->frameSizeSpinBox->show();
    ui->frameSizeSpinBox->setValue(0);
    ui->Simple->hide();
    ui->Arboretum->hide();
    ui->Fancy->hide();
    ui->Circle_Frame->hide();
}


void demo_photoshop::on_Fancy_clicked()
{
    currentFrameType=Fancy;
    ui->selectColor->show();
    ui->frameSizeSpinBox->show();
    ui->Simple->hide();
    ui->Arboretum->hide();
    ui->Fancy->hide();
    ui->Circle_Frame->hide();
}


void demo_photoshop::on_Circle_Frame_clicked()
{
    currentFrameType=CircleFrame;
    ui->selectColor->show();
    ui->frameSizeSpinBox->show();
    ui->Simple->hide();
    ui->Arboretum->hide();
    ui->Fancy->hide();
    ui->Circle_Frame->hide();

}





// Function to check if the frame width is even
bool isEven(int value) {
    return value % 2 == 0;
}

// Function to create a semicircle frame
void applySemicircleFrame(QImage &image, QColor primaryColor, QColor secondaryColor, int frameSize) {

    if(frameSize<6 || frameSize>50 || frameSize%2!=0){
        QMessageBox::warning(nullptr, "Invalid Input", "Please select an even number of circles from 6 to 50.");
        return;
    }
    // Ask for the number of semicircles (even number between 6 and 50)
    int n=frameSize;

    // Split the number of circles into two components
    n >>= 1;  // Halve n since we're working with semicircles
    int n2 = static_cast<float>(n) * image.height() / image.width();
    n = image.width() / n;

    float arcoef = 6.283186f / n;
    float coef = 1 / arcoef;

    n2 = image.height() / n2;
    float arcoef2 = 6.283186f / n2;
    float coef2 = 1 / arcoef2;

    QPainter painter(&image);
    painter.setPen(Qt::NoPen);  // We'll set the pixel colors manually

    // Iterate through the image pixels to draw the semicircles
    for (int i = 0; i < image.width(); ++i) {
        for (int j = 0; j < image.height(); ++j) {
            int sini = std::sin(i * arcoef) * coef;
            int sinj = std::sin(j * arcoef2) * coef2;

            // Apply primary color for one side of the semicircles
            if (sini > j || -sini > image.height() - j || -sinj > i || sinj > image.width() - i) {
                image.setPixel(i, j, primaryColor.rgb());
            }
            // Apply secondary color for the opposite side of the semicircles
            else if (-sini > j || sini > image.height() - j || sinj > i || -sinj > image.width() - i) {
                image.setPixel(i, j, secondaryColor.rgb());
            }
        }
    }
}


inline int sq(int x){
    return x*x;
}

// Function to create a fancy frame
void demo_photoshop::applyFancyFrame(QImage &image, QColor frameColor, QColor frameColor2, int frameSize) {
    // Calculate the dimensions of the image
    int width = image.width();
    int height = image.height();

    // Determine end size and default values based on image dimensions
    int end = ((width < height) ? width : height) * 0.13;
    int value = ((width < height) ? width : height) * 0.03;

    // Frame sizes
    int n = value;               // Number of pixels colored by frame
    int n2 = n * 1.25;          // Second white line
    int n4 = n * 0.8, n5 = n * 0.9; // First white line
    int n3 = n << 1;            // Square part
    int n6 = n * 2.3, n7 = n * 2.4; // Third line
    int n8 = n * 2.5, n9 = n * 2.85; // Fourth line
    int c = n * 1.75, c2 = n * 3.35; // Center positions
    int r = sq(n * 0.4), r2 = sq(n * 0.52); // Radii for circular cutouts

    // Iterate over each pixel in the image
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            // Apply frame color for the outer frame parts
            if (i < n || j < n || width - n < i || height - n < j) {
                image.setPixelColor(i, j, frameColor);
            }

            // Apply secondary frame color for specific patterns inside the frame
            if (i >= n && i < n2 || j >= n && j < n2 ||
                width - n2 < i && width - n >= i || height - n2 < j && height - n >= j ||
                i > n && i < n3 && j > n && j < n3 ||
                width - n3 < i && i < width - n && j > n && j < n3 ||
                i > n && i < n3 && height - n3 < j && height - n > j ||
                width - n3 < i && width - n > i && height - n3 < j && height - n > j ||
                i > n4 && i < n5 || j > n4 && j < n5 ||
                width - n5 < i && width - n4 > i || height - n5 < j && height - n4 > j ||
                i > n && i < n7 && j < n7 && (j > n && i > n6 || j > n6) ||
                j > n && i > width - n7 && (j < n7 && i < width - n6 || width - n > i && j > n6 && j < n7) ||
                i > n && i < n7 && height - n7 < j && (height - n6 > j || i > n6 && height - n > j) ||
                j > height - n7 && width - n7 < i && (height - n > j && height - n7 < j && width - n6 > i || width - n > i && j < height - n6) ||
                i > n && i < n9 && j < n9 && (j > n && i > n8 || j > n8) ||
                j > n && i > width - n9 && (j < n9 && i < width - n8 || width - n > i && j > n8 && j < n9) ||
                i > n && i < n9 && height - n9 < j && (height - n8 > j || i > n8 && height - n > j) ||
                j > height - n9 && width - n9 < i && (height - n > j && height - n9 < j && width - n8 > i || width - n > i && j < height - n8) ||
                sq(i - c) + sq(j - c2) <= r2 && sq(i - c) + sq(j - c2) >= r ||
                sq(i - c2) + sq(j - c) <= r2 && sq(i - c2) + sq(j - c) >= r ||
                sq(i - c) + sq(j - (height - c2)) <= r2 && sq(i - c) + sq(j - height + c2) >= r ||
                sq(i - (width - c2)) + sq(j - c) <= r2 && sq(i - (width - c2)) + sq(j - c) >= r ||
                sq(i - (width - c)) + sq(j - c2) <= r2 && sq(i - (width - c)) + sq(j - c2) >= r ||
                sq(i - c2) + sq(j - (height - c)) <= r2 && sq(i - c2) + sq(j - height + c) >= r ||
                sq(i - (width - c2)) + sq(j - (height - c)) <= r2 && sq(i - (width - c2)) + sq(j - height + c) >= r ||
                sq(i - (width - c)) + sq(j - (height - c2)) <= r2 && sq(i - (width - c)) + sq(j - height + c2) >= r) {
                // Apply secondary color for inner frame sections
                image.setPixelColor(i, j, frameColor2);
            }
        }
    }
}




// Function to create an arboretum frame
void applyArboretumFrame(QImage &image, QColor primaryColor, QColor secondaryColor, int frameSize) {
    QPainter painter(&image);

    // Increase the frame size for both the outer and inner frames
    int adjustedFrameSize = frameSize * 2.0; // Double the original frame size

    // Draw the outer rectangle with primary color
    painter.setPen(QPen(primaryColor, adjustedFrameSize));
    painter.setBrush(Qt::NoBrush); // No brush for the outer frame
    painter.drawRect(adjustedFrameSize / 2, adjustedFrameSize / 2,
                     image.width() - adjustedFrameSize, image.height() - adjustedFrameSize);

    // Calculate space and size for the inner frame
    int space = adjustedFrameSize / 1.5; // Increased space between outer and inner frame
    int innerFrameSize = adjustedFrameSize * 0.75; // Larger inner frame size (increased thickness)

    // Draw the inner rectangle with secondary color (make it larger)
    painter.setPen(QPen(secondaryColor, innerFrameSize));
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(space + innerFrameSize / 2, space + innerFrameSize / 2,
                     image.width() - 2 * (space + innerFrameSize / 2),
                     image.height() - 2 * (space + innerFrameSize / 2));

    // Ensure outer frame fully covers the corners by drawing slightly beyond edges
    painter.setPen(QPen(primaryColor, adjustedFrameSize));
    painter.drawRect(0, 0, image.width(), image.height());
}









// Function for selecting color and drawing the frame
void demo_photoshop::on_selectColor_clicked() {
    int currentIndex = ui->tabs_menu->currentIndex();
    if (currentIndex >= 0) {
        QWidget *currentTab = ui->tabs_menu->widget(currentIndex);
        QLabel *tabImageLabel = currentTab->findChild<QLabel*>();  // Get the QLabel in the current tab
        if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
            originalImage = tabImageLabel->pixmap().toImage();  // Store the original image
            QImage image = originalImage.copy();  // Copy the original image

            // Open the color dialog to select the primary color
            QColor primaryColor = QColorDialog::getColor(Qt::white, this, "Select Primary Frame Color");

            QColor secondaryColor;  // Declare secondary color

            // If the current frame type is not Simple, prompt for the secondary color
            if (primaryColor.isValid()) {
                if (currentFrameType != Simple) {
                    secondaryColor = QColorDialog::getColor(Qt::black, this, "Select Secondary Frame Color");
                }

                // Get the frame size from the spin box
                int frameSize = ui->frameSizeSpinBox->value();

                // Apply the respective frame based on the selected frame type
                if (currentFrameType == Simple) {
                    // Simple frame with primary color only
                    QPainter painter(&image);
                    painter.setPen(QPen(primaryColor, frameSize));
                    painter.drawRect(0, 0, image.width() - 1, image.height() - 1);
                } else if (currentFrameType == Arboretum && secondaryColor.isValid()) {
                    // Apply Arboretum frame
                    applyArboretumFrame(image, primaryColor, secondaryColor, frameSize);
                } else if (currentFrameType == Fancy && secondaryColor.isValid()) {
                    // Apply Fancy frame
                    applyFancyFrame(image, primaryColor, secondaryColor, frameSize);
                } else if (currentFrameType == CircleFrame && secondaryColor.isValid()) {
                    // Apply Semicircle frame
                    applySemicircleFrame(image, primaryColor, secondaryColor, frameSize);
                }

                // Update the label with the processed image
                tabImageLabel->setPixmap(QPixmap::fromImage(image));

                // Update image history and display
                originalImage = image;
                updateImageHistory(originalImage);
                updateDisplayedImage(originalImage);  // Function to update the displayed image
                updateImageProperties(originalImage);
            }
        }
    }
    // Hide the color selector and spinbox after applying the frame
    ui->selectColor->hide();
    ui->frameSizeSpinBox->setValue(0);
    ui->frameSizeSpinBox->hide();
    Show();
}

















#include <QMessageBox>
#include "demo_photoshop.h"
#include "ui_demo_photoshop.h"

// Function to initiate cropping
void demo_photoshop::on_Crop_clicked() {
    // Get the current tab index
    int currentIndex = ui->tabs_menu->currentIndex();
    QWidget *currentTab = ui->tabs_menu->widget(currentIndex);

    // Find QLabel in the current tab
    QLabel *tabImageLabel = currentTab->findChild<QLabel*>();

    // Check if the tabImageLabel is found and has a valid pixmap
    if (tabImageLabel && !tabImageLabel->pixmap().isNull()) {
        // Store the original image from the QLabel
        QImage originalImage = tabImageLabel->pixmap().toImage();

        // Ensure that the spinbox values do not exceed image dimensions
        ui->startXInput->setMaximum(originalImage.width() - 1);
        ui->startYInput->setMaximum(originalImage.height() - 1);
        ui->widthInput->setMaximum(originalImage.width() - ui->startXInput->value());
        ui->heightInput->setMaximum(originalImage.height() - ui->startYInput->value());

        // Get the cropping dimensions and starting points from spinboxes
        int startX = ui->startXInput->value();  // QSpinBox for startX
        int startY = ui->startYInput->value();  // QSpinBox for startY
        int width = ui->widthInput->value();     // QSpinBox for width
        int height = ui->heightInput->value();   // QSpinBox for height

        // Validate the cropping dimensions
        if (startX < 0 || startY < 0 || width <= 0 || height <= 0 ||
            (startX + width) > originalImage.width() || (startY + height) > originalImage.height()) {
            QMessageBox::warning(this, "Out Of Range", "The cropping dimensions are out of range.");
            return;  // Exit the function if the dimensions are invalid
        }

        // Crop the image using the specified dimensions
        QImage croppedImage = originalImage.copy(startX, startY, width, height);

        // Update the QLabel to display the cropped image
        tabImageLabel->setPixmap(QPixmap::fromImage(croppedImage));

        // Optional: Update image history or properties if needed
        updateImageHistory(croppedImage);
        updateDisplayedImage(croppedImage);
        updateImageProperties(croppedImage);
    } else {
        QMessageBox::warning(this, "No Image", "The image is not loaded or the label is not found.");
    }

    // Hide UI elements after cropping
    ui->Crop->hide();
    ui->startXInput->hide();
    ui->startYInput->hide();
    ui->widthInput->hide();
    ui->heightInput->hide();
    ui->starting_points->hide();
    ui->cropped_dims->hide();
    ui->X_cord->hide();
    ui->Y_cord->hide();
    ui->Hight_crop->hide();
    ui->Width_crop->hide();
    Show();
}












void demo_photoshop::on_CropTools_clicked()
{
    Hide_2();
    ui->SliderBox->hide();
    ui->Crop->show();
    ui->startXInput->show();
    ui->startYInput->show();
    ui->widthInput->show();
    ui->heightInput->show();
    ui->starting_points->show();
    ui->cropped_dims->show();
    ui->X_cord->show();
    ui->Y_cord->show();
    ui->Hight_crop->show();
    ui->Width_crop->show();
}







