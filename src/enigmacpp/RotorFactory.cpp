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
#include "RotorFactory.h"

namespace enigmacpp {

// ------------------------------------------------------------------
// Enigma 1 rotor constants
// ------------------------------------------------------------------

const char ENIGMA1_ALPHABET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char ENIGMA1_1_WIRING[] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
const char ENIGMA1_1I_WIRING[] = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
const char ENIGMA1_III_WIRING[] = "BDFHJLCPRTXVZNYEIWGAKMUSQO";

const char ENIGMA1_1_NOTCHES[] = "Q";
const char ENIGMA1_1I_NOTCHES[] = "E";
const char ENIGMA1_III_NOTCHES[] = "V";

RotorFactory::RotorFactory() {
    // Register Enigma 1 rotors (I, II, III)
    RegisterRotor(ROTOR_ENIGMA1_I,
                  ENIGMA1_ALPHABET,
                  ENIGMA1_1_WIRING,
                  ENIGMA1_1_NOTCHES);
    RegisterRotor(ROTOR_ENIGMA1_II,
                  ENIGMA1_ALPHABET,
                  ENIGMA1_1I_WIRING,
                  ENIGMA1_1I_NOTCHES);
    RegisterRotor(ROTOR_ENIGMA1_III,
                  ENIGMA1_ALPHABET,
                  ENIGMA1_III_WIRING,
                  ENIGMA1_III_NOTCHES);
}

std::unique_ptr<Rotor> RotorFactory::CreateRotor(const std::string& name,
                                                 char ringSetting,
                                                 char startPosition) const {
    auto it = rotorDefinitions_.find(name);
    if (it == rotorDefinitions_.end())
        throw std::invalid_argument("Unknown rotor type: " + name);

    const auto& def = it->second;
    auto rotor = std::make_unique<Rotor>(def.alphabet,
                                         def.wiring,
                                         def.notches,
                                         ringSetting);
    rotor->SetPosition(startPosition);
    return rotor;
}

void RotorFactory::RegisterRotor(const std::string& name,
    const std::string& alphabet,
    const std::string& wiring,
    const std::string& notchPositions) {
    rotorDefinitions_[name] = { alphabet, wiring, notchPositions };
}

}   // namespace enigmacpp
