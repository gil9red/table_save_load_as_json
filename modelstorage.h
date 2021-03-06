#ifndef MODELSTORAGE_H
#define MODELSTORAGE_H

#include <QStandardItemModel>
#include <QStandardItem>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class ModelStorage
{
public:
    static bool load(const QString& fileName, QStandardItemModel & model);
    static bool save(const QString& fileName, const QStandardItemModel& model);
};

#endif // MODELSTORAGE_H
