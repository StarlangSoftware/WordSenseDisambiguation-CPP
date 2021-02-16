//
// Created by Olcay Taner YILDIZ on 16.02.2021.
//

#include "MostFrequentSentenceAutoSemantic.h"

/**
 * Constructor for the {@link MostFrequentSentenceAutoSemantic} class. Gets the Turkish wordnet and Turkish fst based
 * morphological analyzer from the user and sets the corresponding attributes.
 * @param turkishWordNet Turkish wordnet
 * @param fsm Turkish morphological analyzer
 */
MostFrequentSentenceAutoSemantic::MostFrequentSentenceAutoSemantic(WordNet &turkishWordNet, FsmMorphologicalAnalyzer &fsm) {
    this->turkishWordNet = turkishWordNet;
    this->fsm = fsm;
}

SynSet MostFrequentSentenceAutoSemantic::mostFrequent(vector<SynSet> synSets, string root){
    if (synSets.size() == 1){
        return synSets.at(0);
    }
    int minSense = 50;
    SynSet best = SynSet("");
    for (SynSet synSet : synSets){
        for (int i = 0; i < synSet.getSynonym().literalSize(); i++){
            if (Word::startsWith(Word::toLowerCase(synSet.getSynonym().getLiteral(i).getName()), root)
                || Word::endsWith(Word::toLowerCase(synSet.getSynonym().getLiteral(i).getName()), " " + root)){
                if (synSet.getSynonym().getLiteral(i).getSense() < minSense){
                    minSense = synSet.getSynonym().getLiteral(i).getSense();
                    best = synSet;
                }
            }
        }
    }
    return best;
}

void MostFrequentSentenceAutoSemantic::autoLabelSingleSemantics(AnnotatedSentence *sentence) {
    for (int i = 0; i < sentence->wordCount(); i++) {
        vector<SynSet> synSets = getCandidateSynSets(turkishWordNet, fsm, sentence, i);
        if (!synSets.empty()){
            SynSet best = mostFrequent(synSets, ((AnnotatedWord*) sentence->getWord(i))->getParse()->getWord()->getName());
            if (!best.getId().empty()){
                ((AnnotatedWord*) sentence->getWord(i))->setSemantic(best.getId());
            }
        }
    }
}
