#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <cstring>
using namespace std;

class Matrix{
    private:
        int ** matrix,rows,cols;
        string info;
        void MakeString(){
            info = "";
            info +="[";
            for(int i = 0; i < rows;i++){
                for(int  j = 0; j < cols;j++){
                    info+= to_string(matrix[i][j]);
                    if(j != cols-1)
                        info+=",";
                }
                info+=";";
            }         
            info +="]";       
        }
    public:
        explicit Matrix(int **matrix = NULL, int rows = 0, int cols = 0){
            this->matrix  = matrix;
            if(rows >= 0)
                this->rows = rows;
            if(cols >= cols)
                this->cols = cols;
            MakeString();
        } 
        Matrix(int num){
        	matrix = new int*[1];
        	matrix[0] = new int[1];
        	matrix[0][0] = num;
        	rows = 1;
        	cols=1;
        	MakeString();
		}
		Matrix(Matrix const &copy){
            matrix = new int* [copy.rows];
            for(int i = 0; i < copy.rows;i++){
                matrix[i] = new int[copy.cols];
                memcpy(matrix[i], copy.matrix[i],sizeof(copy.matrix[i]));
            }
            rows = copy.rows;
            cols = copy.cols;
            info = copy.info;
        }
        Matrix(Matrix &&copy){
        	matrix = NULL;
        	swap(matrix,copy.matrix);
            rows = copy.rows;
            cols = copy.cols;
            info = copy.info;
        }
      	Matrix (string s){
			if(s[0] == '[' || s[s.size()-2] != ';'){
        		int *current_cols = new int[s.size()],current_rows = 0;
        		for(int i =0; i < s.size();i++){
       				current_cols[i]=1;
				}
        		for(int i = 1; i < s.size()-1;i++){
       				if(s[i] == ',')
       					current_cols[current_rows]++;
       				else if(s[i] == ';')
       					current_rows++;
				}
				for(int i =1; i < current_rows;i++){
					if(current_cols[0] != current_cols[i]){
						this->matrix  = NULL;
           		 		this->rows = 0;
            	   		this->cols = 0;
            			MakeString();
            			return;
					}
				}
				this->rows = current_rows;
				this->cols = current_cols[0];
				this->matrix = new int*[current_rows];
				int col,num,string_index = 0,minus;
				for(int i = 0; i < this->rows;i++){
					this->matrix[i] = new int [this->cols];
					minus = 1;
					col = 0;
					num = 0;
				
					while(s[string_index] != ';'){
						if(s[string_index] == '-')
							minus = -1;
						else if(isdigit(s[string_index]))
							num= num*10+(s[string_index]-'0');
						else if(s[string_index] == ',' || s[string_index] == ';'){
							num*=minus;
							minus = 1;
							this->matrix[i][col++] = num;
							num = 0;
						}else if(s[string_index] == ']'){
							MakeString();
							break;
						}
						string_index++;
					}
					num*=minus;
					this->matrix[i][col] = num;
					string_index++;
				}
				MakeString();
			}else{
				this->matrix  = NULL;
            	this->rows = 0;
           		this->cols = 0;
           		MakeString();
           		return;
			}      	
		}
        Matrix & operator = (Matrix const &move){
            if (this != &move) {
                for(int i = 0; i < rows;i++){
                    delete matrix[i];
                }
                delete matrix;
                matrix = new int* [move.rows];
                for(int i = 0; i < move.rows;i++){
                    matrix[i] = new int[move.cols];
                    memcpy(matrix[i], move.matrix[i],sizeof(move.matrix[i]));
                }
	            rows = move.rows;
	            cols = move.cols;
	            info = move.info;
			}
            return *this;
        }
        Matrix & operator = (Matrix &&move){
            if (this != &move) {
                for(int i = 0; i < rows;i++){
                    delete matrix[i];
                }
                delete matrix;
                matrix = move.matrix;
            	move.matrix = NULL;
                rows = move.rows;
                cols = move.cols;
                info = move.info;}
            return *this;
        }
        ~ Matrix(){
        	if(matrix != NULL){
        		for(int i = 0; i < rows;i++){
                	delete matrix[i];
            	}
            	delete matrix;
			}
            
        }
        
        static int ** CreateMatrix(int rows, int cols ){
            int **temp_m = new int *[rows];
            for(int i = 0; i < rows;i++){
                temp_m[i] = new int [cols];
                for(int ind = 0; ind < cols;ind++){
                    temp_m[i][ind] = 0;
                }
            }
            return temp_m;
        }
        
        string get_info(){
            return info;
        }
        int get_rows(){
            return rows;
        }
        int get_cols(){
            return cols;
        }
        int **get_matrix(){
            int **temp = new int *[rows];
            for(int i = 0; i < rows;i++){
                temp[i] = new int [cols];
                memcpy (temp[i], matrix[i],cols*sizeof(int));
            }
            return temp;
        }
        void set_new_matrix(int **matrix, int rows, int cols){
            if(cols > 0 && rows > 0 && matrix != NULL){
                for(int i = 0; i < rows;i++){
                delete matrix[i];
                }
                delete matrix;
                this->matrix = matrix;
                this->rows = rows;
                this->cols = cols;
            }
        }
        void set_new_matrix(string mat){
            *this = Matrix(mat);
        }
        int matrix_sum() const{
            int sum =0;
            for(int i = 0; i < rows;i++){
                for(int j =0; j<cols;j++ ){
                    sum+=matrix[i][j];
                }
            }
            return sum;
        }
        
        Matrix operator +(const Matrix& m){
            if(this->cols != m.cols  || this->rows != m.rows)
                return Matrix();
            int **temp = CreateMatrix(this->rows,this->cols);
            for(int i = 0; i < rows;i++){
                for(int j =0; j < cols;j++){
                    temp[i][j] = m.matrix[i][j] +this->matrix[i][j];
                }
            }
            return Matrix(temp,this->rows,this->cols);
        }
        Matrix operator-(const Matrix& m){
            if(this->cols != m.cols  || this->rows != m.rows)
                return Matrix();
            int **temp = CreateMatrix(this->rows,this->cols);
            for(int i = 0; i < rows;i++){
                for(int j =0; j < cols;j++){
                    temp[i][j] = this->matrix[i][j]-m.matrix[i][j];
                }
            }
            return Matrix(temp,this->rows,this->cols);
        }
        Matrix operator *(const Matrix& m){
            if(this->cols != m.rows )
                return Matrix();
            int **temp = CreateMatrix(this->rows,this->cols);
            for(int i = 0; i < this->rows;i++){
                for(int j = 0; j < this->cols;j++){
                    for(int col = 0; col < this->cols;col++){
                        temp[i][j] += this->matrix[i][col]*m.matrix[col][j];
                    }
                }
            }
            return Matrix(temp,this->rows,this->cols);
        }
        bool operator == (const Matrix& m){
            return this->matrix_sum() == m.matrix_sum();
        }
        bool operator < (const Matrix& m){
            return this->matrix_sum() < m.matrix_sum();
        }
        bool operator > (const Matrix& m){
            return this->matrix_sum() > m.matrix_sum();
        }
        bool operator != (const Matrix& m){
            return !(this->matrix_sum() == m.matrix_sum());
        }
        bool operator >= (const Matrix& m){
            return this->matrix_sum() == m.matrix_sum() || this->matrix_sum() > m.matrix_sum();
        }
        bool operator <= (const Matrix& m){
            return this->matrix_sum() == m.matrix_sum() || this->matrix_sum() < m.matrix_sum();
        }
        Matrix & operator += (const Matrix &move){
            *this =(*this+move);
            return *this;
        }
        Matrix & operator -= (const Matrix &move){
            *this =(*this-move);
            return *this;
        }
        Matrix & operator *= (const Matrix &move){
            *this = (*this*move);
            return *this;
        }
        Matrix & operator += (int move){
            *this =(*this+Matrix(move));
            return *this;
        }
        Matrix & operator -= (int move){
            *this =(*this-Matrix(move));
            return *this;
        }
        Matrix & operator *= (int move){
            *this = (*this*Matrix(move));
            return *this;
        }
        Matrix operator +(string s){
            return *this + Matrix(s);
        }
        Matrix operator-(string s){
            return *this - Matrix(s);
        }
        Matrix operator *(string s){
             return *this * Matrix(s);
        }
         Matrix operator +(int num){
            return *this + Matrix(num);
        }
        Matrix operator-(int num){
            return *this - Matrix(num);
        }
        Matrix operator *(int num){
             return *this * Matrix(num);
        }
        void PrintInfo(){
            for(int i = 0; i < rows;i++){
                for(int  j = 0; j < cols;j++){
                    cout << matrix[i][j] << " ";
                }
            cout << endl;}
        }
};
int ** RandomFill(int ** matrix,int rows,int cols,int from =0, int  to = 100){
    for(int i = 0; i < rows;i++){
        for(int j = 0; j < cols;j++){
            matrix[i][j] = rand()%to+from;
        }
    }
    return matrix;
}
int main(){
    srand(time(0));
    Matrix temp_mat(5);
    temp_mat.set_new_matrix("[1,2,3;1,2,3;1,2,3;]");
    temp_mat.PrintInfo();
	system("pause");
	system("cls");
    cout << "Convert [1,2,3;1,2,3;1,2,3;] to matrix object:\n";
    Matrix string_mat("[1,2,3;1,2,3;1,2,3;]");
    string_mat.PrintInfo();
	system("pause");
	system("cls");
	cout << "Convert integer 5 to matrix object:\n";
    Matrix num_mat(5);
    num_mat.PrintInfo();
	system("pause");
	system("cls");
    Matrix mat1(RandomFill(Matrix::CreateMatrix(2,2),2,2),2,2),mat3(mat1);//copy test
    //Test of get functions 
    cout << "Test of get functions: \n";
    cout << mat1.get_info() << endl<< endl;
    cout << "Get matrix array: \n";
    int **mat2 = mat1.get_matrix();
    for(int i = 0; i < mat1.get_rows();i++){
       for(int  j = 0; j < mat1.get_cols();j++){
           cout << mat2[i][j] << " ";}
       cout << endl;}
    for(int i = 0; i < mat1.get_rows();i++)
       delete mat2[i];
    delete mat2;
    system("pause");
    system("cls");
   //End of the test

   //Op assigment test
   Matrix temp(RandomFill(Matrix::CreateMatrix(2,2),2,2),2,2),dest;
   cout << "Operator assigment test: \n";
   cout << "Copy temp matrix: " << temp.get_info() << ".";
   cout << "To dest matrix" << endl;
   dest = temp;
   cout << "Dest matrix: \n";
   dest.PrintInfo();
   system("pause");
   system("cls");
   //End of the test

   //Test of arithmetic
   cout <<"Test of arithmetic: \n";
   cout << "Matrix mat1: \n";
   mat1.PrintInfo();cout << endl;
   cout << "Matrix mat3: \n";
   mat3.PrintInfo();cout << endl;
   cout << "mat1+mat3+mat3: \n";(mat1+mat3+mat3).PrintInfo(); cout << endl;
   cout << "mat1-mat3-mat3: \n";(mat1-mat3-mat3).PrintInfo(); cout << endl;
   cout << "mat1*mat3: \n";(mat1*mat3).PrintInfo(); cout << endl;
   cout << "mat1+=mat3 \n";mat1+=mat3;
   mat1.PrintInfo(); cout << endl;
   cout << "mat1-=mat3 \n";mat1-=mat3;
   mat1.PrintInfo(); cout << endl;
   cout << "mat1*=mat3 \n";mat1*=mat3;
   mat1.PrintInfo(); cout << endl;
   system("pause");
   system("cls");
   //End of the test
   Matrix a;
   cout << "Test of bool operators: \n";
   cout << "Matrix a is NULL matrix" << endl;
   cout << "Matrix mat1 is: " << mat1.get_info() << endl;
   cout <<"(a > mat1): "<< (a > mat1) << endl;
   cout <<"(a < mat1): "<< (a < mat1) << endl;
   cout <<"(a <= mat1): "<< (a <= mat1) << endl;
   cout <<"(a >= mat1): "<< (a >= mat1) << endl;
   cout <<"(a == a): "<< (a == a) << endl;
   cout <<"(a != mat1): "<< (a !=mat1) << endl;
   system("pause");
   system("cls");
   cout << "Test of arithmetic with integers: \n";
   cout << "num_mat = 5" << endl;
   cout << "num_mat+5 = ";(num_mat+5).PrintInfo(); 
   cout << "num_mat-5 = ";(num_mat-5).PrintInfo();
   cout << "num_mat*5 = ";(num_mat*5).PrintInfo(); 
   system("pause");
   system("cls");
   cout << "Test of arithmetic with strings: \n";
   cout << "string_mat = [1,2,3;1,2,3;1,2,3;]" << endl;
   cout << "string_mat+[1,2,3;1,2,3;1,2,3;]: \n";(string_mat+"[1,2,3;1,2,3;1,2,3;]").PrintInfo();
   cout << "string_mat-[1,2,3;1,2,3;1,2,3;]: \n";(string_mat-"[1,2,3;1,2,3;1,2,3;]").PrintInfo();
   cout << "string_mat*[1,2,3;1,2,3;1,2,3;]: \n";(string_mat*"[1,2,3;1,2,3;1,2,3;]").PrintInfo();
   return 0;
}
