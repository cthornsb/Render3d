# PreRequisites.cmake
# To use this macro in your project, simply use:
#  include(PreRequisites)
# somewhere in your cmake script. The following functions are available to
# easily include OtterEngine libraries in your project.
#  ott_use_core()  : Enable the use of 2d opengl graphics (requires opengl and glfw3) 
#  ott_use_3d()    : Enable the use of 2d and 3d opengl graphics (requires opengl, glfw3, glew, and soil)
#  ott_use_audio() : Enable the use of portaudio functionality (requires portaudio)
#  ott_find_all_packages() : Find all required packages (opengl, glfw3, glew, soil, and portaudio)
#  ott_find_glfw()         : Find glfw3
#  ott_find_opengl()       : Find opengl
#  ott_find_glew()         : Find glew
#  ott_find_soil()         : Find soil
#  ott_find_port_audio()   : Find portaudio

# Enable the use of libOtterCore
# Find packages glfw3 and OpenGL and set
# OTTER_INCLUDE_CORE
# OTTER_LIBRARIES
function(ott_use_core)
	set(OTTER_INCLUDE_CORE ${OTTER_DIRECTORY}/graphics/include PARENT_SCOPE)
	set(OTTER_LIBRARIES
		${OTTER_DIRECTORY}/install/lib/libOtterCore.so
		PARENT_SCOPE
	)		
	ott_find_glfw()
	ott_find_opengl()
endfunction()

# Enable the use of all 2d and 3d libraries
# Find packages glfw3, OpenGL, GLEW, and SOIL and set
# OTTER_INCLUDE_CORE
# OTTER_INCLUDE_3D
# OTTER_LIBRARIES
function(ott_use_3d)
	set(OTTER_INCLUDE_CORE ${OTTER_DIRECTORY}/graphics/include PARENT_SCOPE)
	set(OTTER_INCLUDE_3D ${OTTER_DIRECTORY}/include PARENT_SCOPE)
	set(OTTER_LIBRARIES 
		${OTTER_DIRECTORY}/install/lib/libOtterCore.so
		${OTTER_DIRECTORY}/install/lib/libOtter3dCore.so
		${OTTER_DIRECTORY}/install/lib/libOtter3dGeom.so
		${OTTER_DIRECTORY}/install/lib/libOtterGraphics.so
		${OTTER_DIRECTORY}/install/lib/libOtterMath.so
		PARENT_SCOPE
	)
	ott_find_glfw()
	ott_find_opengl()
	ott_find_glew()
	ott_find_soil()
endfunction()
	
# Enable the use of port audio libraries
# Find package portaudio and set
# OTTER_INCLUDE_AUDIO
# OTTER_LIBRARIES
function(ott_use_audio)
	set(OTTER_INCLUDE_AUDIO ${OTTER_DIRECTORY}/audio/include PARENT_SCOPE)
	set(OTTER_LIBRARIES 
		${OTTER_LIBRARIES}
		${OTTER_DIRECTORY}/install/lib/libOtterAudio.so
		PARENT_SCOPE
	)
	ott_find_port_audio()
endfunction()

# Find all required packages
function(ott_find_all_packages)
	ott_find_glfw()
	ott_find_opengl()
	ott_find_glew()
	ott_find_soil()
	ott_find_port_audio()
endfunction()

# Find OpenGL and GLU install
# Sets the variables:
# GLFW3_LIBRARY
# GLFW3_INCLUDE_DIR
function(ott_find_glfw)
	find_package(GLFW3 REQUIRED)
	message(STATUS "Found glfw3: ${GLFW3_LIBRARY}")
endfunction()

# Find OpenGL and GLU install
# Sets the variables:
# OPENGL_LIBRARIES (should also include GLU, use of OpenGL::* is recommended)
# OPENGL_INCLUDE_DIR
function(ott_find_opengl)
	find_package(OpenGL REQUIRED)
	message(STATUS "Found OpenGL: ${OPENGL_LIBRARIES}")
endfunction()

# Find GLEW install
# Sets the variables:
# GLEW_LIBRARIES (GLEW::glew)
# GLEW_SHARED_LIBRARIES
# GLEW_STATIC_LIBRARIES
# GLEW_INCLUDE_DIRS
function(ott_find_glew)
	find_package(GLEW REQUIRED)

	if(GLEW::glew)
		set(GLEW_LIBRARY GLEW::glew CACHE INTERNAL FORCE)
	elseif(GLEW::GLEW)
		set(GLEW_LIBRARY GLEW::GLEW CACHE INTERNAL FORCE)
	else()
		message(FATAL_ERROR "Failed to determine GLEW install location")
	endif()

	message(STATUS "Found GLEW: ${GLEW_LIBRARY}")
endfunction()

# Find SOIL install
# Sets the variables:
# SOIL_LIBRARY
# SOIL_INCLUDE_DIR
function(ott_find_soil)
	find_package(SOIL REQUIRED)
	message(STATUS "Found SOIL: ${SOIL_LIBRARY}")
endfunction()

# Find portaudio install
# Sets the variables:
# PORT_AUDIO_LIBRARY
# PORT_AUDIO_INCLUDE
function(ott_find_port_audio)
	find_package(PortAudio REQUIRED)
	message(STATUS "Found PortAudio: ${PORT_AUDIO_LIBRARY}")
endfunction()

