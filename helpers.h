#include <iostream>
using namespace std;

// function untuk format tab
string formatTab(string text) {
  string result = text + " ";
  int panjang = result.length() + 1;

  if (panjang < 11) {
    result += "\t\t\t";
  } else if (panjang < 15) {
    result += "\t\t";
  } else {
    result += "";
  }

  return result;
}
