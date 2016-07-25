#include <QCoreApplication>

#include "TestScript/jsontooltest.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);

  JsonToolTest::Test();

  return a.exec();
}
