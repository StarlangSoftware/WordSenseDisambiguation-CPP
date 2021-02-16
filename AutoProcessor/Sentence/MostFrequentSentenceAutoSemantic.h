//
// Created by Olcay Taner YILDIZ on 16.02.2021.
//

#ifndef WORDSENSEDISAMBIGUATION_MOSTFREQUENTSENTENCEAUTOSEMANTIC_H
#define WORDSENSEDISAMBIGUATION_MOSTFREQUENTSENTENCEAUTOSEMANTIC_H

#include "SentenceAutoSemantic.h"

class MostFrequentSentenceAutoSemantic : public SentenceAutoSemantic {
private:
    WordNet turkishWordNet;
    FsmMorphologicalAnalyzer fsm;
    SynSet mostFrequent(vector<SynSet> synSets, string root);
public:
    MostFrequentSentenceAutoSemantic(WordNet& turkishWordNet, FsmMorphologicalAnalyzer& fsm);
protected:
    void autoLabelSingleSemantics(AnnotatedSentence* sentence) override;
};


#endif //WORDSENSEDISAMBIGUATION_MOSTFREQUENTSENTENCEAUTOSEMANTIC_H
