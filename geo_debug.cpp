#include <bits/stdc++.h>
using namespace std;
string s;
#define S(x) s += x
#define T to_string
void line(double x1, double y1, double x2, double y2, string c = "black") {
    S("<line x1='" + T(x1) + "' y1='" + T(y1) + "' x2='" + T(x2) + "' y2='" + T(y2) + "' stroke='" + c + "'/>");
}
void circle(double x, double y, double r = 3, string f = "red") {
    S("<circle cx='" + T(x) + "' cy='" + T(y) + "' r='" + T(r) + "' fill='" + f + "'/>");
}
void poly(vector<pair<double, double>> v, string sc = "black", string fc = "none") {
    string pts;
    for (auto &a : v)
        pts += T(a.first) + "," + T(a.second) + " ";
    S("<polygon points='" + pts + "' stroke='" + sc + "' fill='" + fc + "'/>");
}
void rect(double x, double y, double w, double h, string sc = "black", string fc = "none") {
    S("<rect x='" + T(x) + "' y='" + T(y) + "' width='" + T(w) + "' height='" + T(h) + "' stroke='" + sc + "' fill='" + fc + "'/>");
}
void text(double x, double y, string c, string col = "black", int f = 12) {
    S("<text x='" + T(x) + "' y='" + T(y) + "' fill='" + col + "' font-size='" + T(f) + "'>" + c + "</text>");
}
void render(string fn = "o.html", double w = 500, double h = 500) {
    ofstream f(fn);
    f << "<!DOCTYPE html><html><body><svg xmlns='http://www.w3.org/2000/svg' width='" << w << "' height='" << h << "'>" << s << "</svg></body></html>";
    f.close();
    s = "";
}
int main() {
    line(250, 0, 250, 500, "grey");
    line(0, 250, 500, 250, "grey");
    
    vector<pair<double, double>> tr = {{200, 100}, {300, 100}, {250, 200}};
    poly(tr, "blue", "lightblue");
    
    rect(300, 300, 100, 50, "purple", "lavender");
    circle(100, 400, 10, "green");
    
    text(240, 90, "Triangle", "blue", 14);
    text(310, 290, "Rectangle", "purple", 14);
    text(90, 410, "Circle", "green", 14);
    render();
}
