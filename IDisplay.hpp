#ifndef IDISPLAY_HPP
# define IDISPLAY_HPP

#include <string>
#include <functional>
#include <memory>

namespace display
{
  /*
   * This interface is responsible for all the graphic library.
   */
  class IDisplay
  {
  public:
    /*
     * Represents a sprite in a sprite sheet.
     * The given index is ligne major, and indexed from the top left to the bottom right.
     * ex: 0 1 2
     *     3 4 5
     * This struct should be passed by value.
     * Rational: it's sizeof is 8, which is the size of pointers on most modern architectures, the size of a pointer.
     */
    struct Sprite
    {
      unsigned int spriteSheet;
      unsigned int index;
    };

    /*
     * The implementation shall free every texture loaded.
     */
    virtual ~IDisplay() = default;

    /*
    * size: the game size
    */
    virtual void setSize(unsigned int const (&size)[2]) = 0;

    /*
     * The implementation shall open name + an extension depending on the lib (like .txt or .png)
     */
    virtual unsigned int loadSpriteSheet(std::string const &name, unsigned int const (&size)[2]) = 0;

    /*
     * The implementation shall free all SpriteSheets
     */
    virtual void clearSpriteSheets() = 0;

    /*
     * The implementation shall clear all registered callbacks
     */
    virtual void clearCallbacks(void) = 0;

    /*
     * The implementation shall render the sprite upon the render function call.
     * The position represents a position in game coordinates.
     */
    virtual void renderSprite(Sprite, float const (&pos)[2]) = 0;

    /*
     * Overload of previous function. For situations where float precisness isn't needed.
     */
    virtual void renderSprite(Sprite, int const (&pos)[2]) = 0;

    /*
     * The implementation shall render the grid of size 'size'.
     * The 'provider' parameter provides the sprite for each each tile given each corrdinate.
     */
    virtual void renderGrid(std::function<Sprite(unsigned int const (&pos)[2])> provider) = 0;

    /*
     * Convenience function : renders the grid.
     * Uses one spriteSheet and renders with the given indices.
     */
    virtual void renderGrid(unsigned int spriteSheet, unsigned int const *indices) = 0;

    /*
     * Convenience function : renders the grid.
     * Takes a array of sprites to render.
     */
    virtual void renderGrid(Sprite const *sprites) = 0;

    /*
     * Renders the sprite as background.
     */
    virtual void renderBackground(Sprite sprite) = 0;

    /*
     * Load a font, if applicable
     */
    virtual void loadFont(std::string const &name) = 0;

    /*
     * render text.
     */
    virtual void renderText(std::string const &text, unsigned int const (&pos)[2]) = 0;

    /*
     * clears the screen
     */
    virtual void clear() = 0;

    /*
     * refreshes the screen, can be a noop
     * If true is returned, the program will (to handle closing windows, etc)
     */
    virtual bool render() = 0;

    /*
     * Enum for key handling
     * Keys not present in this enum have an implementation defined behavior.
     * Multiple keys are allowed to trigger a same KeyCode.
     */
    enum class KeyCode: unsigned int
      {
        ESC = 0,
	TWO = 1,
	THREE = 2,
	FOUR = 3,
	FIVE = 4,
	EIGHT = 5,
        NINE = 6,
	UP = 7,
	DOWN = 8,
	LEFT = 9,
	RIGHT = 10,
	SHOOT = 11,
	LETTER_A = 12,
	LETTER_B = LETTER_A + 'b' - 'a',
	LETTER_C = LETTER_A + 'c' - 'a',
	LETTER_D = LETTER_A + 'd' - 'a',
	LETTER_E = LETTER_A + 'e' - 'a',
	LETTER_F = LETTER_A + 'f' - 'a',
	LETTER_G = LETTER_A + 'g' - 'a',
	LETTER_H = LETTER_A + 'h' - 'a',
	LETTER_I = LETTER_A + 'i' - 'a',
	LETTER_J = LETTER_A + 'j' - 'a',
	LETTER_K = LETTER_A + 'k' - 'a',
	LETTER_L = LETTER_A + 'l' - 'a',
	LETTER_M = LETTER_A + 'm' - 'a',
	LETTER_N = LETTER_A + 'n' - 'a',
	LETTER_O = LETTER_A + 'o' - 'a',
	LETTER_P = LETTER_A + 'p' - 'a',
	LETTER_Q = LETTER_A + 'q' - 'a',
	LETTER_R = LETTER_A + 'r' - 'a',
	LETTER_S = LETTER_A + 's' - 'a',
	LETTER_T = LETTER_A + 't' - 'a',
	LETTER_U = LETTER_A + 'u' - 'a',
	LETTER_V = LETTER_A + 'v' - 'a',
	LETTER_W = LETTER_A + 'w' - 'a',
	LETTER_X = LETTER_A + 'x' - 'a',
	LETTER_Y = LETTER_A + 'y' - 'a',
	LETTER_Z = LETTER_A + 'z' - 'a',
        SIZE,
      };

    /*
     * Register callBack for given key.
     */
    virtual void registerCallBack(KeyCode k, std::function<void(void)>) = 0;

    /*
     * Register global callBack, called if no callback exists for given key.
     */
    virtual void registerGlobalCallBack(std::function<void(KeyCode)>) = 0;
  };
};

/*
 * Creates an display::IDisplay.
 */
extern "C" std::unique_ptr<display::IDisplay> createDisplay();

#endif
