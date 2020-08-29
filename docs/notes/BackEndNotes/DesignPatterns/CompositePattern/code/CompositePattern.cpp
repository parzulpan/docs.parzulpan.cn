#include <iostream>
#include <algorithm>
#include <list>
#include <string>
#include <memory>
#include <typeinfo>

// 组件类
class Component {
protected:
    Component *parent_;

public:
    virtual ~Component() {}
    void setParent(Component *parent) {
        this->parent_ = parent;
    }
    Component* getParent() const {
        return this->parent_;
    }
    virtual void add(Component* component) {}
    virtual void remove(Component* component) {}
    virtual bool isComposite() const {
        return false;
    }
    virtual std::string operation() const = 0;
};

// 叶节点类
class Leaf: public Component {
public:
    std::string operation() const override {
        return "Leaf";
    }
};

// 容器类
class Composite: public Component {
protected:
    std::list<Component *> children_;

public:
    void add(Component *component) override {
        this->children_.push_back(component);
        component->setParent(this);
    }
    void remove(Component *component) override {
        // if( find(children_.begin(), children_.end(), component) != children_.end() ) {
        //     children_.remove(component);
        //     component->setParent(nullptr);
        // }
        children_.remove(component);
        component->setParent(nullptr);
    }
    bool isComposite() const override {
        return true;
    }
    std::string operation() const override {
        std::string result;
        for(const Component* c : children_) {
            if( c == children_.back() ) {
                result += c->operation();
            } else {
                result += c->operation() + "+";
            }
        }
        return "Branch(" + result + ")";
    }
};

// 
void ClientCode(Component* component) {
    //...
    std::cout << "REST: " << component->operation();
    //...
}

// 
void ClientCode2(Component* component1, Component* component2) {
    //...
    if(component1->isComposite()) {
        component1->add(component2);
    }
    std::cout << "REST: " << component1->operation();
    //...
}

int main(int argc, char *argv[]) {
    // std::shared_ptr<Component> simple = std::make_shared<Leaf>();
    // std::shared_ptr<Component> simple(new Leaf);
    Component *simple = new Leaf;
    std::cout << "Client: simple component: " << std::endl;
    ClientCode(simple);
    std::cout << std::endl << std::endl;

    // std::shared_ptr<Component> tree = std::make_shared<Composite>();
    // std::shared_ptr<Component> branch1 = std::make_shared<Composite>();
    // std::shared_ptr<Component> branch2 = std::make_shared<Composite>();
    // std::shared_ptr<Component> leaf_1 = std::make_shared<Leaf>();
    // std::shared_ptr<Component> leaf_2 = std::make_shared<Leaf>();
    // std::shared_ptr<Component> leaf_3 = std::make_shared<Leaf>();
    Component *tree = new Composite;
    Component *branch1 = new Composite;
    Component *branch2 = new Composite;
    Component *leaf_1 = new Leaf;
    Component *leaf_2 = new Leaf;
    Component *leaf_3 = new Leaf;
    branch1->add(leaf_1);
    branch1->add(leaf_2);
    branch2->add(leaf_3);
    tree->add(branch1);
    tree->add(branch2);
    std::cout << "Client: component tree: " << std::endl;
    ClientCode(tree);
    std::cout << std::endl << std::endl;

    std::cout << "Client: component tree not check: " << std::endl;
    branch1->remove(leaf_2);
    // branch1->remove(leaf_2);
    ClientCode2(tree, simple);
    std::cout << std::endl << std::endl;

    delete simple;
    delete tree;
    delete branch1;
    delete branch2;
    delete leaf_1;
    delete leaf_2;
    delete leaf_3;

    return 0;
}