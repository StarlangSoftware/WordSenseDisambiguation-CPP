//
// Created by Olcay Taner YILDIZ on 16.02.2021.
//

#include "RandomSentenceAutoSemantic.h"

/**
 * Constructor for the RandomSentenceAutoSemantic class. Gets the Turkish wordnet and Turkish fst based
 * morphological analyzer from the user and sets the corresponding attributes.
 * @param turkishWordNet Turkish wordnet
 * @param fsm Turkish morphological analyzer
 */
RandomSentenceAutoSemantic::RandomSentenceAutoSemantic(const WordNet &turkishWordNet, const FsmMorphologicalAnalyzer &fsm) {
    this->turkishWordNet = turkishWordNet;
    this->fsm = fsm;
}

/**
 * The method annotates the word senses of the words in the sentence randomly. The algorithm processes target
 * words one by one. First, the algorithm constructs an array of all possible senses for the target word to
 * annotate. Then it chooses a sense randomly.
 * @param sentence Sentence to be annotated.
 * @return True.
 */
bool RandomSentenceAutoSemantic::autoLabelSingleSemantics(AnnotatedSentence *sentence) {
    for (int i = 0; i < sentence->wordCount(); i++) {
        vector<SynSet> synSets = getCandidateSynSets(turkishWordNet, fsm, sentence, i);
        if (!synSets.empty()){
            ((AnnotatedWord*) sentence->getWord(i))->setSemantic(synSets.at(random() % synSets.size()).getId());
        }
    }
    return true;
}
