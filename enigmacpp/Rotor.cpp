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
#include "Rotor.h"

namespace enigmacpp {

Rotor::Rotor(const std::string& alphabet,
    const std::string& wiring,
    const std::string& notchChars,
    char ringSettingChar)
    : alphabet_(alphabet),
    alphabetSize_(alphabet.size()),
    position_(0),
    ringSetting_(0) {
    if (wiring.size() != alphabetSize_) {
        throw std::invalid_argument("Wiring and alphabet must be same length");
    }

    forwardWiring_.resize(alphabetSize_);
    backwardWiring_.resize(alphabetSize_);

    // Set up wiring
    for (size_t i = 0; i < alphabetSize_; ++i) {
        size_t from = i;
        size_t to = CharToIndex(wiring[i]);
        forwardWiring_[from] = static_cast<int>((to - from + alphabetSize_) %
                               alphabetSize_);
        backwardWiring_[to] = static_cast<int>((from - to + alphabetSize_) %
                              alphabetSize_);
    }

    // Set notches
    for (char c : notchChars) {
        notchPositions_.push_back(CharToIndex(c));
    }

    // Set ring setting if provided
    if (ringSettingChar != '\0')
        ringSetting_ = CharToIndex(ringSettingChar);
}

void Rotor::SetPosition(char pos) {
    position_ = CharToIndex(pos);
}

void Rotor::Step() {
    position_ = (position_ + 1) % alphabetSize_;
}

bool Rotor::AtNotch() const {
    return std::find(notchPositions_.begin(), notchPositions_.end(),
                     position_) != notchPositions_.end();
}

char Rotor::EncodeForward(char c) const {
    int input = static_cast<int>(CharToIndex(c));
    int alphabetSize = static_cast<int>(alphabetSize_);

    int shifted = (input + position_ - ringSetting_ + alphabetSize) %
                  alphabetSize_;
    int wired = (shifted + forwardWiring_[shifted]) % alphabetSize;
    int output = (wired - position_ + ringSetting_ + alphabetSize) %
                 alphabetSize_;
    return IndexToChar(output);
}

char Rotor::EncodeBackward(char c) const {
    int input = CharToIndex(c);
    int alphabetSize = static_cast<int>(alphabetSize_);

    int shifted = (input + position_ - ringSetting_ + alphabetSize) %
                  alphabetSize;
    int wired = (shifted + backwardWiring_[shifted]) % alphabetSize;
    int output = (wired - position_ + ringSetting_ + alphabetSize) %
                 alphabetSize;
    return IndexToChar(output);
}

int Rotor::CharToIndex(char c) const {
    auto it = alphabet_.find(c);

    if (it == std::string::npos) {
        throw std::invalid_argument(std::string("Invalid character: ") + c);
    }

    return static_cast<int>(it);
}

char Rotor::IndexToChar(int i) const {
    return alphabet_[i % alphabetSize_];
}

}   // namespace enigmacpp
