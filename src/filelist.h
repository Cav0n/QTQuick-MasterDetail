#ifndef FILELIST_H
#define FILELIST_H

#include <QObject>
#include <QList>

class File;

class FileList : public QObject
{
    Q_OBJECT
    QList<File*> m_files;
public:
    explicit FileList(QString path, QObject *parent = nullptr);

    void append(File* file);
    File *at(int place) const;
    int count() const;
    void createFile(QString name);
    void removeFile(int position);

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

    void itemChanged(int row);

public slots:
};



#endif // FILELIST_H
