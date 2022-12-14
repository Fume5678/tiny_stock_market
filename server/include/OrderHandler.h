
#ifndef ORDERHANDLER_H
#define ORDERHANDLER_H

#include <string>
#include <vector>
#include <map>
#include <mutex>
#include <memory>
#include <queue>
#include <functional>
#include <exception>
#include <optional>

using std::map;
using std::mutex;
using std::pair;
using std::shared_ptr;
using std::string;
using std::vector;
using std::weak_ptr;
// using std::tuple;

class OrderPairType {
public:
    std::string source;
    std::string target;
    std::string type; // SELL or BUY

    friend bool operator==(const OrderPairType& a, const OrderPairType& b) {
        return (a.source == b.source) && (a.target == b.target) && (a.type) == (b.type);
    }

    operator string() const {
        return source + "/" + target + "/" + type;
    }
};

class Order {
public:
    std::string user_id;
    float       price;
    float       value;
    OrderPairType   order_pair_type;

    Order();

    Order(const Order& other);

    Order& operator=(const Order& other);

    std::string serialize() const;
};

// using OrderPair = pair<string, string>;

class OrderHandler {
    void match(OrderPairType order_pair_type);

    OrderHandler();

public:
    using CompOrder = std::function<bool(const shared_ptr<Order>& v1,
                                         const shared_ptr<Order>& val2)>;
    using OrderList = std::priority_queue<shared_ptr<Order>,
                                          std::vector<shared_ptr<Order>>,
                                          CompOrder>;
    using UserMap   = map<string, vector<weak_ptr<Order>>>;
    using OrderMap  = map<std::string, OrderList>;

    static std::shared_ptr<OrderHandler> get_instance();

    void add_order(const Order& order);

    std::optional<std::reference_wrapper<OrderList>> get_orders_by_pair(OrderPairType pair);

    std::optional<vector<Order>> get_orders_by_user(std::string user_id);

private:
    CompOrder comp_order_buy;
    CompOrder comp_order_sell;
    mutex     mtx;
    OrderMap  order_map;
    UserMap   users;
};

#endif // ORDERHANDLER_H
