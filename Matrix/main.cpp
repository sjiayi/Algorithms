#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Complex{
public:
    double re;
    double im;

    Complex(double reval = 0.0, double imval = 0.0){
        re = reval;
        im = imval;
    }

    Complex(const Complex& other){
        re = other.re;
        im = other.im;
    }

    Complex operator+(const Complex& other){
        Complex result;
        result.re = other.re + re;
        result.im = other.im + im;
        return result;
    }

    Complex operator-(const Complex& other){
        Complex result;
        result.re = re - other.re;
        result.im = im - other.im;
        return result;
    }

    Complex operator*(const Complex& other){
        Complex result;
        result.re = re * other.re - (im * other.im);
        result.im = other.im*re + im*other.re;
        return result;
    }

    Complex& operator=(const Complex& other){
        re = other.re;
        im =  other.im;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Complex& dt);
};

std::ostream& operator<<(std::ostream& os, const Complex& dt){
    if(dt.im >= 0){
        os << dt.re << " + " << dt.im << "i";
    }else{
        os << dt.re << " - " << (dt.im * -1) << "i";
    }
    return os;
}

template <typename T>
class Matrix{
public:
    Matrix(){       
        numRows = 0;
        numCols = 0;
    }

    Matrix(const Matrix& other){;
        set(other);
    }

    Matrix(Matrix&& other){       
        std::swap(matrix, other.matrix);
        numRows = other.numRows;
        numCols = other.numCols;
        other.numRows = 0;
        other.numCols = 0;
    }

    Matrix(int rows, int cols, const T value){
        resize(rows, cols);
        for(int i = 0; i < numRows; i++){
            for(int j = 0; j < numCols; j++){
                matrix[i][j] = value;
            }
        }
    }

    Matrix(int rows, int cols, const std::vector<T>& data){
        resize(rows, cols);
        int k = 0;
        for(int i = 0; i < numRows; i++){
            for(int j = 0; j < numCols; j++){
                if(k < data.size()){
                    matrix[i][j] = data[k];
                    k++;
                }else{
                    break;
                }
            }
        }
    }

    Matrix(int rows, int cols, const std::initializer_list<T> data){
        resize(rows, cols);
        auto itr = data.begin();
        for(int i = 0; i < numRows; i++){
            for(int j = 0; j < numCols; j++){
                if(itr != data.end()){
                    matrix[i][j] = *itr;
                    itr++;
                }else{
                    break;
                }
            }
        }
    }

    Matrix transpose(){
        Matrix result(numCols, numRows, 0);
        for(int i = 0; i < result.numRows; i++){
            for(int j = 0; j < result.numCols; j++){
                result(i, j) = matrix[j][i];
            }
        }
        return result;
    }

    void resize(int rows, int cols){
        numRows = rows;
        numCols = cols;
        matrix.resize(numRows);
        for(int i = 0; i < numRows; i++){
            matrix[i].resize(numCols); 
        }
    }

    T& operator()(int i, int j)
    {
        return matrix[i][j];
    }

    Matrix operator+(const Matrix& other){
        if(other.numRows != numRows || other.numCols != numCols){
            throw std::runtime_error("Incompatible operation");
        }
        Matrix result(numRows, numCols, 0);
        for(int i = 0; i < numRows; i++){
            for(int j = 0; j < numCols; j++){
                result.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }
        return result;
    }

    Matrix operator-(const Matrix& other){
        if(other.numRows != numRows || other.numCols != numCols){
            throw std::runtime_error("Incompatible operation");
        }
        Matrix result(numRows, numCols, 0);
        for(int i = 0; i < numRows; i++){
            for(int j = 0; j < numCols; j++){
                result.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
            }
        }
        return result;
    }

    Matrix& operator=(const Matrix& other){
        set(other);
        return *this;
    }
    
    Matrix& operator=(Matrix&& other){
        std::swap(matrix, other.matrix);
        numRows = other.numRows;
        numCols = other.numCols;
        other.numRows = 0;
        other.numCols = 0;
        return *this;
    }

    Matrix& operator+=(const Matrix& other){
        if(other.numRows != numRows || other.numCols != numCols){
            throw std::runtime_error("Incompatible operation");
        }
        for(int i = 0; i < numRows; i++){
            for(int j = 0; j < numCols; j++){
                matrix[i][j] += other.matrix[i][j];
            }
        }
        return *this;
    }

    Matrix& operator-=(const Matrix& other){
        if(other.numRows != numRows || other.numCols != numCols){
            throw std::runtime_error("Incompatible operation");
        }
        for(int i = 0; i < numRows; i++){
            for(int j = 0; j < numCols; j++){
                matrix[i][j] -= other.matrix[i][j];
            }
        }
        return *this;
    }

    Matrix operator*(const Matrix& other){
        if(numCols != other.numRows){
            throw std::runtime_error("Incompatible operation");
        }
        Matrix result (numRows, other.numCols, T(0));
        for(int i = 0; i < numRows; i++){
            for(int j = 0; j < other.numCols; j++){
                for(int k = 0; k < numCols; k++){
                    result.matrix[i][j] = result.matrix[i][j] + (matrix[i][k] * other.matrix[k][j]);
                }
            }
        }
        return result;
    }

    void printMatrix(){
        std::cout << "[" << std::endl;
        for(int i = 0; i < numRows; i++){
            for(int j = 0; j < numCols; j++){
                std::cout << " " << matrix[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << "]" << std::endl;
    }

    ~Matrix(){
        numRows = 0;
        numCols = 0;
        matrix.resize(0);
    }


private:
    std::vector<std::vector<T>> matrix;
    int numRows;
    int numCols;

    void set(const Matrix& other){
        resize(other.numRows, other.numCols);
        for(int i = 0; i < numRows; i++){
            for(int j = 0; j < numCols; j++){
                matrix[i][j] = other.matrix[i][j];
            }
        }
    }
};

int main(){
    std::cout << "Empty Constructor" << std::endl;
    Matrix<float> A;
    A.printMatrix();
    A.resize(3, 3);
    std::cout << "Single Value Constructor" << std::endl;
    Matrix<float> B(4, 4, 4.0f);
    B.printMatrix();
    std::cout << "Single Element Value Access" << std::endl;
    B(1, 1) = 0;
    B.printMatrix();
    std::cout << "Copy Constructor" << std::endl;
    Matrix<float> C(B);
    C.printMatrix();
    std::cout << "Move Constructor" << std::endl;
    Matrix<float> D(std::move(C));
    C.printMatrix();
    D.printMatrix();
    std::cout << "List of Values Constructor" << std::endl;
    Matrix<float> E(4, 3, { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    E.printMatrix();
    std::cout << "= Operator" << std::endl;
    E = B;
    E.printMatrix();
    Matrix<float> F;
    F = std::move(B);
    F.printMatrix();
    B.printMatrix();
    std::cout << "+ Operator" << std::endl;
    F = E + E;
    F.printMatrix();
    std::cout << "- Operator" << std::endl;
    F = E - F;
    F.printMatrix();
    std::cout << "+= Operator" << std::endl;
    F += F;
    F.printMatrix();
    std::cout << "-= Operator" << std::endl;
    F -= E;
    F.printMatrix();
    E = (F = E) + F;
    F.printMatrix();
    E.printMatrix();
    std::cout << "*Operator" << std::endl;
    Matrix<float>A1(2, 2, {0, 1, 1, 2});
    Matrix<float>A2(2, 3, {1, 2, 1, 1, 2, 1});
    Matrix<float> product = A1 * A2;
    product.printMatrix();
    std::cout << "Complex Numbers Matrix" << std::endl;
    Matrix<Complex> AZ(2, 2, Complex(1, 2));
    AZ.printMatrix();
    Matrix<Complex> AZ2(2, 1, Complex(3, -1));
    AZ2.printMatrix();
    AZ2 = AZ * AZ2;
    AZ2.printMatrix();
    AZ2(0, 0) = Complex(5, 5);
    AZ2.printMatrix();
    std::cout << "Transpose Matrix" << std::endl;
    Matrix<Complex> AZ3;
    AZ3 = AZ2.transpose();
    AZ3.printMatrix();

}
