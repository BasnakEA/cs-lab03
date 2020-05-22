#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED

#include "histogram.h"
#include <vector>
#include <string>

void svg_begin(double width, double height);
void svg_end();
void svg_text(double left, double baseline, size_t text);
void svg_rect(double x, double y, double width, double height, std::string stroke = "black", std::string fill = "black");
std::string make_color(const std::vector<size_t>& bins, size_t bin, size_t max_count);
void show_histogram_svg(const std::vector<size_t>& bins);
size_t find_min(const std::vector<size_t>& bins);
size_t find_max(const std::vector<size_t>& bins);
void show_version(double y);
void show_computername(double y);

#endif // SVG_H_INCLUDED
