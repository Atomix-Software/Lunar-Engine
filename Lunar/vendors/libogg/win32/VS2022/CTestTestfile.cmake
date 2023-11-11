# CMake generated Testfile for 
# Source directory: C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg
# Build directory: C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/win32/VS2022
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(test_bitwise "C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/win32/VS2022/Debug/test_bitwise.exe")
  set_tests_properties(test_bitwise PROPERTIES  _BACKTRACE_TRIPLES "C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/CMakeLists.txt;192;add_test;C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(test_bitwise "C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/win32/VS2022/Release/test_bitwise.exe")
  set_tests_properties(test_bitwise PROPERTIES  _BACKTRACE_TRIPLES "C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/CMakeLists.txt;192;add_test;C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(test_bitwise "C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/win32/VS2022/MinSizeRel/test_bitwise.exe")
  set_tests_properties(test_bitwise PROPERTIES  _BACKTRACE_TRIPLES "C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/CMakeLists.txt;192;add_test;C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(test_bitwise "C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/win32/VS2022/RelWithDebInfo/test_bitwise.exe")
  set_tests_properties(test_bitwise PROPERTIES  _BACKTRACE_TRIPLES "C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/CMakeLists.txt;192;add_test;C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/CMakeLists.txt;0;")
else()
  add_test(test_bitwise NOT_AVAILABLE)
endif()
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(test_framing "C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/win32/VS2022/Debug/test_framing.exe")
  set_tests_properties(test_framing PROPERTIES  _BACKTRACE_TRIPLES "C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/CMakeLists.txt;200;add_test;C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(test_framing "C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/win32/VS2022/Release/test_framing.exe")
  set_tests_properties(test_framing PROPERTIES  _BACKTRACE_TRIPLES "C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/CMakeLists.txt;200;add_test;C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(test_framing "C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/win32/VS2022/MinSizeRel/test_framing.exe")
  set_tests_properties(test_framing PROPERTIES  _BACKTRACE_TRIPLES "C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/CMakeLists.txt;200;add_test;C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(test_framing "C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/win32/VS2022/RelWithDebInfo/test_framing.exe")
  set_tests_properties(test_framing PROPERTIES  _BACKTRACE_TRIPLES "C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/CMakeLists.txt;200;add_test;C:/Workspace/visual_studio/game-engine/Lunar/vendors/libogg/CMakeLists.txt;0;")
else()
  add_test(test_framing NOT_AVAILABLE)
endif()