//
// Created by Olcay Taner YILDIZ on 16.02.2021.
//

#include "Lesk.h"

/**
 * Constructor for the {@link Lesk} class. Gets the Turkish wordnet and Turkish fst based
 * morphological analyzer from the user and sets the corresponding attributes.
 * @param turkishWordNet Turkish wordnet
 * @param fsm Turkish morphological analyzer
 */
Lesk::Lesk(const WordNet &turkishWordNet, const FsmMorphologicalAnalyzer &fsm) {
    this->turkishWordNet = turkishWordNet;
    this->fsm = fsm;
}

int Lesk::intersection(const SynSet& synSet, AnnotatedSentence* sentence){
    vector<string> words1;
    if (!synSet.getExample().empty()){
        words1 = Word::split(synSet.getLongDefinition() + " " + synSet.getExample());
    } else {
        words1 = Word::split(synSet.getLongDefinition());
    }
    vector<string> words2 = Word::split(sentence->toWords());
    int count = 0;
    for (const string& word1 : words1){
        for (const string& word2 : words2){
            if (Word::toLowerCase(word1) == Word::toLowerCase(word2)){
                count++;
            }
        }
    }
    return count;
}

void Lesk::autoLabelSingleSemantics(AnnotatedSentence *sentence) {
    for (int i = 0; i < sentence->wordCount(); i++) {
        vector<SynSet> synSets = getCandidateSynSets(turkishWordNet, fsm, sentence, i);
        int maxIntersection = -1;
        for (const auto& synSet : synSets){
            int intersectionCount = intersection(synSet, sentence);
            if (intersectionCount > maxIntersection){
                maxIntersection = intersectionCount;
            }
        }
        vector<SynSet> maxSynSets;
        for (const auto& synSet : synSets){
            if (intersection(synSet, sentence) == maxIntersection){
                maxSynSets.emplace_back(synSet);
            }
        }
        if (!maxSynSets.empty()){
            ((AnnotatedWord*) sentence->getWord(i))->setSemantic(maxSynSets.at(random() % maxSynSets.size()).getId());
        }
    }
}
