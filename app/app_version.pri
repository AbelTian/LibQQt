#################################################################
##project $${TARGET} version pri
#################################################################

APP_MAJOR_VERSION = 0
APP_MINOR_VERSION = 0
APP_PATCH_VERSION = 0
APP_BUILD_VERSION = 0

APP_VERSION = $${APP_MAJOR_VERSION}.$${APP_MINOR_VERSION}.$${APP_PATCH_VERSION}
APP_VERSION4 = $${APP_MAJOR_VERSION}.$${APP_MINOR_VERSION}.$${APP_PATCH_VERSION}.$${APP_BUILD_VERSION}
DEFINES += APP_VERSION=$${APP_VERSION}
message (Build $${TARGET} version: $$APP_VERSION4)
unix:VERSION = $${APP_VERSION}
