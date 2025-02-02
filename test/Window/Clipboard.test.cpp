#include <SFML/Window/Clipboard.hpp>

// Other 1st party headers
#include <SFML/System/String.hpp>

#include <catch2/catch_test_macros.hpp>

#include <WindowUtil.hpp>

TEST_CASE("[Window] sf::Clipboard", runDisplayTests())
{
    // Capture current clipboard state
    const auto currentClipboard = sf::Clipboard::getString();

    SECTION("Set/get string")
    {
        sf::Clipboard::setString("Welcome to SFML!");
        CHECK(sf::Clipboard::getString() == "Welcome to SFML!");
    }

    SECTION("Set/get CJK string")
    {
        const sf::String str(U"Welcome \u65E5!");
        sf::Clipboard::setString(str);
        CHECK(sf::Clipboard::getString() == str);
    }

    SECTION("Set/get non-BMP emoji string")
    {
        const sf::String str(U"Welcome \U0001F40C!");
        sf::Clipboard::setString(str);
        CHECK(sf::Clipboard::getString() == str);
    }

    // Restore clipboard
    sf::Clipboard::setString(currentClipboard);

    // We rely on getString triggering clipboard event processing on X11 to make
    // setString work, but note that the way setString is guaranteed to work is
    // by having an open window for which events are being handled.
    CHECK(sf::Clipboard::getString() == currentClipboard);
}
