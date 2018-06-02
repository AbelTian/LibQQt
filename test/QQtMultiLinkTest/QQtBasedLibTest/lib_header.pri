#---------------------------------------------------------------
#lib_header.pri
#你可以通过这个文件告诉lib用户，这个文件不要修改
#---------------------------------------------------------------

#################################################################
##definition and configration
##need QSYS
#################################################################
#...

##################################################################
##include directories
##################################################################
defineReplace(lib_header){
    path = $$1
    !isEmpty(2) : error("lib_header(path) requires one arguments.")
    isEmpty(1) : error("lib_header(path) requires one arguments.")

    #basic
    command += $${path}

    return ($$command)
}

#= INCLUDEPATH += $$lib_header($$PWD)
add_headers( $$lib_header($$PWD) )
message($$INCLUDEPATH)
