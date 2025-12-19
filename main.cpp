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

const ld EPS = 1e-9;

enum class Errors {
    WrongMatrixSize,
    DivisionByZero,
    NotSquareMatrix
};
/*
 messages:
"wrong matrix's sizes"
"division by zero"
"matrix is not square, need square matrix"
 */
using enum Errors;

string convert_message_by_error(Errors error_state) {
    switch (error_state) {
        case WrongMatrixSize:
            return "wrong matrix's sizes";
        case DivisionByZero:
            return "division by zero";
        case NotSquareMatrix:
            return "matrix is not square, need square matrix";
    }
    return "unknown error";
}

#define extended_assert(condition, error_type) { if (!condition) { std::cerr << "ASSERT FAILED: " << #condition << " @ " << __FILE__ << " (" << __LINE__ << ") ERROR: " << convert_message_by_error(error_type) << std::endl;}}

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
        extended_assert((m == other.n), WrongMatrixSize);

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
        extended_assert((n == other.n && m == other.m), WrongMatrixSize);

        Matrix <T> res(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res.matr[i][j] = matr[i][j] + other.matr[i][j];
            }
        }
        return res;
    }
    Matrix <T> operator -(Matrix <T>& other) {
        extended_assert((n == other.n && m == other.m), WrongMatrixSize);

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

    //determinate matrix with Gauss method
    T determinate() {
        extended_assert((n == m), NotSquareMatrix);

        vec <vec <T>> a = matr;

        T det = 1;
        for (int i = 0; i < n; i++) {
            T k = 1;
            for (int j = i + 1; j < n; j++) {
                if (abs(a[i][j]) > abs(a[k][j])) {
                    k = j;
                }
            }

            if (abs(a[k][i]) < EPS) {
                det = 0;
                break;
            }

            swap(a[i], a[k]);
            if (i != k) {
                det = -det;
            }
            det *= a[i][i];

            for (int j = i + 1; j < n; j++) {
                a[i][j] = a[i][i];
            }
            for (int j = 0; j < n; j++) {
                if (i != j && abs(a[j][i]) > EPS) {
                    for (int k = i + 1; k < n; k++) {
                        a[j][k] -= a[i][k] * a[j][i];
                    }
                }
            }
        }
        return det;
    }
};

/*
template <typename T>
Matrix <T> pow(Matrix <T>& A, int degree) {}
*/

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
