#ifndef QQTNETWORKDEFINE_H
#define QQTNETWORKDEFINE_H

#include <qqtprotocolmanager.h>

#include <qqtprotocol.h>
#include <qqtmessage.h>

#include <qqttcpclient.h>
#include <qqttcpserver.h>

#include <qqtudpclient.h>
#include <qqtudpserver.h>

#include <qqtserialport.h>

#ifdef __BLUETOOTH__
#include <qqtbluetoothclient.h>
#include <qqtbluetoothserver.h>
#include <qqtbluetoothmanager.h>
#endif

#ifdef __WEBSOCKETSUPPORT__
#include <qqtwebsocketclient.h>
#include <qqtwebsocketserver.h>
#endif

#ifdef __WEBACCESSSUPPORT__
#include <qqtwebaccessmanager.h>
#endif

#endif // QQTNETWORKDEFINE_H
