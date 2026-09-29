#include <QApplication>
#include <QTableWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTableWidget table;
    table.setStyleSheet(
    "QTableWidget {"
    "    background-color: #333333;"
    "    color: red;"
    "    padding: 8px 16px;"
    "    border-radius: 5px;"
    "}"
);
    table.setRowCount(3);
    table.setColumnCount(3);

    table.setHorizontalHeaderLabels({
        "Name",
        "Type",
        "Value"
    });

    table.setItem(0, 0, new QTableWidgetItem("Motor"));
    table.setItem(0, 1, new QTableWidgetItem("BOOL"));
    table.setItem(0, 2, new QTableWidgetItem("true"));

    table.setItem(1, 0, new QTableWidgetItem("Speed"));
    table.setItem(1, 1, new QTableWidgetItem("INT"));
    table.setItem(1, 2, new QTableWidgetItem("1500"));

    table.setItem(2, 0, new QTableWidgetItem("Temperature"));
    table.setItem(2, 1, new QTableWidgetItem("FLOAT"));
    table.setItem(2, 2, new QTableWidgetItem("72.5"));

    table.resize(1000, 800);
    table.show();

    return app.exec();
}
