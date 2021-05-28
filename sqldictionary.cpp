#include "sqldictionary.h"

SqlDictionary::SqlDictionary(QObject *parent) : QSqlQueryModel(parent)
{
  conectToDataBase();
  setDataFromDataBase();
}

SqlDictionary::~SqlDictionary()
{
 // mydb.removeDatabase("qt_sql_default_connection");
  mydb.close();
  qDebug() << "connection with database was closed";
}

void SqlDictionary::addWordToDictionary(QString wordEnglish, QString wordTranslated)
{
  QSqlQuery query = mydb.exec("INSERT INTO dictionary VALUES ('"+ wordEnglish + "','"+ wordTranslated +"')");
  query.next();
  qDebug() << "insert completed: ";
  setDataFromDataBase();
}

QVariant SqlDictionary::data(const QModelIndex &index, int role) const
{
    QVariant value;

       if (index.isValid()) {
           if (role < Qt::UserRole) {
               value = QSqlQueryModel::data(index, role);
           } else {
               int columnIdx = role - Qt::UserRole - 1;
               QModelIndex modelIndex = this->index(index.row(), columnIdx);
               value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
           }
       }
       return value;
}

QHash<int, QByteArray> SqlDictionary::roleNames() const
{
   QHash<int, QByteArray> roles;
   // record() returns an empty QSqlRecord
   for (int i = 0; i < this->record().count(); i ++) {
       roles.insert(Qt::UserRole + i + 1, record().fieldName(i).toUtf8());
   }
   return roles;
}

void SqlDictionary::setDataFromDataBase()
{
    this->setQuery("SELECT * FROM dictionary");
    qDebug() << "Data was setted";
    qDebug() <<"Roles: " << this->roleNames();

}
void SqlDictionary::conectToDataBase()
{
       mydb = QSqlDatabase::addDatabase("QSQLITE");
       // if database do not work on ubuntu just remove extansion of file
       QString path = "dictionary.db";
       qDebug() << path;
       mydb.setDatabaseName(path);
       if(mydb.open())
       {
           qDebug() << "Connection sucsess";
       }
       else
       {
           qDebug() << "Connection failed";
       }
}
