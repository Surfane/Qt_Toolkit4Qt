#ifndef CLASSFACTORY_H
#define CLASSFACTORY_H

#include <QObject>
#include <QMetaObject>

//use:
//ObjectFactory factory;
//factory.registerObject<MyClass>();
//QObject *obj= factory.createObject("MyClass");
//
class ObjectFactory
{
private:
    QHash< QByteArray, const QMetaObject* > metaObjects;
public:
    template <typename T>
    void registerObject()
    {
        metaObjects.insert( T::staticMetaObject.className(),&(T::staticMetaObject) );
    }
    QObject *createObject( const QByteArray &type )
    {
        const QMetaObject *meta = metaObjects.value( type );
        return meta->newInstance();
    }
};


//use:
//ClassFactory::registerClass<MyClass>();
//QObject* foo = ClassFactory::createObject( "MyClass" );
//
class ClassFactory
{
public:
    template<typename T>
    static void registerClass()
    {
        constructors().insert( T::staticMetaObject.className(), &constructorHelper<T> );
    }

    static QObject* createObject( const QByteArray& className, QObject* parent = NULL )
    {
        Constructor constructor = constructors().value( className );
        if ( constructor == NULL )
            return NULL;
        return (*constructor)( parent );
    }

private:
    typedef QObject* (*Constructor)( QObject* parent );

    template<typename T>
    static QObject* constructorHelper( QObject* parent )
    {
        return new T( parent );
    }

    static QHash<QByteArray, Constructor>& constructors()
    {
        static QHash<QByteArray, Constructor> instance;
        return instance;
    }
};

#endif // CLASSFACTORY_H
