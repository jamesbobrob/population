/* pop.h */

// headers for Numerical recipies functions
float ran3(long *);

enum gender{
	MALE,
	FEMALE
};

class Person{
private:
	double age;
    gender sex;
public:
    bool student;
    bool employed;
    money salary;
    money assets;
    money liabilities;
    int IQ;

    int getAge(){
    	return age;
    }
    void setAge(double a){
    	age=a;
    }
    gender getGender{
    	return sex;
    }
};	