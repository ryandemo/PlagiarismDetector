/*
600.120.01 CS120 Intermediate Programming
Final Project - Plagiarism Detector
PlagiarismDetector.hpp - header for a plagiarism detector model
12/1/2016

Ryan Demo
rdemo1
rdemo1@jhu.edu

Mengying Pan
mpan4
mpan4@jhu.edu
*/

#ifndef CS120_PLAGIARISM_DETECTOR_HPP
#define CS120_PLAGIARISM_DETECTOR_HPP

#include <string>
#include <vector>
#include <tuple>
#include <set>
#include <cassert>
#include "NgramCollection.hpp"


/* Sensitivities corresponding to level of detection granularity. */
enum Sensitivity { low = 4, medium = 3, high = 2, invalid = 0 };



/* Model that holds a collection of NgramDocuments and can perform plagiarism detection on them. */
class PlagiarismDetector {

public:

  /* Constructor; need to specify sensitivity. */
  PlagiarismDetector(Sensitivity s) : n((unsigned int)s)  { }

  /* Takes name of a file that contains paths to the documents. */
  std::vector<std::string> readFileList(std::string &fname);

  /* Detects any documents listed in the file list that may be plagiarized, to the initialized sensitivity.
   * Results stored in matches variable. */
  void detect();

  /* Returns a set of tuples with the possible detected matches. */
  std::set<std::tuple<std::string, std::string>> getPossibleMatches();

  /* toString to test purpose. */
  std::string toString();

  /* toString to test sentences. */
  std::string sentenceToString();
  
private:

  /* Simple class to hold a filename and its ngram collection. */
  class NgramDocument {

  public:

    /* Constructor: need to specify n. */
    NgramDocument(std::string fname, int n) : name(fname), ngrams(n) { assert(n > 1); }

    /* Checks if another NgramDocument is suspect of plagiarizing the current NgramDocument. */
    bool isPlagiarismSuspect(NgramDocument &other);

    /* The name of the file. */
    std::string name;

    /* The ngrams model of the file. */
    NgramCollection ngrams;

    /* Return a vector of ngram collections representing each sentence. */
    std::vector<NgramCollection> sentenceNgrams;

  };

  
  /* The n value corresponding to the sensitivity to which the detector is calibrated. */
  unsigned int n;

  /* Whether detection has previously been ran on this object with the same files. */
  bool detectionPerformed = false;

  /* Read a list of paths from a file. */
  std::vector<std::string> readNames(std::string &listFile);

  /* Add text from the given document file to the model. */
  void addTextFromFile(std::string &fname);

  /* Add ngrams to the model from a vector of words. */
  void buildNgramDoc(const std::string &fname, const std::vector<std::string> &text, const std::vector<NgramCollection> &sentences);
  
  /* Holds the ngram collection of each file. */
  std::vector<NgramDocument> documents;

  /* The set of possible matches. */
  std::set<std::tuple<unsigned int, unsigned int>> matches;

};


/* Overloads << for a set of string tuples. */
std::ostream& operator<<(std::ostream& out, const std::set<std::tuple<std::string, std::string>>& strTuples);


#endif

