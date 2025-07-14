/*
This source file is part of EnigmaCpp
For the latest info, see https://github.com/SwatKat1977/EnigmaCpp

Copyright 2025 SwatKat1977

    This program is free software : you can redistribute it and /or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see < https://www.gnu.org/licenses/>.
*/
#ifndef ROTORFACTORY_H_
#define ROTORFACTORY_H_
#include <memory>
#include <string>
#include <unordered_map>
#include "Rotor.h"

namespace enigmacpp {

// Names of Enigma 1 rotors

// Enigma1 I rotor I : Introduced 1930
const char ROTOR_ENIGMA1_I[] = "Enigma1_I";

// Enigma1 I rotor II : Introduced 1930
const char ROTOR_ENIGMA1_II[] = "Enigma1_II";

// Enigma1 I rotor III : Introduced 1930
const char ROTOR_ENIGMA1_III[] = "Enigma1_III";

/**
 * @class RotorFactory
 * @brief Factory for creating and registering Enigma rotors.
 */
class RotorFactory {
 public:
    /**
     * @brief Constructs a new RotorFactory instance.
     */
    RotorFactory();

    /**
     * @brief Creates a rotor instance by name with optional ring and
     *        start position.
     * @param name Name of the rotor to create.
     * @param ringSetting Ring setting character (default 'A').
     * @param startPosition Start position character (default 'A').
     * @return A unique_ptr to the created Rotor instance.
     */
    std::unique_ptr<Rotor> CreateRotor(const std::string& name,
                                       char ringSetting = 'A',
                                       char startPosition = 'A') const;

    /**
     * @brief Registers a new rotor definition for later creation.
     * @param name Name to register the rotor under.
     * @param alphabet Alphabet the rotor uses.
     * @param wiring Wiring string defining rotor substitution.
     * @param notchPositions Positions that trigger stepping of next rotor.
     */
    void RegisterRotor(const std::string& name,
        const std::string& alphabet,
        const std::string& wiring,
        const std::string& notchPositions);

 private:
    /**
     * @struct RotorDefinition
     * @brief Holds the properties that define a rotor.
     */
    struct RotorDefinition {
        std::string alphabet;     /// The alphabet used by the rotor.
        std::string wiring;       /// Wiring substitution pattern.
        std::string notches;      /// Notch positions triggering stepping.
    };

    /// Map of rotor names to definitions.
    std::unordered_map<std::string, RotorDefinition> rotorDefinitions_;
};

}   // namespace enigmacpp

#endif  // ROTORFACTORY_H_
