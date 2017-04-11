//
// IGame.hpp for  in /home/grange_c/rendu/arcade/common
//
// Made by Benjamin Grange
// Login   <grange_c@epitech.net>
//
// Started on  Thu Apr 06 15:46:31 2017 Benjamin Grange
// Last update Tue Apr 11 17:03:35 2017 Jakob Kellendonk
//

#ifndef AGAME_HPP
# define AGAME_HPP

# include <functional>
# include <memory>
# include <map>

namespace display  {
  class IDisplay;
};

namespace arcade
{
  class IGame
  {
    public:
      virtual ~IGame(void) {}

      /// Load the game for the given display
      virtual void loadDisplay(display::IDisplay &) = 0;

      /// Update the game
      virtual void update(void) = 0;

      /// Render the game
      virtual void render(display::IDisplay &) = 0;

      virtual void registerGameOverCallback(std::function<void(std::string const, unsigned int)>) = 0;

    private:
      /// Write a arcade::WhereAmI structure to stdout
      virtual void writePosition(void) = 0;

      /// Write a arcade::GetMap structure to stdout
      virtual void writeMap(void) = 0;

      /// Go on the given direction
      virtual void goUp(void) = 0;
      virtual void goDown(void) = 0;
      virtual void goLeft(void) = 0;
      virtual void goRight(void) = 0;
      virtual void goForward(void) = 0;

      /// Shoot (for Solar Fox and Centipede).
      /// Default implem does nothing
      virtual void shoot(void) = 0;

      /// ???
      virtual void illegal(void) = 0;

      virtual void play(void) = 0;
  };
};

extern "C" {
  /// Required by the subject
  void Play(void);

  /// Creates a arcade::Game.
  std::unique_ptr<arcade::IGame> createGame(void);
}

#endif // !AGAME_HPP
