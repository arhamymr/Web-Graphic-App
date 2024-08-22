#include <string>
using namespace std;

class Colors
{
public:
  // color
  void setFill(string color);
  void setStroke(string color);

  string getFill();
  string getStroke();

private:
  // color
  string fill = "#000000";
  string stroke = "#000000";
};