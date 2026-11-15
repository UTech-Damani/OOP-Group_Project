#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

using namespace std;

// Since this class contains abstract methods/destructor, it is now an abstract class
class Person{
    private:
        int IdNom;
        string FullName;
        int Age;
        string Gender;

    public:
        virtual ~Person() = 0;
        virtual void Display() =0;

        //Constructors
        Person()
        {
            //initializes
            IdNom = 0;
            FullName = "BLANK";
            Age = 0;
            Gender = "BLANK";

        }

        Person(int id, string name,int a, string g)
        {
            //will store data entered by the user.
            IdNom = id;
            FullName = name;
            Age = a;
            Gender = g;
        }

        //Getters
        int getIdNom() const{
            return IdNom;
        }
        std::string getFullName() const{
            return FullName;
        }
        int getAge() const{
            return Age;
        }
        string getGender() const{
            return Gender;
        }

        //setters
        void setIdNom(int id){
            IdNom = id;
        }
        void setFullName(const std::string& name){
            FullName = name;
        }
        void setAge(int a){
            Age = a;
        }
        void setGender(string g){
            Gender = g;
        }
};
inline Person::~Person(){}


#endif // PERSON_H
