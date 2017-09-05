#ifndef QQTSERIALMESSAGE_H
#define QQTSERIALMESSAGE_H

#include "qqtmessage.h"


#define _SERIAL_HEAD            0xAA55
#define _SERIAL_TAIL            0xCC33

class QQTSerialMessage : public QQTMessage
{
public:
    explicit QQTSerialMessage(QObject* parent = 0);

    const quint16& head() const;
    void setHead(quint16 head);
    const quint16& size() const;
    void setSize(quint16 size);
    //user
    const quint16& cmd() const;
    void setCmd(quint16 cmd);
    //user
    const QByteArray& data() const;
    void setData(QByteArray& data);
    const quint16& sum() const;
    void setSum(quint16 sum);
    const quint16& tail() const;
    void setTail(quint16 tail);
    void translate();

    // QQTSyntax interface
public:
    void parser(const QByteArray &l) override;
    void packer(QByteArray &l) override;
private:
    quint16 m_Head;
    quint16 m_Size;
    quint16 m_Cmd;
    QByteArray m_Data;
    quint16 m_Sum;
    quint16 m_Tail;
};

QDebug operator<< (QDebug dbg, const QQTSerialMessage &c);

#endif // QQTSERIALMESSAGE_H
