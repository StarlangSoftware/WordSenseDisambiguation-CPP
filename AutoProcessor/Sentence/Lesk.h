//
// Created by Olcay Taner YILDIZ on 16.02.2021.
//

#ifndef WORDSENSEDISAMBIGUATION_LESK_H
#define WORDSENSEDISAMBIGUATION_LESK_H

#include "SentenceAutoSemantic.h"

class Lesk : public SentenceAutoSemantic {
private:
    WordNet turkishWordNet;
    FsmMorphologicalAnalyzer fsm;
    int intersection(SynSet synSet, AnnotatedSentence* sentence);
public:
    Lesk(WordNet& turkishWordNet, FsmMorphologicalAnalyzer& fsm);
protected:
    void autoLabelSingleSemantics(AnnotatedSentence* sentence) override;
};


#endif //WORDSENSEDISAMBIGUATION_LESK_H
