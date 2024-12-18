#include <GL/freeglut.h>
#include <bits/stdc++.h>
#include "geo.h"
using namespace std;

#define vec2 point2d
#define eb emplace_back
#define pb push_back
#define PI acos(-1)

int H = 1280;
int W = 1280;
double iTime = 0;
struct Trans{
    int prev;
    int post;
    double dur;
    Trans() {}
    Trans(int prev, int post, double dur) : prev(prev), post(post), dur(dur) {}
};


void InitGL();
void Reshape(int width, int height);
void Display();
void draw(vector<vec2> pts);
vector<vec2> scan(string dir);
vector<vec2> process(int n, vector<vec2> pts);
vector<vec2> pts;
vector<vec2> cur_state;
vector<vector<vec2>> states;
queue<Trans> transQueue;
double dist(const vec2& p1, const vec2& p2) {
    return abs_val(p1 - p2);
}


int Tween(vector<vec2> &prev, vector<vec2> &post, double dur)
{
    if(iTime >= dur) return 0;
    for(int i = 0; i < prev.size(); i++)
        cur_state[i] = prev[i] * (1 - iTime / dur) + post[i] * (iTime / dur);
    return 1;
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.f, 1.f, 1.f);

  //  for(auto [x, y] : cur_state) cout << x << ' ' << y << endl;
    draw(cur_state);
  //  draw(states[0]);
    glutSwapBuffers();
}
void timer(int val) {
    if(!transQueue.empty())
    {
    auto [prev, post, dur] = transQueue.front();
    if(!Tween(states[prev], states[post], dur))
        transQueue.pop(),
        iTime = 0;
    }
    iTime += 1.0;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}
int main(int argc, char* argv[])
{
    int windowWidth, windowHeight;
    windowWidth = W;
    windowHeight = H;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - windowWidth) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - windowHeight) / 2);
    glutCreateWindow("OpenGL FreeGlut Window");


    states.push_back(scan("C:\\Users\\User\\Downloads\\umbrella.txt"));
    states.push_back(scan("C:\\Users\\User\\Downloads\\boat.txt"));
    states.push_back(scan("C:\\Users\\User\\Downloads\\Hello.txt"));
    int N = 50000;
    for(auto &state : states) state = process(N, state);
    cur_state.assign(N, {0, 0});
    transQueue.push({0, 0, 50});
    transQueue.push({0, 1, 100});
    transQueue.push({1, 1, 50});
    transQueue.push({1, 2, 100});
    transQueue.push({2, 2, 50});
    transQueue.push({2, 0, 100});

    glutReshapeFunc(Reshape);
    glutDisplayFunc(Display);
    InitGL();
    glutTimerFunc(16, timer, 0);

    glutMainLoop();

    return 0;
}

void InitGL()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

void Reshape(int width, int height)
{
    glViewport(0, 0, width, height);
}

void draw(vector<vec2> pts){
    glBegin(GL_LINE_STRIP);
    for(auto [x, y] : pts)
        glVertex2d(x, y);
    glEnd();
}



vector<vec2> process(int n, vector<vec2> pts){
    double sum = 0;

    for(int i = 0; i < pts.size() - 1; i++)
        sum += dist(pts[i], pts[i + 1]);

    double len = sum / n;
    vector<vec2> ans = {pts[0]};
    double cur = len;
    vec2 cur_pt = pts[0];

    for(int i = 1; i < pts.size(); i++) {
        if(ans.size() == n) break;

        auto dir = pts[i] - cur_pt;
        double segment_len = dist(cur_pt, pts[i]);

        while(segment_len >= cur) {
            ans.push_back(ans.back() + Norml(dir) * cur);
            cur_pt = ans.back();
            segment_len -= cur;
            cur = len;
        }

        cur_pt = pts[i];
    }

    return ans;
}

vector<vec2> scan(string dir){
    fstream in(dir);
    double x, y;
    string _;
    vector<vec2> ans;
    while(in >> _ >> x >> y) {
        ans.eb(x, -y);
    }
    return ans;
}
