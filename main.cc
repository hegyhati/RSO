#define QT_FATAL_WARNINGS
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QVariantMap>

#include "TestSystem.hh"

#include "gui/ForkliftModel.hh"
#include "gui/InputBufferModel.hh"
#include "gui/BlockModel.hh"

using namespace std;

int main(int argc, char ** argv){
    // CLI version
    //TestSystem t;
    //t.interact();

    QGuiApplication app(argc, argv);

    Forklift forklift = Forklift("4m");
    InputBuffer input_buffer = InputBuffer(5);
    PalletBlock block = PalletBlock({
      {"2m","3m","4m"},
      {"12cm", "1500cm","19m"},
      {"4cm","8km","6in","4ft"},
      {"12cm", "1500cm","19m"}
    }, 5);

    input_buffer.generateNewPallet(0, "3m");
    input_buffer.generateNewPallet(1, "1m");
    forklift.load(true, input_buffer, 0u);
    forklift.unload(true, block, BlockPosition{0, 0, 0});

    ForkliftModel forkliftModel(forklift);
    InputBufferModel inputbufferModel(input_buffer, forkliftModel);
    BlockModel blockModel(block, forkliftModel);

    QVariantMap qmlProps;
    qmlProps["forkliftModel"] = QVariant::fromValue(&forkliftModel);
    qmlProps["inputBufferModel"] = QVariant::fromValue(&inputbufferModel);
    qmlProps["blockModel"] = QVariant::fromValue(&blockModel);

    QQmlApplicationEngine engine;
    engine.setInitialProperties(qmlProps);
    engine.load("qrc:gui/main.qml");

    return app.exec();
}
