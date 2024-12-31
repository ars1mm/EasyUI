get_filename_component(EASYUI_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(CMakeFindDependencyMacro)

if(NOT TARGET EasyUI::easyui)
    include("${EASYUI_CMAKE_DIR}/EasyUITargets.cmake")
endif()

set(EASYUI_LIBRARIES EasyUI::easyui)
set(EASYUI_INCLUDE_DIRS "${EASYUI_CMAKE_DIR}/../include")
set(EASYUI_FOUND TRUE)
