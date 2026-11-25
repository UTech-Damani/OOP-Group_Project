#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include "../universal/FileManager.h"

using namespace std;

// Since this class contains abstract methods/destructor, it is now an abstract class
class Person : public Persistable{
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

        //Setters - Monecia

        // Set ID
        void setIdNom(int id){
            if (id > 0){
                IdNom = id;
            }
        }

        // Set full name
        void setFullName(const std::string& name)
        {
            if (name != "")
                {
                    FullName = name;
                }
        }

        // Set age
        void setAge(int a)
        {
            if (a >= 0)
                {
                    Age = a;
                }
        }

        // Set gender
        void setGender(const string& g)
        {
            if (!g.empty())
                Gender = g;
        }
};
inline Person::~Person(){}


#endif // PERSON_H
