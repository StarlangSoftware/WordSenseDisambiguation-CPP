//
// Created by olcay on 2.05.2019.
//

#include "SentenceAutoSemantic.h"

void SentenceAutoSemantic::autoSemantic(AnnotatedSentence *sentence) {
    autoLabelSingleSemantics(sentence);
}

/**
 * The method constructs all possible senses for the word at position index in the given sentence. The method checks
 * the previous two words and the current word; the previous, current and next word, current and the next
 * two words to add three word multiword sense (that occurs in the Turkish wordnet) to the result list. The
 * method then check the previous word and current word; current word and the next word to add a two word multiword
 * sense to the result list. Lastly, the method adds all possible senses of the current word to the result list.
 * @param wordNet Turkish wordnet
 * @param fsm Turkish morphological analyzer
 * @param sentence Sentence to be semantically disambiguated.
 * @param index Position of the word to be disambiguated.
 * @return All possible senses for the word at position index in the given sentence.
 */
vector<SynSet>
SentenceAutoSemantic::getCandidateSynSets(WordNet &wordNet, const FsmMorphologicalAnalyzer &fsm, AnnotatedSentence *sentence,
                                          int index) {
    AnnotatedWord* twoPrevious = nullptr, *previous = nullptr, *current, *twoNext = nullptr, *next = nullptr;
    vector<SynSet> synSets;
    current = (AnnotatedWord*) sentence->getWord(index);
    if (index > 1){
        twoPrevious = (AnnotatedWord*) sentence->getWord(index - 2);
    }
    if (index > 0){
        previous = (AnnotatedWord*) sentence->getWord(index - 1);
    }
    if (index != sentence->wordCount() - 1){
        next = (AnnotatedWord*) sentence->getWord(index + 1);
    }
    if (index < sentence->wordCount() - 2){
        twoNext = (AnnotatedWord*) sentence->getWord(index + 2);
    }
    synSets = wordNet.constructSynSets(current->getParse()->getWord()->getName(),
                                       *current->getParse(), *current->getMetamorphicParse(), fsm);
    if (twoPrevious != nullptr && twoPrevious->getParse() != nullptr && previous->getParse() != nullptr){
        vector<SynSet> vector2 = wordNet.constructIdiomSynSets(*twoPrevious->getParse(), *previous->getParse(), *current->getParse(),
                                                               *twoPrevious->getMetamorphicParse(), *previous->getMetamorphicParse(), *current->getMetamorphicParse(), fsm);
        synSets.insert(synSets.end(), vector2.begin(), vector2.end());
    }
    if (previous != nullptr && previous->getParse() != nullptr && next != nullptr && next->getParse() != nullptr){
        vector<SynSet> vector2 = wordNet.constructIdiomSynSets(*previous->getParse(), *current->getParse(), *next->getParse(),
                                                               *previous->getMetamorphicParse(), *current->getMetamorphicParse(), *next->getMetamorphicParse(), fsm);
        synSets.insert(synSets.end(), vector2.begin(), vector2.end());
    }
    if (next != nullptr && next->getParse() != nullptr && twoNext != nullptr && twoNext->getParse() != nullptr){
        vector<SynSet> vector2 = wordNet.constructIdiomSynSets(*current->getParse(), *next->getParse(), *twoNext->getParse(),
                                                               *current->getMetamorphicParse(), *next->getMetamorphicParse(), *twoNext->getMetamorphicParse(), fsm);
        synSets.insert(synSets.end(), vector2.begin(), vector2.end());
    }
    if (previous != nullptr && previous->getParse() != nullptr){
        vector<SynSet> vector2 = wordNet.constructIdiomSynSets(*previous->getParse(), *current->getParse(),
                                                               *previous->getMetamorphicParse(), *current->getMetamorphicParse(), fsm);
        synSets.insert(synSets.end(), vector2.begin(), vector2.end());
    }
    if (next != nullptr && next->getParse() != nullptr){
        vector<SynSet> vector2 = wordNet.constructIdiomSynSets(*current->getParse(), *next->getParse(),
                                                               *current->getMetamorphicParse(), *next->getMetamorphicParse(), fsm);
        synSets.insert(synSets.end(), vector2.begin(), vector2.end());
    }
    return synSets;
}
