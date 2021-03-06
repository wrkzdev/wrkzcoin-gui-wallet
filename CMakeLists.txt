cmake_minimum_required(VERSION 3.1)

foreach(p
    CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

#Set build version
set(VERSION_MAJOR "0")
set(VERSION_MINOR "1.2.8")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}")
find_package(Git QUIET)
if(Git_FOUND OR GIT_FOUND)
    message(STATUS "Found Git: ${GIT_EXECUTABLE}")
    execute_process(COMMAND git rev-parse --abbrev-ref HEAD  # Get the current branch
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE)

    execute_process(COMMAND git log -1 --format=%h # Get latest commit hash
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE COMMIT_ID
        OUTPUT_STRIP_TRAILING_WHITESPACE)
else()
    message(STATUS "Git not found !")
    set(GIT_BRANCH "unknown")
    set(COMMIT_ID "unknown")
endif()

set(GIT_REVISION "${COMMIT_ID}-${CMAKE_BUILD_TYPE}")
foreach(p
        CMP0071 # 3.1: Let AUTOMOC and AUTOUIC process GENERATED files
        )
    if(POLICY ${p})
        cmake_policy(SET ${p} NEW)
    endif()
endforeach()

include(CryptoNoteWallet.cmake)

project(${CN_PROJECT_NAME})

set(CRYPTONOTE_LIB cryptoNote)

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    src
    include
    cryptonote/external
    cryptonote/external/rocksdb/include/
    cryptonote/include
    cryptonote/src
    )

find_package(Qt5 REQUIRED
    Gui
    Widgets
    Network
    DBus
    )

include_directories(${Qt5DBus_INCLUDE_DIRS} cryptonote/external/rocksdb/include/ include src external "${CMAKE_CURRENT_BINARY_DIR}/version")

set(Boost_USE_STATIC_LIBS ON)
if(WIN32)
    set(Boost_USE_STATIC_RUNTIME OFF)
else(WIN32)
    set(Boost_USE_STATIC_RUNTIME ON)
endif(WIN32)

find_package(Boost 1.58 REQUIRED COMPONENTS date_time filesystem program_options regex serialization system thread chrono)
if ((${Boost_MAJOR_VERSION} EQUAL 1) AND (${Boost_MINOR_VERSION} EQUAL 54))
  message(SEND_ERROR "Boost version 1.58 is unsupported, more details are available here http://goo.gl/RrCFmA")
endif ()

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})


add_definitions(-DGIT_REVISION="${GIT_REVISION}")

set(CMAKE_AUTOMOC ON)

file(GLOB_RECURSE CRYPTONOTE_SOURCES
  cryptonote/external/miniupnpc/connecthostport.c
  cryptonote/external/miniupnpc/igd_desc_parse.c
  cryptonote/external/miniupnpc/minisoap.c
  cryptonote/external/miniupnpc/miniupnpc.c
  cryptonote/external/miniupnpc/miniwget.c
  cryptonote/external/miniupnpc/minixml.c
  cryptonote/external/miniupnpc/portlistingparse.c
  cryptonote/external/miniupnpc/receivedata.c
  cryptonote/external/miniupnpc/upnpcommands.c
  cryptonote/external/miniupnpc/upnpreplyparse.c
  cryptonote/src/BlockchainExplorer/BlockchainExplorer.cpp
  cryptonote/src/BlockchainExplorer/BlockchainExplorerErrors.cpp
  cryptonote/src/Common/Base58.cpp
  cryptonote/src/Common/CommandLine.cpp
  cryptonote/src/Common/Util.cpp
  cryptonote/src/Common/StringTools.cpp
  cryptonote/src/Common/JsonValue.cpp
  cryptonote/src/Common/ConsoleTools.cpp
  cryptonote/src/Common/MemoryInputStream.cpp
  cryptonote/src/Common/PathTools.cpp
  cryptonote/src/Common/StdInputStream.cpp
  cryptonote/src/Common/StdOutputStream.cpp
  cryptonote/src/Common/StreamTools.cpp
  cryptonote/src/Common/StringOutputStream.cpp
  cryptonote/src/Common/StringView.cpp
  cryptonote/src/Common/VectorOutputStream.cpp
  cryptonote/src/Common/ScopeExit.cpp
  cryptonote/src/ConnectivityTool/ConnectivityTool.cpp
  cryptonote/src/crypto/aesb.c
  cryptonote/src/crypto/blake256.c
  cryptonote/src/crypto/chacha8.c
  cryptonote/src/crypto/crypto-ops-data.c
  cryptonote/src/crypto/crypto-ops.c
  cryptonote/src/crypto/crypto.cpp
  cryptonote/src/crypto/groestl.c
  cryptonote/src/crypto/hash-extra-blake.c
  cryptonote/src/crypto/hash-extra-groestl.c
  cryptonote/src/crypto/hash-extra-jh.c
  cryptonote/src/crypto/hash-extra-skein.c
  cryptonote/src/crypto/hash.c
  cryptonote/src/crypto/jh.c
  cryptonote/src/crypto/keccak.c
  cryptonote/src/crypto/oaes_lib.c
  cryptonote/src/crypto/random.c
  cryptonote/src/crypto/skein.c
  cryptonote/src/crypto/slow-hash.c
  cryptonote/src/crypto/tree-hash.c
  cryptonote/src/CryptoNoteCore/*.cpp
  cryptonote/src/CryptoNoteProtocol/*.cpp
  cryptonote/src/Daemon/*.cpp
  cryptonote/src/HTTP/*.cpp
  cryptonote/src/InProcessNode/InProcessNode.cpp
  cryptonote/src/InProcessNode/InProcessNodeErrors.cpp
  cryptonote/src/Logging/*.cpp
  cryptonote/src/NodeRpcProxy/NodeErrors.cpp
  cryptonote/src/NodeRpcProxy/NodeRpcProxy.cpp
  cryptonote/src/P2p/*.cpp
  cryptonote/src/Rpc/*.cpp
  cryptonote/src/Serialization/*.cpp
  cryptonote/src/Transfers/BlockchainSynchronizer.cpp
  cryptonote/src/Transfers/SynchronizationState.cpp
  cryptonote/src/Transfers/TransfersConsumer.cpp
  cryptonote/src/Transfers/TransfersContainer.cpp
  cryptonote/src/Transfers/TransfersSubscription.cpp
  cryptonote/src/Transfers/TransfersSynchronizer.cpp
  cryptonote/src/Wallet/*.cpp
  cryptonote/src/WalletLegacy/KeysStorage.cpp
  cryptonote/src/WalletLegacy/WalletLegacy.cpp
  cryptonote/src/WalletLegacy/WalletHelper.cpp
  cryptonote/src/WalletLegacy/WalletLegacySerializer.cpp
  cryptonote/src/WalletLegacy/WalletLegacySerialization.cpp
  cryptonote/src/WalletLegacy/WalletTransactionSender.cpp
  cryptonote/src/WalletLegacy/WalletUnconfirmedTransactions.cpp
  cryptonote/src/WalletLegacy/WalletUserTransactionsCache.cpp
  cryptonote/src/System/ContextGroup.cpp
  cryptonote/src/System/Event.cpp
  cryptonote/src/System/EventLock.cpp
  cryptonote/src/System/InterruptedException.cpp
  cryptonote/src/System/Ipv4Address.cpp
  cryptonote/src/System/TcpStream.cpp
  cryptonote/src/JsonRpcServer/*.cpp
  cryptonote/src/Miner/*.cpp
)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE FORMS src/gui/*.ui)
## Added this Mnemonics
file(GLOB_RECURSE Mnemonics cryptonote/src/Mnemonics/*)

if(MSVC)
  include_directories(Platform/Windows)
  set(SOURCES ${SOURCES} ${CMAKE_SOURCE_DIR}/Platform/Windows/ApplicationEventHandler.cpp)
elseif(APPLE)
  include_directories(Platform/OSX)
  include_directories(Platform/Posix)
  set(SOURCES ${SOURCES} ${CMAKE_SOURCE_DIR}/Platform/Posix/System/MemoryMappedFile.cpp)
else()
  include_directories(Platform/Linux)
  include_directories(Platform/Posix)
  set(SOURCES ${SOURCES} ${CMAKE_SOURCE_DIR}/Platform/Linux/ApplicationEventHandler.cpp)
  set(SOURCES ${SOURCES} ${CMAKE_SOURCE_DIR}/Platform/Posix/System/MemoryMappedFile.cpp)
endif()


set(QRC src/resources.qrc)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

qt5_wrap_ui(UIS ${FORMS})
qt5_add_resources(RCC ${QRC})

if (WIN32)
    if (NOT MSVC)
        message(FATAL_ERROR "Only MSVC is supported on this platform")
    endif ()

        set(STATIC ${MSVC} CACHE BOOL "Link libraries statically")
    if(STATIC)
        foreach(VAR CMAKE_C_FLAGS_DEBUG CMAKE_CXX_FLAGS_DEBUG CMAKE_C_FLAGS_RELWITHDEBINFO CMAKE_CXX_FLAGS_RELWITHDEBINFO CMAKE_C_FLAGS_RELEASE CMAKE_CXX_FLAGS_RELEASE)
			string(REPLACE "/MD" "/MT" ${VAR} "${${VAR}}")
        endforeach()
    endif()
    add_definitions(/D_CRT_SECURE_NO_WARNINGS /D_WIN32_WINNT=0x0600 /DSTATICLIB)
    include_directories(cryptonote/src/Platform/msc)
    link_directories(cryptonote/external/rocksdb)

    set(PLATFORM_DIR Windows)
    set(BUILD_PLATFORM WIN32)
    set(BUILD_RESOURCES src/wrkzcoinwallet.rc)
    set(QTMAIN Qt5::WinMain)

elseif (UNIX)  
 set(CRYPTONOTE_SOURCES ${CRYPTONOTE_SOURCES} cryptonote/external/miniupnpc/minissdpc.c)

    if (APPLE)
        enable_language(ASM)
        file(GLOB_RECURSE OBJC_SOURCES Platform/OSX/*.mm)
        set(WALLET_SOURCES ${WALLET_SOURCES} ${OBJC_SOURCES})
        set(PLATFORM_DIR OSX)
        set(MACOSX_BUNDLE_INFO_STRING "WrkzCoin GUI wallet v${VERSION} ${GIT_REVISION}")
        set(MACOSX_BUNDLE_LONG_VERSION_STRING "${VERSION} ${GIT_REVISION}")
        set(MACOSX_BUNDLE_BUNDLE_NAME WrkzCoinWallet)
        set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${VERSION}")
        set(MACOSX_BUNDLE_BUNDLE_VERSION "${VERSION}")

        find_package(Qt5PrintSupport REQUIRED)
        include_directories(/usr/include/malloc)

		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes -std=c++11 -stdlib=libc++")
		set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -maes -D_DARWIN_C_SOURCE")
		set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework CoreFoundation -framework Carbon -framework IOKit -L/usr/lib")

        set(MACOSX_BUNDLE_ICON_FILE wrkzcoin.icns)
        set(APPLICATION_ICON src/images/wrkzcoin.icns)
        set_source_files_properties(${APPLICATION_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

		set(BUILD_PLATFORM MACOSX_BUNDLE)
		set(BUILD_RESOURCES ${APPLICATION_ICON})
		
		GET_TARGET_PROPERTY(QT_LIB_DIR "${Qt5Widgets_LIBRARIES}" LOCATION)
		GET_FILENAME_COMPONENT(QT_LIB_DIR "${QT_LIB_DIR}" PATH)
    else(APPLE)
        set(PLATFORM_DIR Linux)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes -std=c++11")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -maes -std=c11")
    endif (APPLE)
endif ()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${DEBUG_FLAGS}")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEBUG_FLAGS}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} ${RELEASE_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${RELEASE_FLAGS}")
include_directories(cryptonote/src/Platform/${PLATFORM_DIR})
file(GLOB PLATFORM_SOURCES cryptonote/src/Platform/${PLATFORM_DIR}/System/*)
set(CRYPTONOTE_SOURCES ${CRYPTONOTE_SOURCES} ${PLATFORM_SOURCES} ${CRYPTONOTE_PLATFORM})

add_library(${CRYPTONOTE_LIB} STATIC ${CRYPTONOTE_SOURCES})
## Added this Mnemonics
add_library(Mnemonics ${Mnemonics})
set_target_properties(${CRYPTONOTE_LIB} PROPERTIES COMPILE_DEFINITIONS _GNU_SOURCE)
target_link_libraries(${CRYPTONOTE_LIB} rocksdb ${Boost_LIBRARIES} ${Qt5DBus_LIBRARIES})

## Added this Mnemonics
set_target_properties(Mnemonics PROPERTIES COMPILE_DEFINITIONS _GNU_SOURCE)
target_link_libraries(Mnemonics ${Boost_LIBRARIES})

add_executable(${PROJECT_NAME} ${BUILD_PLATFORM} ${BUILD_RESOURCES} ${SOURCES} ${HEADERS} ${UIS} ${RCC})

set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS _GNU_SOURCE)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${QTMAIN} ${CRYPTONOTE_LIB} ${Qt5DBus_LIBRARIES} Mnemonics)

if (APPLE)
    qt5_use_modules(${PROJECT_NAME} PrintSupport)
elseif (UNIX)
    target_link_libraries(${PROJECT_NAME} -lpthread)
elseif (WIN32)
    target_link_libraries(${PROJECT_NAME} rpcrt4.lib wtsapi32.lib  Imm32 Iphlpapi Winmm)
endif (APPLE)

qt5_use_modules(${PROJECT_NAME} Widgets Gui Network)
add_subdirectory(cryptonote/external)

if(NOT MSVC)
  execute_process(
    COMMAND cmake ${CMAKE_SOURCE_DIR}/cryptonote/external/rocksdb -DWITH_GFLAGS=0 -B${PROJECT_BINARY_DIR}/rocksdb
  )
  set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${PROJECT_BINARY_DIR}/rocksdb/librocksdb.a")
endif()

configure_file("cryptonote/src/version.h.in" "version.h")
configure_file("cryptonote/src/version.h.in" ${CMAKE_SOURCE_DIR}/src/version.h)
configure_file("src/CryptoNoteWalletConfig.h.in" "CryptoNoteWalletConfig.h")