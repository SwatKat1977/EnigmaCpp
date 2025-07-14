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

class RotorFactory {
public:
    RotorFactory();

    std::unique_ptr<Rotor> CreateRotor(const std::string& name,
        char ringSetting = 'A',
        char startPosition = 'A') const;

    void RegisterRotor(const std::string& name,
        const std::string& alphabet,
        const std::string& wiring,
        const std::string& notchPositions);

private:
    struct RotorDefinition {
        std::string alphabet;
        std::string wiring;
        std::string notches;
    };

    std::unordered_map<std::string, RotorDefinition> rotorDefinitions_;
};

}   // namespace enigmacpp

#endif  // ROTORFACTORY_H_
