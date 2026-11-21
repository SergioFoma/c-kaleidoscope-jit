find_package(FLEX REQUIRED)
find_package(BISON 3.8 REQUIRED)

flex_target(KaleidoscopeLexer lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lex.yy.cc)
bison_target(KaleidoscopeParser parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.tab.cc)
add_flex_bison_dependency(KaleidoscopeLexer KaleidoscopeParser)

add_library(frontend OBJECT
  ${BISON_KaleidoscopeParser_OUTPUTS}
  ${FLEX_KaleidoscopeLexer_OUTPUTS}
)

target_include_directories(frontend PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}   # ast.hpp
  ${CMAKE_CURRENT_BINARY_DIR}   # parse.tab.hh
)


