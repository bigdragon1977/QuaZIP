#include "testquagzipfile.h"
#include <zlib.h>
#include <QDir>
#include <quazip/quagzipfile.h>
#include <QtTest/QtTest>

void TestQuaGzipFile::read()
{
    QDir curDir;
    curDir.mkpath("tmp");
    voidp gzFile = gzopen("tmp/test.gz", "wb");
    gzwrite(gzFile, "test", 4);
    gzclose(gzFile);
    QuaGzipFile testFile("tmp/test.gz");
    QVERIFY(testFile.open(QIODevice::ReadOnly));
    char buf[5];
    buf[4] = '\0';
    QCOMPARE(testFile.read(buf, 5), static_cast<qint64>(4));
    testFile.close();
    QVERIFY(!testFile.isOpen());
    QCOMPARE(buf, "test");
    curDir.remove("tmp/test.gz");
    curDir.rmdir("tmp");
}

void TestQuaGzipFile::write()
{
    QDir curDir;
    curDir.mkpath("tmp");
    QuaGzipFile testFile("tmp/test.gz");
    QVERIFY(testFile.open(QIODevice::WriteOnly));
    QCOMPARE(testFile.write("test", 4), static_cast<qint64>(4));
    testFile.close();
    QVERIFY(!testFile.isOpen());
    voidp gzFile = gzopen("tmp/test.gz", "rb");
    char buf[5];
    buf[4] = '\0';
    QCOMPARE(gzread(gzFile, buf, 5), 4);
    gzclose(gzFile);
    QCOMPARE(buf, "test");
    curDir.remove("tmp/test.gz");
    curDir.rmdir("tmp");
}
