#ifndef FILE_H
#define FILE_H

#include <QObject>

class File : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int size READ size WRITE setSize NOTIFY sizeChanged)

    QString m_name;
    int m_size;

public:
    explicit File(QString name, int size, QObject *parent = nullptr);

    QString name() const;
    int size() const;

signals:

    void nameChanged(QString name);

    void sizeChanged(int size);
    void fileChanged();

public slots:
    void setName(QString name);
    void setSize(int size);
};

#endif // FILE_H
