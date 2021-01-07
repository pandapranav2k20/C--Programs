#include "linked_list.h"
#include <iostream>
#include <string>
using std::cout, std::endl, std::string;

void MyList::add(string name, int score) {
    // TODO
    MyNode* new_node = new MyNode(name, score);
    if(_headPtr == NULL) {
        _headPtr = new_node;
        _tailPtr = new_node;
    } else {
        _tailPtr -> setNext(new_node);
        _tailPtr = new_node;
    }
    _size++;
}

void MyList::clear() {
    // TODO
    while(_headPtr != nullptr) {
        _marker = _headPtr;
        _headPtr = _headPtr->next();
        delete _marker;
    }
    _headPtr = nullptr;
    _marker = nullptr;
    _tailPtr = nullptr;
    _size = 0;

}

bool MyList::remove(string name) {
    // TODO
    bool _remove = false;
    bool _found = false;

    if (_marker == nullptr) {
        if (_headPtr == nullptr) {
            return _remove;
        } else {
            _marker = _headPtr;
        }
    }

    if(_headPtr == _tailPtr) {
        if (_headPtr->name() == name) {
            _found = true;
            clear();
            _marker = nullptr;
            return _found;
        } else {
            return _found;
        }
    }

    while(_marker != nullptr) {
        if(_marker->name() == name) {
            _found = true;
            break;
        }
        _prevPtr = _marker;
        _marker = _marker->next();
    }

    if(_found) {
        if(_marker == _headPtr) {
            _headPtr = _marker->next();
            delete _marker;
            _marker = nullptr;
            _size--;
            _remove = true;
        } else if(_marker == _tailPtr) {
            _tailPtr = _prevPtr;
            _prevPtr->setNext(nullptr);
            delete _marker;
            _marker = nullptr;
            _size--;
            _remove = true;
        } else {
            _prevPtr->setNext(_marker->next());
            delete _marker;
            _marker = nullptr;
            _size--;
            _remove = true;
        }
    }

    return _remove;
}

bool MyList::insert(string name, int score, size_t index) {
    // TODO
    return false;
}

MyList::MyList() {
    _size = 0;
    _headPtr = nullptr;
    _tailPtr = nullptr;
    _prevPtr = nullptr;
    _marker = nullptr;
}

MyList::~MyList() {
    clear();
}

size_t MyList::size() {
    return _size;
}

bool MyList::empty() {
    return _headPtr == nullptr;
}

MyNode* MyList::head() {
    return _headPtr;
}

void MyList::printList() {
    _marker = _headPtr;
    if (_marker == nullptr) {
        cout << "Linked list is empty" << endl;
        return;
    }

    while (_marker != nullptr) {
        cout << "[ " << _marker->name() << ", " << _marker->score() << " ]" << endl;
        _marker = _marker->next();
    }
}

MyNode::MyNode(std::string name, int score) {
    _name = name;
    _score = score;
    _nextPtr = nullptr;
}

std::string MyNode::name()  {
    return _name;
}

int MyNode::score() {
    return _score;
}

void MyNode::setNext(MyNode* other) {
    _nextPtr = other;
}

MyNode* MyNode::next() {
    return _nextPtr;
}