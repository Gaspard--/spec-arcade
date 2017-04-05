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
    virtual void setSize(unsigned int (&size)[2]) = 0;
    
    /*
     * The implementation shall open name + an extension depending on the lib (like .txt or .png)
     */
    virtual unsigned int loadSpriteSheet(std::string const &name, unsigned int (&size)[2]) = 0;

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
     * clears the screen
     */
    virtual void clear() = 0;

    /*
     * refreshes the screen, can be a noop
     */
    virtual void render() = 0;

    /*
     * Enum for key handling
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
	FULLSCREEN = 12,
        SIZE = 13,
      };

    /*
     * Register callBack for given key.
     */
    virtual void registerCallBack(KeyCode k, std::function<void(void)>) = 0;
  };
};

/*
 * Creates an display::IDisplay.
 */
extern "C" std::unique_ptr<display::IDisplay> createDisplay();

#endif
