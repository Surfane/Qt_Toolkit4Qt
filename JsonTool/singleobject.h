#ifndef SINGLEOBJECT_H
#define SINGLEOBJECT_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QList>

#include "baseobject.h"

class SingleObject : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool BParameter READ BParameter WRITE BParameter)
  Q_PROPERTY(int IntParameter READ IntParameter WRITE IntParameter)
  Q_PROPERTY(QString StrParameter READ StrParameter WRITE StrParameter)

  Q_PROPERTY(int * IntArray READ IntArray WRITE IntArray)
  Q_PROPERTY(QString * StrArray  READ StrArray WRITE StrArray)
  Q_PROPERTY(QString * StrPtr  READ StrPtr WRITE StrPtr)
  Q_PROPERTY(QList<QString> StrList  READ StrList WRITE StrList)
  Q_PROPERTY(QList<BaseObject> ObjList  READ ObjList WRITE ObjList)

  Q_PROPERTY(BaseObject ObjPtr  READ ObjPtr WRITE ObjPtr)
public:
   explicit SingleObject(QObject *parent = 0 ) : QObject(parent)
  {
    strPtr =new QString();
    obj = new BaseObject();
    for( int i = 0 ; i < 3 ; ++i)
      {
        intArray[i]=0;
        strArray[i]="";
      }
  }

  SingleObject(const SingleObject &other)
  {
        BParameter(other.BParameter());
        IntParameter(other.IntParameter());
        StrParameter(other.StrParameter());
        StrPtr(other.StrPtr());
  }

  bool BParameter() const
  {
     return bParameter;
  }
  bool BParameter(const bool value)
  {
     bParameter = value;
     return BParameter();
  }

  int IntParameter() const
  {
    return intParameter;
  }
  int IntParameter(const int value)
  {
    intParameter=value;
    return IntParameter();
  }

  QString StrParameter() const
  {
    return strParameter;
  }
  QString StrParameter(const QString &value)
  {
    if(strParameter.isNull() || 0 != QString::compare(strParameter,value))
      {
        strParameter = value;
      }
    return StrParameter();
  }

  QList<QString> StrList() const
  {
    return strList;
  }
  QList<QString> StrList(const QList<QString> &value)
  {
    if( strList != value)
      {
        strList = value;
      }
    return StrList();
  }

  QList<BaseObject> ObjList() const
  {
    return objList;
  }
  QList<BaseObject> ObjList(const QList<BaseObject> &value)
  {
    if( objList != value)
      {
        objList = value;
      }
    return ObjList();
  }

  QString *StrPtr() const
  {
    return strPtr;
  }
  QString * StrPtr( const QString * const value)
  {
    if(strPtr->isNull() || 0 != QString::compare(*strPtr,*value))
      {
        *strPtr = *value;
      }
    return StrPtr();
  }

  int* IntArray() //const
  {
    return intArray;
  }
  int* IntArray( int* value)
  {
    for (int i = 0; i < 3; ++i)
      {
        intArray[i] = *(value+i);
      }    
    return IntArray();
  }

  QString* StrArray() //const
  {
    return strArray;
  }
  QString* StrArray(const QString * const value)
  {
    for (int i = 0; i < 3; ++i)
      {
        if(strArray[i].isNull() || 0 != QString::compare(strArray[i],value[i]))
          {
            strArray[i] = value[i];
          }
    }
    return StrArray();
  }

  BaseObject ObjPtr() const
  {
    return *obj;
  }

  BaseObject ObjPtr(BaseObject &value)
  {
    if(this->ObjPtr() != value)
    {
      *obj = value;
    }
   return ObjPtr();
  }

signals:

public slots:

private:
  bool bParameter;
  int intParameter;
  QString strParameter;
  QString *strPtr;
  QList<QString> strList;
  QList<BaseObject> objList;

  int intArray[3];
  QString strArray[3];

  BaseObject *obj;

};

#endif // SINGLEOBJECT_H
