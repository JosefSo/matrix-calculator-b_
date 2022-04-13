#include "Matrix.hpp"

// (unsigned int) is the unsigned integer type of the result of sizeof which is used to represent the size of objects in bytes
// (const Matrix &mat) - const - can't change Matrix, & - object not copied
// Matrix &Matrix - for p1+=p2+=p3... for work with object

namespace zich{



    //check funcs
    void CheckMultCompilation(int cols_a, int rows_b){
        if(cols_a != rows_b)
        {
            throw runtime_error("cols of first matrix need be equal to rows of second matrx");
        }
    }
    void CheckMatCorectness(int rows_a, int cols_a, int rows_b, int cols_b){
        if (rows_a != rows_b || cols_a != cols_b)
        {
            throw runtime_error("rows and cols of both matrix must be the same!");
        }
    }
    void CheckNegative(int rows, int cols){
        if (rows <= 0 || cols <= 0)
        {
            throw runtime_error("only positive numbers for: rows & cols!");
        }
    }
    void CheckSize(int matsize, int rows, int cols){
        if(matsize != rows * cols)
        {
            throw runtime_error("the size of the matrix and size of the array need be the same!");
        }
    }
    //help funcs
    double Matrix::Sum()
    {
        double sum = 0;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                sum += this->mat[(unsigned int)(i * cols + j)];
            }
        }
        return sum;
    }
    double Matrix::SumMult(const Matrix &mat, const int tempRow, const int tempCol)
    {
        double sum = 0;
        for (int i = 0; i < this->cols; i++)
        {   
            sum += this->mat[(unsigned int)(this->cols * tempRow + i)] * mat.mat[(unsigned int)(mat.cols * i + tempCol)];
        }
        return sum;
    }
    
    vector<string> StrSplit(string str, char seprtr) 
    {
        string temp;
        vector<string> data;
        for (unsigned int i = 0; i < str.length(); i++)
        {
            if (str[i] == seprtr && !temp.empty())
            {
                data.push_back(temp);
                temp = "";
            }
            else
            {
                if (str[i] == '[' || str[i] == ']') {continue;}
                temp += str[i];
            }
        }
        data.push_back(temp);
        return data;
    }


    //constructors
    Matrix::Matrix(const int _rows, const int _cols) : rows(_rows), cols(_cols)
    {
        CheckNegative(_rows, _cols);
    }

    Matrix::Matrix(const vector<double> &_mat, const int _rows, const int _cols) : mat(_mat), rows(_rows), cols(_cols)
    {
        CheckNegative(_rows, _cols);
        CheckSize(_mat.size(), _rows, _cols);      
    }
    //destructor
    Matrix::~Matrix() { }

    //Increment and decrement operators
    Matrix &Matrix::operator++()
    {
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                this->mat[(unsigned int)(i * cols + j)] += 1;
            }
        }
        return *this;
    }
    Matrix Matrix::operator++(int)
    {
        Matrix copy = *this;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                this->mat[(unsigned int)(i * cols + j)] += 1;
            }
        }
        return copy;
    }
    Matrix &Matrix::operator--()
    {
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                this->mat[(unsigned int)(i * cols + j)] -= 1;
            }
        }
        return *this;
    }
    Matrix Matrix::operator--(int)
    {
        Matrix copy = *this;
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                this->mat[(unsigned int)(i * cols + j)] -= 1;
            }
        }
        return copy;
    }

    //-,+,* operators
    Matrix Matrix::operator-(const Matrix &mat)
    {
        CheckMatCorectness(this->rows, this->cols, mat.rows, mat.cols);
        vector<double> sum;
        sum.resize((unsigned int)(rows * cols));
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                sum[(unsigned int)(i * cols + j)] = this->mat[(unsigned int)(i * cols + j)] - mat.mat[(unsigned int)(i * cols + j)];
            }
        }
        
        Matrix new_mat(sum, this->rows, mat.cols);
        return new_mat;
    }
    Matrix Matrix::operator+(Matrix const &mat)
    {
        CheckMatCorectness(this->rows, this->cols, mat.rows, mat.cols);
        vector<double> sum;
        
        sum.resize((unsigned int)(rows * cols));
        
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                sum[(unsigned int)(i * cols + j)] = this->mat[(unsigned int)(i * cols + j)] + mat.mat[(unsigned int)(i * cols + j)];
            }
        }
        Matrix new_mat(sum, this->rows, mat.cols);
        return new_mat;
    }
    Matrix Matrix::operator*(const Matrix &mat)
    {
        
        CheckMultCompilation(this->cols, mat.rows);
        vector<double> sum;
        sum.resize((unsigned int)(this->rows * mat.cols));
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < mat.cols; j++)
            {
                sum[(unsigned int)(i * mat.cols + j)] = SumMult(mat, i, j);
            }
        }
        Matrix new_mat(sum, this->rows, mat.cols);
        return new_mat;
    }
    Matrix Matrix::operator*(const double alpha)
    {
        vector<double> sum;
        
        sum.resize((unsigned int)(rows * cols));
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                sum[(unsigned int)(i * this->cols + j)] = this->mat[(unsigned int)(i * this->cols + j)] * alpha;
            }
        }
        Matrix new_mat(sum, this->rows, this->cols);
        
        return new_mat;
    }
    
    //-=,+=,*= operators
    Matrix &Matrix::operator+=(const Matrix &mat)
    {
        CheckMatCorectness(this->rows, this->cols, mat.rows, mat.cols);
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                this->mat[(unsigned int)(i * cols + j)] += mat.mat[(unsigned int)(i * cols + j)];
            }
        }
        return *this;
    }
    Matrix &Matrix::operator-=(const Matrix &mat)
    {
        CheckMatCorectness(this->rows, this->cols, mat.rows, mat.cols);
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                this->mat[(unsigned int)(i * cols + j)] -= mat.mat[(unsigned int)(i * cols + j)];
            }
        }
        return *this;
    }
    Matrix &Matrix::operator*=(const Matrix &mat)
    {
        CheckMultCompilation(this->cols, mat.rows);
        vector<double> sum;
        Matrix new_mat(this->rows, mat.cols); //create new matrix
        sum.resize((unsigned int)(this->rows * mat.cols));
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < mat.cols; j++)
            {
                sum[(unsigned int)(i * mat.cols + j)] = SumMult(mat, i, j);
            }
        }
        this->cols = mat.cols;
        this->mat = sum;
        return *this;
    }
    Matrix &Matrix::operator*=(const double alpha)
    {
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                this->mat[(unsigned int)(i * this->cols + j)] *= alpha;
            }
        }
        return *this;
    }

    //compare operators
    bool Matrix::operator>(Matrix &mat)
    {
        CheckMatCorectness(this->rows, this->cols, mat.rows, mat.cols);
        return this->Sum() > mat.Sum();
    }
    bool Matrix::operator>=(Matrix &mat)
    {
        CheckMatCorectness(this->rows, this->cols, mat.rows, mat.cols);
        return this->Sum() >= mat.Sum();
    }
    bool Matrix::operator<(Matrix &mat)
    {
        CheckMatCorectness(this->rows, this->cols, mat.rows, mat.cols);
        return this->Sum() < mat.Sum();
    }
    bool Matrix::operator<=(Matrix &mat)
    {
        CheckMatCorectness(this->rows, this->cols, mat.rows, mat.cols);
        return this->Sum() <= mat.Sum();
    }

    bool Matrix::operator!=(Matrix &mat)
    {
        CheckMatCorectness(this->rows, this->cols, mat.rows, mat.cols);
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                if (this->mat[(unsigned int)(i * cols + j)] != mat.mat[(unsigned int)(i * cols + j)])
                {
                    return true;
                }
            }
        }
        return false;
    }

    //output operator
    ostream & operator << (ostream &out, const Matrix &mat){
        for (int i = 0; i < mat.rows; i++)
        {
            out << '[';
            for (int j = 0; j < mat.cols; j++)
            {   
                if (j != mat.cols -1 )
                {
                    out << mat.mat[(unsigned int)(i * mat.cols + j)] << ' ';
                }
                else{
                    out <<mat.mat[(unsigned int)(i * mat.cols + j)];
                }
            }
            if (i != mat.rows-1)
            {
                out << ']' << '\n';
            }
            else
            {
                out << ']' ;
            }       
        }
        return out;
    }
    //input operator
    //input example:  "[1 1 1 1],[1 1 1 1],[1 1 1 1]\n"  >> mat1
    istream & operator >> (istream &input, Matrix &mat)
    {
        int col = 0;
        int flag = 1;
        string str;
        vector<string> vec;
        vector<string> vec2;
        vector<double> vec3;

        for (char c = input.get(); c != '\n'; c = input.get()) {str+=c;}
        str.pop_back(); 
        
        for (unsigned int i = 0; i < str.length()-1; i++){
            if (str.at(i) == ',' && str.at(i+1) != ' '){throw runtime_error("input isn't correct!");} 
        }

        vec = StrSplit(str, ','); 

        for (unsigned int i = 0; i < vec.size(); i++){
            vec2 = StrSplit(vec[i], ' ');
            int len = vec2.size();
            if (flag != 0){ col = len; flag = 0; }
            if (col != len) {throw runtime_error("go fix your input!");}
          
            for (unsigned int j = 0; j < len; j++){vec3.push_back(stod(vec2[j]));}
        }
        mat.mat = vec3;
        mat.rows = vec.size();
        mat.cols = col;
        return input;
    }

    //friend func operators
    Matrix operator-(Matrix &mat){
        Matrix ans(mat.rows, mat.cols);
        ans.mat.resize((unsigned int)(mat.rows * mat.cols));
        for (int i = 0; i < mat.rows; i++)
        {
            for (int j = 0; j < mat.cols; j++)
            {
                ans.mat[(unsigned int)(i * mat.cols + j)] = (-1) * mat.mat[(unsigned int)(i * mat.cols + j)];
            }
        }
        return ans;
    }
    Matrix operator+(Matrix &mat){ // this func changes nothing
        return mat;
    }
    Matrix operator*(const double alpha, Matrix &mat){
        
        vector<double> temp_mat;
        temp_mat.resize((unsigned int)(mat.rows * mat.cols));
        for (int i = 0; i < mat.rows; i++)
        {
            for (int j = 0; j < mat.cols; j++)
            {
                temp_mat[(unsigned int)(i * mat.cols + j)] = alpha * mat.mat[(unsigned int)(i * mat.cols + j)];
            }
        }
        Matrix ans(temp_mat, mat.rows, mat.cols);
        return ans;
    }

    bool operator==(Matrix const &mat, Matrix const &other)
    {
        CheckMatCorectness(other.rows, other.cols, mat.rows, mat.cols);

        //return !(mat != other);

        for (int i = 0; i < mat.rows; i++)
        {
            for (int j = 0; j < mat.cols; j++)
            {
                if (mat.mat[(unsigned int)(i * mat.cols + j)] != other.mat[(unsigned int)(i * other.cols + j)])
                {
                    return false;
                }
            }
        }
        return true;
    }
}