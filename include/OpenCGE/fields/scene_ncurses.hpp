#ifndef INCLUDE_OPENCGE_FIELDS_SCENE_NCURSES_HPP_
#define INCLUDE_OPENCGE_FIELDS_SCENE_NCURSES_HPP_

namespace OpenCGE
{
  namespace Field
  {
    struct SceneNcurses
    {
      SceneNcurses(std::string const& text)
        : text(text) {}
      // TODO Change text to a c string since that's what ncurses uses
      std::string text;
    };
  }
}

#endif /* INCLUDE_OPENCGE_FIELDS_SCENE_NCURSES_HPP_ */
