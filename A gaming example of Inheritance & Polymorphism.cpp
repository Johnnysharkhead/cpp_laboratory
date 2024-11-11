#include <vector>
#include <iostream>

// 定义一个简单的游戏物品系统的基础结构

// 主要特性:
// 1.抽象基类 Item 定义了所有物品的通用接口
// 2.派生类 Armor 和 Weapon 实现了具体的物品类型
// 3.Actor 类模拟游戏角色，包含背包系统
// 4.全局 pickup 函数处理物品拾取逻辑

struct Actor{
	double dmg; // Actor's damage 
	double res; // Actor's resistance

	// 定义了一个名为 bag 的成员变量（代表角色的背包），它是一个向量（vector），用于存储 Item 类型的指针
	// 使用指针和多态允许角色的背包存储不同类型的物品
	std::vector <Item*> bag{}; //Item是一个基类，而 Armor 和 Weapon 是它的派生类，通过使用基类指针，bag可以存储不同类型的派生类对象，实现了多态。
};


// 这是一个全局函数，用于角色拾取物品 (全局 pickup 封装了物品添加到背包和触发效果的过程)
// 参数：Actor& a 是对角色的引用，Item *i 是要拾取的物品指针
// 全局 pickup 函数在其实现中调用了 Item 的 pickup 方法：i->pickup(a);
void pickup(Actor& a, Item *i){
	a.bag.push_back(i); // 将物品指针添加到角色的背包中
	i->pickup(a); // 调用物品的 pickup 方法，可能会影响角色的属性（这里的传参只有Actor a，可以判断调用的是Item类里的 pickup 方法）
}


// 抽象基类：Item 是一个抽象类，不能直接实例化，只能被继承
class Item{
public:
	virtual double weight() const = 0; // pure virtual（派生类必须实现这个函数）
	virtual void pickup(Actor &a) const = 0; // 参数是对 Actor 的引用，允许物品影响拾取它的角色，比如damage属性和resistance属性发生变化，具体怎么变化需要在派生类里去实现
	virtual ~Item() = default; // Destructor, only call in parent class instead of child class（虚析构函数，确保正确删除派生类的对象）
};


// 全局 pickup 负责整体流程和背包管理；而Item::pickup 负责物品特定的效果实现
// 全局 pickup 封装了物品添加到背包和触发效果的过程，提供了一个简单的接口给外部使用
// 全局 pickup 函数作为一个高层操作，而 Item::pickup 作为一个可定制的低层操作，两者协同工作，实现了灵活且强大的物品拾取系统
// 添加新类型的物品只需实现新的 Item::pickup，无需修改全局的pickup


class Armor : public Item{ // Inherit from Class Item
public:
	double weight() const override{ 
		return 0.25 * rating; // 返回护甲重量，为 rating（自身的成员变量）的 0.25 倍
	}

	void pickup(Actor& a) const override{
		a.res += rating; // 增加角色的抗性（res）
	}

	Armor(double rating) : rating{rating} {}; // Constructor

protected:
	double rating{};
};


class Weapon: public Item{ // Inherit from Class Item
public:
	double weight() const override{
		return mass;
	}

	void pickup(Actor& a) const override{
		a.dmg += dmg;
		a.res -= 0.1 * mass;
	}

	Weapon(double dmg, double mass): dmg{dmg}, mass{mass} {}; // Constructor

protected:
	double dmg{};
	double mass{};
};


int main(){
	
	Actor tom{};

	// 创建一个 Item 指针的向量 items，包含多个 Armor 和 Weapon 对象
	// 基类的容器，实际存储的是 Armor 和 Weapon 对象的指针，它们都是 Item 的派生类，典型Polymorphism的实现（我们可以轻松地向这个向量添加新类型的物品，只要它们继承自 Item；不需要修改现有的代码结构就可以支持新的物品类型）
	std::vector <Item*> items{
		new Armor{9}, new Weapon{5,3}, new Armor{8}, new Weapon{7,7}
	};


	for (Item* item : items) { // 每一个item里面都是指向派生类的指针
    std::cout << "Weight: " << item->weight() << std::endl; // 这里会调用 Armor 或 Weapon 的 weight() 方法，调用哪个取决于实际对象类型
	}

	// 使用 pickup 函数（注意这里是全局pickup函数）为角色 tom 拾取物品
	// 全局 pickup 封装了物品添加到背包和触发效果的过程，提供了一个简单的接口给外部使用
	pickup(tom,items.at(1)); //items.at(1)是指针
	pickup(tom,items.at(2));

	// Avoid Memory Leak
	for (Item *i: items){
		delete i; 
	}

}

// Polymorphism的体现：
// std::vector <Item*> bag{};
// std::vector <Item*> items{ new Armor{9}, new Weapon{5,3}, new Armor{8}, new Weapon{7,7}};


