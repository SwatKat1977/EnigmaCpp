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

class Rotor {
 public:
    Rotor(const std::string& alphabet,
        const std::string& wiring,
        const std::string& notchChars,
        char ringSettingChar = '\0');

    void SetPosition(char pos);

    void Step();

    bool AtNotch() const;

    char EncodeForward(char c) const;
    char EncodeBackward(char c) const;

    size_t GetAlphabetSize() const { return alphabetSize_; }

 private:
    std::string alphabet_;
    size_t alphabetSize_;

    std::vector<int> forwardWiring_;
    std::vector<int> backwardWiring_;
    std::vector<int> notchPositions_;

    int position_;
    int ringSetting_;

    int CharToIndex(char c) const;
    char IndexToChar(int i) const;
};

}   // namespace enigmacpp

#endif  // ROTOR_H_
