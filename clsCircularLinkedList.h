#include <iostream>
#include <optional>

template <typename T>
class clsCircularSinglyList {

    
private:

    struct _Node {
        T _Value;
        _Node* _Next;
    };

    _Node* _Head;
    _Node* _Tail;
    _Node* _Current;
    int _Count = 0;

    _Node* _FindNode(T searchVal) const {
        
        // check if the list is empty or not.
        if (_Head == nullptr) {
            return nullptr;
        }

        _Node* tempNode = _Head;
        do {
            if (tempNode->_Value == searchVal) {
                return tempNode;
            }
            tempNode = tempNode->_Next;
        } while (tempNode != _Head);

        return nullptr;
    }

public:

    clsCircularSinglyList(T value) {
        _Node* newNode = new _Node;
        newNode->_Value = value;
        newNode->_Next = newNode;

        _Current = newNode;
        _Head = newNode;
        _Tail = newNode;
        _Count++;
    }
    
    clsCircularSinglyList() {
        _Current = nullptr;
        _Head = nullptr;
        _Tail = nullptr;
    }

    // return current value if it's not empty.
    std::optional<T> getCurrent() const {
        if (_Current == nullptr) {
            return std::nullopt;
        }
        return _Current->_Value;
    }

    
    
    // return head value if it's not empty.
    std::optional<T> getHead() const {
        if (_Head == nullptr) {
            return std::nullopt;
        }
        return _Head->_Value;
    }
    
    // return tail value if it's not empty.
    std::optional<T> getTail() const {
        if (_Tail == nullptr) {
            return std::nullopt;
        }
        return _Tail->_Value;
    }

    // return the number of nodes in the list.
    int getSize () const {
        return _Count;
    }

    // check the existance of node by the value.
    bool find(T searchVal) {
        return _FindNode(searchVal) != nullptr;
    }
    
    // check the existance of node by the value and set it as current.
    bool setAsCurrent(T  Val) {
        _Node* currentNode = _FindNode(Val);
        if (currentNode != nullptr) {
            _Current = currentNode;
            return true;
        }
        return false;
    }

    // insert at the beginning or the end of the list.
    bool insertAtTheBeginningOrEnd(T newVal, bool atBeginning) {
        _Node* newNode = new _Node;
        newNode->_Value = newVal;

        // check if the list is empty or not.
        if (_Head == nullptr) {
            newNode->_Next = newNode;
            _Head = newNode;
            _Tail = newNode;
            _Current = newNode;
        }
        else {
            newNode->_Next = _Head;
            _Tail->_Next = newNode;
            if (atBeginning) {
                _Head = newNode;
            }
            else {
                _Tail = newNode;
            }
        }
        _Count++;
        return true;
    }

    // insert after a specific node by check the previous node by value.
    bool insertAfter(T preVal, T newVal) {

        // check if the list id empty or not.
        if (_Head == nullptr) {
            return false;
        }

        _Node* tempNode = _FindNode(preVal);

        // check if the previous not is exists or not
        if (tempNode == nullptr) {
            return false;
        }

        // check if the previous node is the last one or not.
        if (tempNode == _Tail) {
            return insertAtTheBeginningOrEnd(newVal, false);
        }
        
        _Node* newNode = new _Node;
        newNode->_Value = newVal;
        newNode->_Next = tempNode->_Next;
        tempNode->_Next = newNode;
        _Count++;
        return true;
    }

    // delete the first or last node.
    bool deleteFirstOrLastNode(bool deleteFirst) {

        // check if the list is empty or not.
        if (_Head == nullptr) {
            return false;
        }
        // // check if the current is at the node we want to delete or not.
        // if (_Current == _Head) {
        //     _Current = _Current->_Next;
        // }

        // check if the list has one node or not.
        if (_Head == _Tail) {
            delete _Head;
            _Head = nullptr;
            _Current = nullptr;
            _Tail = nullptr;
        }
        else {
            _Node* tempNode = nullptr;

            if (_Current == _Head || _Current == _Tail) {
                _Current = _Current->_Next;
            }

            if (deleteFirst) {
                tempNode = _Head;
                _Head = _Head->_Next;
                _Tail->_Next = _Head;
            }
            else {
                tempNode = _Tail;
                _Node* tempCurrent = _Head;

                while (tempCurrent->_Next->_Next != _Head) {
                    tempCurrent = tempCurrent->_Next;
                }
                tempCurrent->_Next = _Head;
                _Tail = tempCurrent;
            }
            delete tempNode;
        }
        _Count--;
        return true;
    }

    // delete a specific node.
    bool deleteNode(T deleteVal) {

        // check if the list is empty or not.
        if (_Head == nullptr) {
            return false;
        }

        // check if the node we want to delete is the first one or not.
        if (_Head->_Value == deleteVal) {
            return deleteFirstOrLastNode(true);
        }
        
        // check if the node we want to delete is the last one or not.
        if (_Tail->_Value == deleteVal) {
            return deleteFirstOrLastNode(false);
        }
        
        //  check if the node is existed or not.
        _Node* tempDeleteNode = _FindNode(deleteVal);
        if (tempDeleteNode == nullptr) {
            return false;
        }

        _Node* PreNode = nullptr;
        _Node* tempNode = _Head;
        while (tempNode != tempDeleteNode) {
            PreNode = tempNode;
            tempNode = tempNode->_Next;
        }

        // check if the current is at the node we want to delete or not.
        if (_Current == tempDeleteNode) {
            _Current = _Head;
        }

        PreNode->_Next = tempDeleteNode->_Next;
        delete tempDeleteNode;
        _Count--;
        return true;
    }

    // delete the full list.
    void deleteFullList() {
        _Node* tempNode = nullptr;

        if (_Head == nullptr) {
            return;
        }

        // changed the next in the tail to break the circle.
        _Tail->_Next = nullptr;

        while (_Head != nullptr) {
            tempNode = _Head;
            _Head = _Head->_Next;
            delete tempNode;
        }
        _Head = nullptr;
        _Current = nullptr;
        _Tail = nullptr;
        _Count = 0;
    }

    ~clsCircularSinglyList() {
        deleteFullList();
    } 
};


template <typename T>
class CircularDoublyList {

private:
    struct _Node {
        T _Value;
        _Node* _Previous;
        _Node* _Next;
    };

    _Node* _Head;
    _Node* _Tail;
    _Node* _Current;
    int _Count = 0;

    // finds node by the val and return the node once we find it, and return nullptr if it doesn't exist.
    _Node* _FindNode(T searchVal) {

        // check if the list is empty or not.
        if (_Head == nullptr) {
            return nullptr;
        }

        _Node* tempNode = _Head;
        do {
            if (tempNode->_Value == searchVal) {
                return tempNode;
            }
            tempNode = tempNode->Next;            
        } while (tempNode != _Head);

        return nullptr;
    }

public:

    CircularDoublyList(T val) {
        _Node* newNode = new _Node;
        newNode->_Value = val;
        newNode->_Next = NewNode;
        newNode->_Previous = NewNode;

        _Current = newNode;
        _Head = newNode;
        _Tail = newNode;
        _Count++;
    }

    CircularDoublyList() {
        _Current = nullptr;
        _Head = nullptr;
        _Tail = nullptr;
    }

    // return current value if it's not empty.
    std::optional<T> getCurrent() const {
        if (_Current == nullptr) {
            return std::nullopt;
        }
        return _Current->_Value;
    }
    
    // return head value if it's not empty.
    std::optional<T> getHead() const {
        if (_Head == nullptr) {
            return std::nullopt;
        }
        return _Head->_Value;
    }
    
    // return tail value if it's not empty.
    std::optional<T> getTail() const {
        if (_Tail == nullptr) {
            return std::nullopt;
        }
        return _Tail->_Value;
    }

    // return the number of nodes in the list.
    int getSize() const {
        return _Count;
    }

        // check if the val exists or not.
    bool find(T searchVal) {
        return _FindNode(searchVal);
    }

    // check if the value exists or not and set is as the current.
    bool setAsCurrent(T Val) {
        _Node* tempcurrent = _FindNode(Val);
        if (tempcurrent != nullptr) {
            _Current = tempcurrent;
            return true;
        }
        return false;
    }

    ~CircularDoublyList() {
        deleteFullList();
    }
};