#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED

#include <vector>
#include <string>
using namespace std;

void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, size_t text);
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");
string make_color(const vector<size_t>& bins, size_t bin, size_t max_count);
void show_histogram_svg(const vector<size_t>& bins);
size_t find_min(const vector<size_t>& bins);
size_t find_max(const vector<size_t>& bins);

#endif // SVG_H_INCLUDED
