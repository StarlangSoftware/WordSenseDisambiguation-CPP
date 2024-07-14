//
// Created by Olcay Taner YILDIZ on 16.02.2021.
//

#include "Lesk.h"

/**
 * Constructor for the Lesk class. Gets the Turkish wordnet and Turkish fst based
 * morphological analyzer from the user and sets the corresponding attributes.
 * @param turkishWordNet Turkish wordnet
 * @param fsm Turkish morphological analyzer
 */
Lesk::Lesk(const WordNet &turkishWordNet, const FsmMorphologicalAnalyzer &fsm) {
    this->turkishWordNet = turkishWordNet;
    this->fsm = fsm;
}

/**
 * Calculates the number of words that occur (i) in the definition or example of the given synset and (ii) in the
 * given sentence.
 * @param synSet Synset of which the definition or example will be checked
 * @param sentence Sentence to be annotated.
 * @return The number of words that occur (i) in the definition or example of the given synset and (ii) in the given
 * sentence.
 */
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

/**
 * The method annotates the word senses of the words in the sentence according to the simplified Lesk algorithm.
 * Lesk is an algorithm that chooses the sense whose definition or example shares the most words with the target
 * word’s neighborhood. The algorithm processes target words one by one. First, the algorithm constructs an array of
 * all possible senses for the target word to annotate. Then for each possible sense, the number of words shared
 * between the definition of sense synset and target sentence is calculated. Then the sense with the maximum
 * intersection count is selected.
 * @param sentence Sentence to be annotated.
 * @return True, if at least one word is semantically annotated, false otherwise.
 */
bool Lesk::autoLabelSingleSemantics(AnnotatedSentence *sentence) {
    bool done = false;
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
            done = true;
            ((AnnotatedWord*) sentence->getWord(i))->setSemantic(maxSynSets.at(random() % maxSynSets.size()).getId());
        }
    }
    return done;
}
