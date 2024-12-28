#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <random>
#include <string>
#include <algorithm>

using namespace std;

class Habitat {
private:
    static Habitat* habitatInstance;
    map<int, string> antColonies;
    map<int, map<string, int>> colonyResources;
    Habitat() {}
public:
    static Habitat* getHabitatInstance() {
        if (!habitatInstance) {
            habitatInstance = new Habitat();
        }
        return habitatInstance;
    }
    int createColony(int posX, int posY, const string& antSpecies) {
        int colonyID = antColonies.size() + 1;
        antColonies[colonyID] = antSpecies;
        colonyResources[colonyID] = {}; // Initialize empty resources
        cout << "Colony " << colonyID << " of species " << antSpecies << " created at (" << posX << ", " << posY << ").\n";
        return colonyID;
    }
    void allocateResources(int colonyID, const string& resourceName, int quantity) {
        if (antColonies.find(colonyID) != antColonies.end()) {
            colonyResources[colonyID][resourceName] += quantity;
            cout << "Allocated " << quantity << " of " << resourceName << " to colony " << colonyID << ".\n";
        } else {
            cout << "Colony " << colonyID << " does not exist.\n";
        }
    }
    void showColonies() {
        for (const auto& [colonyID, species] : antColonies) {
            cout << "Colony ID: " << colonyID << ", Species: " << species << ", Resources: ";
            for (const auto& [resource, amount] : colonyResources[colonyID]) {
                cout << resource << "=" << amount << " ";
            }
            cout << "\n";
        }
    }
};
Habitat* Habitat::habitatInstance = nullptr;

class AntNest {
public:
    class Builder {
    private:
        int totalRooms = 0;
        int capacity = 0;
    public:
        Builder& configureRooms(int roomCount) {
            totalRooms = roomCount;
            return *this;
        }
        Builder& configureCapacity(int restingCapacity) {
            capacity = restingCapacity;
            return *this;
        }
        AntNest build() {
            return AntNest(totalRooms, capacity);
        }
    };

    void displayNest() {
        cout << "AntNest with " << totalRooms << " rooms and resting capacity " << capacity << ".\n";
    }
private:
    int totalRooms;
    int capacity;
    AntNest(int roomCount, int restingCapacity) : totalRooms(roomCount), capacity(restingCapacity) {}
};

class Insect {
public:
    virtual void executeAction() = 0;
    virtual ~Insect() {}
};

class Worker : public Insect {
public:
    void executeAction() override {
        cout << "Worker is collecting resources.\n";
    }
};

class Soldier : public Insect {
public:
    void executeAction() override {
        cout << "Soldier is defending the colony.\n";
    }
};

class Monarch : public Insect {
public:
    void executeAction() override {
        cout << "Monarch is laying eggs.\n";
    }
};

class InsectFactory {
public:
    unique_ptr<Insect> produceInsect(const string& insectType) {
        if (insectType == "Worker") {
            return make_unique<Worker>();
        } else if (insectType == "Soldier") {
            return make_unique<Soldier>();
        } else if (insectType == "Monarch") {
            return make_unique<Monarch>();
        } else {
            return nullptr;
        }
    }
};

class InsectTraits {
public:
    virtual void defineTraits() = 0;
    virtual ~InsectTraits() {}
};

class BasicTraits : public InsectTraits {
public:
    void defineTraits() override {
        cout << "Basic insect traits.\n";
    }
};

class AgilityTrait : public InsectTraits {
private:
    shared_ptr<InsectTraits> basicTrait;
public:
    AgilityTrait(shared_ptr<InsectTraits> baseTrait) : basicTrait(baseTrait) {}
    void defineTraits() override {
        basicTrait->defineTraits();
        cout << "Agility trait added.\n";
    }
};

class StrengthTrait : public InsectTraits {
private:
    shared_ptr<InsectTraits> basicTrait;
public:
    StrengthTrait(shared_ptr<InsectTraits> baseTrait) : basicTrait(baseTrait) {}
    void defineTraits() override {
        basicTrait->defineTraits();
        cout << "Strength trait added.\n";
    }
};

class SimulationCoordinator {
public:
    void executeCycle(vector<shared_ptr<Insect>>& insectGroup) {
        shuffle(insectGroup.begin(), insectGroup.end(), mt19937{random_device{}()});
        for (auto& insect : insectGroup) {
            insect->executeAction();
        }
    }
};

void commandLineInterface() {
    Habitat* habitat = Habitat::getHabitatInstance();
    InsectFactory insectProducer;
    SimulationCoordinator coordinator;
    vector<shared_ptr<Insect>> insectCollection;

    string userCommand;
    while (true) {
        cout << "Enter command: ";
        getline(cin, userCommand);

        if (userCommand.find("create") == 0) {
            int coordX, coordY;
            string antSpecies;
            if (sscanf(userCommand.c_str(), "create %d %d %s", &coordX, &coordY, &antSpecies[0]) == 3) {
                int colonyID = habitat->createColony(coordX, coordY, antSpecies);
                insectCollection.push_back(insectProducer.produceInsect("Monarch"));
            } else {
                cout << "Invalid command format.\n";
            }
        } else if (userCommand.find("allocate") == 0) {
            int colonyID, quantity;
            char resource[50];
            if (sscanf(userCommand.c_str(), "allocate %d %s %d", &colonyID, resource, &quantity) == 3) {
                habitat->allocateResources(colonyID, resource, quantity);
            } else {
                cout << "Invalid command format.\n";
            }
        } else if (userCommand == "overview") {
            habitat->showColonies();
        } else if (userCommand.find("cycle") == 0) {
            coordinator.executeCycle(insectCollection);
        } else if (userCommand == "terminate") {
            break;
        } else {
            cout << "Unrecognized command.\n";
        }
    }
}

int main() {
    commandLineInterface();
    return 0;
}
