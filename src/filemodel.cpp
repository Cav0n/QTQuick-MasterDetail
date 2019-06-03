#include "filemodel.h"
#include "filelist.h"
#include "file.h"

#include <QDebug>
#include <QTextStream>


FileModel::FileModel(QObject *parent)
    : QAbstractListModel(parent), m_fileList(nullptr)
{
}

FileList *FileModel::list() const
{
    return m_fileList;
}

void FileModel::setList(FileList *fileList)
{
    beginResetModel();

       if (m_fileList)
           m_fileList->disconnect(this);

       m_fileList = fileList;

       if (m_fileList) {
           connect(m_fileList, &FileList::preItemAppended, this, [=]() {
               const int index = m_fileList->count();        // Append implies end
               beginInsertRows(QModelIndex(), index, index);
           });
           connect(m_fileList, &FileList::postItemAppended, this, [=]() {
               endInsertRows();
           });

           connect(m_fileList, &FileList::preItemRemoved, this, [=](int index) {
               beginRemoveRows(QModelIndex(), index, index);
           });
           connect(m_fileList, &FileList::postItemRemoved, this, [=]() {
               endRemoveRows();
           });
           connect(m_fileList, &FileList::itemChanged,
                   this, [=](int row){ qDebug()<< "itemChanged " << row; emit FileModel::dataChanged(this->index(row), this->index(row)); });
       }

   endResetModel();
}



QHash<int, QByteArray> FileModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FileName] = "name";
    roles[Size]     = "size";
    roles[File]     = "file";

    return roles;
}

void FileModel::newElement()
{
    QString name(tr("Unknown"));
    QTextStream stream(&name);
    stream << "-" << m_fileList->count();

    m_fileList->createFile(name);
}

void FileModel::removeRow(int index)
{
    m_fileList->removeFile(index);
}

int FileModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if ( parent.isValid())
        return 0;

    return m_fileList->count();
}

QVariant FileModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto file = m_fileList->at(index.row());

    switch (role) {
    case FileName:
        return file->name();
    case Size:
        return file->size();
    case File:
        return QVariant::fromValue(file);
    default:
        break;
    }
    return QVariant();
}

bool FileModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) != value) {

        auto file = m_fileList->at(index.row());

        switch (role) {
        case FileName:
            file->setName(value.toString());
            emit dataChanged(index, index, QVector<int>() << role);
        default:
            break;
        }
        return true;
    }
    return false;
}

Qt::ItemFlags FileModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}
