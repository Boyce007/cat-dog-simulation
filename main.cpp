#include <iostream>
#include <random>
using namespace std;

/*
 * bool isNearObject(location l ) {
 *      return(absvalue of location of x  - l.x <= 5 and location of y  - l <=5) {
 *
 *
 * }
 */


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
    Location location{};
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
        id = -1;

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


    static void removeDog() {
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
//            cout << "cat:"<< id<< " turned " <<"dog: "<<  dog.getId() << " into a cat \n";
            health-=5;
            Dog::removeDog();
            return true;
        }
//        cout << "Dog " << dog.getId() << " beat cat " << id << endl;
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


/*
* void fight(Dog dog){
    * if (dog is near cat ){
    *        if (determineWinner(dogHealth) {
    *
    *              Cat newCat(dog.getId()+catCount)
    *              catHeath-=5;
    *
    *        } else {
    *          cout << dog.getId << killed << cat.get ID
    *          dogHealt-=5;
    *
    *        }
    *  }
      */

/*

* bool determineWinner(dogHealth) {
    * chanceOf winning  = 50
    chanceOfWinning += (catHealth -dogHealth)
    generate random number between 0 and 100
    if randomNUmber <=chanceOfWinning {
          return true;
                *          } else {
        *          return false;
        *
                * }
    */



void populateArray(Dog dogs[],int arraySize ) {
    for(int i =0; i<arraySize; i++) {
        dogs[i] = Dog(i);
    }
}

void populateArray(Cat cats[],int arraySize ) {
    for(int i =0; i<arraySize; i++) {
        cats[i] = Cat(i);
    }
}


void showAnimalsMeeting(Dog &dog, Cat &cat) {
    cout << "dog: " <<dog.getId() << " at "; dog.showAnimalLocation(); cout << " met cat: " << cat.getId() << " at "; cat.showAnimalLocation();
}

int main() {


    Cat cats[50];
    Dog dogs[50];
    populateArray(cats,3);
    populateArray(dogs,47);
    int earliestFreeSpace = 3;
    int count = 0;
    int time =0;
    while((Dog::getCount()>0 && Cat::getCount()>0) && time<10000) {
        cout << "days: " << time <<endl;
        for(Dog &dog:dogs) {
            if(dog.getId() == -1) {
//                cout << "first -1 dog conditiond \n";
                continue;
            }
            for(Cat &cat:cats ) {
                if(cat.getId() == -1) {
//                    cout << "first -1 cat condition\n";
                    count++;
                    if (count <= earliestFreeSpace) {
//                        cout << "free space true condition \n";
                        earliestFreeSpace = count;
                    }
                    continue;
                }
                if(dog.getId() == -1 || cat.getId() == -1) {
                    continue;
                }
                cat.move();
                dog.move();

                if(dog.isNearObject(cat.getLocation())) {
                    if (cat.fight(dog)) {
                        Cat newCat = Cat(100 + dog.getId(), dog.getLocation(), 100);
                        dog.setId(-1);
                        cats[earliestFreeSpace] = newCat;
                        earliestFreeSpace = Cat::getCount();
                    } else {
                        cat.setId(-1);
                        if (count < earliestFreeSpace)
                            earliestFreeSpace = count;
                    }
                }
                count++;
                cout << "Number of dogs left " << Dog::getCount() << endl;
                cout << "Number of cats left " << Cat::getCount() << endl;
                cout<< "total: " << Dog::getCount() + Cat::getCount() << endl;
            }
            count =0;
        }
        time++;

    }



    return 0;

}


