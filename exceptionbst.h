#ifndef EXCEPTIONBST_H
#define EXCEPTIONBST_H

#include <stdexcept>
#include <string>

/**
 * @author Armanini Justin
 * 
 * @section Description 
 * Classe che implementa eccezione nel caso di inserimento di un elemento duplicato
 * in un albero binario di ricerca
 * 
 * @brief Eccezione elemento duplicato
 */

class duplicated_value : public std::logic_error
{
    public:
        /**
         * Costruttore
         */
        duplicated_value(const std::string &message);
};

#endif