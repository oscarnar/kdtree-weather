cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

project(weather)

find_package(VTK COMPONENTS 
  vtkCommonColor
  vtkCommonCore
  vtkCommonDataModel
  vtkFiltersSources
  vtkFiltersGeneral
  vtkInteractionWidgets
  vtkInteractionStyle
  vtkRenderingCore
  vtkRenderingFreeType
  vtkRenderingOpenGL2 QUIET)
file(GLOB_RECURSE sources *.cpp *.h)
if (NOT VTK_FOUND)
  message("Skipping weather: ${VTK_NOT_FOUND_MESSAGE}")
  return ()
endif()
message (STATUS "VTK_VERSION: ${VTK_VERSION}")
if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  add_executable(Weather MACOSX_BUNDLE weather.cpp )
  target_link_libraries(Weather PRIVATE ${VTK_LIBRARIES})
else ()
  # include all components
  add_executable(Weather MACOSX_BUNDLE weather.cpp )
  target_link_libraries(Weather PRIVATE ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS weather
    MODULES ${VTK_LIBRARIES}
    )
endif () 
