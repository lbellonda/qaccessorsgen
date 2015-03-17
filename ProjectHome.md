This project aims to generate getter and setter methods for a property of a C++ class (accessors) in a way that fits well with the Qt property system, reducing the boilerplate code written in a typical project.

sample input:

---

> qaccessorsgen `TestClass` QString name

sample output:

---

DECLARATIONS:

QString `_`name;

Q\_PROPERTY(QString name READ name WRITE setName)

QString name();

void setName(const QString& value);


---

IMPLEMENTATION:

QString `TestClass`::name()
{
> return `_`name ;
}


void `TestClass`::setName(const QString& value)
{
> `_`name = value ;
}


---

