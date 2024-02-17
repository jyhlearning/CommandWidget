#include <QApplication>
#include "CommandWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    CommandWidget widget;
    widget.setPrefix("Sample");
    widget.resize(1000,500);
    widget.initView();
    widget.show();
    return QApplication::exec();
}
