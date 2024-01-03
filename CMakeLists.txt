cmake_minimum_required(VERSION 3.17)
project(WordSenseDisambiguation)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

find_package(annotated_tree REQUIRED)

add_library(WordSenseDisambiguation src/AutoProcessor/Sentence/SentenceAutoSemantic.cpp src/AutoProcessor/Sentence/SentenceAutoSemantic.h src/AutoProcessor/Sentence/TurkishSentenceAutoSemantic.cpp src/AutoProcessor/Sentence/TurkishSentenceAutoSemantic.h src/AutoProcessor/Sentence/RandomSentenceAutoSemantic.cpp src/AutoProcessor/Sentence/RandomSentenceAutoSemantic.h src/AutoProcessor/Sentence/MostFrequentSentenceAutoSemantic.cpp src/AutoProcessor/Sentence/MostFrequentSentenceAutoSemantic.h src/AutoProcessor/Sentence/Lesk.cpp src/AutoProcessor/Sentence/Lesk.h)
target_link_libraries(WordSenseDisambiguation annotated_tree::annotated_tree)