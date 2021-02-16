//
// Created by Olcay Taner YILDIZ on 16.02.2021.
//

#include "RandomSentenceAutoSemantic.h"

/**
 * Constructor for the {@link RandomSentenceAutoSemantic} class. Gets the Turkish wordnet and Turkish fst based
 * morphological analyzer from the user and sets the corresponding attributes.
 * @param turkishWordNet Turkish wordnet
 * @param fsm Turkish morphological analyzer
 */
RandomSentenceAutoSemantic::RandomSentenceAutoSemantic(WordNet &turkishWordNet, FsmMorphologicalAnalyzer &fsm) {
    this->turkishWordNet = turkishWordNet;
    this->fsm = fsm;
}

void RandomSentenceAutoSemantic::autoLabelSingleSemantics(AnnotatedSentence *sentence) {
    for (int i = 0; i < sentence->wordCount(); i++) {
        vector<SynSet> synSets = getCandidateSynSets(turkishWordNet, fsm, sentence, i);
        if (!synSets.empty()){
            ((AnnotatedWord*) sentence->getWord(i))->setSemantic(synSets.at(random() % synSets.size()).getId());
        }
    }
}
