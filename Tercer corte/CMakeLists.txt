cmake_minimum_required(VERSION 3.16)

project(RastreadorSalud
    VERSION 1.0
    LANGUAGES CXX
)

# Usa C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Busca Qt6 primero, si no, Qt5
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

# Necesario para que CMake procese las clases de Qt (moc, uic, etc.)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Archivos de código fuente
set(SOURCES
    main.cpp
    loginwindow.cpp
    mainwindow.cpp
    databasemanager.cpp
    utils.cpp
)

# Archivos de cabecera (opcional, pero ayuda a IDEs)
set(HEADERS
    loginwindow.h
    mainwindow.h
    databasemanager.h
    models.h
    utils.h
)

# Ejecutable (para Qt6 usamos qt_add_executable, para Qt5 add_executable normal)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RastreadorSalud
        ${SOURCES}
        ${HEADERS}
    )
else()
    add_executable(RastreadorSalud
        ${SOURCES}
        ${HEADERS}
        # ${UIS}
    )
endif()

# Enlazar con las librerías de Qt necesarias
target_link_libraries(RastreadorSalud
    PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        Qt${QT_VERSION_MAJOR}::Sql
)

# Ruta donde estará la BD (opcional, solo para tenerla cerca del ejecutable)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/data)
