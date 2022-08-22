//
// Created by Olcay Taner YILDIZ on 16.02.2021.
//

#ifndef WORDSENSEDISAMBIGUATION_RANDOMSENTENCEAUTOSEMANTIC_H
#define WORDSENSEDISAMBIGUATION_RANDOMSENTENCEAUTOSEMANTIC_H

#include "SentenceAutoSemantic.h"

class RandomSentenceAutoSemantic : public SentenceAutoSemantic {
private:
    WordNet turkishWordNet;
    FsmMorphologicalAnalyzer fsm;
public:
    RandomSentenceAutoSemantic(WordNet& turkishWordNet, FsmMorphologicalAnalyzer& fsm);
protected:
    void autoLabelSingleSemantics(AnnotatedSentence* sentence) override;
};


#endif //WORDSENSEDISAMBIGUATION_RANDOMSENTENCEAUTOSEMANTIC_H
