#include <QApplication>
#include <locale>
#include "Device.h"
#include "DrawEngine.h"
#include "Layer.h"
#include "BaseCanvas.h"

using namespace DE;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setlocale(LC_ALL, "zh_CN.UTF-8");
    
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(fmt);
    
    BaseCanvas w;
    w.show();
    
    Device::GetInstance()->setGLInitHandler([](){
        Layer* lay = new Layer();
        Device::GetInstance()->getCurrentCanvas()->setPrimaryLayer(lay);
        lay->loadImages("bgimage/bg1.png");
        lay->setAllChildEnabled(true);
        Layer* lay2 = new Layer();
        lay->addChild(lay2);
        lay2->loadImages("image/configb1_1.png");
        lay2->setAnchorX(0.5);
        lay2->setAnchorY(0.5);
        lay2->setRotation(45);
        lay2->setLeft(400);
        lay2->setTop(300);
        lay2->setEnabled(true);
    });
    return a.exec();
}
