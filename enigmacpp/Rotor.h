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
#ifndef ROTOR_H_
#define ROTOR_H_
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace enigmacpp {

/**
 * @class Rotor
 * @brief Represents a single rotor in the Enigma machine.
 *
 * A Rotor performs character substitution based on its internal wiring,
 * ring setting, and position. It supports bidirectional encoding, stepping,
 * and notch detection, which triggers rotation in adjacent rotors.
 */
class Rotor {
 public:
    /**
     * @brief Constructs a Rotor with specified wiring and settings.
     * @param alphabet The valid set of characters used by the rotor.
     * @param wiring A permutation of the alphabet representing forward wiring.
     * @param notchChars Characters that indicate the rotor notch positions.
     * @param ringSettingChar Optional ring setting character (default '\0').
     * @throws std::invalid_argument if the wiring and alphabet are different
               lengths.
     */
    Rotor(const std::string& alphabet,
        const std::string& wiring,
        const std::string& notchChars,
        char ringSettingChar = '\0');

    /**
     * @brief Sets the current rotor position using a character.
     * @param pos The character to set the rotor position to.
     */
    void SetPosition(char pos);

    /**
     * @brief Steps the rotor forward by one position (modular rotation).
     */
    void Step();

    /**
     * @brief Checks whether the rotor is at a notch position.
     * @return true if rotor is at notch position, false otherwise.
     */
    bool AtNotch() const;

    /**
     * @brief Encodes a character in the forward direction through the rotor.
     * @param c The input character to encode.
     * @return The encoded character after passing through the rotor forward.
     */
    char EncodeForward(char c) const;

    /**
     * @brief Encodes a character in the backward direction through the rotor.
     * @param c The input character to encode.
     * @return The encoded character after passing through the rotor backward.
     */
    char EncodeBackward(char c) const;

    /**
     * @brief Returns the size of the rotor's alphabet.
     * @return The number of characters in the alphabet.
     */
    size_t GetAlphabetSize() const { return alphabetSize_; }

 private:
    std::string alphabet_;             /// Valid character set for the rotor.
    size_t alphabetSize_;              /// No of characters in the alphabet.

    std::vector<int> forwardWiring_;   /// Forward wiring transformation.
    std::vector<int> backwardWiring_;  /// Backward wiring transformation.
    std::vector<int> notchPositions_;  /// Indices of notch trigger positions.

    int position_;                     /// Current rotor position (index-based).
    int ringSetting_;                  /// Ring setting offset (index-based).

    /**
     * @brief Converts a character to its index in the alphabet.
     * @param c The character to convert.
     * @return Index of the character in the alphabet.
     * @throws std::invalid_argument if the character is not in the alphabet.
     */
    int CharToIndex(char c) const;

    /**
     * @brief Converts an index back to a character in the alphabet.
     * @param i The index to convert.
     * @return The corresponding character.
     */
    char IndexToChar(int i) const;
};

}   // namespace enigmacpp

#endif  // ROTOR_H_
