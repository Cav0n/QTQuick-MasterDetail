#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QAbstractListModel>

class FileList;

class FileModel : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(FileList *list READ list WRITE setList )
    FileList *m_fileList;

public:
    explicit FileModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    FileList *list() const;

    void setList(FileList *list);


    QHash<int, QByteArray> roleNames() const;
    enum {
        FileName = Qt::UserRole,
        Size,
        File
    };

protected:

public:
    Q_INVOKABLE void newElement();
    Q_INVOKABLE void removeRow(int index);

};

#endif // FILEMODEL_H
