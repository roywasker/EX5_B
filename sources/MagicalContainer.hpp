#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <memory>
#include <algorithm>

using namespace std;

namespace ariel {
    class MagicalContainer {

    private:
        class SimpleIterator {
        public:
            SimpleIterator(MagicalContainer &magicalContainer);
            SimpleIterator(const SimpleIterator &other);
            ~SimpleIterator() = default;
            SimpleIterator(SimpleIterator&& other) = default;
            SimpleIterator& operator=(SimpleIterator&& other) = default;
            SimpleIterator& operator=(const SimpleIterator& other)= default;

            bool operator==(const SimpleIterator& other) const;
            bool operator!=(const SimpleIterator& other) const;
            bool operator>(const SimpleIterator& other) const;
            bool operator<(const SimpleIterator& other) const;

            MagicalContainer *magicalcontainer;
            size_t CurrentIndex;
            std::vector<shared_ptr<int>>::iterator costumeIterator;
        };

    public:
        MagicalContainer();

        void addElement(int element);
        void removeElement(int element);
        int size() const;
        bool isPrime(int num)const;

        class AscendingIterator : public SimpleIterator {
        public:
            AscendingIterator(MagicalContainer &magicalContainer);
            AscendingIterator(const AscendingIterator &other);
            ~AscendingIterator() = default;
            AscendingIterator(AscendingIterator&& other) = default;
            AscendingIterator& operator=(AscendingIterator&& other) = default;

            AscendingIterator& operator=(const AscendingIterator& other);
            int operator*() const;
            AscendingIterator& operator++();

            AscendingIterator begin();
            AscendingIterator end();

        };

        class SideCrossIterator : public SimpleIterator{
        public:
            SideCrossIterator(MagicalContainer &magicalContainer);
            SideCrossIterator(const SideCrossIterator &other);
            ~SideCrossIterator() = default;
            SideCrossIterator(SideCrossIterator&& other) = default;
            SideCrossIterator& operator=(SideCrossIterator&& other) = default;

            SideCrossIterator& operator=(const SideCrossIterator& other);
            int operator*() const;
            SideCrossIterator& operator++();

            SideCrossIterator begin();
            SideCrossIterator end();

        };

        class PrimeIterator : public SimpleIterator{
        public:
            PrimeIterator(MagicalContainer &magicalContainer);
            PrimeIterator(const PrimeIterator &other);
            ~PrimeIterator() = default;
            PrimeIterator(PrimeIterator&& other)= default;
            PrimeIterator& operator=(PrimeIterator&& other) = default;

            PrimeIterator& operator=(const PrimeIterator& other);

            int operator*() const;
            PrimeIterator& operator++();

            PrimeIterator begin();
            PrimeIterator end();

        };

    private:
        std::vector <shared_ptr<int>> container;
        std::vector <shared_ptr<int>> AscendingIteratorVec;
        std::vector <shared_ptr<int>> SideCrossIteratorVec;
        std::vector <shared_ptr<int>> PrimeIteratorVec;
    };
}

#endif //MAGICALCONTAINER_HPP