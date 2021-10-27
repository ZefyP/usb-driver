#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED
#include <string>
#include <vector>
/**
 * \brief Fonction qui additionne deux nombre reçus en arguments
 * \param a nombre a
 * \param b nombre b 
 * \return a + b
 */
int addition(int a, int b);
/**
 * @brief Additionne trois nombres entiers 
 * 
 * @param a nombre a
 * @param b nombre b
 * @param c nombre c
 * @return int a+b+c
 */
int addition(int a, int b,int c);
/**
 * @brief Dessine dans la console un rectangle de taille x * y
 * 
 * @param x nombre de colonnes
 * @param y nombre de lignes 
 * @return int status du dessin (0 si ok; 1 si nok)
 */
int drawRect(int x, int y);
/**
 * @brief Met au carré la valeur dans la référence en entrée
 * 
 * @param a Référence vers la valeur à mettre au carré
 * @return int status (0 si ok; 1 si nok)
 */
int carre(int& a);
int carre(double&);
int upper(std::string texte);
/**
 * @brief Fait la moyenne des valeurs dans le tableau
 * 
 * @param tab 
 * @param size 
 * @return double 
 */
double moyenneTab(double *tab,int size);
double moyenneTab(std::vector<double>const& tab);
#endif // MAIN_H_INCLUDED