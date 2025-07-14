#include "Rotor.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

using namespace enigmacpp;

class RotorTest : public ::testing::Test {
protected:
    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string wiring = "EKMFLGDQVZNTOWYHXUSPAIBRCJ"; // Rotor I
    const std::string notch = "Q"; // Rotor I notches at Q
};

TEST_F(RotorTest, ConstructorThrowsIfWiringWrongLength) {
    EXPECT_THROW(
        Rotor(alphabet, "SHORTWIRING", notch),
        std::invalid_argument
    );
}

TEST_F(RotorTest, ConstructorThrowsOnInvalidWiringChar) {
    std::string badWiring = wiring;
    badWiring[0] = '#'; // not in alphabet
    EXPECT_THROW(
        Rotor(alphabet, badWiring, notch),
        std::invalid_argument
    );
}

TEST_F(RotorTest, ConstructorThrowsOnInvalidNotchChar) {
    EXPECT_THROW(
        Rotor(alphabet, wiring, "1"),
        std::invalid_argument
    );
}

TEST_F(RotorTest, SetPositionAcceptsValidChar) {
    Rotor rotor(alphabet, wiring, notch);
    rotor.SetPosition('B'); // Should not throw
}

TEST_F(RotorTest, SetPositionThrowsOnInvalidChar) {
    Rotor rotor(alphabet, wiring, notch);
    EXPECT_THROW(rotor.SetPosition('#'), std::invalid_argument);
}

TEST_F(RotorTest, StepWrapsAround) {
    Rotor rotor(alphabet, wiring, notch);
    for (int i = 0; i < 26; ++i)
        rotor.Step();
    rotor.Step(); // wraps from Z to A
    EXPECT_NO_THROW(rotor.EncodeForward('A')); // Just to trigger internal logic
}

TEST_F(RotorTest, AtNotchReturnsTrueAtNotchPosition) {
    Rotor rotor(alphabet, wiring, notch);
    rotor.SetPosition('Q');
    EXPECT_TRUE(rotor.AtNotch());
}

TEST_F(RotorTest, AtNotchReturnsFalseOtherwise) {
    Rotor rotor(alphabet, wiring, notch);
    rotor.SetPosition('P');
    EXPECT_FALSE(rotor.AtNotch());
}

TEST_F(RotorTest, EncodeForwardBasic) {
    Rotor rotor(alphabet, wiring, notch);
    rotor.SetPosition('A');
    rotor.Step();  // to B
    char encoded = rotor.EncodeForward('A');
    EXPECT_TRUE(isalpha(encoded));
}

TEST_F(RotorTest, EncodeBackwardBasic) {
    Rotor rotor(alphabet, wiring, notch);
    rotor.SetPosition('A');
    rotor.Step();  // to B
    char encoded = rotor.EncodeForward('A');
    char decoded = rotor.EncodeBackward(encoded);
    EXPECT_EQ(decoded, 'A');
}

TEST_F(RotorTest, EncodeForwardWithRingSetting) {
    Rotor rotor(alphabet, wiring, notch, 'B'); // ring setting of B (1)
    rotor.SetPosition('A');
    char result = rotor.EncodeForward('A');
    EXPECT_TRUE(isalpha(result));
}

TEST_F(RotorTest, EncodeBackwardWithRingSetting) {
    Rotor rotor(alphabet, wiring, notch, 'C'); // ring setting of C (2)
    rotor.SetPosition('A');
    char result = rotor.EncodeBackward('A');
    EXPECT_TRUE(isalpha(result));
}

TEST_F(RotorTest, CharToIndexThrowsForInvalidChar) {
    Rotor rotor(alphabet, wiring, notch);
    EXPECT_THROW(rotor.EncodeForward('#'), std::invalid_argument);
}

TEST_F(RotorTest, IndexToCharWrapsProperly) {
    Rotor rotor(alphabet, wiring, notch);
    // Call indirectly via EncodeBackward
    rotor.SetPosition('Z');
    rotor.Step(); // Wraps to A
    char encoded = rotor.EncodeForward('Z');
    char decoded = rotor.EncodeBackward(encoded);
    EXPECT_EQ(decoded, 'Z');
}

TEST_F(RotorTest, AlphabetSizeIsCorrect) {
    Rotor rotor(alphabet, wiring, notch);
    EXPECT_EQ(rotor.GetAlphabetSize(), alphabet.size());
}
