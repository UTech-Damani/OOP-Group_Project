#ifndef PERSON_H
#define PERSON_H

#include <string>

// Since this class contains abstract methods/destructor, it is now an abstract class
class Person{
    private:
        int IdNom;
        std::string FullName;
        int Age;
        int Gender;

    public:
        virtual ~Person() = 0;
        virtual Display() =0;

        //Constructors
        Person()
        {
            //initializes
            IdNom = 0;
            FullName = "";
            Age = 0;
            Gender = "";

        }

        Person(int id, string name,int a, int g)
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
        int getGender() const{
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
        void setGender(int g){
            Gender = g;
        }
};
inline Person::~Person(){}


#endif // PERSON_H
