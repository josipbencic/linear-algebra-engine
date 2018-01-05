#ifndef VIEW_HPP
#define VIEW_HPP

enum State;

/*  A family of functors used to display states.
  Each class represents a part of application and
  handles certain (name - explainatory) function.
*/


/*  All classes are derived from base class View, so
  pointer polymorphism is allowed.
*/
class View {
public:
  virtual ~View() {}
  virtual State operator ()() = 0;
};

/*  First screen to appear when the application is started.
  A simple greet message that ends with any keystroke.
*/
class WelcomeView : public View {
public:
  State operator ()();
};

/*  Main menu. All Views return to this when they finish.
  It allows to switch all other Views (except WelcomeView).
*/
class MainMenuView : public View {
public:
  State operator ()();
};

/*  One of given options at Main Menu View.
  Gives an overview of input methods for all algorithms.
*/
class TutorialView : public View {
public:
  State operator ()();
};

/*  Base class for all algorithms. Contains an additional
  reference to InputManager class that contains vectors given
  by user.
*/
class AlgorithmView : public View {
public:
  AlgorithmView(class InputManager& rManager)
    : input(rManager)
  {}
  virtual State operator ()() = 0;
protected:
  class InputManager &input;
};

/*  Handles distance from subspace algorithm.
  Sole algorithm is documented in GramSchmidt.hpp file,
  this is only its View.
*/
class DistanceFromSubspaceView : public AlgorithmView {
public:
  DistanceFromSubspaceView(class InputManager& rManager)
    : AlgorithmView(rManager)
  {}

  State operator ()();
};

/*  Gram Schmidt Orthogonalization Algorithm View.
  Returns an array of solution which are printed and then destroyed.
*/
class GramSchmidtView : public AlgorithmView {
public:
  GramSchmidtView(class InputManager& rManager)
    : AlgorithmView(rManager)
  {}

  State operator ()();
};

/*  Handles Linear System solver. Also repeats the input tutorial
  regarding Linear Systems.
*/
class LinearSystemView : public AlgorithmView {
public:
  LinearSystemView(class InputManager& rManager)
    : AlgorithmView(rManager)
  {}

  State operator ()();
};

#endif
