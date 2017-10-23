//Modified by Svetleen Guerrier
/** Listing 7-6.
    @file PrecondViolatedExcep.cpp */
#include "PreconditionViolatedException.h"

PreconditionViolatedException::PreconditionViolatedException(const string& message): logic_error("Precondition Violated Exception: " + message)
{
}  // end constructor

// End of implementation file.
