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
#ifndef REFLECTOR_H_
#define REFLECTOR_H_
#include <string>
#include <vector>


namespace enigmacpp {

/**
 * @class Reflector
 * @brief Represents the reflector component in the Enigma machine.
 *
 * The Reflector performs a fixed, non-reversible character substitution
 * using an internally defined wiring. It reflects the signal back through
 * the rotors to ensure symmetric encryption. The wiring must be an involution,
 * meaning applying it twice yields the original character.
 */
class Reflector {
 public:
    /**
     * @brief Constructs a Reflector with the specified wiring.
     * @param alphabet The set of valid characters (e.g., "ABCDEFGHIJKLMNOPQRSTUVWXYZ").
     * @param wiring A permutation of the alphabet defining the reflector's substitution wiring.
     * @throws std::invalid_argument if the wiring and alphabet differ in length,
     *         contain invalid characters, or do not form a valid reflector mapping.
     */
    Reflector(const std::string& alphabet, const std::string& wiring);

    /**
     * @brief Reflects an input character using the reflector wiring.
     * @param input The character to reflect.
     * @return The character mapped by the reflector.
     * @throws std::invalid_argument if the input character is not in the alphabet.
     */
    char Reflect(char input) const;

 private:
    /// The valid character set used for mapping.
    std::string alphabet_;

    /// Internal forward mapping from character index to reflected index
    std::vector<int> forwardMap_;
};

}   // namespace enigmacpp

#endif  // REFLECTOR_H_
