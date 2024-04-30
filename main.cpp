#include <iostream>
#include <random>
#include <vector>
using namespace std;

int randRange(int start, int end) {
    random_device rd;
    uniform_int_distribution<int> dist(start,end);
    int randomNum = dist(rd);
    return randomNum;
}

struct Location {
     int x;
     int y;
};

class Animal {
protected:
    int health;
    Location location {};
    int id;
    void stayInGrid(int &x,int movementValue) {
        if (x > 100) {
            x = 100;
            x -= randRange(0, movementValue);
        } else if (x < 0) {
            x = 0;
            x += randRange(0, movementValue);
        }

    }

public:

    Animal() {

    }
    Animal(int id) : health(randRange(20,100)),id(id)
    {
        location.x = randRange(0,100);
        location.y = randRange(0,100);
    }

    int getHealth() const {
        return health;
    }
    Location getLocation() const {
        return location;
    }
    int getId() const {
        return id;
    }
    void setHealth(int health) {
        this->health = health;
    }
    void setLocation(Location location) {
        this->location = location;
    }
    void setId(int id) {
        this->id =  id;
    }

    virtual void move() {

    }

    bool isNearObject(Location l) const {
        return abs(location.x - l.x) <= 5 && abs(location.y - l.y) <=5;
    }
    void showAnimalLocation() {
        cout  << location.x << "," << location.y;
    }

};

class Dog : public Animal {
private:
    static int numberOfDogs;
public:

    Dog() :Animal() {

    }

    Dog(int id) : Animal(id) {
        numberOfDogs++;
    }
    ~Dog() {

    }

    static int getCount()  {
        return numberOfDogs;
    }

    void operator--() {

        numberOfDogs--;
    }
};
int Dog::numberOfDogs = 0;

class Cat : public Animal {
private:
   static int numberOfCats;

public:

    Cat(int id) : Animal(id) {
        numberOfCats++;
    }
    Cat() : Animal() {

    }
    Cat(int id,Location l,int health) : Animal(id) {
        location = l;
        this->health = health;
        numberOfCats++;
    }

    ~Cat() {

  }
    static int getCount() {
        return numberOfCats;
    }


    void move() override  {
        Location newLocation;
        int newX  = location.x + randRange(-5,5);
        int newY = location.y + randRange(-10,10);
        stayInGrid(newX,5);
        stayInGrid(newY,10);
        newLocation.x = newX;
        newLocation.y = newY;
        setLocation(newLocation);
    }

    bool fight(Dog dog) {
        if (determineWinner(dog.getHealth())) {
            cout << "cat:"<< id<< " turned " <<"dog: "<<  dog.getId() << " into a cat \n";
            health-=5;
            dog.operator--();
            numberOfCats++;
            return true;
        }
        cout << "Dog " << dog.getId() << " beat cat " << id << endl;
        dog.setHealth(dog.getHealth()-5);
        numberOfCats--;
        return false;
    }

    bool determineWinner(int opponentHealth) {
        int chanceOfWinning = 50;
        chanceOfWinning+= (health - opponentHealth);
        int randomNumber = randRange(1,100);
        return randomNumber <=chanceOfWinning;
    }
};

int Cat::numberOfCats = 0;


void populateArray(Cat* cats,int arraySize ) {
    for(int i =0; i<arraySize; i++) {
        cats[i] = Cat(i);
    }
}
void populateArray(Dog* dogs,int size) {
    for(int i=0;i<size;i++) {
        dogs[i] = Dog(i);

    }
}

class NeverDog {
private:
    Dog* dogs;
    Cat* cats;
    int startingNumOfCats;
    int startingNumOfDogs;
public:

    NeverDog(int numberOfCats, int numberOfDogs) :startingNumOfCats(numberOfCats),startingNumOfDogs(numberOfDogs) {
        dogs = new Dog[numberOfDogs];
        populateArray(dogs,numberOfDogs);
        cats = new Cat[numberOfCats];
        populateArray(cats,numberOfCats);
    }

    void increaseCatArray(int newSize) {
        Cat* newArr = new Cat[newSize];
        for(int i =0;i<newSize;i++) {
            newArr[i] = cats[i];
        }
        delete[] cats;
        cats = newArr;
    }

    void removeFromArray(Dog& dog,int size) {
        Dog* newArr = new Dog[size-1];
        for(int i = 0,j = 0;i<size;i++) {
            if(dogs[i].getId() != dog.getId()) {
                newArr[j].setId(dogs[i].getId());
                newArr[j].setLocation(dogs[i].getLocation());
                newArr[j].setHealth(dogs[i].getHealth());
            } else  {

                continue;
            }
            j++;
        }
        delete[] dogs;
        dogs = newArr;
    }

    void removeFromArray(Cat& cat,int size) {
        Cat* newArr = new Cat[size-1];
        for(int i = 0,j = 0;i<size;i++) {
            if(cats[i].getId() != cat.getId()) {
                newArr[j].setId(cats[i].getId());
                newArr[j].setLocation(cats[i].getLocation());
                newArr[j].setHealth(cats[i].getHealth());
            } else  {

                continue;
            }
            j++;
        }
        delete[] cats;
        cats = newArr;
    }


   Cat* getCats() {
        return cats;
    }
    Dog* getDogs() {
        return dogs;
    }






};


void showAnimalsMeeting(Dog &dog, Cat &cat) {
    cout << "dog: " <<dog.getId() << " at "; dog.showAnimalLocation(); cout << " met cat: " << cat.getId() << " at "; cat.showAnimalLocation();
}

int main() {
    NeverDog neverDog(3,5);
    Dog* dogs =  neverDog.getDogs();
    for(int i=0;i<Dog::getCount();i++) {
        cout << dogs[i].getId() << " is at " << dogs[i].getLocation().x << "," << dogs[i].getLocation().y << endl;
    }
    neverDog.removeFromArray(dogs[0],Dog::getCount());
    for(int i=0;i<Dog::getCount();i++) {
        cout << dogs[i].getId() << " is at " << dogs[i].getLocation().x << "," << dogs[i].getLocation().y << endl;
    }






}


