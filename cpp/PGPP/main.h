#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
/**
 * @brief Get the Number from user
 * 
 * @param number number ref
 * @return int status
 */
int getNumber(int& number);
/**
 * @brief Set the Random Number 
 * 
 * @param number 
 * @return int status
 */
int setRandomNumber(int& number);
/**
 * @brief Fonction de fin de partie
 * 
 * @param choix 
 * @return int status
 */
int FinDePartie(bool& choix);
/**
 * @brief Check if string is a number
 * 
 * @param str 
 * @return boolean answer
 */
bool isNumber (std::string const str);
/**
 * @brief Get name from player
 *
 * @param playerName
 * @ return int status
 */
int getPlayerName(std::string& playerName);
#endif // MAIN_H_INCLUDED
