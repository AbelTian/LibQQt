#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "qqtdictionary.h"

class QqtdicttestTest : public QObject
{
    Q_OBJECT

public:
    QqtdicttestTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1_data();
    void testCase1();
    void testCase2_data();
    void testCase2();

private:
    QQtDict dict;
};

QqtdicttestTest::QqtdicttestTest()
{
}

void QqtdicttestTest::initTestCase()
{
}

void QqtdicttestTest::cleanupTestCase()
{
}

void QqtdicttestTest::testCase1_data()
{
    QTest::addColumn<QString> ( "data" );
    QTest::addColumn<QString> ( "result" );
    QTest::newRow ( "0" ) << "cc" << "dd";
    QTest::newRow ( "1" ) << "dd" << "ee";
    QTest::newRow ( "2" ) << "gg" << "ff";
}

void QqtdicttestTest::testCase1()
{
    QFETCH ( QString, data );
    QFETCH ( QString, result );
    dict[data] = result;
    QVERIFY2 ( dict[data].getValue() == result, "Failure" );
}

void QqtdicttestTest::testCase2_data()
{

}

void QqtdicttestTest::testCase2()
{
    QFETCH ( QString, data );
    QFETCH ( QString, result );
    dict[0] = result;
    QVERIFY2 ( dict[0].getValue() == result, "Failure" );
}

QTEST_MAIN ( QqtdicttestTest )

#include "tst_qqtdicttesttest.moc"
