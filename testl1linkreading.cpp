#include <QtTest/QtTest>

class TestL1LinkReading : public QObject
{
    Q_OBJECT
private slots:
    void toUpper();
};

void TestL1LinkReading::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}

QTEST_MAIN(TestL1LinkReading)
