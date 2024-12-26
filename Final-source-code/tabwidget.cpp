// #include "tabwidget.h"
// #include <QWidget>
// #include <QVBoxLayout>
// #include <QPushButton>
// #include <QLabel>

// TabWidget::TabWidget(QWidget *parent) : QTabWidget(parent)
// {
//     // Optional: Set up the initial state or style of the tab widget
// }

// void TabWidget::addPhotoTab(const QString &photoName)
// {
//     QWidget *photoTab = new QWidget();
//     QVBoxLayout *layout = new QVBoxLayout(photoTab);
//     QLabel *photoLabel = new QLabel(photoName, photoTab);
//     layout->addWidget(photoLabel);
//     photoTab->setLayout(layout);

//     this->addTab(photoTab, photoName);
// }

// void TabWidget::removeCurrentTab()
// {
//     int index = this->currentIndex();
//     if (index != -1)
//         this->removeTab(index);
// }
