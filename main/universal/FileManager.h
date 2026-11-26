#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <filesystem>
#include <system_error>

#include "../exceptions/DataFileException.h"
#include "../exceptions/KPFLExceptions.h"

using namespace std;

class Persistable
{
public:
    virtual ~Persistable() = default;
    virtual string toFileString() const { return ""; }
};

class FileManager
{
private:
    string dataDirectory;

    string getPath(const string& fileName) const
    {
        if (dataDirectory.empty())
            return fileName;

        return (filesystem::path(dataDirectory) / filesystem::path(fileName)).string();
    }

public:
    static inline const char* const TEAMS_FILE = "teams.csv";
    static inline const char* const PEOPLE_FILE = "people.csv";
    static inline const char* const STADIUMS_FILE = "stadiums.csv";
    static inline const char* const FIXTURES_FILE = "fixtures.csv";
    static inline const char* const RESULTS_FILE = "results.csv";
    static inline const char* const TICKETS_FILE = "tickets.csv";
    static inline const char* const PRODUCTS_FILE = "products.csv";
    static inline const char* const TRANSACTIONS_FILE = "transactions.csv";

    explicit FileManager(const string& directory = "data")
        : dataDirectory(directory)
    {
        if (!dataDirectory.empty())
        {
            error_code error;
            const filesystem::path directoryPath(dataDirectory);

            if (filesystem::exists(directoryPath, error))
            {
                if (error || !filesystem::is_directory(directoryPath, error))
                    throw DataFileException();
            }
            else if (error || (!filesystem::create_directories(directoryPath, error) && error))
                throw DataFileException();
        }
    }

    string getFullPath(const string& fileName) const
    {
        return getPath(fileName);
    }

    void clearFile(const string& fileName) const
    {
        ofstream outFile(getPath(fileName), ios::trunc);
        if (!outFile)
            throw DataFileException();
    }

    vector<string> readLines(const string& fileName) const
    {
        ifstream inFile(getPath(fileName));
        if (!inFile)
            throw DataFileException();

        vector<string> lines;
        string line;
        while (getline(inFile, line))
        {
            if (!line.empty() && line.back() == '\r')
                line.pop_back();
            if (!line.empty())
                lines.push_back(line);
        }

        if (inFile.bad())
            throw DataFileException();

        return lines;
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
        catch (...)
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
        if (count < 0)
            throw DataFileException();

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
        catch (...)
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

    void saveStadiums(Persistable* stadiums[], int count) const
    {
        saveRecords(STADIUMS_FILE, stadiums, count);
    }

    void saveResults(Persistable* results[], int count) const
    {
        saveRecords(RESULTS_FILE, results, count);
    }

    void saveTickets(Persistable* tickets[], int count) const
    {
        saveRecords(TICKETS_FILE, tickets, count);
    }

    void saveProducts(Persistable* products[], int count) const
    {
        saveRecords(PRODUCTS_FILE, products, count);
    }

    void saveTransactions(Persistable* transactions[], int count) const
    {
        saveRecords(TRANSACTIONS_FILE, transactions, count);
    }

    template <typename T>
    int loadRecords(
        const string& fileName,
        unique_ptr<T> records[],
        int maxRecords) const
    {
        if (maxRecords < 0)
            throw DataFileException();

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
                T record = T::fromFileString(line);
                records[count] = unique_ptr<T>(new T(record));
            }
            catch (...)
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

    template <typename T>
    int loadStadiums(unique_ptr<T> stadiums[], int maxStadiums) const
    {
        return loadRecords(STADIUMS_FILE, stadiums, maxStadiums);
    }

    template <typename T>
    int loadResults(unique_ptr<T> results[], int maxResults) const
    {
        return loadRecords(RESULTS_FILE, results, maxResults);
    }

    template <typename T>
    int loadTickets(unique_ptr<T> tickets[], int maxTickets) const
    {
        return loadRecords(TICKETS_FILE, tickets, maxTickets);
    }

    template <typename T>
    int loadProducts(unique_ptr<T> products[], int maxProducts) const
    {
        return loadRecords(PRODUCTS_FILE, products, maxProducts);
    }

    template <typename T>
    int loadTransactions(unique_ptr<T> transactions[], int maxTransactions) const
    {
        return loadRecords(TRANSACTIONS_FILE, transactions, maxTransactions);
    }
};

#endif // FILEMANAGER_H
