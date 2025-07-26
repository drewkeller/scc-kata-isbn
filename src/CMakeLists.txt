set(SOURCES
    main.cpp
    Isbn.cpp
    Isbn.h
    )

target_sources(${PROJECT} PUBLIC ${SOURCES})
add_library(${PROJECT_LIB} STATIC ${SOURCES})
