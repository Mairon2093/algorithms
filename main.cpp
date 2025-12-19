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

const ld EPS = 1e-12;

bool equal(ld a, ld b) {
    return abs(a - b) < EPS;
}

enum class Errors {
    WrongMatrixSize,
    DivisionByZero,
    NotSquareMatrix,
    EmptyMatrixInitialization
};
/*
 messages:
"wrong matrix's sizes"
"division by zero"
"matrix is not square, need square matrix"
"try to initialize an empty matrix"
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
        case EmptyMatrixInitialization:
            return "try to initialize an empty matrix";
    }
    return "unknown error";
}

#define extended_assert(condition, error_type) { if (!condition) { std::cerr << "ASSERT FAILED: " << #condition << " @ " << __FILE__ << " (" << __LINE__ << ") ERROR: " << convert_message_by_error(error_type) << std::endl;}}

class Matrix {
public:
    int n, m; // cnt of rows, columns
    vec <vec <ld>> matr;

    template <typename Y>
    Matrix(vec <vec <Y>>& data) {
        // data.empty()



        n = data.size();
        m = data.back().size(); // !!!
        matr = data;
    }
    Matrix(int _n, int _m) {
        n = _n;
        m = _m;
        matr = vec <vec <ld>>(n, vec <ld>(m));
    }

    template <typename Y>
    Matrix operator *(Y val) {
        Matrix res(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res.matr[i][j] = val * matr[i][j];
            }
        }
        return res;
    }

    Matrix operator *(Matrix & other) {
        extended_assert((m == other.n), WrongMatrixSize);

        Matrix res(n, other.m);
        for (int row = 0; row < n; row++) {
            for (int column = 0; column < other.m; column++) {
                for (int i = 0; i < m; i++) {
                    res.matr[row][column] += matr[row][i] * other.matr[i][column];
                }
            }
        }
        return res;
    }
    Matrix operator +(Matrix& other) {
        extended_assert((n == other.n && m == other.m), WrongMatrixSize);

        Matrix res(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res.matr[i][j] = matr[i][j] + other.matr[i][j];
            }
        }
        return res;
    }
    Matrix operator -(Matrix& other) {
        extended_assert((n == other.n && m == other.m), WrongMatrixSize);

        Matrix res(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res.matr[i][j] = matr[i][j] - other.matr[i][j];
            }
        }
        return res;
    }
    Matrix transpose() {
        Matrix res(m, n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                res.matr[j][i] = matr[i][j];
            }
        }
        return res;
    }

    //determinate matrix with Gauss method
    ld determinate() {
        extended_assert((n == m), NotSquareMatrix);

        vec <vec <ld>> a = matr;
        ld det = 1;

        int swapCount = 0;

        for (int i = 0; i < n; i++) {
            // Выбор главного элемента
            int maxRow = i;
            for (int k = i + 1; k < n; k++) {
                if (fabs(a[k][i]) > fabs(a[maxRow][i])) {
                    maxRow = k;
                }
            }

            if (fabs(a[maxRow][i]) < 1e-12) {
                return 0.0;
            }

            if (maxRow != i) {
                swap(a[i], a[maxRow]);
                swapCount++;
            }

            for (int k = i + 1; k < n; k++) {
                ld val = a[k][i] / a[i][i];
                for (int j = i; j < n; j++) {
                    a[k][j] -= val * a[i][j];
                }
            }

            det *= a[i][i];
        }

        if (swapCount % 2 == 1) {
            det = -det;
        }

        return det;
    }
};

/*
template <typename T>
Matrix <T> pow(Matrix <T>& A, int degree) {}
*/

template <typename T>
istream& operator>>(istream& in, Matrix& a) {
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++) in >> a.matr[i][j];
    }
    return in;
}
template <typename T>
ostream& operator<<(ostream& out, Matrix& a) {
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.m; j++) {
            out << a.matr[i][j] << " ";
        }
        cout << "\n";
    }
    return out;
}

int main() {
    cout << fixed << setprecision(5);

    vec <vec <ld>> mtr = {
        {1, 2},
        {3, 4},
    };
    Matrix a(mtr);
    cout << a.determinate();
}
