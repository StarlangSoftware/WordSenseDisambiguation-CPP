cmake_minimum_required(VERSION 3.17)
project(WordSenseDisambiguation)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
set(CONAN_INCLUDE_DIRS_ANNOTATEDTREE "/Users/olcay/.conan/data/AnnotatedTree/1.0.0/_/_/package/e24f3a24ba1e5db53e914b9af88ac8896605cc13/include")

add_library(WordSenseDisambiguation src/AutoProcessor/Sentence/SentenceAutoSemantic.cpp src/AutoProcessor/Sentence/SentenceAutoSemantic.h src/AutoProcessor/Sentence/TurkishSentenceAutoSemantic.cpp src/AutoProcessor/Sentence/TurkishSentenceAutoSemantic.h src/AutoProcessor/Sentence/RandomSentenceAutoSemantic.cpp src/AutoProcessor/Sentence/RandomSentenceAutoSemantic.h src/AutoProcessor/Sentence/MostFrequentSentenceAutoSemantic.cpp src/AutoProcessor/Sentence/MostFrequentSentenceAutoSemantic.h src/AutoProcessor/Sentence/Lesk.cpp src/AutoProcessor/Sentence/Lesk.h)
target_link_libraries(WordSenseDisambiguation ${CONAN_LIBS})