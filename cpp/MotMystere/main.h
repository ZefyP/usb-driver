#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Get the Word From Player1
 * 
 * @param word 
 * @return int status
 */
int getWordFromPlayer1(std::string& word);
/**
 * @brief Get the Word From French Dict
 * 
 * @param word 
 * @return int status
 */
int getWordFromFrenchDict(std::string& word);
/**
 * @brief shuffle the word string and put the result into the result string
 * 
 * @param word 
 * @param result 
 * @return int status
 */
int shuffle(std::string const word, std::string& result);
/**
 * @brief Get the Word From Player2 
 * 
 * @param shuffled shuffled word to print
 * @param word answer from P2
 * @return int status (0 = win)
 */
int getWordFromPlayer2(std::string shuffled, std::string& word,std::string const secret);
/**
 * @brief Fin de partie
 * 
 * @param choix 
 * @return int status
 */
int FinDePartie(bool& choix);
#endif // MAIN_H_INCLUDED
