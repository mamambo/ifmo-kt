#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

FILE *fin = fopen("spantree.in", "r");
FILE *fout = fopen("spantree.out", "w");

int n;
vector<int> xc, yc;

double g(int v1, int v2){
    return sqrt(pow((xc[v2]-xc[v1]),2)+pow((yc[v2]-yc[v1]),2));
}


int main(int argc, char **argv) {
    fscanf(fin, "%d", &n);
    xc.push_back(0);
    yc.push_back(0);
    for(int i = 1, x, y; i <= n; i++) {
        fscanf(fin, "%d %d", &x, &y);
        xc.push_back(x);
        yc.push_back(y);
    }

    vector<bool> used(n + 1);
    vector<double> min_e(n + 1, (double)INT_MAX);
    vector<int> sel_e(n + 1, -1);
    double answer = 0;
    min_e[1] = 0; // вес наименьшего допустимого ребра из вершины i

    for(int i = 1; i <= n; ++i) {
        int v = -1;

        for(int j = 1; j <= n; ++j) {
            if(!used[j] && (v == -1 || min_e[j] < min_e[v])) {
                v = j;
            }
        }

        used[v] = true;

        if(sel_e[v] != -1) {
            answer += g(v, sel_e[v]);
        }

        for(int to = 1; to <= n; ++to)
            if(g(v, to) < min_e[to]) {
                min_e[to] = g(v, to);
                sel_e[to] = v;
            }
    }

    fprintf(fout, "%f", answer);
    fclose(fin);
    fclose(fout);
    return 0;
}
