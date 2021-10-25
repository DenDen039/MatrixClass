#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <cstring>
using namespace std;
class Exception{
	protected:
		string e_type;	
	public:
		Exception(string error_type = "unknown_error"){
			e_type = error_type;
		}
		Exception(const Exception &e){
			e_type =e.e_type;
		}
		Exception& operator = (const Exception &e){
			e_type =e.e_type;
			return *this;
		}
		Exception(Exception &&e){
			e_type =e.e_type;
		}
		Exception& operator = (Exception &&e){
			e_type =e.e_type;
			return *this;
		}
		string get_error_type(){
			return e_type;
		}
};
class DivisionError:public Exception{
	private:
		int mat_rows,mat_cols;
	public:
		DivisionError(int rows, int cols, string error_type="wrong_dvision_matrix_size"){
			e_type = error_type;
		DivisionError(int rows, int cols, string error_type="wrong_dvision_matrix_size"):Exception(error_type){
			mat_rows = rows;
			mat_cols = cols;
		}
		DivisionError(const DivisionError &e){
			e_type =e.e_type;
		DivisionError(const DivisionError &e):Exception(e){
			mat_rows =e.mat_rows;
			mat_cols =e.mat_cols;
		}
@@ -58,11 +56,9 @@ class DivisionError:public Exception{
};
class DivisionByZero:public Exception{
	public:
		DivisionByZero(string error_type="division_by_zero"){
			e_type = error_type;
		DivisionByZero(string error_type="division_by_zero"):Exception(error_type){
		}
		DivisionByZero(const DivisionByZero &e){
			e_type =e.e_type;
		DivisionByZero(const DivisionByZero &e):Exception(e){
		}
		DivisionByZero & operator = (const DivisionByZero &e){
			e_type =e.e_type;
@@ -73,14 +69,13 @@ class SizeError:public Exception{
	private:
		int rows1,rows2,cols1,cols2;
	public:
		SizeError(int rows1,int cols1,int rows2,int cols2,string error_type="size_error"){
			e_type = error_type;
		SizeError(int rows1,int cols1,int rows2,int cols2,string error_type="size_error"):Exception(error_type){
			this->cols1 = cols1;
			this->cols2 = cols2;
			this->rows1 = rows1;
			this->rows2 = rows2;
		}
		SizeError(const SizeError &e){
		SizeError(const SizeError &e):Exception(e){
			e_type =e.e_type;
			rows1 =e.rows1;
			rows2 =e.rows2;
@@ -107,12 +102,12 @@ class MultiplicationSizeError:public Exception{
	private:
		int rows2,cols1;
	public:
		MultiplicationSizeError(int cols1,int rows2, string error_type="multiplication_size_error"){
		MultiplicationSizeError(int cols1,int rows2, string error_type="multiplication_size_error"):Exception(error_type){
			e_type = error_type;
			this->cols1 = cols1;
			this->rows2 = rows2;
		}
		MultiplicationSizeError(const MultiplicationSizeError &e){
		MultiplicationSizeError(const MultiplicationSizeError &e):Exception(e){
			e_type =e.e_type;
			rows2 =e.rows2;
			cols1 =e.cols1;
@@ -134,14 +129,14 @@ class IndexError:public Exception{
	private:
		int row,col,mrows,mcols;
	public:
		IndexError(int row, int col,int mrows,int mcols,string error_type="index_error"){
		IndexError(int row, int col,int mrows,int mcols,string error_type="index_error"):Exception(error_type){
			e_type = error_type;
			this->row = row;
			this->col =col;
			this->mrows = mrows;
			this->mcols = mcols;
		}
		IndexError(const IndexError &e){
		IndexError(const IndexError &e):Exception(e){
			e_type =e.e_type;
			row = e.row;
			col = e.col;
@@ -180,12 +175,12 @@ class StringConvertError:public Exception{
		string reason;
		int index_error;
	public:
		StringConvertError (int index_error,string reason = "uknown error", string error_type="string_convert_error"){
		StringConvertError (int index_error,string reason = "uknown error", string error_type="string_convert_error"):Exception(error_type){
			this->reason = reason;
			this->index_error = index_error;
			e_type = error_type;
		}
		StringConvertError(const StringConvertError &e){
		StringConvertError(const StringConvertError &e):Exception(e){
			e_type =e.e_type;
			reason = e.reason;
		}
		StringConvertError& operator = (const StringConvertError &e){
			e_type =e.e_type;
			reason =e.reason;
			return *this;
		}
		int get_index_error(){
			return index_error; 
		}
		string get_reason(){
			return reason;
		}
};
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
        	try{
        		if(rows < 0)
        			throw Exception("Variable out of range");
        		this->rows = rows;
			}catch(Exception &e){
				cout << e.get_error_type() << endl;
        		this->rows = 0;
			}
			try{
        		if(cols < 0)
        			throw Exception("Variable out of range");
        		this->cols = cols;
			}catch(Exception &e){
				cout << e.get_error_type() << endl;
        		this->cols = 0;
			}
            this->matrix  = matrix;
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
      		try{
      			if(s[0] != '[')
      				throw StringConvertError(0,"Wrong string set up");
      			if(s[s.size()-2] != ';')
				  	throw StringConvertError(s.size()-2,"Wrong string set up"); 
				if(s[s.size()-1] != ']')
					throw StringConvertError(s.size()-1,"Wrong string set up"); 
        		int *current_cols = new int[s.size()],current_rows = 0;
        		for(int i =0; i < s.size();i++){
       					current_cols[i]=1;
				}
        		for(int i = 1; i < s.size()-1;i++){
        			if(!isdigit(s[i]) && s[i] != ','&& s[i] != ';'&& s[i] != '-')
        				throw StringConvertError(i,"Unexpected symbol");
       				if(s[i] == ',')
       					current_cols[current_rows]++;
       				else if(s[i] == ';')
       					current_rows++;
				}
				for(int i =1; i < current_rows;i++){
					if(current_cols[0] != current_cols[i])
						throw StringConvertError(-1,"Not the same amount of elements in the columns");
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
			}
			catch(StringConvertError &e){
				cout << e.get_error_type() << endl;
				cout << e.get_reason() << endl;
				if(e.get_index_error() != -1)
					cout << "Index error: " << e.get_index_error() << endl;
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
                matrix = NULL;
            	swap(move.matrix,matrix);
                rows = move.rows;
                cols = move.cols;
                info = move.info;}
            return *this;
        }
        ~ Matrix(){
        	if(rows < 0)
        		throw 1;
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
        int get_elment_by_index(int row, int col){
        	try{
        		if(row > rows || row < 0 || col > cols || col <0){
        			throw IndexError(row,col,rows,cols);
				}
			}
        	catch(IndexError &e){
        		cout << e.get_error_type() << endl;
        		cout << e.get_out_of_bounce_info();
        		return 0;
			}
			return matrix[row][col];
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
                delete this->matrix[i];
                }
                delete this->matrix;
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
        	try{
        		if(this->cols != m.cols  || this->rows != m.rows)
            		throw SizeError(this->rows,this->cols,m.rows,m.cols);
            	int **temp = CreateMatrix(this->rows,this->cols);
            	for(int i = 0; i < rows;i++){
             	   for(int j =0; j < cols;j++){
              	      temp[i][j] = m.matrix[i][j] +this->matrix[i][j];
                	}
            	}
            	return Matrix(temp,this->rows,this->cols);
			}
			catch(SizeError &e){
				cout << e.get_error_type() << endl;
				cout << e.get_size_info();
				return Matrix();
			}
            
        }
        Matrix operator-(const Matrix& m){
        	try{
            	if(this->cols != m.cols  || this->rows != m.rows)
            		throw SizeError(this->rows,this->cols,m.rows,m.cols);
            	int **temp = CreateMatrix(this->rows,this->cols);
            	for(int i = 0; i < rows;i++){
                	for(int j =0; j < cols;j++){
                    	temp[i][j] = this->matrix[i][j]-m.matrix[i][j];
                	}
            	}
            	return Matrix(temp,this->rows,this->cols);
            }
			catch(SizeError &e){
				cout << e.get_error_type() << endl;
				cout << e.get_size_info();
				return Matrix();
			}
            
        }
        Matrix operator *(const Matrix& m){
        	try{
            	if(this->cols != m.rows )
            	    throw MultiplicationSizeError(this->cols,m.rows);
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
            catch(MultiplicationSizeError &e){
            	cout << e.get_error_type() << endl;
				cout << e.get_size_info();
            	return Matrix();
			}
        }
        Matrix operator /(const Matrix& m){
        	try{
        		if(this->matrix == NULL)
        			throw 1;
        		if(m.cols != 1 || m.rows != 1){
        			throw DivisionError(m.cols,m.rows);
				}
				if(m.matrix[0][0] == 0){
					throw DivisionByZero();
				}
				return Matrix(*this*(1/m.matrix[0][0]));
			}
        	catch(DivisionByZero &e){
        		cout << e.get_error_type() << endl;
        		return Matrix();
			}
			catch(DivisionError &e){
        		cout << e.get_error_type()<< endl;
        		cout << "Matrix size: " << e.get_rows() << "x" << e.get_cols() << endl;
        		return Matrix();
			}
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
        Matrix & operator /= (const Matrix &move){
            *this = (*this/move);
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
        Matrix & operator /= (int move){
            *this = (*this/Matrix(move));
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
        Matrix operator /(string s){
             return *this / Matrix(s);
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
        Matrix operator /(int num){
    		return *this / Matrix(num);
		}
        friend ostream& operator<<(ostream& os,const Matrix &A);
};
ostream& operator<<(ostream& os,const Matrix &A){
    for(int i = 0; i < A.rows;i++){
        for(int  j = 0; j < A.cols;j++){
        	os << A.matrix[i][j] << " ";
        }
        os << endl;
	}
	return os;
}
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
    set_terminate([](){cout << "Unhandled exception" << endl;abort();});
    //Matrix emat,temp_mat1;
	//emat /= temp_mat1;
	//int b = 5/0;
    DivisionError e1(1,2,"OldInfo"),e2(2,3,"NewInfo");
    e1 = e2;
    cout <<  e1.get_error_type();
    system("pause");
	system("cls");
    Matrix temp_mat(5);
    (temp_mat/"[1,2;]");
    (temp_mat/0);
    system("pause");
	system("cls");
	temp_mat.get_elment_by_index(-1,1);
	system("pause");
	system("cls");
	(Matrix("[1,2;1,2;]")+Matrix("[1,2;1,2;1,2;]"));
	system("pause");
	system("cls");
	(Matrix("[1,2;1,2;]")*Matrix("[1,2;1,2;1,2;]"));
	system("pause");
	system("cls");
	Matrix string_mat_e("[1,2,3 ;1,2,3;1,2,3;]");
    cout << string_mat_e;
	system("pause");
	system("cls");
    temp_mat.set_new_matrix("[1,2,3;1,2,3;1,2,3;]");
    cout << temp_mat;
	system("pause");
	system("cls");
    cout << "Convert [1,2,3;1,2,3;1,2,3;] to matrix object:\n";
    Matrix string_mat("[1,2,3;1,2,3;1,2,3;]");
    cout << string_mat;
	system("pause");
	system("cls");
	cout << "Convert integer 5 to matrix object:\n";
    Matrix num_mat(5);
    cout << num_mat;
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
   cout << dest;
   system("pause");
   system("cls");
   //End of the test
   //Test of arithmetic
   cout <<"Test of arithmetic: \n";
   cout << "Matrix mat1: \n";
   cout << mat1 << endl;
   cout << "Matrix mat3: \n";
   cout << mat3 << endl;
   cout << "mat1+mat3+mat3: \n"<<(mat1+mat3+mat3)<< endl;
   cout << "mat1-mat3-mat3: \n"<<(mat1-mat3-mat3)<< endl;
   cout << "mat1*mat3: \n"<<(mat1*mat3)<< endl;
   cout << "mat1+=mat3 \n";mat1+=mat3;
   cout <<mat1<< endl;
   cout << "mat1-=mat3 \n";mat1-=mat3;
   cout <<mat1<< endl;
   cout << "mat1*=mat3 \n";mat1*=mat3;
   cout <<mat1<< endl;
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
   cout << "num_mat+5 = "<<(num_mat+5); 
   cout << "num_mat-5 = "<<(num_mat-5);
   cout << "num_mat*5 = "<<(num_mat*5); 
   system("pause");
   system("cls");
   cout << "Test of arithmetic with strings: \n";
   cout << "string_mat = [1,2,3;1,2,3;1,2,3;]" << endl;
   cout << "string_mat+[1,2,3;1,2,3;1,2,3;]: \n"<<(string_mat+"[1,2,3;1,2,3;1,2,3;]");
   cout << "string_mat-[1,2,3;1,2,3;1,2,3;]: \n"<<(string_mat-"[1,2,3;1,2,3;1,2,3;]");
   cout << "string_mat*[1,2,3;1,2,3;1,2,3;]: \n"<<(string_mat*"[1,2,3;1,2,3;1,2,3;]");
   return 0;
}
