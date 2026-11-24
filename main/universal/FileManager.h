#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <memory>
#include <string>
#include <direct.h>
#include <cerrno>

#include "../exceptions/DataFileException.h"
#include "../exceptions/KPFLExceptions.h"

using namespace std;

class Persistable
{
public:
    virtual ~Persistable() = default;
    virtual string toFileString() const;
};

class FileManager
{
private:
    string dataDirectory;

    string getPath(const string& fileName) const
    {
        if (dataDirectory.empty())
            return fileName;

        const char last = dataDirectory.back();
        if (last == '/' || last == '\\')
            return dataDirectory + fileName;

        return dataDirectory + "\\" + fileName;
    }

public:
    static const char* const TEAMS_FILE;
    static const char* const PEOPLE_FILE;
    static const char* const STADIUMS_FILE;
    static const char* const FIXTURES_FILE;
    static const char* const RESULTS_FILE;
    static const char* const TICKETS_FILE;
    static const char* const PRODUCTS_FILE;
    static const char* const TRANSACTIONS_FILE;

    explicit FileManager(const string& directory = "data")
        : dataDirectory(directory)
    {
        if (!dataDirectory.empty())
        {
            if (_mkdir(dataDirectory.c_str()) != 0 && errno != EEXIST)
                throw DataFileException();
        }
    }

    void appendLine(const string& fileName, const string& line) const
    {
        const string path = getPath(fileName);

        try
        {
            ofstream outFile(path, ios::app);
            if (!outFile)
                throw DataFileException();

            outFile << line << '\n';
            if (!outFile)
                throw DataFileException();
        }
        catch (const KPFLExceptions&)
        {
            throw DataFileException();
        }
    }

    void appendRecord(const string& fileName, const Persistable& record) const
    {
        appendLine(fileName, record.toFileString());
    }

    void addTeam(const Persistable& team) const
    {
        appendRecord(TEAMS_FILE, team);
    }

    void addPerson(const Persistable& person) const
    {
        appendRecord(PEOPLE_FILE, person);
    }

    void addStadium(const Persistable& stadium) const
    {
        appendRecord(STADIUMS_FILE, stadium);
    }

    void addFixture(const Persistable& fixture) const
    {
        appendRecord(FIXTURES_FILE, fixture);
    }

    void addResult(const Persistable& result) const
    {
        appendRecord(RESULTS_FILE, result);
    }

    void addTicket(const Persistable& ticket) const
    {
        appendRecord(TICKETS_FILE, ticket);
    }

    void addProduct(const Persistable& product) const
    {
        appendRecord(PRODUCTS_FILE, product);
    }

    void addTransaction(const Persistable& transaction) const
    {
        appendRecord(TRANSACTIONS_FILE, transaction);
    }

    void saveRecords(
        const string& fileName,
        Persistable* records[],
        int count) const
    {
        const string path = getPath(fileName);

        try
        {
            ofstream outFile(path, ios::trunc);
            if (!outFile)
                throw DataFileException();

            for (int i = 0; i < count; ++i)
            {
                if (records[i] == nullptr)
                    throw DataFileException();

                outFile << records[i]->toFileString() << '\n';
            }

            if (!outFile)
                throw DataFileException();
        }
        catch (const KPFLExceptions&)
        {
            throw DataFileException();
        }
    }

    void saveTeams(Persistable* teams[], int count) const
    {
        saveRecords(TEAMS_FILE, teams, count);
    }

    void savePeople(Persistable* people[], int count) const
    {
        saveRecords(PEOPLE_FILE, people, count);
    }

    void saveFixtures(Persistable* fixtures[], int count) const
    {
        saveRecords(FIXTURES_FILE, fixtures, count);
    }

    template <typename T>
    int loadRecords(
        const string& fileName,
        unique_ptr<T> records[],
        int maxRecords,
        unique_ptr<T> (*create)(const string&)) const
    {
        const string path = getPath(fileName);
        ifstream inFile(path);
        if (!inFile)
            throw DataFileException();

        int count = 0;
        string line;

        while (getline(inFile, line))
        {
            if (!line.empty() && line.back() == '\r')
                line.pop_back();

            if (line.empty())
                continue;

            if (count >= maxRecords)
                throw DataFileException();

            try
            {
                records[count] = create(line);
                if (!records[count])
                    throw DataFileException();
            }
            catch (const KPFLExceptions&)
            {
                throw DataFileException();
            }

            ++count;
        }

        if (inFile.bad())
            throw DataFileException();

        return count;
    }

    template <typename T>
    int loadRecords(
        const string& fileName,
        unique_ptr<T> records[],
        int maxRecords) const
    {
        return loadRecords(
            fileName,
            records,
            maxRecords,
            &T::fromFileString
        );
    }

    template <typename T>
    int loadTeams(unique_ptr<T> teams[], int maxTeams) const
    {
        return loadRecords(TEAMS_FILE, teams, maxTeams);
    }

    template <typename T>
    int loadFixtures(unique_ptr<T> fixtures[], int maxFixtures) const
    {
        return loadRecords(FIXTURES_FILE, fixtures, maxFixtures);
    }

    template <typename T>
    int loadPeople(unique_ptr<T> people[], int maxPeople) const
    {
        return loadRecords(PEOPLE_FILE, people, maxPeople);
    }
};

const char* const FileManager::TEAMS_FILE = "teams.csv";
const char* const FileManager::PEOPLE_FILE = "people.csv";
const char* const FileManager::STADIUMS_FILE = "stadiums.csv";
const char* const FileManager::FIXTURES_FILE = "fixtures.csv";
const char* const FileManager::RESULTS_FILE = "results.csv";
const char* const FileManager::TICKETS_FILE = "tickets.csv";
const char* const FileManager::PRODUCTS_FILE = "products.csv";
const char* const FileManager::TRANSACTIONS_FILE = "transactions.csv";

#endif // FILEMANAGER_H
