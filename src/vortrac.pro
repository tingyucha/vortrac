>######################################################################
# Automatically generated by qmake (2.00a) Thu Jul 21 17:39:59 2005
######################################################################

TEMPLATE = app
DEPENDPATH += . Config Grids GUI IO Radar
INCLUDEPATH += . GUI Config IO Radar
INCLUDEPATH += $$(RADX_INCLUDE) $$(NETCDF_INCLUDE) $$(ARMADILLO_INCLUDE) /usr/local/include
QMAKE_LIBDIR += $$(RADX_LIB) $$(NETCDF_LIB) $$(ARMADILLO_LIB)
#QMAKE_LFLAGS += -Wl,-rpath,$$(NETCDF_LIB)
QMAKE_CXXFLAGS += -std=c++0x
# Input
HEADERS += Threads/workThread.h \
           Threads/SimplexThread.h \
           Threads/VortexThread.h \
           DataObjects/VortexData.h \
           DataObjects/SimplexData.h \
           DataObjects/VortexList.h \
           DataObjects/SimplexList.h \
           DataObjects/Coefficient.h \
           DataObjects/Center.h \
           Config/Configuration.h \
           DataObjects/AnalyticGrid.h \
           DataObjects/CappiGrid.h \
           DataObjects/GriddedData.h \
           DataObjects/GriddedFactory.h \
           GUI/ConfigTree.h \
           GUI/ConfigurationDialog.h \
           GUI/MainWindow.h \
           GUI/AnalysisPage.h \
           GUI/GraphFace.h \
           GUI/KeyPicture.h \
           GUI/AbstractPanel.h \
           GUI/panels.h \
           GUI/DiagnosticPanel.h \
           GUI/RadarListDialog.h \
           GUI/StopLight.h \
           GUI/CappiDisplay.h \
           GUI/StormSignal.h \
           GUI/StartDialog.h \
           NRL/Hvvp.h \
           IO/Message.h \
           IO/Log.h \
           IO/ATCF.h \
           Radar/DateChecker.h \
           Radar/RadarFactory.h \
           Radar/LevelII.h \
           Radar/NcdcLevelII.h \
           Radar/RadxGrid.h \
           Radar/LdmLevelII.h \
           Radar/RadxData.h \
           Radar/AnalyticRadar.h \
           Radar/nexh.h \
           NRL/RadarQC.h \
           Radar/RadarData.h \
           Radar/Ray.h \
           Radar/Sweep.h \
           VTD/VTD.h \
           VTD/GVTD.h \
           VTD/GBVTD.h \
           VTD/mgbvtd.h \
           VTD/VTDFactory.h \
           Math/Matrix.h \
           ChooseCenter.h \
           Pressure/PressureData.h \
           Pressure/PressureList.h \
           Pressure/PressureFactory.h \
           Pressure/HWind.h \
           Pressure/AWIPS.h \
           Pressure/MADIS.h \
           Pressure/MADISFactory.h \
           Radar/FetchRemote.h \
           Batch/DriverBatch.h \
           Batch/BatchWindow.h \
           DriverAnalysis.h

SOURCES += main.cpp \
           Threads/workThread.cpp \
           Threads/SimplexThread.cpp \
           Threads/VortexThread.cpp \
           DataObjects/VortexData.cpp \
           DataObjects/SimplexData.cpp \
           DataObjects/VortexList.cpp \
           DataObjects/SimplexList.cpp \
           DataObjects/Coefficient.cpp \
           DataObjects/Center.cpp \
           Config/Configuration.cpp \
           DataObjects/AnalyticGrid.cpp \
           DataObjects/CappiGrid.cpp \
           DataObjects/GriddedData.cpp \
           DataObjects/GriddedFactory.cpp \
           GUI/ConfigTree.cpp \
           GUI/ConfigurationDialog.cpp \
           GUI/MainWindow.cpp \
           GUI/AnalysisPage.cpp \
           GUI/GraphFace.cpp \
           GUI/KeyPicture.cpp \
           GUI/AbstractPanel.cpp \
           GUI/panels.cpp \
           GUI/DiagnosticPanel.cpp \
           GUI/RadarListDialog.cpp \
           GUI/StopLight.cpp \
           GUI/CappiDisplay.cpp \
           GUI/StormSignal.cpp \
           GUI/StartDialog.cpp \
           NRL/Hvvp.cpp \
           IO/Message.cpp \
           IO/Log.cpp \
           IO/ATCF.cpp \
           Radar/DateChecker.cpp \
           Radar/RadarFactory.cpp \
           Radar/LevelII.cpp \
           Radar/NcdcLevelII.cpp \
           Radar/RadxGrid.cpp \
           Radar/LdmLevelII.cpp \
           Radar/RadxData.cpp \
           Radar/AnalyticRadar.cpp\
           NRL/RadarQC.cpp \
           Radar/RadarData.cpp \
           Radar/Ray.cpp \
           Radar/Sweep.cpp \
           VTD/VTD.cpp \
           VTD/GVTD.cpp \
           VTD/GBVTD.cpp \
           VTD/mgbvtd.cpp \
           VTD/VTDFactory.cpp \
           Math/Matrix.cpp \
           ChooseCenter.cpp \
           Pressure/PressureData.cpp \
           Pressure/PressureList.cpp \
           Pressure/PressureFactory.cpp \
           Pressure/HWind.cpp \
           Pressure/AWIPS.cpp \
           Pressure/MADIS.cpp \
           Pressure/MADISFactory.cpp \
           Radar/FetchRemote.cpp \
           Batch/DriverBatch.cpp \
           Batch/BatchWindow.cpp \
           DriverAnalysis.cpp
RESOURCES += vortrac.qrc
# LIBS += -ludunits2 -lRadx -lbz2 -larmadillo -lhdf5_cpp -lnetcdf_c++
LIBS += -lbz2 -larmadillo  -L/usr/local/lib -ludunits2 -lRadx -lnetcdf_c++ -lhdf5_cpp -lNcxx
QT += xml network widgets
CONFIG += debug
#CONFIG -= app_bundle
