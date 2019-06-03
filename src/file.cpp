#include "file.h"

File::File(QString name, int size, QObject *parent)
    : QObject(parent),
    m_name(name), m_size(size)
{
    connect(this, &File::nameChanged, this, &File::fileChanged );
    connect(this, &File::sizeChanged, this, &File::fileChanged );
}

QString File::name() const
{
    return m_name;
}

int File::size() const
{
    return m_size;
}

void File::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void File::setSize(int size)
{
    if (m_size == size)
        return;

    m_size = size;
    emit sizeChanged(m_size);
}
