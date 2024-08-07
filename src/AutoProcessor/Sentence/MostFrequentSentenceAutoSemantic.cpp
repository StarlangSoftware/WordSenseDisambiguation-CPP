//
// Created by Olcay Taner YILDIZ on 16.02.2021.
//

#include "MostFrequentSentenceAutoSemantic.h"

/**
 * Constructor for the MostFrequentSentenceAutoSemantic class. Gets the Turkish wordnet and Turkish fst based
 * morphological analyzer from the user and sets the corresponding attributes.
 * @param turkishWordNet Turkish wordnet
 * @param fsm Turkish morphological analyzer
 */
MostFrequentSentenceAutoSemantic::MostFrequentSentenceAutoSemantic(const WordNet &turkishWordNet, const FsmMorphologicalAnalyzer &fsm) {
    this->turkishWordNet = turkishWordNet;
    this->fsm = fsm;
}

/**
 * Determines the synset containing the literal with the lowest sense number.
 * @param literals an ArrayList of Literal objects
 * @return the SynSet containing the literal with the lowest sense number, or null if the input list is empty
 */
SynSet* MostFrequentSentenceAutoSemantic::mostFrequent(const vector<Literal>& literals){
    if (literals.size() == 1) {
        return turkishWordNet.getSynSetWithId(literals[0].getSynSetId());
    }
    int minSense = INT_MAX;
    SynSet* bestSynset = nullptr;
    for (const Literal& literal : literals) {
        if(literal.getSense() < minSense) {
            minSense = literal.getSense();
            bestSynset = turkishWordNet.getSynSetWithId(literal.getSynSetId());
        }
    }
    return bestSynset;
}

/**
 * Checks
 * 1. the previous two words and the current word; the previous, current and next word, current and the next
 * two words for a three word multiword expression that occurs in the Turkish wordnet.
 * 2. the previous word and current word; current word and the next word for a two word multiword expression that
 * occurs in the Turkish wordnet.
 * 3. the current word
 * and sets the most frequent sense for that multiword expression or word.
 * @param sentence The sentence for which word sense will be determined automatically.
 */
bool MostFrequentSentenceAutoSemantic::autoLabelSingleSemantics(AnnotatedSentence *sentence) {
    bool done = false;
    AnnotatedWord* twoPrevious = nullptr, *previous = nullptr, *current, *twoNext = nullptr, *next = nullptr;
    for (int i = 0; i < sentence->wordCount(); i++) {
        current = (AnnotatedWord*) sentence->getWord(i);
        if (i > 1) {
            twoPrevious = (AnnotatedWord*) sentence->getWord(i - 2);
        }
        if (i > 0) {
            previous = (AnnotatedWord*) sentence->getWord(i - 1);
        }
        if (i != sentence->wordCount() - 1) {
            next = (AnnotatedWord*) sentence->getWord(i + 1);
        }
        if (i < sentence->wordCount() - 2) {
            twoNext = (AnnotatedWord*) sentence->getWord(i + 2);
        }
        if (current->getSemantic().empty() && current->getParse() != nullptr) {
            if (twoPrevious != nullptr && twoPrevious->getParse() != nullptr && previous->getParse() != nullptr) {
                vector<Literal> literals = turkishWordNet.constructIdiomLiterals(*(twoPrevious->getParse()),
                                                                                  *(previous->getParse()),
                                                                                  *(current->getParse()),
                                                                                  *(twoPrevious->getMetamorphicParse()),
                                                                                  *(previous->getMetamorphicParse()),
                                                                                  *(current->getMetamorphicParse()),
                                                                                  fsm);
                if (!literals.empty()) {
                    SynSet* bestSynset = mostFrequent(literals);
                    if (bestSynset != nullptr){
                        current->setSemantic(bestSynset->getId());
                        done = true;
                        continue;
                    }
                }
            }
            if (previous != nullptr && previous->getParse() != nullptr && next != nullptr && next->getParse() != nullptr) {
                vector<Literal> literals = turkishWordNet.constructIdiomLiterals(*(previous->getParse()),
                                                                                 *(current->getParse()),
                                                                                 *(next->getParse()),
                                                                                 *(previous->getMetamorphicParse()),
                                                                                 *(current->getMetamorphicParse()),
                                                                                 *(next->getMetamorphicParse()),
                                                                                 fsm);
                if (!literals.empty()) {
                    SynSet* bestSynset = mostFrequent(literals);
                    if (bestSynset != nullptr) {
                        current->setSemantic(bestSynset->getId());
                        done = true;
                        continue;
                    }
                }
            }
            if (next != nullptr && next->getParse() != nullptr && twoNext != nullptr && twoNext->getParse() != nullptr) {
                vector<Literal> literals = turkishWordNet.constructIdiomLiterals(*(current->getParse()),
                                                                                 *(next->getParse()),
                                                                                 *(twoNext->getParse()),
                                                                                 *(current->getMetamorphicParse()),
                                                                                 *(next->getMetamorphicParse()),
                                                                                 *(twoNext->getMetamorphicParse()),
                                                                                 fsm);
                if (!literals.empty()) {
                    SynSet* bestSynset = mostFrequent(literals);
                    if (bestSynset != nullptr) {
                        current->setSemantic(bestSynset->getId());
                        done = true;
                        continue;
                    }
                }
            }
            if (previous != nullptr && previous->getParse() != nullptr) {
                vector<Literal> literals = turkishWordNet.constructIdiomLiterals(*(previous->getParse()),
                                                                                 *(current->getParse()),
                                                                                 *(previous->getMetamorphicParse()),
                                                                                 *(current->getMetamorphicParse()),
                                                                                 fsm);
                if (!literals.empty()) {
                    SynSet* bestSynset = mostFrequent(literals);
                    if (bestSynset != nullptr) {
                        current->setSemantic(bestSynset->getId());
                        done = true;
                        continue;
                    }
                }
            }
            if (current->getSemantic().empty() && next != nullptr && next->getParse() != nullptr) {
                vector<Literal> literals = turkishWordNet.constructIdiomLiterals(*(current->getParse()),
                                                                                 *(next->getParse()),
                                                                                 *(current->getMetamorphicParse()),
                                                                                 *(next->getMetamorphicParse()),
                                                                                 fsm);
                if (!literals.empty()) {
                    SynSet* bestSynset = mostFrequent(literals);
                    if (bestSynset != nullptr) {
                        current->setSemantic(bestSynset->getId());
                        done = true;
                        continue;
                    }
                }
            }
            vector<Literal> literals = turkishWordNet.constructLiterals(current->getParse()->getWord()->getName(),
                                                                        *(current->getParse()),
                                                                        *(current->getMetamorphicParse()),
                                                                        fsm);
            if (current->getSemantic().empty() && !literals.empty()) {
                SynSet* bestSynset = mostFrequent(literals);
                if (bestSynset != nullptr) {
                    current->setSemantic(bestSynset->getId());
                    done = true;
                }
            }
        }
    }
    return done;
}
