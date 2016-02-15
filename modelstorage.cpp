#include "modelstorage.h"


bool ModelStorage::load(const QString& fileName, QStandardItemModel& model) {
    QFile loadFile(fileName);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc = QJsonDocument::fromJson(saveData);
    QJsonObject json = loadDoc.object();

    // Очистка модели
    while (model.rowCount() > 0) {
        model.invisibleRootItem()->removeRow(0);
    }

    const int rowCount = json["rowCount"].toInt();
    const int columnCount = json["columnCount"].toInt();
    QJsonArray data = json["data"].toArray();

    model.setRowCount(rowCount);
    model.setColumnCount(columnCount);

    for (int i = 0; i < rowCount; i++) {
        QJsonArray row = data[i].toArray();

        for (int j = 0; j < columnCount; j++) {
            model.setItem(i, j, new QStandardItem(row[j].toString()));
        }
    }

    return true;
}

bool ModelStorage::save(const QString& fileName, const QStandardItemModel& model) {
    QFile saveFile(fileName);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject json;
    json["rowCount"] = model.rowCount();
    json["columnCount"] = model.columnCount();

    QJsonArray data;
    for (int i = 0; i < model.rowCount(); i++) {
        QJsonArray row;

        for (int j = 0; j < model.columnCount(); j++) {
            row.append(QJsonValue(model.item(i, j)->text()));
        }

        data.append(row);
    }
    json["data"] = data;

    QJsonDocument saveDoc(json);
    saveFile.write(saveDoc.toJson());

    return true;
}
