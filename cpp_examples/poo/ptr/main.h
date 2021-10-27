#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <stdlib.h>
#include <time.h>
#include "Personnage.h"
/**
 * @brief Get the Action From User object
 * 
 * @param choix 
 * @return true 
 * @return false 
 */
bool getActionFromUser(int &choix);
/**
 * @brief Get the Name From User object
 * 
 * @param nom 
 * @return true 
 * @return false 
 */
bool getNameFromUser(std::string &nom);
/**
 * @brief process
 * 
 * @param choix 
 * @param actif 
 * @param autre 
 * @return true 
 * @return false 
 */
bool gameProcess(int choix, Personnage *actif, Personnage *autre);
#endif // MAIN_H_INCLUDED
