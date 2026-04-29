#include "hw1.h"
#include <random>
#include <iomanip>

using namespace algebra;
////1//////////////////////////////////////////////////////////
Matrix algebra::zeros(size_t n, size_t m)
{
    Matrix matrix{};
    std::vector<double> mat{};
    for(int i{0}; i<n; i++)
    {
        for(int j{0}; j<m; j++)
        {
            mat.push_back(0);
        }
        matrix.push_back(mat);
        mat.clear();
    }
    return matrix;
}
////2//////////////////////////////////////////////////////////
Matrix algebra::ones(size_t n, size_t m)
{
    Matrix matrix{};
    std::vector<double> mat{};
    for(int i{0}; i<n; i++)
    {
        for(int j{0}; j<m; j++)
        {
            mat.push_back(1);
        }
        matrix.push_back(mat);
        mat.clear();
    }
    return matrix;
}
////3//////////////////////////////////////////////////////////
Matrix algebra::random(size_t n, size_t m, double min, double max)
{
    if(min > max)
        throw std::logic_error("Caution: min cannot be greater than max");

    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_real_distribution<double> distribution(min,max);


    Matrix matrix{};
    std::vector<double> mat{};
    for(int i{0}; i<n; i++)
    {
        for(int j{0}; j<m; j++)
        {
            double number = distribution(generator);
            mat.push_back(number);
        }
        matrix.push_back(mat);
        mat.clear();
    }
    return matrix;
}
////4//////////////////////////////////////////////////////////
void algebra::show(const Matrix &matrix)
{
    for (int i{0}; i < matrix.size(); i++)
    {
        for (int j{0}; j < matrix[i].size(); j++)
        {
            std::cout << std::setw(3) << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
////5//////////////////////////////////////////////////////////
Matrix algebra::multiply(const Matrix &matrix, double c)
{
    Matrix matrix_1{};
    std::vector<double> mat{};
    for (int i{0}; i < matrix.size(); i++)
    {
        for (int j{0}; j < matrix[i].size(); j++)
        {
            mat.push_back(matrix[i][j] * c);
        }
        matrix_1.push_back(mat);
        mat.clear();
    }
    return matrix_1;
}
////6//////////////////////////////////////////////////////////
Matrix algebra::multiply(const Matrix &matrix1, const Matrix &matrix2)
{
    size_t row1{matrix1.size()};
    size_t row2{matrix2.size()};
    size_t column1{};
    size_t column2{};

    if (row1 > 0)
        column1 = matrix1[0].size();
    else
        column1 = 0;

    if (row2 > 0)
        column2 = matrix2[0].size();
    else
        column2 = 0;
   
    std::vector<double> mat{};
    Matrix matrix{};
    double sum{0};

    if (column1 != row2)
    {
        throw std::logic_error("Caution: matrices with wrong dimensions cannot be multiplied");
    }

    for (int i{0}; i < row1; i++)
    {
        for (int j{0}; j < column2; j++)
        {
            for (int k{0}; k < column1; k++)
            {
                sum += matrix1[i][k] * matrix2[k][j];
            }
            mat.push_back(sum);
            sum = 0;
        }
        matrix.push_back(mat);
        mat.clear();
    }
    return matrix;
}
////7//////////////////////////////////////////////////////////
Matrix algebra::sum(const Matrix &matrix, double c)
{
    std::vector<double> mat{};
    Matrix matrix_1{};
    for (int i{0}; i < matrix.size(); i++)
    {
        for (int j{0}; j < matrix[i].size(); j++)
        {
            mat.push_back(matrix[i][j] + c);
        }
        matrix_1.push_back(mat);
        mat.clear();
    }
    return matrix_1;
}
////8//////////////////////////////////////////////////////////
Matrix algebra::sum(const Matrix &matrix1, const Matrix &matrix2)
{
    size_t row1{matrix1.size()};
    size_t row2{matrix2.size()};
    size_t column1{};
    size_t column2{};

    if (row1 > 0)
        column1 = matrix1[0].size();
    else
        column1 = 0;

    if (row2 > 0)
        column2 = matrix2[0].size();
    else
        column2 = 0;
   
    std::vector<double> mat{};
    Matrix matrix{};
    double sum{0};

    if (row1 != row2 || column1 != column2)
    {
        throw std::logic_error("Caution: matrices with wrong dimensions cannot be multiplied");
    }

    for (int i{0}; i < row1; i++)
    {
        for (int j{0}; j < column1; j++)
        {
            sum = matrix1[i][j] + matrix2[i][j];
            mat.push_back(sum);
        }
        matrix.push_back(mat);
        mat.clear();
    }
    return matrix;
}
////9//////////////////////////////////////////////////////////
Matrix algebra::transpose(const Matrix& matrix)
{
    if(matrix.empty())
        return matrix;
    size_t row{matrix.size()};
    size_t column{matrix[0].size()};
    Matrix matrix_1{};
    std::vector<double> mat{};
    for (int i{0}; i < column; i++)
    {
        for (int j{0}; j < row; j++)
        {
            mat.push_back(matrix[j][i]);
        }
        matrix_1.push_back(mat);
        mat.clear();
    }
    return matrix_1;
}
////10//////////////////////////////////////////////////////////
Matrix algebra::minor(const Matrix& matrix, size_t n, size_t m)
{
    size_t row{matrix.size()};
    size_t column{matrix[0].size()};
    Matrix matrix_1{};
    std::vector<double> mat{};
    for (int i{0}; i < row; i++)
    {
        if(i != n)
        {
            for (int j{0}; j < column; j++)
            {
                if(j != m)
                    mat.push_back(matrix[i][j]);
            }
            matrix_1.push_back(mat);
            mat.clear();
        }
    }
    return matrix_1; 
}
////11//////////////////////////////////////////////////////////
double algebra::determinant(const Matrix& matrix)
{
    if(matrix.empty())
        return 1;
    double det{0};
    size_t row{matrix.size()};
    size_t column{matrix[0].size()};
    Matrix matrix_1{};
    std::vector<double> mat{};
    if(row != column)
        throw std::logic_error("Caution: non-square matrices have no determinant");
    if(row == 2)
        return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
    for (int j{0}; j < column; j++)
    {
        det += matrix[0][j] * determinant(minor(matrix,0,j)) * pow(-1, j);

    }
    return det;    
}
////12//////////////////////////////////////////////////////////
Matrix algebra::inverse(const Matrix& matrix)
{
    if(matrix.empty())
        return matrix;
    size_t row{matrix.size()};
    size_t column{matrix[0].size()};
    Matrix matrix_1{};
    double det;
    std::vector<double> mat{};
    if(row != column)
        throw std::logic_error("Caution: non-square matrices have no inverse");
    det = determinant(matrix);
    if(det == 0)
        throw std::logic_error("Caution: singular matrices have no inverse");
    for (int i{0}; i < row; i++)
    {
        for (int j{0}; j < column; j++)
        {
            mat.push_back(determinant(minor(matrix,i,j)) * pow(-1, i+j));
        }
        matrix_1.push_back(mat);
        mat.clear();
    }
    matrix_1 = transpose(matrix_1);
    matrix_1 = multiply(matrix_1, 1/det);
    return matrix_1;
}
////13//////////////////////////////////////////////////////////
Matrix algebra::concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis=0)
{
    size_t row1{matrix1.size()};
    size_t row2{matrix2.size()};
    size_t column1{};
    size_t column2{}; 
    Matrix matrix_1{};
    std::vector<double> mat{};
    if (row1 > 0)
        column1 = matrix1[0].size();
    else
        column1 = 0;

    if (row2 > 0)
        column2 = matrix2[0].size();
    else
        column2 = 0;   
    if(axis == 0)
    {
        if(column1 != column2)
            throw std::logic_error("Caution: matrices with wrong dimensions cannot be concatenated");
        for (int i{0}; i < row1 + row2; i++)
        {
            for (int j{0}; j < column1; j++)
            {
                if(i < row1)
                    mat.push_back(matrix1[i][j]);
                else
                    mat.push_back(matrix2[i - row1][j]);
            }
            matrix_1.push_back(mat);
            mat.clear();
        }
    }
    else
    {
        if(row1 != row2)
            throw std::logic_error("Caution: matrices with wrong dimensions cannot be concatenated");
        for (int i{0}; i < row1; i++)
        {
            for (int j{0}; j < column1 + column2; j++)
            {
                if(j < column1)
                    mat.push_back(matrix1[i][j]);
                else
                    mat.push_back(matrix2[i][j - column1]);
            }
            matrix_1.push_back(mat);
            mat.clear();
        }   
    }
    return matrix_1;
}
////14//////////////////////////////////////////////////////////
Matrix algebra::ero_swap(const Matrix& matrix, size_t r1, size_t r2)
{
    size_t row{matrix.size()};
    size_t column{matrix[0].size()};
    Matrix matrix_1{};
    std::vector<double> mat{};
    if(r1 >= row or r2 >= row)
        throw std::logic_error("Caution: r1 or r2 inputs are out of range");
    for(int i{0}; i<row; i++)
    {
        for(int j{0}; j<column; j++)
        {
            if(i == r1)
                mat.push_back(matrix[r2][j]);
            else if(i == r2)
                mat.push_back(matrix[r1][j]);
            else
                mat.push_back(matrix[i][j]);
        }
        matrix_1.push_back(mat);
        mat.clear();
    }
    return matrix_1;         
}
////15//////////////////////////////////////////////////////////
Matrix algebra::ero_multiply(const Matrix& matrix, size_t r, double c)
{
    size_t row{matrix.size()};
    size_t column{matrix[0].size()};
    Matrix matrix_1{};
    std::vector<double> mat{};
    for(int i{0}; i<row; i++)
    {
        for(int j{0}; j<column; j++)
        {
            if(i == r)
                mat.push_back(matrix[i][j] * c);
            else
                mat.push_back(matrix[i][j]);
        }
        matrix_1.push_back(mat);
        mat.clear();
    }
    return matrix_1;     
}
////16//////////////////////////////////////////////////////////
Matrix algebra::ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2)
{
    size_t row{matrix.size()};
    size_t column{matrix[0].size()};
    Matrix matrix_1{};
    std::vector<double> mat{};
    for(int i{0}; i<row; i++)
    {
        for(int j{0}; j<column; j++)
        {
            if(i == r2)
                mat.push_back(matrix[r1][j] * c + matrix[r2][j]);
            else
                mat.push_back(matrix[i][j]);
        }
        matrix_1.push_back(mat);
        mat.clear();
    }
    return matrix_1;     
}
////17//////////////////////////////////////////////////////////
Matrix algebra::upper_triangular(const Matrix& matrix)
{
    if(matrix.empty())
        return matrix;
    size_t row{matrix.size()};
    size_t column{matrix[0].size()};
    size_t i{0};
    if(row != column)
        throw std::logic_error("Caution: non-square matrices have no upper triangular form");
    Matrix matrix_1{matrix}; 
    while(i < row)
    {
        if(matrix_1[i][i] == 0)
            matrix_1 = ero_swap(matrix_1, i, i + 1);
        i++;
    }   
    for(int i{0}; i<row; i++)
    {
        for(int j{i+1}; j<row; j++)
        {
            matrix_1 = ero_sum(matrix_1, i, -matrix_1[j][i]/matrix_1[i][i], j);
        }
    }
    return matrix_1;      
}