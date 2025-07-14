#include <gtest/gtest.h>
#include "RotorFactory.h"

using namespace enigmacpp;

TEST(RotorFactoryTest, CreateDefaultRotors) {
    RotorFactory factory;

    // Rotor I
    auto rotor1 = factory.CreateRotor(ROTOR_ENIGMA1_I);
    EXPECT_NE(rotor1, nullptr);

    // Rotor II
    auto rotor2 = factory.CreateRotor(ROTOR_ENIGMA1_II);
    EXPECT_NE(rotor2, nullptr);

    // Rotor III
    auto rotor3 = factory.CreateRotor(ROTOR_ENIGMA1_III);
    EXPECT_NE(rotor3, nullptr);
}

TEST(RotorFactoryTest, CreateRotorWithCustomSettings) {
    RotorFactory factory;
    auto rotor = factory.CreateRotor(ROTOR_ENIGMA1_II, 'C', 'D');

    EXPECT_NE(rotor, nullptr);
    // You could check internal state if Rotor exposes relevant accessors
    // e.g. EXPECT_EQ(rotor->GetRingSetting(), 'C');
    //       EXPECT_EQ(rotor->GetPosition(), 'D');
}

TEST(RotorFactoryTest, ThrowsOnUnknownRotor) {
    RotorFactory factory;
    EXPECT_THROW(factory.CreateRotor("NonExistentRotor"), std::invalid_argument);
}

TEST(RotorFactoryTest, CanRegisterAndCreateCustomRotor) {
    RotorFactory factory;
    factory.RegisterRotor("CustomRotor", "ABCDEF", "BADCFE", "D");

    auto rotor = factory.CreateRotor("CustomRotor", 'B', 'C');
    EXPECT_NE(rotor, nullptr);

    // Again, test wiring/alphabet/notch logic if Rotor exposes accessors
}

