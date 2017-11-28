#-------------------------------------------------------------
#user computer path settings
#-------------------------------------------------------------
#deploy root
equals(QMAKE_HOST.os, Darwin) {
    APP_DEPLOY_ROOT = $$PWD/../..
} else: equals(QMAKE_HOST.os, Linux) {
    APP_DEPLOY_ROOT = $$PWD/../..
} else: equals(QMAKE_HOST.os, Windows) {
    APP_DEPLOY_ROOT = $$PWD/../..
}

