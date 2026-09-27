#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget window;
    window.resize(800, 600);
    QPushButton button("Hello, Qt!");

    window.setWindowTitle("My Qt App");
    button.resize(10, 10);
    button.show();
    window.show();

    return app.exec();
}
