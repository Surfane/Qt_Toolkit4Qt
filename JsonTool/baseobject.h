#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <QObject>
#include <QString>
#include<QDebug>

class BaseObject : public QObject
{
  Q_OBJECT
  Q_PROPERTY(bool BParameter READ BParameter WRITE BParameter)
  Q_PROPERTY(int IntParameter READ IntParameter WRITE IntParameter)
  Q_PROPERTY(QString StrParameter READ StrParameter WRITE StrParameter)
public:
  explicit BaseObject(QObject *parent = 0) : QObject(parent)
  {

  }

  BaseObject(const BaseObject &other)
  {
    if(*this != other)
      {
        *this=other;
      }
  }

  BaseObject(const bool bPar, const int iPar, const QString sPar)
  {
    BParameter(bPar);
    IntParameter(iPar);
    StrParameter(sPar);
  }

  bool operator !=(const BaseObject &other) const
  {
    return (this->bParameter!=other.bParameter) || (this->intParameter!=other.intParameter) || (0 != QString::compare(this->strParameter,other.strParameter));
  }
  bool operator ==(const BaseObject &other) const
  {
    return (this->bParameter==other.bParameter) && (this->intParameter==other.intParameter) && (0 == QString::compare(this->strParameter,other.strParameter));
  }
  void operator =(const BaseObject &other)
  {
        BParameter(other.BParameter());
        IntParameter(other.IntParameter());
        StrParameter(other.StrParameter());
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

signals:

public slots:

private :
  bool bParameter;
  int intParameter;
  QString strParameter;
};

#endif // BASEOBJECT_H
