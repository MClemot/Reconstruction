cmake_minimum_required(VERSION 3.1...3.14)
project( SooAlphaShape )

set (SOOSRC "D:/Stage/Git/SooNodes/Algorithms.cxx;D:/Stage/Git/SooNodes/Algorithms.h;D:/Stage/Git/SooNodes/GLScene.cxx;D:/Stage/Git/SooNodes/GLScene.h;D:/Stage/Git/SooNodes/GLViewer.cxx;D:/Stage/Git/SooNodes/GLViewer.h;D:/Stage/Git/SooNodes/Idle.cxx;D:/Stage/Git/SooNodes/Idle.h;D:/Stage/Git/SooNodes/Matrix4x4.cxx;D:/Stage/Git/SooNodes/Matrix4x4.h;D:/Stage/Git/SooNodes/Misc.cxx;D:/Stage/Git/SooNodes/Misc.h;D:/Stage/Git/SooNodes/MiscMath.cxx;D:/Stage/Git/SooNodes/MiscMath.h;D:/Stage/Git/SooNodes/Mouse.cxx;D:/Stage/Git/SooNodes/Mouse.h;D:/Stage/Git/SooNodes/Quaternion.h;D:/Stage/Git/SooNodes/Range.cxx;D:/Stage/Git/SooNodes/Range.h;D:/Stage/Git/SooNodes/SooAxes.cxx;D:/Stage/Git/SooNodes/SooAxes.h;D:/Stage/Git/SooNodes/SooBox.cxx;D:/Stage/Git/SooNodes/SooBox.h;D:/Stage/Git/SooNodes/SooCamera.cxx;D:/Stage/Git/SooNodes/SooCamera.h;D:/Stage/Git/SooNodes/SooCircle.cxx;D:/Stage/Git/SooNodes/SooCircle.h;D:/Stage/Git/SooNodes/SooColor.cxx;D:/Stage/Git/SooNodes/SooColor.h;D:/Stage/Git/SooNodes/SooDrawable.cxx;D:/Stage/Git/SooNodes/SooDrawable.h;D:/Stage/Git/SooNodes/SooDrawStyle.cxx;D:/Stage/Git/SooNodes/SooDrawStyle.h;D:/Stage/Git/SooNodes/SooGlutModel.cxx;D:/Stage/Git/SooNodes/SooGlutModel.h;D:/Stage/Git/SooNodes/SooGroup.cxx;D:/Stage/Git/SooNodes/SooGroup.h;D:/Stage/Git/SooNodes/SooGroupColor.cxx;D:/Stage/Git/SooNodes/SooGroupColor.h;D:/Stage/Git/SooNodes/SooGroupMaterial.cxx;D:/Stage/Git/SooNodes/SooGroupMaterial.h;D:/Stage/Git/SooNodes/SooGroupRender.cxx;D:/Stage/Git/SooNodes/SooGroupRender.h;D:/Stage/Git/SooNodes/SooLight.cxx;D:/Stage/Git/SooNodes/SooLight.h;D:/Stage/Git/SooNodes/SooMaterial.cxx;D:/Stage/Git/SooNodes/SooMaterial.h;D:/Stage/Git/SooNodes/SooNode.cxx;D:/Stage/Git/SooNodes/SooNode.h;D:/Stage/Git/SooNodes/SooPalette.cxx;D:/Stage/Git/SooNodes/SooPalette.h;D:/Stage/Git/SooNodes/SooPoints.cxx;D:/Stage/Git/SooNodes/SooPoints.h;D:/Stage/Git/SooNodes/SooSphere.cxx;D:/Stage/Git/SooNodes/SooSphere.h;D:/Stage/Git/SooNodes/SooSwitch.cxx;D:/Stage/Git/SooNodes/SooSwitch.h;D:/Stage/Git/SooNodes/SooTriangles.cxx;D:/Stage/Git/SooNodes/SooTriangles.h;D:/Stage/Git/SooNodes/Trackball.cxx;D:/Stage/Git/SooNodes/Trackball.h;D:/Stage/Git/SooNodes/types-cgal.h;D:/Stage/Git/SooNodes/Vector3D.cxx;D:/Stage/Git/SooNodes/Vector3D.h;")

file(GLOB SRC "*.h" "*.cxx")

add_executable ( SooAlphaShape ${SOOSRC} ${SRC})

target_include_directories (SooAlphaShape PUBLIC "D:/Stage/Git/SooNodes/")
target_include_directories (SooAlphaShape PUBLIC "D:/Stage/Git/SooNodes_AlphaShape/")

find_package( Boost )
if(Boost_FOUND)
   target_include_directories (SooAlphaShape PUBLIC ${Boost_INCLUDE_DIR})
   target_link_libraries (SooAlphaShape ${Boost_LIBRARIES})
endif()

find_package( FLTK REQUIRED )
if(FLTK_FOUND)
   target_include_directories (SooAlphaShape PUBLIC ${FLTK_INCLUDE_DIR})
   target_link_libraries (SooAlphaShape ${FLTK_LIBRARIES})
endif()

find_package( OpenGL REQUIRED )
if(OpenGL_FOUND)
   target_include_directories (SooAlphaShape PUBLIC ${OPENGL_INCLUDE_DIR})
   target_link_libraries (SooAlphaShape ${OPENGL_LIBRARIES})
endif()

find_package( TIFF REQUIRED )
if(TIFF_FOUND)
   target_include_directories (SooAlphaShape PUBLIC ${TIFF_INCLUDE_DIR})
   target_link_libraries (SooAlphaShape ${TIFF_LIBRARIES})
endif()

find_package(Eigen3)
target_include_directories(SooAlphaShape PUBLIC ${EIGEN3_INCLUDE_DIR} )

find_package(CGAL)
find_package(GMP)
find_package(MPFR)
target_link_libraries (SooAlphaShape ${GMP_LIBRARIES})
target_link_libraries (SooAlphaShape ${MPFR_LIBRARIES})

target_include_directories(SooAlphaShape PUBLIC "D:/dev/gudhi.3.4.1/include/")

target_compile_definitions(SooAlphaShape PRIVATE _USE_MATH_DEFINES=1)