#ifndef JSONTOOL_H
#define JSONTOOL_H

#include <string>
#include <QDebug>
#include <QString>
#include <QList>
#include <QVariant>
#include <QMetaObject>
#include <QMetaProperty>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>

#include "singleobject.h"
#include "baseobject.h"

#define BASETYPE 1024

class JsonTool
{
public:
  JsonTool(){}

  template<typename T>
  static QList<T> JsonArraytoList(QJsonArray jsonArray)
  {
    QList<T> list ;
    for (int i = 0 ; i < jsonArray.count(); ++i)
      {
        list.append(jsonArray[i].toVariant().value<T>());
      }
    return list;
  }

  template<typename T>
  static T* JsonArraytoArray(QJsonArray jsonArray)
  {
    T* list = (T *)malloc(sizeof(T)*jsonArray.count());
    return JsonArraytoArray(jsonArray,list);
  }

  template<typename T>
  static T* JsonArraytoArray(QJsonArray jsonArray,T* list)
  {
    for (int i = 0 ; i < jsonArray.count(); ++i)
      {
        *(list+i) = jsonArray[i].toVariant().value<T>();
      }
    return list;
  }

  template<typename T>
  static QJsonArray ObjListToJsonArray(T list, int length)
  {
    QJsonArray jsonArray;
    for (int i = 0 ; i < length ; ++ i)
      {
         jsonArray.append(list[i]);
      }
    return jsonArray;
  }

  template<typename T>
  static QJsonArray ObjListToJsonArray(QList<T> list, bool isBaseType)
  {
    QJsonArray jsonArray;
    for (int i = 0 ; i < list.count() ; ++ i)
      {
        jsonArray.append(QJsonValue::fromVariant(list.value(i)));
      }
    return jsonArray;
  }

  template<typename T>
  static QJsonArray ObjListToJsonArray(QList<T> list)
  {
    QJsonArray jsonArray;
    T *obj = new T();
    for (int i = 0 ; i < list.count() ; ++ i)
      {
        *obj = list.value(i);
        jsonArray.append(toJson(obj));
      }
    return jsonArray;
  }

  template<typename T>
  static void toObject(T &obj,  QString &json)
  {
      QJsonDocument jsonDoc = QJsonDocument::fromJson(json.toLocal8Bit());
      if(!(jsonDoc.isNull() || jsonDoc.isEmpty()) && jsonDoc.isObject())
      {
          QJsonObject jsonObject = jsonDoc.object();
          return toObject(obj,jsonObject);
      }
  }

  template<typename T>
  static void toObject(T &obj, QJsonObject &json)
  {
      const QMetaObject* metaObject = obj->metaObject();
      for ( int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
      {
          QMetaProperty pro = metaObject->property(i);
          QString typeName = pro.typeName();
          int typeId = QMetaType::type(typeName.toLatin1().data());
          const char * proName = pro.name();
          QString jsonKey = QString(QLatin1String(proName)).toLower();

          if(BASETYPE > typeId)
            {
              if (1 == typeId)
                obj->setProperty(proName,json[jsonKey].toBool());
              else if(3 >= typeId)
                obj->setProperty(proName,json[jsonKey].toInt());
              else if(6 == typeId)
                obj->setProperty(proName,json[jsonKey].toDouble());
              else
                obj->setProperty(proName,json[jsonKey].toString());
            }
          else if (0 == (QString::compare("*",typeName.right(1))))
            {
              typeId = QMetaType::type(typeName.remove(typeName.lastIndexOf('*'),1).toLatin1().data());
              if(BASETYPE > typeId)
                {
                   QJsonArray jsonArray;
                   if(json[jsonKey].isArray())
                      jsonArray = json[jsonKey].toArray();
                   else
                      jsonArray.append(QJsonValue::fromVariant(json[jsonKey].toVariant()));
                   if (1 == typeId)
                      obj->setProperty(proName,QVariant::fromValue(JsonArraytoArray<bool>(jsonArray)));
                   else if(3 >= typeId)
                      obj->setProperty(proName,QVariant::fromValue(JsonArraytoArray<int>(jsonArray)));
                   else if(6 == typeId)
                      obj->setProperty(proName,QVariant::fromValue(JsonArraytoArray<double>(jsonArray)));
                   else
                     {
                        QString list[jsonArray.count()];
                        obj->setProperty(proName,QVariant::fromValue(JsonArraytoArray<QString>(jsonArray,list)));
                     }
                }
            }
          else if(0 == (QString::compare("QList<",typeName.left(6) )))
          {
            typeName = typeName.remove(typeName.lastIndexOf('>'),1).mid(typeName.indexOf('<')+1);
            if(BASETYPE > QMetaType::type(typeName.toLatin1().data()))
              {
                if (1 == typeId)
                   obj->setProperty(proName,QVariant::fromValue(JsonArraytoList<bool>(json[jsonKey].toArray())));
                else if(3 >= typeId)
                   obj->setProperty(proName,QVariant::fromValue(JsonArraytoList<int>(json[jsonKey].toArray())));
                else if(6 == typeId)
                   obj->setProperty(proName,QVariant::fromValue(JsonArraytoList<double>(json[jsonKey].toArray())));
                else
                  {
                    obj->setProperty(proName,QVariant::fromValue(JsonArraytoList<QString>(json[jsonKey].toArray())));
                  }
              }
            else if(0 == QString::compare("BaseObject",typeName))
              {
                BaseObject *bobj = new BaseObject();
                QList<BaseObject> objList;
                QJsonObject jsonobj;
                QJsonArray jsonArray = json[jsonKey].toArray();
                for (int i = 0 ; i < jsonArray.count(); ++i)
                  {
                    jsonobj = jsonArray[i].toObject();
                    toObject(bobj,jsonobj);
                    objList.append(*bobj);
                  }
                obj->setProperty(proName,QVariant::fromValue(objList));
              }
          }
          else if(0 == QString::compare("BaseObject",typeName))
            {
              BaseObject *bobj = new BaseObject();
              QJsonObject jsonobj = json[jsonKey].toObject();
              toObject(bobj,jsonobj);
              obj->setProperty(proName,QVariant::fromValue(*bobj));
            }
          else
            {

            }
      }
  }

  template<typename T>
  static QJsonObject toJson( T &obj )
  {
      QJsonObject json;
      const QMetaObject* metaObject = obj->metaObject();
      for ( int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
      {
          QMetaProperty pro = metaObject->property(i);
          QString typeName = pro.typeName();
          QString proName = pro.name();
          QString jsonKey = proName.toLower();
          QVariant qv = obj->property(pro.name());

          //how to conver a Qvariant object to object while do not know the object type
          //T par = QVariant.value<T>();however when type T is unknow?
          if(BASETYPE > QMetaType::type(typeName.toLatin1().data()))
            {
              json[jsonKey] = QJsonValue::fromVariant(qv);
            }
          else if(0 == (QString::compare("QList<",typeName.left(6) )))
          {
            typeName = typeName.remove(typeName.lastIndexOf('>'),1).mid(typeName.indexOf('<')+1);
            if(BASETYPE > QMetaType::type(typeName.toLatin1().data()))
              {
                json[jsonKey] = ObjListToJsonArray(qv.value<QList<QVariant>>(),true);
              }
            else if(0 == QString::compare("BaseObject",typeName))
              {
                json[jsonKey]= ObjListToJsonArray(qv.value<QList<BaseObject>>());
              }
          }
          else if(0 == QString::compare("BaseObject",typeName))
            {
              BaseObject *bobj = new BaseObject(qv.value<BaseObject>());
              json[jsonKey]= toJson(bobj);
            }
          else if(0 == (QString::compare("QString*",typeName)))
            {
              //actually we can not compare a pointer parameter is a real pointer or a array address
              //that is must user list<> instead of pointer when we want to user a array parameter
              if (0 == QString::compare("StrPtr",proName))
                {
                  json[jsonKey]=*(qv.value<QString*>());
                }
              else
                {
                  json[jsonKey]= ObjListToJsonArray(qv.value<QString*>(),3);
                }
            }
          else if(0 == (QString::compare("int*",typeName )))
            {
              json[jsonKey]= ObjListToJsonArray(qv.value<int*>(),3);
            }
          else
            {

            }
      }
      return json;
   }

};

#endif // JSONTOOL_H
