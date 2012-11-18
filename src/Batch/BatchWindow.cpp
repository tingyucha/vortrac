#include "BatchWindow.h"

BatchWindow::BatchWindow(QWidget *parent, QDomDocument& xmlfile)
    : QMainWindow(parent)
{
    this->setObjectName("Batch Window");

    qRegisterMetaType<Message>("Message");
    qRegisterMetaType<GriddedData>("GriddedData");
    qRegisterMetaType<VortexList>("VortexList");

    std::cout << "Starting main window ... \n";

    driver = new DriverBatch(this, xmlfile);

    driver->initialize();
    driver->run();
    driver->finalize();

}

BatchWindow::~BatchWindow()
{
    delete driver;
}
