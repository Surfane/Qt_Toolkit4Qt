#ifndef JSONTOOLTEST_H
#define JSONTOOLTEST_H

#include <QDebug>

#include "./JsonTool/baseobject.h"
#include "./JsonTool/singleobject.h"
#include "./JsonTool/jsontool.h"

Q_DECLARE_METATYPE(QList<BaseObject>)
Q_DECLARE_METATYPE(BaseObject)
Q_DECLARE_METATYPE(QString*)
Q_DECLARE_METATYPE(bool*)
Q_DECLARE_METATYPE(int*)
Q_DECLARE_METATYPE(double*)

class JsonToolTest
{
  public:
    JsonToolTest(){}
    //void QDebug(SingleObject &,QString signal= QString(""));

    static void Test()
    {
      qRegisterMetaType<QList<BaseObject>>("QList<BaseObject>");
      qRegisterMetaType<BaseObject>("BaseObject");
      qRegisterMetaType<QString*>("QString*");
      qRegisterMetaType<int*>("int*");

      SingleObject *sobj = new SingleObject();
      QJsonObject *jsonObject = new QJsonObject();
      QList<BaseObject> objList;
      objList.append(BaseObject(false,901,"bobj1 String"));
      objList.append(BaseObject(true,902,"bobj2 String"));
      objList.append(BaseObject(false,903,"bobj3 String"));

      sobj->ObjList(objList);
      sobj->BParameter(true);
      sobj->IntParameter(678);
      sobj->StrParameter("par String");
      sobj->StrPtr(new QString("ptr String"));
      sobj->ObjPtr(*(new BaseObject(false,9000,"bobj String")));
      sobj->IntArray(new int[3]{232,454,676});
      sobj->StrArray(new QString[3]{QString("aaa"),QString("bbb"),QString("ccc")});
      sobj->StrList(QList<QString>()<<"L01"<<"L02"<<"L03");

      QDebug(*sobj,"Object Init");

      *jsonObject = JsonTool::toJson(sobj);

      qDebug() <<"";
      qDebug() <<"Json Object : " ;
      qDebug() <<*jsonObject;

      SingleObject *Sinobj = new SingleObject();
      QString strJson = "{\"bparameter\":false,\"intarray\":[2321,4543,6765],\"intparameter\":6789,\"objlist\":[{\"bparameter\":true,\"intparameter\":9001,\"strparameter\":\"bobj01 String\"},{\"bparameter\":false,\"intparameter\":9002,\"strparameter\":\"bobj02 String\"},{\"bparameter\":true,\"intparameter\":9003,\"strparameter\":\"bobj03 String\"}],\"objptr\":{\"bparameter\":true,\"intparameter\":90000,\"strparameter\":\"bobj 00 String\"},\"strarray\":[\"eeee\",\"cccc\",\"tttt\"],\"strlist\":[\"L001\",\"L002\",\"L003\"],\"strparameter\":\"par 00 String\",\"strptr\":\"ptr 00 String\"}";

      qDebug() <<"";
      qDebug() <<"Json String : " ;
      qDebug() << strJson;

      JsonTool::toObject(Sinobj,*jsonObject);

      QDebug(*Sinobj,"From Json Object");

      JsonTool::toObject(Sinobj,strJson);

      QDebug(*Sinobj,"From Json String");

    }

private:
    static void QDebug(SingleObject &Sinobj,QString signal)
    {
      qDebug() << "";
      qDebug() << "========== Debug Print of : " +  signal + " Start ==========";
      qDebug() << "";
      qDebug() << "Sinobj BParameter    : " << Sinobj.BParameter();
      qDebug() << "Sinobj IntParameter  : " << Sinobj.IntParameter();
      qDebug() << "Sinobj StrParameter  : " << Sinobj.StrParameter();
      qDebug() << "Sinobj StrPtr        : " << *(Sinobj.StrPtr());
      qDebug() << "Sinobj ObjPtr        : " << Sinobj.ObjPtr().BParameter() << " , "<< Sinobj.ObjPtr().IntParameter()<< " , "<< Sinobj.ObjPtr().StrParameter();

      for (int i = 0 ; i < 3 ; ++i)
        {
          qDebug() << "Sinobj IntArray[" << i <<"] : " << Sinobj.IntArray()[i];
        }

      for (int i = 0 ; i < 3 ; ++i)
        {
          qDebug() << "Sinobj StrArray[" << i <<"] : " << Sinobj.StrArray()[i];
        }

      for (int i = 0 ; i < Sinobj.StrList().count() ; ++i)
        {
          qDebug() << "Sinobj  StrList[" << i <<"] : "<< Sinobj.StrList().value(i);
        }
      for (int i = 0 ; i < Sinobj.ObjList().count() ; ++i)
        {
          qDebug() << "Sinobj  ObjList[" << i <<"] : "<< Sinobj.ObjList().value(i).BParameter() <<" , " << Sinobj.ObjList().value(i).IntParameter() << " , " << Sinobj.ObjList().value(i).StrParameter();
        }
      qDebug() << "";
      qDebug() << "========== Debug Print of : " +  signal + " End ==========";

    }
};

#endif // JSONTOOLTEST_H


//  QJsonObject strJson = {
//                    "bparameter": "true",
//                    "intarray": [
//                        232,
//                        454,
//                        676
//                    ],
//                    "intparameter": "678",
//                    "objlist": [
//                        {
//                            "bparameter": "false",
//                            "intparameter": "901",
//                            "strparameter": "bobj1 String"
//                        },
//                        {
//                            "bparameter": "true",
//                            "intparameter": "902",
//                            "strparameter": "bobj2 String"
//                        },
//                        {
//                            "bparameter": "false",
//                            "intparameter": "903",
//                            "strparameter": "bobj3 String"
//                        }
//                    ],
//                    "objptr": {
//                        "bparameter": "false",
//                        "intparameter": "9000",
//                        "strparameter": "bobj String"
//                    },
//                    "strarray": [
//                        "aaa",
//                        "bbb",
//                        "ccc"
//                    ],
//                    "strlist": [
//                        "L01",
//                        "L02",
//                        "L03"
//                    ],
//                    "strparameter": "par String",
//                    "strptr": "prt String"
//                }
