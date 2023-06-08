#include "MagicalContainer.hpp"
using namespace ariel;

MagicalContainer::MagicalContainer() {}

/**
 * add element to the container
 * @param element to add
 */
void MagicalContainer::addElement(int element) {
    shared_ptr<int> newElement(new int(element)); // create new element of shared pointer
    container.push_back(newElement); // inset the element to regular container
    SideCrossIteratorVec.clear(); // clear SideCrossIterator Vector

    // AscendingIterator
    AscendingIteratorVec.push_back(newElement);

    //sort
    std::sort(AscendingIteratorVec.begin(), AscendingIteratorVec.end(), [](const shared_ptr<int> a, const shared_ptr<int> b) {
        return *a < *b;
    });

    //SideCrossIterator
    auto rindex = AscendingIteratorVec.begin();
    auto lindex = AscendingIteratorVec.rbegin();
    for (int i=0 ; i<AscendingIteratorVec.size()/2;i++){// go over array in size /2 step to add element in both side
       SideCrossIteratorVec.push_back(*rindex);
       SideCrossIteratorVec.push_back(*lindex);
       rindex++;
       lindex++;
    }
    if ((AscendingIteratorVec.size()%2)!=0){// if we have odd element add the element in the middle
        SideCrossIteratorVec.push_back(*rindex);
    }

    //Prime
    if(isPrime(element)) { // check if new number is prime
        PrimeIteratorVec.push_back(newElement);
        std::sort(PrimeIteratorVec.begin(), PrimeIteratorVec.end(), // sort vector
                  [](const shared_ptr<int> a, const shared_ptr<int> b) {
                      return *a < *b;
                  });
    }
}

/**
 *  remove element from container
 * @param element to remove
 */
void MagicalContainer::removeElement(int element) {

    //https://stackoverflow.com/questions/14917169/finding-an-element-in-a-shared-ptr-container
    auto index = std::find_if(container.begin(), container.end(), [element](std::shared_ptr<int> const& i) {// get the index of element in regular container
        return *i.get() == element;
    });
    if (index== container.end()){
        throw runtime_error("element not exits\n");
    }
    container.erase(index); //delete this element

    //AscendingIterator
    auto Aindex = std::find_if(AscendingIteratorVec.begin(), AscendingIteratorVec.end(), [element](std::shared_ptr<int> const& i) { //find this element in Ascending Iterator
        return *i.get() == element;
    });
    AscendingIteratorVec.erase(Aindex);

    //SideCrossIterator
    SideCrossIteratorVec.clear(); // clear the vector
    auto rindex = container.begin();
    auto lindex = container.rbegin();
    for (int i=0 ; i<container.size()/2;i++){ // go over array in size /2 step to add element in both side
        SideCrossIteratorVec.push_back(*rindex);
        SideCrossIteratorVec.push_back(*lindex);
        rindex++;
        lindex++;
    }
    if (container.size()%2!=0){ // if we have odd element add the element in the middle
        SideCrossIteratorVec.push_back(*rindex);
    }

    //Prime
    if (isPrime(element)){
        auto Pindex = std::find_if(PrimeIteratorVec.begin(), PrimeIteratorVec.end(), [element](std::shared_ptr<int> const& i) {//find this element in Prime Iterator
            return *i.get() == element;
        });
        PrimeIteratorVec.erase(Pindex);
    }
}

/**
 *  get the number of element in container
 * @return number of element in container
 */
int MagicalContainer::size() const {
    return container.size();
}

/**
 * constructor for iterator
 * @param magicalContainer magicalContainer for iterator
 */
ariel::MagicalContainer::SimpleIterator::SimpleIterator(ariel::MagicalContainer &magicalContainer) :magicalcontainer(&magicalContainer) , CurrentIndex(0) {}

/**
 * copy constructor for iterator
 * @param other magicalContainer for iterator
 */
ariel::MagicalContainer::SimpleIterator::SimpleIterator(const ariel::MagicalContainer::SimpleIterator &other) :magicalcontainer(other.magicalcontainer) , CurrentIndex(other.CurrentIndex) {}

/**
 *  Equality comparison
 * @param other element to compere with
 * @return true if two element are equal , otherwise false
 */
bool ariel::MagicalContainer::SimpleIterator::operator==(const ariel::MagicalContainer::SimpleIterator &other) const {
    if (this->magicalcontainer != other.magicalcontainer) { //check if we try to compare different type of containers
        throw std::invalid_argument("can not compare different Magical Containers \n");
    }
    return this->CurrentIndex==other.CurrentIndex;
}

/**
 * Inequality comparison
 * @param other element to compere with
 * @return true if two element are not equal , otherwise false
 */
bool ariel::MagicalContainer::SimpleIterator::operator!=(const ariel::MagicalContainer::SimpleIterator &other) const {
    if (this->magicalcontainer != other.magicalcontainer) { //check if we try to compare different type of containers
        throw std::invalid_argument("can not compare different Magical Containers \n");
    }
    return this->CurrentIndex!=other.CurrentIndex;
}

/**
 * lower that  comparison
 * @param other element to compere with
 * @return true if current element are lower that other element , otherwise false
 */
bool ariel::MagicalContainer::SimpleIterator::operator<(const ariel::MagicalContainer::SimpleIterator &other) const {
    if (this->magicalcontainer != other.magicalcontainer) { //check if we try to compare different type of containers
        throw std::invalid_argument("can not compare different Magical Containers \n");
    }
    return this->CurrentIndex<other.CurrentIndex;
}

/**
 * Grater that comparison
 * @param other element to compere with
 * @return true if current element are grater that other element , otherwise false
 */
bool ariel::MagicalContainer::SimpleIterator::operator>(const ariel::MagicalContainer::SimpleIterator &other) const {
    if (this->magicalcontainer != other.magicalcontainer) { //check if we try to compare different type of containers
        throw std::invalid_argument("can not compare different Magical Containers \n");
    }
    return this->CurrentIndex>other.CurrentIndex;
}

/**
 * constructor for ascending iterator
 * @param magicalContainer magicalContainer for iterator
 */
ariel::MagicalContainer::AscendingIterator::AscendingIterator(ariel::MagicalContainer &magicalContainer) : SimpleIterator(magicalContainer) {
    costumeIterator = magicalContainer.AscendingIteratorVec.begin();//set costumeIterator to AscendingIterator at first element
}

/**
 * copy constructor for ascending iterator
 * @param other magicalContainer for iterator
 */
ariel::MagicalContainer::AscendingIterator::AscendingIterator(const ariel::MagicalContainer::AscendingIterator &other) : SimpleIterator(other) {}

/**
 *  Assignment operator
 * @param other Ascending Iterator
 * @return
 */
ariel::MagicalContainer::AscendingIterator& ariel::MagicalContainer::AscendingIterator::operator=(const ariel::MagicalContainer::AscendingIterator& other) {
    if (this->magicalcontainer != other.magicalcontainer) {
        throw std::runtime_error("can not use = operator from another container\n");
    }
    this->magicalcontainer = other.magicalcontainer;
    this->CurrentIndex=other.CurrentIndex;
    this->costumeIterator=other.costumeIterator;
    return *this;
}

/**
 * Dereference operator
 * @return element after dereference
 */
int ariel::MagicalContainer::AscendingIterator::operator*() const{
    if (costumeIterator == magicalcontainer->AscendingIteratorVec.end()){//check if iterator is in last element
        throw std::runtime_error("iterator out of bound\n");
    }
    return *(magicalcontainer->AscendingIteratorVec.at(CurrentIndex));//return current element
}

/**
 * Pre-increment operator
 * @return  element after increment
 */
ariel::MagicalContainer::AscendingIterator& ariel::MagicalContainer::AscendingIterator::operator++(){
    if (costumeIterator == magicalcontainer->AscendingIteratorVec.end()){//check if iterator is in last element
        throw std::runtime_error("iterator out of bound\n");
    }
    CurrentIndex++;
    costumeIterator++;
    return *this;
}

/**
 * pointing to the first element
 * @return pointing to the first element of the container
 */
ariel::MagicalContainer::AscendingIterator ariel::MagicalContainer::AscendingIterator::begin() {
    AscendingIterator iterator = *this;
    iterator.costumeIterator = magicalcontainer->AscendingIteratorVec.begin();// set iterator to first element
    iterator.CurrentIndex = 0;//set current index to first index
    return iterator;
}

/**
 * pointing to the last element
 * @return pointing to the last element of the container
 */
ariel::MagicalContainer::AscendingIterator ariel::MagicalContainer::AscendingIterator::end() {
   AscendingIterator iterator = *this;
    iterator.costumeIterator = magicalcontainer->AscendingIteratorVec.end();// set iterator to last element
    iterator.CurrentIndex = magicalcontainer->AscendingIteratorVec.size();//set current index to last index
    return iterator;
}

/**
 * constructor for side cross iterator
 * @param magicalContainer magicalContainer for iterator
 */
ariel::MagicalContainer::SideCrossIterator::SideCrossIterator(ariel::MagicalContainer &magicalContainer) : SimpleIterator(magicalContainer) {
    costumeIterator = magicalcontainer->SideCrossIteratorVec.begin();//set costumeIterator to SideCrossIterator at first element
}


/**
 * copy constructor for side cross iterator
 * @param other magicalContainer for iterator
 */
ariel::MagicalContainer::SideCrossIterator::SideCrossIterator(const ariel::MagicalContainer::SideCrossIterator &other):SimpleIterator(other)  {}

/**
 *  Assignment operator
 * @param other Ascending Iterator
 * @return
 */
ariel::MagicalContainer::SideCrossIterator& ariel::MagicalContainer::SideCrossIterator::operator=(const ariel::MagicalContainer::SideCrossIterator& other){
    if (this->magicalcontainer != other.magicalcontainer) {
        throw std::runtime_error("can not use = operator from another container\n");
    }
    this->magicalcontainer = other.magicalcontainer;
    this->CurrentIndex=other.CurrentIndex;
    this->costumeIterator=other.costumeIterator;
    return *this;
}

/**
 * Dereference operator
 * @return element after dereference
 */
int ariel::MagicalContainer::SideCrossIterator::operator*() const{
    if (costumeIterator == magicalcontainer->SideCrossIteratorVec.end()){//check if iterator is in last element
        throw std::runtime_error("iterator out of bound\n");
    }
    return *(magicalcontainer->SideCrossIteratorVec.at(CurrentIndex));//return current element
}

/**
 * Pre-increment operator
 * @return  element after increment
 */
ariel::MagicalContainer::SideCrossIterator& ariel::MagicalContainer::SideCrossIterator::operator++(){
    if (costumeIterator == magicalcontainer->SideCrossIteratorVec.end()){//check if iterator is in last element
        throw std::runtime_error("iterator out of bound\n");
    }
    CurrentIndex++;
    costumeIterator++;
    return *this;
}

/**
 * pointing to the first element
 * @return pointing to the first element of the container
 */
ariel::MagicalContainer::SideCrossIterator ariel::MagicalContainer::SideCrossIterator::begin() {
    SideCrossIterator iterator = *this;
    iterator.costumeIterator = magicalcontainer->SideCrossIteratorVec.begin();// set iterator to first element
    iterator.CurrentIndex = 0;//set current index to first index
    return iterator;
}

/**
 * pointing to the last element
 * @return pointing to the last element of the container
 */
ariel::MagicalContainer::SideCrossIterator ariel::MagicalContainer::SideCrossIterator::end() {
    SideCrossIterator iterator = *this;
    iterator.costumeIterator = magicalcontainer->SideCrossIteratorVec.end();// set iterator to last element
    iterator.CurrentIndex = magicalcontainer->SideCrossIteratorVec.size();//set current index to last index
    return iterator;
}

/**
 * constructor for prime iterator
 * @param magicalContainer magicalContainer for iterator
 */
ariel::MagicalContainer::PrimeIterator::PrimeIterator(ariel::MagicalContainer &magicalContainer) :SimpleIterator(magicalContainer){
    costumeIterator = magicalContainer.PrimeIteratorVec.begin();//set costumeIterator to PrimeIterator at first element
}

/**
 * copy constructor for prime iterator
 * @param other magicalContainer for iterator
 */
ariel::MagicalContainer::PrimeIterator::PrimeIterator(const ariel::MagicalContainer::PrimeIterator &other) :SimpleIterator(other) {}

/**
 *  Assignment operator
 * @param other Ascending Iterator
 * @return
 */
ariel::MagicalContainer::PrimeIterator& ariel::MagicalContainer::PrimeIterator::operator=(const ariel::MagicalContainer::PrimeIterator& other){
    if (this->magicalcontainer != other.magicalcontainer) {
        throw std::runtime_error("can not use = operator from another container\n");
    }
    this->magicalcontainer = other.magicalcontainer;
    this->CurrentIndex=other.CurrentIndex;
    this->costumeIterator=other.costumeIterator;
    return *this;
}


/**
 * Dereference operator
 * @return element after dereference
 */
int ariel::MagicalContainer::PrimeIterator::operator*() const{
    if (costumeIterator == magicalcontainer->PrimeIteratorVec.end()){//check if iterator is in last element
        throw std::runtime_error("iterator out of bound\n");
    }
    return *(magicalcontainer->PrimeIteratorVec.at(CurrentIndex));//return current element
}

/**
 * Pre-increment operator
 * @return  element after increment
 */
ariel::MagicalContainer::PrimeIterator& ariel::MagicalContainer::PrimeIterator::operator++(){
    if (costumeIterator == magicalcontainer->PrimeIteratorVec.end()){//check if iterator is in last element
        throw std::runtime_error("iterator out of bound\n");
    }
    CurrentIndex++;
    costumeIterator++;
    return *this;
}

/**
 * pointing to the first element
 * @return pointing to the first element of the container
 */
ariel::MagicalContainer::PrimeIterator ariel::MagicalContainer::PrimeIterator::begin() {
    PrimeIterator iterator = *this;
    iterator.costumeIterator = magicalcontainer->PrimeIteratorVec.begin();// set iterator to first element
    iterator.CurrentIndex = 0;//set current index to first index
    return iterator;
}

/**
 * pointing to the last element
 * @return pointing to the last element of the container
 */
ariel::MagicalContainer::PrimeIterator ariel::MagicalContainer::PrimeIterator::end() {
    PrimeIterator iterator = *this;
    iterator.costumeIterator = magicalcontainer->PrimeIteratorVec.end(); // set iterator to last element
    iterator.CurrentIndex = magicalcontainer->PrimeIteratorVec.size(); //set current index to last index
    return iterator;
}

/**
 * check if number is a prime
 * @param num number to check
 * @return ture is the number is prime , otherwise false
 */
bool ariel::MagicalContainer::isPrime(int num)const {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i <(num); i++) {//go over all the number between 2 to number and check them
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}