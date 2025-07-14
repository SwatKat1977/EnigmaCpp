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
#include <stdexcept>
#include "Reflector.h"

namespace enigmacpp {

Reflector::Reflector(const std::string& alphabet, const std::string& wiring)
    : alphabet_(alphabet) {
    if (alphabet.size() != wiring.size()) {
        throw std::invalid_argument(
            "Reflector wiring must match alphabet length.");
    }

    size_t N = alphabet.size();
    forwardMap_.resize(N, -1);

    for (size_t i = 0; i < N; ++i) {
        int index = static_cast<int>(i);
        int inputIndex = index;
        int outputIndex = static_cast<int>(alphabet.find(wiring[index]));

        if (outputIndex == std::string::npos) {
            throw std::invalid_argument(
                "Invalid character in reflector wiring.");
        }

        if (forwardMap_[inputIndex] != -1 || forwardMap_[outputIndex] != -1) {
            throw std::invalid_argument(
                "Reflector must be symmetric and non-overlapping.");
        }

        forwardMap_[inputIndex] = outputIndex;
        forwardMap_[outputIndex] = inputIndex;
    }
}

char Reflector::Reflect(char input) const {
    int inputIndex = static_cast<int>(alphabet_.find(input));
    if (inputIndex == std::string::npos) {
        throw std::invalid_argument("Input character not in alphabet.");
    }

    int outputIndex = forwardMap_[inputIndex];
    return alphabet_[outputIndex];
}

}   // namespace enigmacpp
