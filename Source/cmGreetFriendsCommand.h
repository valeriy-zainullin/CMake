/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#pragma once

#include "cmConfigure.h" // IWYU pragma: keep

#include <string>
#include <vector>

class cmExecutionStatus;

/**
 * \brief Greet friends through stdout.
 *
 * cmGreetFriendsCommand prints a random greet message.
 */
bool cmGreetFriendsCommand(std::vector<std::string> const& args,
                    cmExecutionStatus& status);
