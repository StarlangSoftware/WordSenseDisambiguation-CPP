cmake_minimum_required(VERSION 3.17)
project(WordSenseDisambiguation)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(library)

add_library(WordSenseDisambiguation AutoProcessor/Sentence/SentenceAutoSemantic.cpp AutoProcessor/Sentence/SentenceAutoSemantic.h AutoProcessor/Sentence/TurkishSentenceAutoSemantic.cpp AutoProcessor/Sentence/TurkishSentenceAutoSemantic.h AutoProcessor/Sentence/RandomSentenceAutoSemantic.cpp AutoProcessor/Sentence/RandomSentenceAutoSemantic.h AutoProcessor/Sentence/MostFrequentSentenceAutoSemantic.cpp AutoProcessor/Sentence/MostFrequentSentenceAutoSemantic.h AutoProcessor/Sentence/Lesk.cpp AutoProcessor/Sentence/Lesk.h)

target_link_libraries(WordSenseDisambiguation AnnotatedTree AnnotatedSentence)