CONFIG      +=  qt exceptions warn_off thread 
TEMPLATE    =  app
TARGET      =  datetime_test 
DESTDIR     =  ../../bin/

SOURCES +=     \
    main.cpp \
     
INCLUDEPATH     += $$(POCO_ROOT)/include \

QMAKE_LIBDIR    += $$(POCO_ROOT)/lib\
								
LIBS    +=      -lPocoFoundation\
                -lPocoUtil\
                -lPocoJSON\
                -lPocoNet\
                      


