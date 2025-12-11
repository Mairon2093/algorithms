#include <bits/stdc++.h>

//#pragma GCC optimize("O3,unroll-loops")
//#pragma GCC target("avx,avx2")

using namespace std;

using ll = long long;
using ld = long double;
#define all(x) x.begin(), x.end()
template <typename T>
using vec = vector <T>;

template <typename T>
istream& operator>>(istream& in, vector <T>& a) {
    for (int i = 0; i < a.size(); i++) in >> a[i];
    return in;
}
template <typename T>
ostream& operator<<(ostream& out, vector <T>& a) {
    for (int i = 0; i < a.size(); i++) out << a[i] << " ";
    return out;
}
template <typename T, typename Y>
istream& operator>>(istream& in, pair <T, Y>& a) {
    in >> a.first >> a.second;
    return in;
}
template <typename T, typename Y>
ostream& operator<<(ostream& out, pair <T, Y>& a) {
    out << a.first << " " << a.second;
    return out;
}
template <typename T, typename Y>
string to_string(pair <T, Y>& p) {
    return ("(" + to_string(p.first) + "; " + to_string(p.second) + ")");
}

class Error {
public:
    virtual ~Error() = default;
    virtual string error_message() = 0;
};

class WrongMatrixSize : public Error {
    pair <int, int> size_matr1;
    pair <int, int> size_matr2;

public:
    WrongMatrixSize(pair <int, int> size1, pair <int, int> size2) {
        size_matr1 = size1;
        size_matr2 = size2;
    }
    string error_message() override {
        return "error: wrong matrix's sizes: " + to_string(size_matr1) + " with " + to_string(size_matr2);
    }
};

class DivisionByZero : public Error {
public:
    string error_message() override {
        return "error: division by zero";
    }
};

template <typename T>
class Matrix {
public:
    int n, m; // cnt of rows, columns
    vec <vec <T>> matr;

    template <typename Y>
    Matrix(vec <vec <Y>>& data) {
        // data.empty()

        if (data.empty()) {}

        n = data.size();
        m = data.back().size(); // !!!
        matr = data; // ??? vec <int> = vec <ll> cast
    }
    Matrix(int _n, int _m) {
        n = _n;
        m = _m;
        matr = vec <vec <T>>(n, vec <T>(m));
    }

    template <typename Y>
    Matrix <Y> operator *(Y val) {
        Matrix <Y> res(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res.matr[i][j] = val * matr[i][j];
            }
        }
        return res;
    }

    Matrix <T> operator *(Matrix <T>& other) {
        if (!(m == other.n)) {
            throw WrongMatrixSize({n, m}, {other.n, other.m});
        }

        Matrix <T> res(n, other.m);
        for (int row = 0; row < n; row++) {
            for (int column = 0; column < other.m; column++) {
                for (int i = 0; i < m; i++) {
                    res.matr[row][column] += matr[row][i] * other.matr[i][column];
                }
            }
        }
        return res;
    }
    Matrix <T> operator +(Matrix <T>& other) {
        if (!(n == other.n && m == other.m)) {
            return WrongMatrixSize({n, m}, {other.n, other.m});
        }

        Matrix <T> res(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res.matr[i][j] = matr[i][j] + other.matr[i][j];
            }
        }
        return res;
    }
    Matrix <T> operator -(Matrix <T>& other) {
        if (!(n == other.n && m == other.m)) {
            return WrongMatrixSize({n, m}, {other.n, other.m});
        }

        Matrix <T> res(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res.matr[i][j] = matr[i][j] - other.matr[i][j];
            }
        }
        return res;
    }
    Matrix <T> transpose() {
        Matrix <T> res(m, n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res.matr[j][i] = matr[i][j];
            }
        }
        return res;
    }
    T determinate() {}
    //детерминант
};

template <typename T>
Matrix <T> pow(Matrix <T>& A, int degree) {}

template <typename T>
istream& operator>>(istream& in, Matrix <T>& a) {
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++) in >> a.matr[i][j];
    }
    return in;
}
template <typename T>
ostream& operator<<(ostream& out, Matrix <T>& a) {
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++) {
            out << a.matr[i][j] << " ";
        }
        cout << "\n";
    }
    return out;
}

int main() {}
