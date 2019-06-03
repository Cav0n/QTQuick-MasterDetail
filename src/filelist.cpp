#include "filelist.h"
#include "file.h"

#include <QDir>

FileList::FileList(QString path, QObject *parent) : QObject(parent)
{
    QDir dir(path);

    QFileInfoList files = dir.entryInfoList( QDir::AllEntries | QDir::NoDotAndDotDot );
    for ( QFileInfo file : files )
        append( new File(file.baseName(), file.size()) );
}

void FileList::append(File *file)
{
    emit preItemAppended();
    int position = count();
    connect(file, &File::fileChanged, this, [=](){ emit FileList::itemChanged( position ); } );
    m_files.append(file);    
    emit postItemAppended();
}

File *FileList::at(int place) const
{
    return m_files.at(place);
}

int FileList::count() const
{
    return m_files.count();
}

void FileList::createFile(QString name)
{
    append(new File(name, 66) );
}

void FileList::removeFile(int position)
{
    emit preItemRemoved(position);

    // No longer care for the file change
    disconnect ( m_files[position], &File::fileChanged, this, 0);

    m_files.removeAt(position);

    // Reconnect to good positions
    for ( ; position < count() ; ++position ) {
        disconnect ( m_files[position], &File::fileChanged, this, 0);
        connect( m_files[position], &File::fileChanged, this, [=](){ emit FileList::itemChanged( position ); } );
    }
    emit postItemRemoved();
}
