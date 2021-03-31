
#================================
# preset
#================================
# VS_DPI_AWARE from 3.16
cmake_minimum_required(VERSION 3.18)

#================================
# project setting
#================================
project(nidonehsp LANGUAGES C CXX)
message("Building for ... ${CMAKE_SYSTEM_NAME}")

#================================
# build setting
#================================
# default setting
if(EMSCRIPTEN)
	set(N2_BUILD_INTERPRETER_DEFAULT OFF)
	set(N2_BUILD_STUDIO_DEFAULT OFF)
else()
	set(N2_BUILD_INTERPRETER_DEFAULT ON)
	set(N2_BUILD_STUDIO_DEFAULT ON)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	set(N2_BUILD_TYPE_RELEASE_DEFAULT OFF)
else()
	set(N2_BUILD_TYPE_RELEASE_DEFAULT ON)
endif()

# options
option(N2_BUILD_SDL "Enable SDL" ON)

option(N2_SUPPORT_RPMALLC "Enable fast malloc(rpmalloc.h)" ON)
option(N2_SUPPORT_IMAGE_RW "Enable Image Read/Write(stb_image.h/stb_image_write,h)" ON)
option(N2_SUPPORT_ASEPRITE "Enable Aseprite Read(cute_aseprite.h)" ON)
option(N2_SUPPORT_AUDIO_WAV "Enable Audio WAV format(dr_wav.h)" ON)
option(N2_SUPPORT_AUDIO_MP3 "Enable Audio MP3 format(dr_mp3.h)" ON)
option(N2_SUPPORT_AUDIO_OGG "Enable Audio OGG format(stb_vorbis.h)" ON)
option(N2_SUPPORT_AUDIO_FLAC "Enable Audio FLAC format(dr_flac.h)" OFF)
option(N2_SUPPORT_FONT "Enable Font(stb_rect_pack.h/stb_truetype.h)" ON)
option(N2_SUPPORT_Z "Enable Z Compression & Zip(miniz.h)" ON)
option(N2_SUPPORT_ULZ "Enable ULZ Compression(ulz.h)" ON)
option(N2_SUPPORT_JSON "Enable Json(json.h)" ON)
option(N2_SUPPORT_CP932 "Enable cp932" ON)
option(N2_ENABLE_STANDARD "Enable nidonehsp Standard Features" ON)

option(N2_BUILD_TYPE_RELEASE "Release Build Type" N2_BUILD_TYPE_RELEASE_DEFAULT)
option(N2_BUILD_AS_LIB "Build as Library" OFF)
option(N2_BUILD_INTERPRETER "Build Interpreter" ${N2_BUILD_INTERPRETER_DEFAULT})
option(N2_BUILD_STUDIO "Build Studio" ${N2_BUILD_STUDIO_DEFAULT})
option(N2_BUILD_RUNTIME_STANDARD "Build Runtime(Standard)" ON)
option(N2_BUILD_TEST "Build Test" OFF)

# fixed
set(N2_SUPPORT_MSGPACK ON)
set(N2_SUPPORT_MD5 ON)
set(N2_SUPPORT_AES ON)

#================================
# common setting
#================================
# lib
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
if (NOT DEFINED CMAKE_POSITION_INDEPENDENT_CODE)
	set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

# msvc specific setting
if(MSVC)
	# use new style runtime library specification
	cmake_policy(SET CMP0091 NEW)

	# all config
	foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
		string(TOUPPER ${CONFIG} CONFIG )

		# output dir
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG} ${CMAKE_BINARY_DIR}/lib)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG} ${CMAKE_BINARY_DIR}/lib)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG} ${CMAKE_BINARY_DIR}/bin)

		# static link <= old style
		if(CMAKE_C_FLAGS_${CONFIG} MATCHES "/MD")
			string(REGEX REPLACE "/MD" "/MT" CMAKE_C_FLAGS_${CONFIG} "${CMAKE_C_FLAGS_${CONFIG}}")
		else()
			string(APPEND CMAKE_C_FLAGS_${CONFIG} " /MT")
		endif()
		if(CMAKE_CXX_FLAGS_${CONFIG} MATCHES "/MD")
			string(REGEX REPLACE "/MD" "/MT" CMAKE_CXX_FLAGS_${CONFIG} "${CMAKE_CXX_FLAGS_${CONFIG}}")
		else()
			string(APPEND CMAKE_CXX_FLAGS_${CONFIG} " /MT")
		endif()

		# runtime checks
		#string(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	endforeach()
else()
	# we use c99
	set(CMAKE_C_STANDARD 99)
endif()

# external library root
set(EXTERNAL_LIB_DIR ${CMAKE_SOURCE_DIR}/external)

#================================
# nidonehsp common
#================================
set(NIDONEHSP_COMMON_DIR ${CMAKE_SOURCE_DIR}/nidonehsp)

set(NIDONEHSP_COMMON_SRC
	${NIDONEHSP_COMMON_DIR}/nidonehsp.c 
)

set(NIDONEHSP_COMMON_HDR
	${NIDONEHSP_COMMON_DIR}/nidonehsp.h 
)

set(NIDONEHSP_EMBED_SRC
	${NIDONEHSP_COMMON_DIR}/embed/glad.c 
	${NIDONEHSP_COMMON_DIR}/embed/aes.c 
)

set(NIDONEHSP_EMBED_HDR
	${NIDONEHSP_COMMON_DIR}/embed/stb_sprintf.h 
	${NIDONEHSP_COMMON_DIR}/embed/rpmalloc.h 
	${NIDONEHSP_COMMON_DIR}/embed/stb_image.h 
	${NIDONEHSP_COMMON_DIR}/embed/stb_image_write.h 
	${NIDONEHSP_COMMON_DIR}/embed/cute_aseprite.h 
	${NIDONEHSP_COMMON_DIR}/embed/dr_wav.h 
	${NIDONEHSP_COMMON_DIR}/embed/dr_mp3.h 
	${NIDONEHSP_COMMON_DIR}/embed/stb_vorbis.h 
	${NIDONEHSP_COMMON_DIR}/embed/dr_flac.h 
	${NIDONEHSP_COMMON_DIR}/embed/stb_rect_pack.h 
	${NIDONEHSP_COMMON_DIR}/embed/stb_truetype.h 
	${NIDONEHSP_COMMON_DIR}/embed/miniz.h 
	${NIDONEHSP_COMMON_DIR}/embed/culz.h 
	${NIDONEHSP_COMMON_DIR}/embed/json.h 
	${NIDONEHSP_COMMON_DIR}/embed/nuklear.h 
	${NIDONEHSP_COMMON_DIR}/embed/glad_gles3.h 
	${NIDONEHSP_COMMON_DIR}/embed/zed_net.h 
	${NIDONEHSP_COMMON_DIR}/embed/gif.h 
	${NIDONEHSP_COMMON_DIR}/embed/tre.h 
	${NIDONEHSP_COMMON_DIR}/embed/picomsgpack.h 
	${NIDONEHSP_COMMON_DIR}/embed/md5.h 
	${NIDONEHSP_COMMON_DIR}/embed/aes.h 
)

set(NIDONEHSP_INLINE_HDR
	${NIDONEHSP_COMMON_DIR}/inline/shader.h 
	${NIDONEHSP_COMMON_DIR}/inline/cp932.h 
	${NIDONEHSP_COMMON_DIR}/inline/mplus_2m_regular_generalj.h 
	${NIDONEHSP_COMMON_DIR}/inline/mplus_2m_medium_generalj.h 
	${NIDONEHSP_COMMON_DIR}/inline/fa_regular_400.h 
	${NIDONEHSP_COMMON_DIR}/inline/fa_regular_mapping.h 
	${NIDONEHSP_COMMON_DIR}/inline/fa_regular_mapping_none.h 
	${NIDONEHSP_COMMON_DIR}/inline/fa_solid_900.h 
	${NIDONEHSP_COMMON_DIR}/inline/fa_solid_mapping.h 
	${NIDONEHSP_COMMON_DIR}/inline/fa_solid_mapping_none.h 
)

set(NIDONEHSP_ICON
	${CMAKE_SOURCE_DIR}/build/icon.ico
)

#================================
# nidonehsp app common
#================================
set(NIDONEHSP_APP_DIR ${CMAKE_SOURCE_DIR}/src)

# src header
set(NIDONEHSP_APP_HDR
	${NIDONEHSP_APP_DIR}/app.h 
)

# app std build condition
if(N2_ENABLE_STANDARD AND
	N2_SUPPORT_FONT AND N2_SUPPORT_Z AND N2_SUPPORT_ULZ AND
	N2_SUPPORT_MSGPACK AND N2_SUPPORT_AES)
	set(N2_APP_STD_BUILD ON)
else()
	set(N2_APP_STD_BUILD OFF)
endif()

# common function
function(n2_set_app_common target)
	# set common macros
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_SDL_LIB=$<BOOL:${N2_BUILD_SDL}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_RPMALLOC_LIB=$<BOOL:${N2_SUPPORT_RPMALLC}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_IMAGE_READ_LIB=$<BOOL:${N2_SUPPORT_IMAGE_RW}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_IMAGE_WRITE_LIB=$<BOOL:${N2_SUPPORT_IMAGE_RW}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_ASEPRITE_LIB=$<BOOL:${N2_SUPPORT_ASEPRITE}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_AUDIO_WAV_LIB=$<BOOL:${N2_SUPPORT_AUDIO_WAV}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_AUDIO_MP3_LIB=$<BOOL:${N2_SUPPORT_AUDIO_MP3}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_AUDIO_OGG_LIB=$<BOOL:${N2_SUPPORT_AUDIO_OGG}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_AUDIO_FLAC_LIB=$<BOOL:${N2_SUPPORT_AUDIO_FLAC}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_FONT_LIB=$<BOOL:${N2_SUPPORT_FONT}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_Z_LIB=$<BOOL:${N2_SUPPORT_Z}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_ULZ_LIB=$<BOOL:${N2_SUPPORT_ULZ}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_JSON_LIB=$<BOOL:${N2_SUPPORT_JSON}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_MSGPACK_LIB=$<BOOL:${N2_SUPPORT_MSGPACK}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_MD5_LIB=$<BOOL:${N2_SUPPORT_MD5}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_AES_LIB=$<BOOL:${N2_SUPPORT_AES}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_ENCODING_CP932=$<BOOL:${N2_SUPPORT_CP932}>)
	target_compile_definitions(${target} PUBLIC N2_CONFIG_USE_N2_STANDARD=$<BOOL:${N2_ENABLE_STANDARD}>)

	# set common include
	target_include_directories(${target} BEFORE PRIVATE ${CMAKE_SOURCE_DIR}/nidonehsp)

	if(MSVC)
		# supress secure warnings
		target_compile_definitions(${target} PRIVATE _CRT_SECURE_NO_WARNINGS)
		target_compile_definitions(${target} PRIVATE _CRT_NONSTDC_NO_DEPRECATE)
		target_compile_definitions(${target} PRIVATE _WINSOCK_DEPRECATED_NO_WARNINGS)

		# force use utf8
		#target_compile_definitions(${target} PRIVATE UNICODE)
		#target_compile_definitions(${target} PRIVATE _UNICODE)
		target_compile_options(${target} PRIVATE "/utf-8")
		#target_compile_options(${target} PRIVATE "/source-charset:utf-8")

		# static link
		set_property(TARGET ${target} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	endif()

	# max warning level
	if(NOT N2_BUILD_TYPE_RELEASE)
		if(MSVC)
			#target_compile_options(${target} PRIVATE /W4 /WX)
			target_compile_options(${target} PRIVATE /W4)
		else()
			#target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic -Werror)
			target_compile_options(${target} PRIVATE -Wall)
		endif()
	endif()
endfunction()

function(n2_set_app_std target)
	n2_set_app_common(${target})

	if(MSVC)
		# hidpi
		set_property(TARGET ${target} PROPERTY VS_DPI_AWARE "PerMonitor")
		#set_property(TARGET ${target} PROPERTY VS_DPI_AWARE "ON")
	endif()
endfunction()

#================================
# sdl2
#================================
if(N2_BUILD_SDL AND NOT EMSCRIPTEN)
	# required flag for win
	if(WIN32)
		set(HAVE_LIBC TRUE)
	endif()

	set(SDL_STATIC ON CACHE BOOL "" FORCE)
	set(SDL_SHARED OFF CACHE BOOL "" FORCE)
	set(FORCE_STATIC_VCRT ON CACHE BOOL "" FORCE)

	# from submodule
	add_subdirectory(${EXTERNAL_LIB_DIR}/sdl2)

	# runtime library
	if(MSVC)
		set_property(TARGET SDL2main PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
		set_property(TARGET SDL2-static PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	endif()
endif()

#================================
# as lib
#================================
if(N2_BUILD_AS_LIB)
	n2_set_app_common(n2lib)

	add_library(n2lib STATIC ${NIDONEHSP_COMMON_SRC})

	if(N2_BUILD_SDL)
		target_include_directories(
			n2lib PRIVATE 
			${EXTERNAL_LIB_DIR}/sdl2/include 
		)

		target_link_libraries(n2lib PRIVATE SDL2-static SDL2main)
	endif()
endif()

#[[
#================================
# interpreter
#================================
if(N2_BUILD_INTERPRETER AND NOT EMSCRIPTEN)
	add_executable(n2i ${CMAKE_SOURCE_DIR}/src/interpreter.c ${NIDONEHSP_COMMON_SRC})

	n2_set_app_common(n2i)

	target_compile_definitions(n2i PUBLIC N2_CONFIG_USE_DEBUGGING=1)
	target_compile_definitions(n2i PUBLIC N2_CONFIG_USE_PROFILING=1)
endif()
]]

#================================
# studio
#================================
if(N2_BUILD_STUDIO AND NOT EMSCRIPTEN AND N2_BUILD_SDL AND N2_APP_STD_BUILD)
	add_executable(n2studio WIN32 ${NIDONEHSP_APP_DIR}/studio.c ${NIDONEHSP_COMMON_SRC} ${NIDONEHSP_COMMON_HDR} ${NIDONEHSP_EMBED_HDR} ${NIDONEHSP_INLINE_HDR} ${NIDONEHSP_APP_HDR} ${NIDONEHSP_APP_DIR}/dap.h)

	n2_set_app_std(n2studio)

	target_compile_definitions(n2studio PUBLIC N2_CONFIG_USE_DEBUGGING=1)
	target_compile_definitions(n2studio PUBLIC N2_CONFIG_USE_PROFILING=1)
	#target_compile_definitions(n2studio PUBLIC N2_CONFIG_USE_NET_SOCKET_LIB=1)

	if(N2_BUILD_TYPE_RELEASE)
		# manually disable assertion
		target_compile_definitions(n2studio PUBLIC N2_CONFIG_USE_ASSERT=0)
	endif()

	target_include_directories(
		n2studio PRIVATE 
		${EXTERNAL_LIB_DIR}/sdl2/include 
	)

	target_link_libraries(n2studio SDL2-static SDL2main)

	if(MSVC)
		# デバッグ実行時のワーキングディレクトリ
		#set_property(TARGET n2studio PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_world/studio")
		set_property(TARGET n2studio PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_world/demo")

		if(NOT N2_BUILD_TYPE_RELEASE)
			# CONSOLEサブシステムに（printf等を見せる）
			set_target_properties(n2studio PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)
		endif()

		# リソース
		target_sources(n2studio PRIVATE ${CMAKE_SOURCE_DIR}/build/msvc/n2studio.rc)
	endif()
endif()

#================================
# runtime(standard)
#================================
if(N2_BUILD_RUNTIME_STANDARD AND N2_BUILD_SDL AND N2_APP_STD_BUILD)
	add_executable(n2r_std WIN32 ${NIDONEHSP_APP_DIR}/runtime.c ${NIDONEHSP_COMMON_SRC} ${NIDONEHSP_COMMON_HDR} ${NIDONEHSP_EMBED_HDR} ${NIDONEHSP_INLINE_HDR} ${NIDONEHSP_APP_HDR})

	n2_set_app_std(n2r_std)

	target_compile_definitions(n2r_std PUBLIC N2R_CONFIG_RUNTIME_STANDARD=1)
	target_compile_definitions(n2r_std PUBLIC N2_CONFIG_USE_DEBUGGING=0)
	target_compile_definitions(n2r_std PUBLIC N2_CONFIG_USE_PROFILING=0)

	if(N2_BUILD_TYPE_RELEASE)
		# manually disable assertion
		target_compile_definitions(n2r_std PUBLIC N2_CONFIG_USE_ASSERT=0)
	endif()

	if(EMSCRIPTEN)
		set(n2r_emcflags "")
		set(n2r_emlflags "")

		list(APPEND n2r_emcflags "-s USE_SDL=2")
		list(APPEND n2r_emlflags "-s USE_SDL=2")

		# wasm mode
		list(APPEND n2r_emlflags "-s WASM=1")
		#list(APPEND n2r_emlflags "-s WASM=2")

		# initial memory = 64MB
		list(APPEND n2r_emlflags "-s INITIAL_MEMORY=67108864 -s ALLOW_MEMORY_GROWTH=1")

		# force filesystem
		list(APPEND n2r_emlflags "-s FORCE_FILESYSTEM=1")

		# enable IDBFS filesystem
		list(APPEND n2r_emlflags "-lidbfs.js")

		# fetch api
		list(APPEND n2r_emlflags "-s FETCH=1")

		# use webgl2
		list(APPEND n2r_emlflags "-s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2")

		# -s WASM_BIGINT=1
		# -s MEMORY64=1
		# -s USE_PTHREADS=1
		# -s FULL_ES3=1

		list(APPEND n2r_emlflags "--pre-js ${CMAKE_SOURCE_DIR}/build/html/n2pre.js")
		#list(APPEND n2r_emlflags "--post-js ${CMAKE_SOURCE_DIR}/build/html/n2post.js")

		if(NOT N2_BUILD_TYPE_RELEASE)
			list(APPEND n2r_emcflags "-s ASSERTIONS=1 -s GL_DEBUG=1")

			# for easy debug
			list(APPEND n2r_emlflags "--emrun")

			# profiling
			list(APPEND n2r_emcflags "--profiling")
		else()
			# optimization
			list(APPEND n2r_emcflags "-O2")
			list(APPEND n2r_emlflags "-O2")
			list(APPEND n2r_emcflags "-fno-rtti -fno-exceptions -flto")
			list(APPEND n2r_emlflags "-flto")
			list(APPEND n2r_emcflags "-s ASSERTIONS=0")

			# omit symbol names
			list(APPEND n2r_emlflags "-g0")
		endif()

		#list(APPEND n2r_emlflags "--preload-file ${CMAKE_SOURCE_DIR}/build/html/empty@n2r_ebin")

		#list(APPEND n2r_emlflags "-s SINGLE_FILE=1")

		# -s USE_WEBGPU=1

		string(REPLACE ";" " " n2r_emcflags "${n2r_emcflags}")
		set_property(TARGET n2r_std PROPERTY COMPILE_FLAGS ${n2r_emcflags})

		string(REPLACE ";" " " n2r_emlflags "${n2r_emlflags}")
		set_property(TARGET n2r_std PROPERTY LINK_FLAGS ${n2r_emlflags})

		# for easy use
		set_property(TARGET n2r_std PROPERTY SUFFIX ".html")
	else()
		target_include_directories(
			n2r_std PRIVATE 
			${EXTERNAL_LIB_DIR}/sdl2/include 
		)

		target_link_libraries(n2r_std SDL2-static SDL2main)

		if(MSVC)
			# デバッグ実行時のワーキングディレクトリ
			set_property(TARGET n2r_std PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_world/runtime")
			if(NOT N2_BUILD_TYPE_RELEASE)
				# CONSOLEサブシステムに（printf等を見せる）
				set_target_properties(n2r_std PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)
			endif()
		endif()
	endif()
endif()

#[[
#================================
# runtime(console)
#================================
if(N2_BUILD_RUNTIME_CONSOLE)
	add_executable(n2r_cl WIN32 ${NIDONEHSP_APP_DIR}/runtime.c ${NIDONEHSP_COMMON_SRC} ${NIDONEHSP_COMMON_HDR} ${NIDONEHSP_EMBED_HDR} ${NIDONEHSP_INLINE_HDR} ${NIDONEHSP_APP_HDR})

	n2_set_app_common(n2r_cl)

	target_compile_definitions(n2r_cl PUBLIC N2R_CONFIG_RUNTIME_CONSOLE=1)

endif()
]]

#================================
# test
#================================
if(N2_BUILD_TEST AND NOT EMSCRIPTEN)
	# test dynlib
	add_library(n2testdynlib MODULE ${NIDONEHSP_APP_DIR}/testdynlib.c ${NIDONEHSP_APP_DIR}/testdynlib.def)
	if(MSVC)
	#	set_target_properties(n2testdynlib PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE /NODEFAULTLIB /NOENTRY")
	endif()

	# test exe
	add_executable(n2test ${NIDONEHSP_APP_DIR}/utest.c ${NIDONEHSP_COMMON_SRC})

	n2_set_app_common(n2test)

	target_compile_definitions(n2test PUBLIC N2_CONFIG_USE_DEBUGGING=1)
	target_compile_definitions(n2test PUBLIC N2_CONFIG_USE_PROFILING=1)

	if(N2_BUILD_SDL)
		target_include_directories(
			n2test PRIVATE 
			${EXTERNAL_LIB_DIR}/sdl2/include 
		)

		target_link_libraries(n2test SDL2-static SDL2main)
	endif()

	if(MSVC)
		# デバッグ実行時のワーキングディレクトリ
		set_property(TARGET n2test PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/test_world")

		# CONSOLEサブシステムに（printf等を見せる）
		set_target_properties(n2test PROPERTIES LINK_FLAGS /SUBSYSTEM:CONSOLE)
	endif()
endif()

