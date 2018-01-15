#ifndef QQTNETWORKMESSAGE_H
#define QQTNETWORKMESSAGE_H

#include "qqtmessage.h"

#define _TCPCMD_TAGHEAD                   0xAA55
#define _TCPCMD_TAGTAIL                   0xCC33C33C

class QQTNetworkMessage : public QQtMessage
{
    Q_OBJECT
public:
    explicit QQTNetworkMessage ( QObject* parent = 0 );

    const quint16& head() const;
    void setHead ( quint16 head );
    const quint16& size() const;
    void setSize ( quint16 size );
    const quint16& cmd() const;
    void setCmd ( quint16 cmd );
    const quint32& uid() const;
    void setUid ( quint32 uid );
    const QByteArray& data() const;
    void setData ( QByteArray& data );
    const quint16& sum() const;
    void setSum ( quint16 sum );
    const quint32& tail() const;
    void setTail ( quint32 tail );
    void translate();

signals:

public slots:

    // QQtMessage interface
public:

    void parser ( const QByteArray& l ) override;

    void packer ( QByteArray& l ) const override;
private:
    quint16 m_Head;
    quint16 m_Size;
    quint16 m_Cmd;
    quint32 m_Uid;
    QByteArray m_Data;
    quint16 m_Sum;
    quint32 m_Tail;


};

QDebug operator<< ( QDebug dbg, const QQTNetworkMessage& c );


#endif // QQTNETWORKMESSAGE_H
