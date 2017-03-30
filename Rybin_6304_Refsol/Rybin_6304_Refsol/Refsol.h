/*!
\file
\brief Refsol header file
\author Rybin Aleksandr 1 course 2 half
\date 30.03.2017
\version 2.0
*/

#include "Generator.h"

#define Sizeof_Commands 10		//!< Start min lenth of vector reading commands

/*!
\brief Read commands from file
\param[in] commands File with commands
\return info Info about readed vector
\ingroup Refsol
*/
Vector Read_Commands(FILE* commands);

