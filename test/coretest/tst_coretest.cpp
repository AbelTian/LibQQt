#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include <qqtcore.h>

class CoreTest : public QObject
{
    Q_OBJECT

public:
    CoreTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testCase1_data();
    void testCase1();
    void testCase2_data();
    void testCase2();
};

CoreTest::CoreTest()
{
}

void CoreTest::initTestCase()
{

}

void CoreTest::cleanupTestCase()
{

}

void CoreTest::testCase1_data()
{
    QTest::addColumn<int> ( "num" );
    QTest::addColumn<int> ( "reslt" );
    //nullprt = 0
    QTest::newRow ( "0" ) << 0 << 0;
    QTest::newRow ( "1" ) << nullptr << 0;
}

void CoreTest::testCase1()
{
    QFETCH ( int, num );
    QFETCH ( int, reslt );
    QVERIFY2 ( num == reslt, "Failure" );
}

void CoreTest::testCase2_data()
{
    QTest::addColumn<int> ( "num" );
    QTest::addColumn<int> ( "reslt" );
    //nullprt = 0
    QTest::newRow ( "2" ) << 0 << 0;
    QTest::newRow ( "3" ) << nullptr << 0;
}

void CoreTest::testCase2()
{
    QString c = "fff";
    QFETCH ( int, num );
    QFETCH ( int, reslt );
    QCOMPARE ( num, reslt );
}

QTEST_MAIN ( CoreTest )

#include "tst_coretest.moc"
