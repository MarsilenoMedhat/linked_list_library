#include <iostream>
#include <optional>

template <typename T>
class singlyList {

private:

    struct _Node {
        T _Value;
        _Node* _Next;
    };

    _Node* _Head;
    _Node* _Tail;
    _Node* _Current;
    int _Count = 0;

    // Optimized search assuming temporal locality.
    // Average case improves when recently accessed nodes are reused.
    // finds node by the val and return the node once we find it, and return nullptr if it doesn't exist.
    _Node* _FindNode(T searchVal) {
        
        // check if the list is empty or not.
        if (_Head == nullptr) {
            return nullptr;
        }

        _Node* tempNode = _Current;

        // check from the current to the tail.
        while (tempNode != nullptr) {
            if (tempNode->_Value == searchVal) {
                return tempNode;
            }
            tempNode = tempNode->_Next;
        }

        // check from head to current if we didn't find.
        if (_Current != _Head) {
            tempNode = _Head;
            while(tempNode != _Current) {
                if (tempNode->_Value == searchVal) {
                    return tempNode;
                }
                tempNode = tempNode->_Next;
            }
        }
        return nullptr;
    }

    public:
    
    singlyList(T value) {
        _Node* newNode = new _Node;
        newNode->_Value = value;
        newNode->_Next = nullptr;

        _Current = newNode;
        _Head = newNode;
        _Tail = newNode;
    }
    
    singlyList() {
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

    // insert at the beginning of the list.
    bool insertAtTheBeginning(T newVal) {
        _Node* newNode = new _Node;
        newNode->_Value = newVal;

        // check if the list is empty or not.
        if (_Head == nullptr) {
            newNode->_Next = nullptr;
            _Head = newNode;
            _Tail = newNode;
            _Current = newNode;
            _Count++;
            return true;
        }
        
        newNode->_Next = _Head;
        _Head = newNode;
        _Count++;
        return true;
    }

    // insert at the end of the list.
    bool insertAtTheEnd(T newVal) {
        _Node* newNode = new _Node;
        newNode->_Value = newVal;
        newNode->_Next = nullptr;
        
        // check if the list is empty or not.
        if (_Head == nullptr) {
            newNode->_Next = nullptr;
            _Head = newNode;
            _Tail = newNode;
            _Current = newNode;
            _Count++;
            return true;
        }

        _Tail->_Next = newNode;
        _Tail = newNode;
        _Count++;
        return true;
    }

    // insert after a spesific node by check the previous node by value.
    bool insertAfter(T preVal, T newVal) {
        _Node* tempNode = _FindNode(preVal);

        // check if the previous not is exists or not
        if (tempNode == nullptr) {
            return false;
        }

        // check if the previous node is the last one or not.
        if (tempNode == _Tail) {
            insertAtTheEnd(newVal);
        }
        
        _Node* newNode = new _Node;
        newNode->_Value = newVal;
        newNode->_Next = tempNode->_Next;
        tempNode->_Next = newNode;
        _Count++;
        return true;
    }

    // delete the first node.
    bool deleteFirstNode() {

        // check if the list is empty or not.
        if (_Head == nullptr) {
            return false;
        }

        // check if the list has one node or not.
        if (_Head->_Next == nullptr) {
            delete _Head;
            _Head = nullptr;
            _Current = nullptr;
            _Tail = nullptr;
            _Count--;
            return true;
        }

        // check if the current is at the node we want to delete or not.
        if (_Current == _Head) {
            _Current = _Current->_Next;
        }

        _Node* tempNode = _Head;
        _Head = _Head->_Next;
        delete tempNode;
        _Count--;
        return true;
    }

    // delete the last node.
    bool deleteLastNode() {

        // check if the list is empty or not.
        if (_Head == nullptr) {
            return false;
        }

        // check if the list has one node or not.
        if (_Head->_Next == nullptr) {
            delete _Head;
            _Head = nullptr;
            _Current = nullptr;
            _Tail = nullptr;
            _Count--;
            return true;
        }
        
        // check if the current is at the node we want to delete or not.
        if (_Current == _Tail) {
            _Current = _Head;
        }

        _Node* tempCurrent = _Head;
        while (tempCurrent->_Next->_Next != nullptr) {
            tempCurrent = tempCurrent->_Next;
        }
        delete tempCurrent->_Next;
        tempCurrent->_Next = nullptr;
        _Tail = tempCurrent;
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
            return deleteFirstNode();
        }
        
        // check if the node we want to delete is the last one or not.
        if (_Tail->_Value == deleteVal) {
            return deleteLastNode();
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

    // print the full list.
    void printFullList() {

        // check if the list is empty or not.
        if (_Head == nullptr) {
            std::cout << "\nThe linked list is empty.\n\n";
            return;
        }
        
        _Node* tempNode = _Head;
        while (tempNode != nullptr) {
            std::cout << tempNode->_Value <<  "  ";
            tempNode = tempNode->_Next;
        }
    }

    ~singlyList() {
        deleteFullList();
    }
};