#ifndef INITIALISEDIRECTORY_H
#define INITIALISEDIRECTORY_H

#include <QString>

/**
 * @brief Returns (and creates if not present) a subdirectory of the users documents folder with a name specified in config.hpp.
 */
QString initialiseDirectory();

#endif