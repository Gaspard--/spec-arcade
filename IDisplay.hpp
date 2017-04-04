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
     * The implementation shall open name + an extension depending on the lib (like .txt or .png)
     */
    virtual unsigned int loadSpriteSheet(std::string const &name, unsigned int (&size)[2]) = 0;

    /*
     * Does not need to be called: the implementaion shall free texture prematurely.
     * (Textures shall also be freed upon IDisplay destruction)
     */
    virtual void freeSpritSheet(unsigned int spritSheet) = 0;

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
     * The implementation shall render a grid of size 'size'.
     * The 'provider' parameter provides the sprite for each each tile given each corrdinate.
     */
    virtual void renderGrid(std::function<Sprite(unsigned int const (&pos)[2])> provider,
			    unsigned int const (&size)[2]) = 0;

    /*
     * Convenience function : renders a grid.
     * Uses one spriteSheet and renders with the given indices.
     */
    virtual void renderGrid(unsigned int spriteSheet, unsigned int const *indices,
			    unsigned int const (&size)[2]) = 0;

    /*
     * Convenience function : renders a grid.
     * Takes a array of sprites to render.
     */
    virtual void renderGrid(Sprite const *sprites, unsigned int const (&size)[2]) = 0;

    /*
     * Renders the sprite as background.
     */
    virtual void renderBackground(Sprite const sprite) = 0;

    /*
     * refreshes the screen
     */
    virtual void render() = 0;
  };
};

extern "C" std::unique_ptr<display::IDisplay> createDisplay();

#endif
