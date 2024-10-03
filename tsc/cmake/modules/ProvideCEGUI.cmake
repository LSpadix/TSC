# Needs to set CEGUI_LIBRARIES and CEGUI_INCLUDE_DIR

# -Wno-dev -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${TSC_BINARY_DIR}/cegui -DCEGUI_BUILD_IMAGECODEC_DEVIL=ON -DCEGUI_BUILD_IMAGECODEC_SDL2=OFF -DCEGUI_BUILD_IMAGECODEC_FREEIMAGE=OFF -DCEGUI_BUILD_STATIC_CONFIGURATION=ON -DCEGUI_BUILD_PYTHON_MODULES=OFF -DCEGUI_BUILD_LUA_MODULE=OFF -DCEGUI_BUILD_XMLPARSER_EXPAT=ON -DCEGUI_BUILD_XMLPARSER_LIBXML2=OFF -DCEGUI_BUILD_XMLPARSER_RAPIDXML=OFF -DCEGUI_BUILD_XMLPARSER_XERCES=OFF -DCEGUI_BUILD_XMLPARSER_TINYXML=OFF -DCEGUI_BUILD_RENDERER_OPENGL=ON -DCEGUI_BUILD_RENDERER_OPENGL3=OFF -DCEGUI_BUILD_RENDERER_OPENGLES=OFF -DCEGUI_BUILD_RENDERER_DIRECT3D1=OFF -DCEGUI_BUILD_RENDERER_DIRECT3D9=OFF -DCEGUI_BUILD_RENDERER_DIRECTFB=OFF -DCEGUI_BUILD_RENDERER_IRRLICHT=OFF -DCEGUI_BUILD_RENDERER_NULL=ON -DCEGUI_BUILD_RENDERER_OGRE=OFF -DCEGUI_SAMPLES_ENABLED=OFF -DCEGUI_BUILD_PYTHON_MODULES_PYPLUSPLUS=OFF -DCEGUI_BUILD_PYTHON_MODULES_SWIG=OFF -DCEGUI_BUILD_SAMPLES=OFF -DCEGUI_BUILD_APPLICATION_TEMPLATES=OFF

find_package(DevIL REQUIRED)
find_package(Freetype REQUIRED)
find_package(EXPAT REQUIRED)
find_package(GLEW REQUIRED)

ExternalProject_Add(
  cegui
  DOWNLOAD_COMMAND ${CMAKE_COMMAND} -E copy_directory "${TSC_SOURCE_DIR}/../cegui" "${TSC_BINARY_DIR}/cegui-source"
  SOURCE_DIR "${TSC_BINARY_DIR}/cegui-source"
  BINARY_DIR "${TSC_BINARY_DIR}/cegui-build"
  INSTALL_DIR "${TSC_BINARY_DIR}/cegui-install"
  PATCH_COMMAND patch -p1 < "${TSC_SOURCE_DIR}/../cegui-cpp11.patch" && patch -p1 < "${TSC_SOURCE_DIR}/../cegui-fix-factorymodule.patch"
  CMAKE_ARGS -Wno-dev -DCMAKE_BUILD_TYPE=Release "-DCMAKE_INSTALL_PREFIX=${TSC_BINARY_DIR}/cegui-install" -DCEGUI_BUILD_IMAGECODEC_DEVIL=ON -DCEGUI_BUILD_IMAGECODEC_SDL2=OFF -DCEGUI_BUILD_IMAGECODEC_FREEIMAGE=OFF -DCEGUI_BUILD_STATIC_CONFIGURATION=ON -DCEGUI_BUILD_PYTHON_MODULES=OFF -DCEGUI_BUILD_LUA_MODULE=OFF -DCEGUI_BUILD_XMLPARSER_EXPAT=ON -DCEGUI_BUILD_XMLPARSER_LIBXML2=OFF -DCEGUI_BUILD_XMLPARSER_RAPIDXML=OFF -DCEGUI_BUILD_XMLPARSER_XERCES=OFF -DCEGUI_BUILD_XMLPARSER_TINYXML=OFF -DCEGUI_BUILD_RENDERER_OPENGL=ON -DCEGUI_BUILD_RENDERER_OPENGL3=OFF -DCEGUI_BUILD_RENDERER_OPENGLES=OFF -DCEGUI_BUILD_RENDERER_DIRECT3D1=OFF -DCEGUI_BUILD_RENDERER_DIRECT3D9=OFF -DCEGUI_BUILD_RENDERER_DIRECTFB=OFF -DCEGUI_BUILD_RENDERER_IRRLICHT=OFF -DCEGUI_BUILD_RENDERER_NULL=ON -DCEGUI_BUILD_RENDERER_OGRE=OFF -DCEGUI_SAMPLES_ENABLED=OFF -DCEGUI_BUILD_PYTHON_MODULES_PYPLUSPLUS=OFF-DCEGUI_BUILD_PYTHON_MODULES_SWIG=OFF -DCEGUI_BUILD_SAMPLES=OFF -DCEGUI_BUILD_APPLICATION_TEMPLATES=OFF)

set(CEGUI_LIBRARIES "${TSC_BINARY_DIR}/cegui-install/lib/libCEGUIOpenGLRenderer-0_Static.a"
  "${TSC_BINARY_DIR}/cegui-install/lib/libCEGUIBase-0_Static.a"
  "${TSC_BINARY_DIR}/cegui-install/lib/libCEGUICoreWindowRendererSet_Static.a"
  "${TSC_BINARY_DIR}/cegui-install/lib/libCEGUIExpatParser_Static.a"
  "${TSC_BINARY_DIR}/cegui-install/lib/libCEGUIDevILImageCodec_Static.a"
  "${IL_LIBRARIES}"
  "${EXPAT_LIBRARIES}"
  "${FREETYPE_LIBRARIES}"
  "${GLEW_LIBRARIES}")

set(CEGUI_INCLUDE_DIR "${TSC_BINARY_DIR}/cegui-install/include/cegui-0")
