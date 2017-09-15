function( msglist INPUTS )
	foreach(src ${INPUTS})
		message( ${src} )
	endforeach(src)
endfunction( msglist INPUTS )

macro( filter_out FILTERS INPUTS OUTPUTS )
    set( FOUT "" )
    foreach( INP ${INPUTS} )
        set( FILTERED 0 )
        foreach( FILT ${FILTERS} )
            if( ${FILTERED} EQUAL 0 )
                if( "${FILT}" STREQUAL "${INP}" )
                    set( FILTERED 1 )
                endif( "${FILT}" STREQUAL "${INP}" )
                if( ${INP} MATCHES ${FILT} )
                    set( FILTERED 1 )
                endif( ${INP} MATCHES ${FILT} )
            endif( ${FILTERED} EQUAL 0 )
        endforeach( FILT ${FILTERS} )
        if( ${FILTERED} EQUAL 0 )
            set( FOUT ${FOUT} ${INP} )
        endif( ${FILTERED} EQUAL 0 )
    endforeach( INP ${INPUTS} )
    set( ${OUTPUTS} ${FOUT} )
endmacro( filter_out FILTERS INPUTS OUTPUTS )

macro(find_framework frameworkname frameworkpath)
    find_library(FRAMEWORK_${frameworkname}
    NAMES ${frameworkname}
    PATHS ${CMAKE_OSX_SYSROOT}/System/Library
    PATH_SUFFIXES Frameworks
    NO_DEFAULT_PATH)
    if( ${FRAMEWORK_${frameworkname}} STREQUAL FRAMEWORK_${frameworkname}-NOTFOUND)
        #MESSAGE(ERROR ": Framework ${frameworkname} not found")
    else()
        set ( ${frameworkpath}  ${FRAMEWORK_${frameworkname}})
        #MESSAGE(STATUS "Framework ${frameworkname} found at ${FRAMEWORK_${frameworkname}}")
    endif()
endmacro(find_framework)

macro(link_framework projectname)
    set(macOSFrameworks Cocoa IOKit DiskArbitration)
    foreach(loop_var ${macOSFrameworks})
        #message(${loop_var})
        find_framework (${loop_var} frameworkpath)
        target_link_libraries(${projectname} ${frameworkpath})
    endforeach(loop_var)
endmacro(link_framework)


macro(link_qt5_libraries projectname)
    set(Qt5Libs Core Widgets Gui Xml Sql Network PrintSupport SerialPort)
    foreach(loop_var ${Qt5Libs})
        #message(Qt5${loop_var})
        find_package(Qt5${loop_var})
        target_link_libraries(${projectname} Qt5::${loop_var})
    endforeach(loop_var)
endmacro(link_qt5_libraries)

#todo: need test
macro(link_qt4_libraries projectname)
    set(Qt4Libs Core Widgets Gui Xml Sql Network PrintSupport SerialPort)
    foreach(loop_var ${Qt4Libs})
        #message(Qt4${loop_var})
        find_package(Qt4${loop_var})
        target_link_libraries(${projectname} Qt4::${loop_var})
    endforeach(loop_var)
endmacro(link_qt4_libraries)

macro (link_qt_libraries projectname)
    if(QT5)
        link_qt5_libraries(${projectname})
    elseif(QT4)
        link_qt4_libraries(${projectname})
    endif()
endmacro(link_qt_libraries)

macro (install_mac_framework projectname)
    install( TARGETS ${projectname}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
endmacro(install_mac_framework)
