#ifndef QQTVERSION_H
#define QQTVERSION_H

#define PRODUCT_ICON              "qqt.ico"

#define _STR(VAR) #VAR
#define STR(VAR) _STR(VAR)
#define _COMMASTR(VAR1, VAR2) VAR1##,##VAR2
#define COMMASTR(VAR1, VAR2) _COMMASTR(VAR1, VAR2)

#define PRODUCT_VERSION_MAJOR     0
#define PRODUCT_VERSION_MINOR     0
#define PRODUCT_VERSION_PATCH     0
#define PRODUCT_VERSION_BUILD     0

#define PRODUCT_VERSION           COMMASTR(COMMASTR(PRODUCT_VERSION_MAJOR, PRODUCT_VERSION_MINOR), PRODUCT_VERSION_PATCH)
#define FILE_VERSION              COMMASTR(PRODUCT_VERSION, PRODUCT_VERSION_BUILD)

#define FILE_VERSION_STR          STR(FILE_VERSION)
#define PRODUCT_VERSION_STR       STR(PRODUCT_VERSION)
#define PRODUCT_VERSION_MAJOR_STR STR(PRODUCT_VERSION_MAJOR)

#define FILE_DESCRIPTION          "QQt"
#define PRODUCT_NAME              "QQt"
#define COMPANY_NAME              "QQt"
#define INTERNAL_NAME             "QQt"
#define ORIGINAL_FILE_NAME        "QQt"
#define LEGAL_COPYRIGHT           "Copyright 2015-2020 QQt Co., Ltd."
#define LEGAL_TRADE_MARKS1        "All rights reserved"
#define LEGALTRADEMARKS2          "All rights reserved"

#define COMPANY_DOMAIN            "www.QQt.com"

#endif // QQTVERSION_H
