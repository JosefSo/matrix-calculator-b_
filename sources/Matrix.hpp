#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <string_view>
//using namespace std;
using std::string;
using std::vector;
using std::ostream;
using std::istream;
using std::runtime_error;
using std::invalid_argument;



namespace zich
{
    class Matrix
    {
    private:
        int rows;
        int cols;
        vector<double> mat;

    public:
    //constructors
        Matrix(const int _rows,const int _cols);
        Matrix(const vector<double> &_mat, const int _rows, const int _cols);

    //destructor
        ~Matrix();

    //help funcs
        double SumMult(const Matrix &mat, const int tempRow, const int tempCol);
        double Sum();

    //operators

        //increment and decrement operators
        Matrix& operator++(); // ++n
        Matrix operator++(int); // n++
        Matrix& operator--(); 
        Matrix operator--(int);

        //-,+,* operators
        Matrix operator-(const Matrix &mat);
        Matrix operator+(Matrix const &mat);
        Matrix operator*(const Matrix &mat);
        Matrix operator*(const double alpha);

        //-=,+=,*= operators
        Matrix& operator+=(const Matrix &mat);
        Matrix& operator-=(const Matrix &mat);
        Matrix& operator*=(const Matrix &mat);
        Matrix& operator*=(const double alpha);

        //compare operators
        bool operator>(Matrix &mat);
        bool operator<(Matrix &mat);
        bool operator>=(Matrix &mat);
        bool operator<=(Matrix &mat);
        bool operator!=(Matrix &mat);

        //input, output operators
        friend ostream & operator << (ostream &out, const Matrix &mat); //friend func to access private & protected members
        friend istream & operator >> (istream &input , Matrix& mat);

        //friend -,+,*,== operators
        friend Matrix operator-(Matrix &mat);
        friend Matrix operator+(Matrix &mat);
        friend Matrix operator*(const double alpha, Matrix &mat);
        friend bool operator==(Matrix const &mat, Matrix const &other);
    };

}